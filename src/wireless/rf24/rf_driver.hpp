/********************************************************************************
 *  File Name:
 *    rf_driver.hpp
 *
 *  Description:
 *    Core RF driver interface that is responsible for abstracting away the
 *    complexities of a radio link and focuses on allowing the main application
 *    to easily pass data through the system.
 *
 *    The driver is written with thread safety in mind so that any thread can
 *    transmit or recieve data without fear.
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_WIRELESS_DRIVER_HPP
#define DC_WIRELESS_DRIVER_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Ripple/netif/nrf24l01>


namespace DC::RF::RF24
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
   * @brief Initialize the RF24 driver module
   */
  void initDriver();

  /**
   * @brief Controls power to the RF24 module
   *
   * @param state     Which state to place the power into
   */
  void setPower( const PowerState state );

  /**
   *  Generates the project's radio configuration structure
   *
   *  @param[in]  config    Object to be configured
   *  @return void
   */
  void genRadioCfg( Ripple::NetIf::NRF24::Physical::Handle &config );

}  // namespace DC::RF

#endif  /* !DC_WIRELESS_DRIVER_HPP */
