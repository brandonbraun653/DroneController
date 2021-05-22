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
    Device Information
    -------------------------------------------------*/
    VersionString softwareVersion();
    int connectionStrength();
    bool isConnected();

    /*-------------------------------------------------
    Configuration
    -------------------------------------------------*/
    void assignSerial( const Chimera::Serial::Channel channel );
    bool setName( const std::string_view &name );
    bool setAdvertisePower( const OutputPower pwr );
    bool setConnectedPower( const OutputPower pwr );
    bool setGAPService( const uint16_t service );
    bool setFeatures( const Feature bitmap );

    /*-------------------------------------------------
    System Commands
    -------------------------------------------------*/
    bool enterCommandMode();
    bool enterDataMode();
    bool enterUARTMode();
    bool reboot();
    bool startAdvertisement();
    bool stopAdvertisement();
    bool killCurrentConnection();

    /*-------------------------------------------------
    Data Transfer
    -------------------------------------------------*/
    StatusCode transfer( const PacketString &cmd );
    StatusCode accumulateResponse( PacketString &rsp, const std::string_view &terminator );

  protected:



  private:
    Chimera::Serial::Channel mSerialChannel; /**< Serial channel device is on */
    OpMode mCurrentMode;
  };
}    // namespace RN4871

#endif /* !RN4871_DEVICE_HPP */
