/********************************************************************************
 *  File Name:
 *    sr_driver.hpp
 *
 *  Description:
 *    Shift register driver for the system's discrete IO.
   * Due to the number IO in the project, most are read/write from a
   * series of shift reg
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_SHIFT_REGISTER_DRIVER_HPP
#define DC_SHIFT_REGISTER_DRIVER_HPP

/* STL Includes */
#include <cstdint>

/* Project Includes */
#include <src/io/pin_mapping.hpp>

namespace DC::GPIO::SR
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Turn on the driver to allow reading/writing to IO
   *
   * Enables the SPI peripheral used to talk with the board's shift
   * registers.
   */
  void init();

  /**
   * @brief Reads the current state of the input shift registers
   *
   * @param buffer    Input buffer to read into
   * @param bytes     Number of bytes to read
   */
  void read( void *const buffer, const size_t bytes );

  /**
   * @brief Writes the output shift register
   *
   * @param buffer    Buffer of data to write
   * @param bytes     Number of bytes to write from the buffer
   */
  void write( const void *const buffer, const uint32_t bytes );

}  // namespace DC::IO

#endif  /* !DC_SHIFT_REGISTER_DRIVER_HPP */
