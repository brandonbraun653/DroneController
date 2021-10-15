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
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }


  /**
   * @brief Sets the TX power during advertisement
   *
   * @param pwr       Power level to transmit at
   * @return bool
   */
  bool DeviceDriver::setAdvertisePower( const OutputPower pwr )
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
    scnprintf( buf, sizeof( buf ), "SGA,%d\r", EnumValue( pwr ) );

    PacketString response;
    this->transfer( buf );
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed configuring Advertise Output Power: %d\r\n", EnumValue( pwr ) );
      return false;
    }
  };


  /**
   * @brief Sets the TX power once connected to a device
   *
   * @param pwr       Power level to transmit at
   * @return bool
   */
  bool DeviceDriver::setConnectedPower( const OutputPower pwr )
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
    scnprintf( buf, sizeof( buf ), "SGC,%d\r", EnumValue( pwr ) );

    PacketString response;
    this->transfer( buf );
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed configuring Connected Output Power: %d\r\n", EnumValue( pwr ) );
      return false;
    }
  }


  /**
   * @brief Sets the GAP service the device will identify as
   * See https://www.bluetooth.com/ for more information, or download the values from
   * https://specificationrefs.bluetooth.com/assigned-values/Appearance%20Values.pdf.
   *
   * @param service   Service ID to identify as
   * @return bool
   */
  bool DeviceDriver::setGAPService( const uint16_t service )
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
    scnprintf( buf, sizeof( buf ), "SDA,%4.4x\r", service );
    LOG_INFO( "Setting service appearance as: 0x%4.4x\r\n", service );

    /*-------------------------------------------------
    Send the transfer. No response is expected.
    -------------------------------------------------*/
    PacketString response;
    bool success = this->transfer( buf ) == StatusCode::OK;
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed configuring GAP service: 0x%4.4x\r\n", service );
      return false;
    }

    return success;
  }


  /**
   * @brief Configure supported feature set on the RN4871
   *
   * @param bitmap      Feature set bitmap
   * @return bool
   */
  bool DeviceDriver::setFeatures( const Feature bitmap )
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
    scnprintf( buf, sizeof( buf ), "SR,%4.4x\r", EnumValue( bitmap ) );

    /*-------------------------------------------------
    Send the transaction
    -------------------------------------------------*/
    PacketString response;
    this->transfer( buf );
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed configuring feature set: 0x%4.4x\r\n", EnumValue( bitmap ) );
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

    if ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      return response;
    }
    else
    {
      return "ERROR";
    }
  }


  /**
   * @brief Gets the current connection signal strength in dBm
   *
   * @return int
   */
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


  /**
   * @brief Instructs the device to enter the UART transparent mode
   * @return bool
   */
  bool DeviceDriver::enterUARTMode()
  {
    /*-------------------------------------------------
    Ensure command mode is entered
    -------------------------------------------------*/
    if( !this->enterCommandMode() )
    {
      return false;
    }

    /*-------------------------------------------------
    Send the command
    -------------------------------------------------*/
    PacketString response;

    this->transfer( "I\r" );
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( strstr( response.c_str(), "AOK" ) ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed transitioning to UART transparent mode\r\n" );
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
    if( this->accumulateResponse( r1, "\r", RESPONSE_TIMEOUT ) != StatusCode::OK )
    {
      return false;
    }
    dcb.currentMode = OpMode::UNKNOWN;
    LOG_INFO( "Bluetooth: %s\r\n", r1.data() );

    /* Wait for the reboot complete */
    if( this->accumulateResponse( r2, "%RE", RESPONSE_TIMEOUT ) == StatusCode::OK )
    {
      return true;
    }
    else
    {
      LOG_INFO( "Bluetooth: Missing reboot message\r\n" );
      return false;
    }
  }


  /**
   * @brief Begin advertisement of the device
   * @return bool
   */
  bool DeviceDriver::startAdvertisement()
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
    PacketString response;
    this->transfer( "A\r" );
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed to start advertising\r\n" );
      return false;
    }
  }


  /**
   * @brief Begin advertisement of the device
   * @return bool
   */
  bool DeviceDriver::stopAdvertisement()
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
    PacketString response;
    this->transfer( "Y\r" );
    if( ( this->accumulateResponse( response, "\r", RESPONSE_TIMEOUT ) == StatusCode::OK ) && ( response == "AOK" ) )
    {
      return true;
    }
    else
    {
      LOG_ERROR( "Failed to start advertising\r\n" );
      return false;
    }
  }

  /**
   * @brief Kills the current active BTLE connection
   * @return bool
   */
  bool DeviceDriver::killCurrentConnection()
  {
    /*-------------------------------------------------
    Eventually will use this: 2.6.25 (K,1)
    -------------------------------------------------*/
    Chimera::insert_debug_breakpoint();
    return false;
  }


}    // namespace RN4871
