/********************************************************************************
 *  File Name:
 *    rn_device.cpp
 *
 *  Description:
 *    Device driver for the RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <string>

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
  /*---------------------------------------------------------------------------
  Class Methods
  ---------------------------------------------------------------------------*/
  DeviceDriver::DeviceDriver()
  {

  }


  DeviceDriver::~DeviceDriver()
  {
    if( dcb.lock )
    {
      free( dcb.lock );
    }
  }


  bool DeviceDriver::initialize()
  {
    dcb.lock = new Chimera::Thread::RecursiveMutex();
    dcb.isInitialized = true;

    return dcb.isInitialized;
  }


  void DeviceDriver::assignSerial( const Chimera::Serial::Channel channel )
  {
    Chimera::Thread::LockGuard lck( *dcb.lock );
    dcb.serialChannel = channel;
  }


  bool DeviceDriver::setName( const std::string_view &name )
  {
    /*-------------------------------------------------------------------------
    Format the command string
    -------------------------------------------------------------------------*/
    PacketBuffer buf;
    memset( buf, 0, sizeof( buf ) );
    scnprintf( buf, sizeof( buf ), "S-,%s\r", name.data() );

    /*-------------------------------------------------------------------------
    Send the command
    -------------------------------------------------------------------------*/
    if( this->doCommand( buf, "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: Assigned device name [%s]\r\n", name.data() );
      return true;
    }
    else
    {
      LOG_ERROR( "BT: Failed to assign device name\r\n" );
      return false;
    }
  }


  bool DeviceDriver::setAdvertisePower( const OutputPower pwr )
  {
    /*-------------------------------------------------------------------------
    Format the command string
    -------------------------------------------------------------------------*/
    PacketBuffer buf;
    memset( buf, 0, sizeof( buf ) );
    scnprintf( buf, sizeof( buf ), "SGA,%d\r", EnumValue( pwr ) );

    /*-------------------------------------------------------------------------
    Send the command
    -------------------------------------------------------------------------*/
    if( this->doCommand( buf, "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: Configured advertise TX power\r\n" );
      return true;
    }
    else
    {
      LOG_ERROR( "BT: Failed configuring advertise TX power: %d\r\n", EnumValue( pwr ) );
      return false;
    }
  };


  bool DeviceDriver::setConnectedPower( const OutputPower pwr )
  {
    /*-------------------------------------------------------------------------
    Format the command string
    -------------------------------------------------------------------------*/
    PacketBuffer buf;
    memset( buf, 0, sizeof( buf ) );
    scnprintf( buf, sizeof( buf ), "SGC,%d\r", EnumValue( pwr ) );

    /*-------------------------------------------------------------------------
    Send the command
    -------------------------------------------------------------------------*/
    if( this->doCommand( buf, "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: Configured connected TX power\r\n" );
      return true;
    }
    else
    {
      LOG_ERROR( "BT: Failed configuring connected TX power: %d\r\n", EnumValue( pwr ) );
      return false;
    }
  }


  bool DeviceDriver::setGAPService( const uint16_t service )
  {
    /*-------------------------------------------------------------------------
    Format the command string
    -------------------------------------------------------------------------*/
    PacketBuffer buf;
    memset( buf, 0, sizeof( buf ) );
    scnprintf( buf, sizeof( buf ), "SDA,%4.4x\r", service );
    LOG_INFO( "BT: Setting GAP service as [0x%4.4x]\r\n", service );

    /*-------------------------------------------------------------------------
    Send the command
    -------------------------------------------------------------------------*/
    if( this->doCommand( buf, "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: GAP assignment OK\r\n" );
      return true;
    }
    else
    {
      LOG_ERROR( "Failed configuring GAP service: 0x%4.4x\r\n", service );
      return false;
    }
  }


  bool DeviceDriver::setFeatures( const Feature bitmap )
  {
    /*-------------------------------------------------------------------------
    Format the command string
    -------------------------------------------------------------------------*/
    PacketBuffer buf;
    memset( buf, 0, sizeof( buf ) );
    scnprintf( buf, sizeof( buf ), "SR,%4.4x\r", EnumValue( bitmap ) );

    /*-------------------------------------------------------------------------
    Do the transaction
    -------------------------------------------------------------------------*/
    if( this->doCommand( buf, "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: Assigned features\r\n" );
      return true;
    }
    else
    {
      LOG_ERROR( "BT: Failed configuring feature set: 0x%4.4x\r\n", EnumValue( bitmap ) );
      return false;
    }
  }


  VersionString DeviceDriver::softwareVersion()
  {
    static const char *error_msg = "ERROR";

    /*-------------------------------------------------------------------------
    Getting the software version requires command mode
    -------------------------------------------------------------------------*/
    if ( !this->enterCommandMode() )
    {
      return error_msg;
    }

    /*-------------------------------------------------------------------------
    Request the current software version
    -------------------------------------------------------------------------*/
    PacketString cmd, response;
    CMD::Action::version( cmd );
    this->transfer( cmd );

    if ( this->accumulateResponse( response, "CMD", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      /*-----------------------------------------------------------------------
      Strip characters off the front
      -----------------------------------------------------------------------*/
      auto start_npos = response.find( "RN4871" );

      /*-----------------------------------------------------------------------
      Sanitize the string by stripping off unused characters
      -----------------------------------------------------------------------*/
      auto end_npos = response.find( "\r" );
      std::fill( &response[ end_npos ], response.end(), 0 );

      /*-----------------------------------------------------------------------
      Rebuild the string
      -----------------------------------------------------------------------*/
      response = PacketString( &response[ start_npos ] );

      return response;
    }
    else
    {
      return error_msg;
    }
  }


  int DeviceDriver::connectionStrength()
  {
    /*-------------------------------------------------
    Must be in command mode
    -------------------------------------------------*/
    if ( !this->enterCommandMode() )
    {
      return -1;
    }

    /*-------------------------------------------------
    Request the connection strength
    -------------------------------------------------*/
    PacketString response;
    this->transfer( "M\r" );

    if ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      if( strstr( response.c_str(), "Err" ) )
      {
        return -1;
      }

      return std::stoi( response.c_str(), nullptr, 16 );
    }
    else
    {
      LOG_ERROR( "Failed to retrieve connection strength\r\n" );
      return -1;
    }
  }


  bool DeviceDriver::isConnected()
  {
    /*-------------------------------------------------
    Must be in command mode
    -------------------------------------------------*/
    if ( !this->enterCommandMode() )
    {
      return false;
    }

    /*-------------------------------------------------
    Request the connection strength
    -------------------------------------------------*/
    PacketString response;
    this->transfer( "GK\r" );

    if ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      if( strstr( response.c_str(), "none" ) )
      {
        return false;
      }

      return true;
    }
    else
    {
      LOG_ERROR( "Failed to retrieve connection status\r\n" );
      return false;
    }
  }


  bool DeviceDriver::reboot()
  {
    /*-------------------------------------------------------------------------
    Ensure command mode is entered
    -------------------------------------------------------------------------*/
    if( !this->enterCommandMode() )
    {
      return false;
    }

    /*-------------------------------------------------------------------------
    Send the command sequence. This can take a second.

    Expected flow:
      Send -> R,1\r
      Recv <- Rebooting\r\n
      Recv <- %REBOOT%
    -------------------------------------------------------------------------*/
    PacketString r1, r2;

    /*-------------------------------------------------------------------------
    Send reboot command
    -------------------------------------------------------------------------*/
    this->transfer( "R,1\r" );
    if( this->accumulateResponse( r1, "\r", RESPONSE_TIMEOUT ) != StatusCode::OK )
    {
      return false;
    }
    dcb.currentMode = OpMode::UNKNOWN;
    LOG_INFO( "BT: %s", r1.data() );

    /*-------------------------------------------------------------------------
    Wait for reboot complete. Will be in DATA mode upon restart.
    -------------------------------------------------------------------------*/
    if( this->accumulateResponse( r2, "%RE", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: Complete\r\n" );
      dcb.currentMode = OpMode::DATA;
      return true;
    }
    else
    {
      return false;
    }
  }


  bool DeviceDriver::startAdvertisement()
  {
    /*-------------------------------------------------------------------------
    Send the command
    -------------------------------------------------------------------------*/
    if( this->doCommand( "A\r", "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_INFO( "BT: Advertisement started\r\n" );
      return true;
    }
    else
    {
      LOG_ERROR( "BT: Advertisement failed to start\r\n" );
      return false;
    }
  }


  bool DeviceDriver::stopAdvertisement()
  {
    /*-------------------------------------------------------------------------
    Send the command
    -------------------------------------------------------------------------*/
    if( this->doCommand( "Y\r", "CMD", "AOK", DFLT_RETRIES, RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      LOG_ERROR( "BT: Advertisement stopped\r\n" );
      return false;
    }
    else
    {
      LOG_ERROR( "BT: Advertisement failed to stop\r\n" );
      return false;
    }
  }

}    // namespace RN4871
