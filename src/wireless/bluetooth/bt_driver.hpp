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
   * @brief Initialize the bluetooth driver module
   */
  void initDriver();

  /**
   * @brief Controls power to the bluetooth module
   *
   * @param state     Which state to place the power into
   */
  void setPower( const PowerState state );


}  // namespace DC::RF::BT

#endif  /* !DC_WIRELESS_BLUETOOTH_DRIVER_HPP */
