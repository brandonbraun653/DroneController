/********************************************************************************
 *  File Name:
 *    bt_driver.hpp
 *
 *  Description:
 *    Interface to the system's bluetooth module: RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_WIRELESS_BLUETOOTH_DRIVER_HPP
#define DC_WIRELESS_BLUETOOTH_DRIVER_HPP

/* STL Includes */
#include <cstdint>

/* Project Includes */
#include <src/wireless/bluetooth/rn4871/rn_device.hpp>

namespace DC::RF::BT
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum class PowerState : uint8_t
  {
    ENABLED,
    DISABLED
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Gets the device driver for the bluetooth module
   *
   * @param dev   Device object
   */
  void getDevice( ::RN4871::DeviceDriver **dev );

  /**
   * @brief Initialize the bluetooth SW module for operation
   */
  void initDriver();

  /**
   * @brief Controls power to the bluetooth module
   *
   * @param state     Which state to place the power into
   */
  void setPower( const PowerState state );

  /**
   * @brief Performs POR procedures to init hardware module
   *
   * @param mgrId     Task ID of the bluetooth manager thread
   */
  void doPowerOnReset( const Chimera::Thread::TaskId mgrId );

}  // namespace DC::RF::BT

#endif  /* !DC_WIRELESS_BLUETOOTH_DRIVER_HPP */
