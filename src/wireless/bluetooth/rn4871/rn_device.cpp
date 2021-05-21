/********************************************************************************
 *  File Name:
 *    rn_device.cpp
 *
 *  Description:
 *    Device driver for the RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_device.hpp>
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>
#include <src/wireless/bluetooth/rn4871/rn_action_cmds.hpp>


namespace RN4871
{
  DeviceDriver::DeviceDriver() : mSerialChannel( Chimera::Serial::Channel::NOT_SUPPORTED )
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
   * @brief Gets the software version running on the RN4871
   *
   * @return VersionString
   */
  VersionString DeviceDriver::softwareVersion()
  {
    /*-------------------------------------------------
    Request the current software version
    -------------------------------------------------*/
    PacketString cmd, response;

    response.clear();
    CMD::Action::version( cmd );
    if( this->command( cmd, &response ) == StatusCode::OK )
    {
      return response;
    }
    else
    {
      return "ERROR";
    }
  }


  /**
   * @brief Instructs the module to pass through UART data
   *
   * @return true     Pass through enabled
   * @return false    Failed to enable pass through
   */
  bool DeviceDriver::enterTransparentMode()
  {
  }


  /**
   * @brief Leaves UART passthrough mode
   */
  void DeviceDriver::exitTransparentMode()
  {
  }


  /**
   * @brief Instructs the RN4871 to perform a warm reset
   */
  void DeviceDriver::reboot()
  {
  }


  /**
   * @brief Sends a command string, optionally listening for a response
   *
   * @param cmd       Command to send
   * @param rsp       Optional buffer to write the raw response into
   * @return StatusCode
   */
  StatusCode DeviceDriver::command( const PacketString &cmd, PacketString *const rsp )
  {
  }
}    // namespace RN4871
