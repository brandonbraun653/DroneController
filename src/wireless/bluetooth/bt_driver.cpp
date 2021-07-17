/********************************************************************************
 *  File Name:
 *    bt_driver.cpp
 *
 *  Description:
 *    Bluetooth module driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/serial>
#include <Chimera/thread>

/* ETL Includes */
#include <etl/circular_buffer.h>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_discrete.hpp>
#include <src/wireless/bluetooth/bt_driver.hpp>
#include <src/wireless/bluetooth/rn4871/rn_device.hpp>

namespace DC::RF::BT
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_is_enabled = false;
  static RN4871::DeviceDriver s_bt_device;

  /*-------------------------------------------------
  Serial Driver Configuration
  -------------------------------------------------*/
  static constexpr size_t HWBufferSize = 256;
  static constexpr size_t CircleBufSize = 2 * HWBufferSize;

  // Transmit Buffers
  static std::array<uint8_t, HWBufferSize> sTXHWBuffer;
  static etl::circular_buffer<uint8_t, CircleBufSize> sTXCircularBuffer;

  // Receive Buffers
  static std::array<uint8_t, HWBufferSize> sRXHWBuffer;
  static etl::circular_buffer<uint8_t, CircleBufSize> sRXCircularBuffer;

  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Initializes the serial driver for RN4871 communications
   */
  static void initSerial()
  {
    using namespace Chimera::Serial;
    using namespace Chimera::Hardware;

    /*------------------------------------------------
    Configuration info for the serial object
    ------------------------------------------------*/
    IOPins pins;
    pins.tx = DC::IO::Bluetooth::txPinInit;
    pins.rx = DC::IO::Bluetooth::rxPinInit;

    Config cfg = DC::IO::Bluetooth::comConfig;

    /*------------------------------------------------
    Create the serial object and initialize it
    ------------------------------------------------*/
    auto result = Chimera::Status::OK;
    auto serial = Chimera::Serial::getDriver( DC::IO::Bluetooth::serialChannel );

    if ( !serial )
    {
      Chimera::insert_debug_breakpoint();
    }

    result |= serial->assignHW( DC::IO::Bluetooth::serialChannel, pins );
    result |= serial->configure( cfg );
    result |= serial->enableBuffering( SubPeripheral::TX, sTXCircularBuffer, sTXHWBuffer.data(), sTXHWBuffer.size() );
    result |= serial->enableBuffering( SubPeripheral::RX, sRXCircularBuffer, sRXHWBuffer.data(), sRXHWBuffer.size() );
    RT_HARD_ASSERT( result == Chimera::Status::OK );

    serial->begin( PeripheralMode::INTERRUPT, PeripheralMode::INTERRUPT );
  }

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Initialize the bluetooth driver module
   */
  void initDriver()
  {
    /*-------------------------------------------------
    Initialize local data
    -------------------------------------------------*/
    s_is_enabled = false;

    /*-------------------------------------------------
    Power up the serial communication
    -------------------------------------------------*/
    initSerial();

    /*-------------------------------------------------
    Initialize the bluetooth device driver
    -------------------------------------------------*/
    s_bt_device.assignSerial( DC::IO::Bluetooth::serialChannel );
  }


  /**
   * @brief Controls power to the bluetooth module
   *
   * @param state     Which state to place the power into
   */
  void setPower( const PowerState state )
  {
    if( state == PowerState::ENABLED )
    {
      HMI::Discrete::set( GPIO::Pin::BT_PWR_EN );
      s_is_enabled = true;
    }
    else
    {
      HMI::Discrete::clear( GPIO::Pin::BT_PWR_EN );
      s_is_enabled = false;
    }

    /*-------------------------------------------------
    Due to the asynchronous nature of HMI, wait a bit
    for this to take effect.
    -------------------------------------------------*/
    Chimera::delayMilliseconds( 25 );
  }


  /**
   * @brief Performs POR procedures to init module
   */
  void doPowerOnReset()
  {
    /*-------------------------------------------------
    Power cycle the unit
    -------------------------------------------------*/
    LOG_INFO( "Powering down bluetooth module...\r\n" );
    setPower( PowerState::DISABLED );
    Chimera::delayMilliseconds( 500 );
    LOG_INFO( "Powering up bluetooth module...\r\n" );
    setPower( PowerState::ENABLED );
    Chimera::delayMilliseconds( 150 );

    auto serial = Chimera::Serial::getDriver( DC::IO::Bluetooth::serialChannel );
    serial->flush( Chimera::Hardware::SubPeripheral::RX );

    /*-------------------------------------------------
    Set core feature set
    -------------------------------------------------*/
    RN4871::Feature bitset = RN4871::Feature::NONE;
    s_bt_device.setFeatures( bitset );

    /*-------------------------------------------------
    Ping the unit to grab version information
    -------------------------------------------------*/
    LOG_INFO( "Bluetooth version: %s\r\n", s_bt_device.softwareVersion().data() );
    LOG_INFO( "Configuring Bluetooth...\r\n" );

    /*-------------------------------------------------
    Set the device name to something useful
    -------------------------------------------------*/
    s_bt_device.setName( "DroneCtrl" );

    /*-------------------------------------------------
    Set device appearance as Generic Remote Control
    -------------------------------------------------*/
    s_bt_device.setGAPService( 0x1080 );

    /*-------------------------------------------------
    Set the output power for broadcasting
    -------------------------------------------------*/
    s_bt_device.setAdvertisePower( RN4871::OutputPower::LEVEL_0 );
    s_bt_device.setConnectedPower( RN4871::OutputPower::LEVEL_0 );

    /*-------------------------------------------------
    Apply configuration settings by doing a warm reset
    -------------------------------------------------*/
    s_bt_device.reboot();
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------
    Begin advertising the controller
    -------------------------------------------------*/
    s_bt_device.startAdvertisement();
    s_bt_device.enterUARTMode();
  }

}    // namespace DC::RF::BT
