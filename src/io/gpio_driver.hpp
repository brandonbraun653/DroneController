/********************************************************************************
 *  File Name:
 *    gpio_driver.hpp
 *
 *  Description:
 *    Driver for reading/writing to GPIO through shift registers
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_GPIO_DRIVER_HPP
#define DC_GPIO_DRIVER_HPP

/* Project Includes */
#include <src/io/pin_mapping.hpp>

namespace DC::GPIO
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Set
   *
   * @param pin
   */
  void setShiftRegister( const SR::OutputPin pin );

  void clearShiftRegister( const SR::OutputPin pin );

  bool getShiftRegister( const SR::InputPin pin );

}  // namespace DC::GPIO

#endif  /* !DC_GPIO_DRIVER_HPP */
