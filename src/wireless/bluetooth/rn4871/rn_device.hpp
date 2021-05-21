/********************************************************************************
 *  File Name:
 *    rn_device.hpp
 *
 *  Description:
 *    High level device interface to an RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef RN4871_DEVICE_HPP
#define RN4871_DEVICE_HPP

/* Chimera Includes */
#include <Chimera/serial>

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>

namespace RN4871
{
  class DeviceDriver
  {
  public:
    DeviceDriver();
    ~DeviceDriver();

    /*-------------------------------------------------
    Info and Configuration
    -------------------------------------------------*/
    void assignSerial( const Chimera::Serial::Channel channel );
    VersionString softwareVersion();

    /*-------------------------------------------------
    System Commands
    -------------------------------------------------*/
    bool enterTransparentMode();
    void exitTransparentMode();
    void reboot();

    /*-------------------------------------------------
    Data Transfer
    -------------------------------------------------*/
    StatusCode command( const PacketString &cmd, PacketString *const rsp = nullptr, const size_t delay = 0 );

  private:
    Chimera::Serial::Channel mSerialChannel; /**< Serial channel device is on */
  };
}    // namespace RN4871

#endif /* !RN4871_DEVICE_HPP */
