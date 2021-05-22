/********************************************************************************
 *  File Name:
 *    rn_device.cpp
 *
 *  Description:
 *    Device driver for the RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>
#include <Aurora/utility>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/serial>

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_device.hpp>
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>
#include <src/wireless/bluetooth/rn4871/rn_action_cmds.hpp>


namespace RN4871
{
  DeviceDriver::DeviceDriver() : mSerialChannel( Chimera::Serial::Channel::NOT_SUPPORTED ), mCurrentMode( OpMode::INVALID )
  {
  }


  DeviceDriver::~DeviceDriver()
  {
  }


  /**
   * @brief Assigns the serial channel used to communicate with the module
   *
   * @param channel     Which serial channel to use
   */
  void DeviceDriver::assignSerial( const Chimera::Serial::Channel channel )
  {
    mSerialChannel = channel;
  }


  /**
   * @brief Assigns the name to the BT device
   *
   * @param name    Name to be assigned
   * @return true   Device accepted the name
   * @return false  Failure occurred
   */
  bool DeviceDriver::setName( const std::string_view &name )
  {
    /*-------------------------------------------------
    This action requires command mode
    -------------------------------------------------*/
    if ( !this->enterCommandMode() )
    {
      return false;
    }

    /*-------------------------------------------------
    Format the command string
    -------------------------------------------------*/
    PacketBuffer buf;
    memset( buf, 0, sizeof( buf ) );
    scnprintf( buf, sizeof( buf ), "S-,%s\r", name.data() );

    PacketString response;
    this->transfer( buf );
    if( ( this->accumulateResponse( response, "\r" ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }


  /**
   * @brief Gets the software version running on the RN4871
   *
   * @return VersionString
   */
  VersionString DeviceDriver::softwareVersion()
  {
    /*-------------------------------------------------
    Getting the version requires command mode
    -------------------------------------------------*/
    if ( !this->enterCommandMode() )
    {
      return "ERROR";
    }

    /*-------------------------------------------------
    Request the current software version
    -------------------------------------------------*/
    PacketString cmd, response;
    CMD::Action::version( cmd );
    this->transfer( cmd );

    if ( this->accumulateResponse( response, "\r" ) == StatusCode::OK )
    {
      return response;
    }
    else
    {
      return "ERROR";
    }
  }


  /**
   * @brief Instructs the module to enter comand mode
   */
  bool DeviceDriver::enterCommandMode()
  {
    PacketString response;

    /*-------------------------------------------------
    Already in command mode?
    -------------------------------------------------*/
    if ( mCurrentMode == OpMode::COMMAND )
    {
      return true;
    }

    /*-------------------------------------------------
    Send the request
    -------------------------------------------------*/
    this->transfer( "$$$" );
    if ( ( this->accumulateResponse( response, " " ) == StatusCode::OK ) && ( response == "CMD>" ) )
    {
      mCurrentMode = OpMode::COMMAND;
      return true;
    }
    else
    {
      return false;
    }
  }


  /**
   * @brief Instructs the module to enter data mode
   */
  bool DeviceDriver::enterDataMode()
  {
    PacketString cmd, response;

    /*-------------------------------------------------
    Already in command mode?
    -------------------------------------------------*/
    if ( mCurrentMode == OpMode::DATA )
    {
      return true;
    }

    /*-------------------------------------------------
    Send the request
    -------------------------------------------------*/
    this->transfer( "---\r" );
    if ( ( this->accumulateResponse( response, " " ) == StatusCode::OK ) && ( response == "END" ) )
    {
      mCurrentMode = OpMode::DATA;
      return true;
    }
    else
    {
      return false;
    }
  }


  /**
   * @brief Instructs the RN4871 to perform a warm reset
   */
  bool DeviceDriver::reboot()
  {
    /*-------------------------------------------------
    Ensure command mode is entered
    -------------------------------------------------*/
    if( !this->enterCommandMode() )
    {
      return false;
    }

    /*-------------------------------------------------
    Send the command sequence. This can take a second.
    Expected flow:
      Send -> R,1\r
      Recv <- Rebooting\r\n
      Recv <- %REBOOT%
    -------------------------------------------------*/
    PacketString r1, r2;

    /* Send reboot command */
    this->transfer( "R,1\r" );
    if( this->accumulateResponse( r1, "\r" ) != StatusCode::OK )
    {
      return false;
    }
    LOG_INFO( "Bluetooth: %s\r\n", r1.data() );

    /* Wait for the reboot complete */
    if( this->accumulateResponse( r2, "%REBOOT%" ) == StatusCode::OK )
    {
      LOG_INFO( "Bluetooth: Done\r\n" );
      return true;
    }
    else
    {
      LOG_INFO( "Bluetooth: Missing reboot message\r\n" );
      return false;
    }
  }


  /**
   * @brief Sends a command string, optionally listening for a response
   *
   * @param cmd       Command to send
   * @param rsp       Optional buffer to write the raw response into
   * @return StatusCode
   */
  StatusCode DeviceDriver::transfer( const PacketString &cmd  )
  {
    using namespace Chimera::Event;
    using namespace Chimera::Thread;

    auto serial = Chimera::Serial::getDriver( mSerialChannel );

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


  /**
   * @brief Accumulates a terminated response
   *
   *
   * @param rsp
   * @return StatusCode
   */
  StatusCode DeviceDriver::accumulateResponse( PacketString &response, const std::string_view &terminator )
  {
    using namespace Chimera::Thread;

    auto serial = Chimera::Serial::getDriver( mSerialChannel );

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

      timeout_expired = ( Chimera::millis() - start_time ) > ( 2 * TIMEOUT_1S );
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
