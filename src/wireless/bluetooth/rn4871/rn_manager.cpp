/********************************************************************************
 *  File Name:
 *    rn_manager.cpp
 *
 *  Description:
 *    Manager thread implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <string>

/* Aurora Includes */
#include <Aurora/logging>
#include <Aurora/utility>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/serial>

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_device.hpp>
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>
#include <src/wireless/bluetooth/rn4871/rn_action_cmds.hpp>


namespace RN4871
{
  /*---------------------------------------------------------------------------
  Local Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t DFLT_STACK_SIZE            = STACK_BYTES( 4096 );
  static constexpr auto DFLT_THREAD_PRIORITY         = Chimera::Thread::Priority::LEVEL_3;
  static constexpr std::string_view DFLT_THREAD_NAME = "rn4871mgr";

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  Chimera::Thread::TaskId startDevice( DeviceDriver &device, const Chimera::Thread::TaskConfig *attr )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------------------------------
    Validate the task isn't already created
    -------------------------------------------------------------------------*/
    RT_HARD_ASSERT( device.dcb.lock );
    LockGuard _lock( *device.dcb.lock );

    if ( device.dcb.mgrID != THREAD_ID_INVALID )
    {
      return device.dcb.mgrID;
    }

    /*-------------------------------------------------------------------------
    Create the new task
    -------------------------------------------------------------------------*/
    Task manager;
    TaskConfig cfg;

    cfg.arg        = nullptr;
    cfg.function   = TaskDelegate::create<DeviceDriver, &DeviceDriver::run>( device );
    cfg.priority   = DFLT_THREAD_PRIORITY;
    cfg.stackWords = DFLT_STACK_SIZE;
    cfg.type       = TaskInitType::DYNAMIC;
    cfg.name       = DFLT_THREAD_NAME.data();

    if ( attr )
    {
      cfg.priority   = attr->priority;
      cfg.stackWords = attr->stackWords;
      cfg.type       = attr->type;
      cfg.name       = attr->name;
    }

    manager.create( cfg );

    /*-------------------------------------------------------------------------
    Start the thread. Yield to allow the scheduler a chance to run the thread.
    Normally this isn't required, but the task init structure is being created
    on the stack, which can cause problems with the FreeRTOS implementation.
    -------------------------------------------------------------------------*/
    device.dcb.mgrID = manager.start();
    this_thread::yield();

    return device.dcb.mgrID;
  }


  /*---------------------------------------------------------------------------
  Class Methods
  ---------------------------------------------------------------------------*/
  void DeviceDriver::run( void *arg )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------------------------------
    Perform initialization procedures
    -------------------------------------------------------------------------*/

    /*-------------------------------------------------------------------------
    Wait for the host system to allow processing
    -------------------------------------------------------------------------*/
    this_thread::pendTaskMsg( TSK_MSG_WAKEUP );

    /* Clean the RX buffers from any spurious power up transients */
    auto serial = Chimera::Serial::getDriver( dcb.serialChannel );
    serial->flush( Chimera::Hardware::SubPeripheral::RX );

    /*-------------------------------------------------------------------------
    Run the bluetooth communication manager stack
    -------------------------------------------------------------------------*/
    size_t last_time = 0;
    while( 1 )
    {
      last_time = Chimera::millis();

      /*-----------------------------------------------------------------------
      Copy out the current execution mode
      -----------------------------------------------------------------------*/
      OpMode mode = OpMode::UNKNOWN;
      dcb.lock->lock();
      mode = dcb.currentMode;
      dcb.lock->unlock();

      /*-----------------------------------------------------------------------
      Process based on the current mode
      -----------------------------------------------------------------------*/
      switch( mode )
      {
        case OpMode::COMMAND:
          doTransactionalProcessing();
          break;

        case OpMode::DATA:
          doPassthroughProcessing();
          break;

        default:
          LOG_DEBUG( "Unhandled BT manager processing mode: %d\r\n", mode );
          break;
      };

      /*-----------------------------------------------------------------------
      Look again in a few milliseconds
      -----------------------------------------------------------------------*/
      dcb.upTime += Chimera::millis() - last_time;
      Chimera::delayMilliseconds( 25 );
    }
  }


  bool DeviceDriver::enterCommandMode()
  {
    using namespace Chimera::Thread;
    PacketString response;

    /*-------------------------------------------------------------------------
    Already in command mode?
    -------------------------------------------------------------------------*/
    if ( dcb.currentMode == OpMode::COMMAND )
    {
      return true;
    }

    /*-------------------------------------------------------------------------
    Ensure the BT module has been online long enough to be listening
    -------------------------------------------------------------------------*/
    size_t uptime = 0;
    do
    {
      LockGuard _lck( *dcb.lock );
      uptime = dcb.upTime;
      this_thread::yield();
    } while ( uptime < ( 2 * TIMEOUT_1S ) );

    /*-------------------------------------------------------------------------
    Do a quick test if the device responds to a command that would indicate it
    is already in command mode from a previous power cycle.
    -------------------------------------------------------------------------*/
    this->transfer( "V\n" );
    if ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      dcb.currentMode = OpMode::COMMAND;
      return true;
    }

    /*-------------------------------------------------------------------------
    Send the request and listen for the entrance success message
    -------------------------------------------------------------------------*/
    this->transfer( "$$$" );
    if ( this->accumulateResponse( response, "CMD", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      dcb.currentMode = OpMode::COMMAND;
      return true;
    }
    else
    {
      LOG_ERROR( "Failed to enter command mode\r\n" );
      return false;
    }
  }


  bool DeviceDriver::enterDataMode()
  {
    using namespace Chimera::Thread;
    PacketString cmd, response;

    /*-------------------------------------------------------------------------
    Already in data mode?
    -------------------------------------------------------------------------*/
    if ( dcb.currentMode == OpMode::DATA )
    {
      return true;
    }

    /*-------------------------------------------------------------------------
    Send the request
    -------------------------------------------------------------------------*/
    this->transfer( "---\r" );
    if ( ( this->accumulateResponse( response, "\r", ( 2 * TIMEOUT_1S ) ) == StatusCode::OK ) && ( response == "END" ) )
    {
      dcb.currentMode = OpMode::DATA;
      return true;
    }
    else
    {
      LOG_ERROR( "Failed to enter data mode\r\n" );
      return false;
    }
  }


  void DeviceDriver::doTransactionalProcessing()
  {
    /*-----------------------------------------------------------------------
    Pull the next transaction off the queue
    -----------------------------------------------------------------------*/
    bool do_transaction = false;
    Internal::Transfer txfr;

    dcb.lock->lock();
    {
      if ( !dcb.txfrQueue.empty() )
      {
        do_transaction = true;
        dcb.txfrQueue.pop_into( txfr );
      }
    }
    dcb.lock->unlock();

    /*-----------------------------------------------------------------------
    Do the next transaction if available
    -----------------------------------------------------------------------*/
    if ( do_transaction )
    {
      /*---------------------------------------------------------------------
      TX the message to the module. Flush the RX queue first so the start of
      the response (if needed) is the first thing out.
      ---------------------------------------------------------------------*/
      auto serial = Chimera::Serial::getDriver( dcb.serialChannel );
      serial->flush( Chimera::Hardware::SubPeripheral::RX );

      StatusCode result = transfer( *txfr.message );

      /*---------------------------------------------------------------------
      Optionally look for a response
      ---------------------------------------------------------------------*/
      if ( txfr.waitForResponse && ( result == StatusCode::OK ) )
      {
        result = accumulateResponse( *txfr.response, txfr.termination, txfr.timeout );
      }

      /*---------------------------------------------------------------------
      Notify whomever queued the transaction
      ---------------------------------------------------------------------*/
      *txfr.result = result;
      txfr.signal->release();
    }
  }


  void DeviceDriver::doPassthroughProcessing()
  {
    // Move data through circular buffers on TX/RX sides
  }


  StatusCode DeviceDriver::transfer( const PacketString &cmd  )
  {
    using namespace Chimera::Event;
    using namespace Chimera::Thread;

    /*-------------------------------------------------------------------------
    Look up the serial driver assigned to the module
    -------------------------------------------------------------------------*/
    auto serial = Chimera::Serial::getDriver( dcb.serialChannel );

    /*-------------------------------------------------------------------------
    Do the transfer, waiting for all bytes to send before continuing.
    -------------------------------------------------------------------------*/
    if( serial->write( cmd.data(), cmd.size() ) == Chimera::Status::OK )
    {
      serial->await( Trigger::TRIGGER_WRITE_COMPLETE, TIMEOUT_BLOCK );
      return StatusCode::OK;
    }
    else
    {
      return StatusCode::FAIL;
    }
  }


  StatusCode DeviceDriver::accumulateResponse( PacketString &response, const std::string_view &terminator,
                                               const size_t timeout )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------------------------------
    Look up the serial driver assigned to the module
    -------------------------------------------------------------------------*/
    auto serial = Chimera::Serial::getDriver( dcb.serialChannel );

    /*-------------------------------------------------
    Use a temp buffer to accumulate into
    -------------------------------------------------*/
    char tmp_buffer[ PacketString::MAX_SIZE ];
    memset( tmp_buffer, 0, PacketString::MAX_SIZE );

    /*-------------------------------------------------
    Start the 2 second timeout waiting for a response
    -------------------------------------------------*/
    size_t start_time        = Chimera::millis();
    bool timeout_expired     = false;
    bool accumulate_done     = false;
    size_t bytesAvailable    = 0;
    size_t byteOffset        = 0;

    while ( !timeout_expired )
    {
      /*-------------------------------------------------
      Pull more data into the accumulation buffer
      -------------------------------------------------*/
      if( serial->available( &bytesAvailable ) )
      {
        /*-------------------------------------------------
        Protect against buffer overflow
        -------------------------------------------------*/
        if( ( byteOffset + bytesAvailable ) > ARRAY_BYTES( tmp_buffer ) )
        {
          return StatusCode::OVERFLOW;
        }

        /*-------------------------------------------------
        Update the accumulation buffer
        -------------------------------------------------*/
        serial->readAsync( reinterpret_cast<uint8_t *>( &tmp_buffer[ byteOffset ] ), bytesAvailable );
        byteOffset += bytesAvailable;
      }

      /*-------------------------------------------------
      Parse the buffer for the expected terminator
      -------------------------------------------------*/
      auto eom_ptr = strstr( tmp_buffer, terminator.data() );
      if ( eom_ptr )
      {
        size_t str_size = eom_ptr - tmp_buffer;
        response        = PacketString( tmp_buffer, str_size );
        accumulate_done = true;
        break;
      }

      timeout_expired = ( Chimera::millis() - start_time ) > timeout;
      this_thread::yield();
    }

    /*-------------------------------------------------
    Ensure the RX buffers are clean on exit to help
    with parsing the next message.
    -------------------------------------------------*/
    serial->flush( Chimera::Hardware::SubPeripheral::RX );

    /*-------------------------------------------------
    Retrieve the response if available
    -------------------------------------------------*/
    if ( timeout_expired || !accumulate_done )
    {
      return StatusCode::NO_RESPONSE;
    }
    else
    {
      return StatusCode::OK;
    }
  }

}    // namespace RN4871
