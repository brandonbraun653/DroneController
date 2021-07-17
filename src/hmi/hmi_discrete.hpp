/********************************************************************************
 *  File Name:
 *    hmi_discrete.hpp
 *
 *  Description:
 *    Digital discrete input interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HMI_DISCRETE_HPP
#define DC_HMI_DISCRETE_HPP

/* STL Includes */
#include <cstdint>

/* Aurora Includes */
#include <Aurora/hmi>

/* Project Includes */
#include <src/io/pin_mapping.hpp>

namespace DC::HMI::Discrete
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Power up the GPIO inputs for processing edge events
   *
   *  @return bool
   */
  bool initialize();

  /**
   * @brief Sets a pin to logical high
   * @note Pin must be a supported output type
   * @warning Does not directly access hardware. There may be some delay.
   *
   * @param pin     Which pin to set
   * @return true   The pin was set successfully
   * @return false  An error occurred
   */
  bool set( const GPIO::Pin pin );

  /**
   * @brief Clears a pin to logical low
   * @note Pin must be a supported output type
   * @warning Does not directly access hardware. There may be some delay.
   *
   * @param pin     Which pin to clear
   * @return true   The pin was set successfully
   * @return false  An error occurred
   */
  bool clear( const GPIO::Pin pin );

  /**
   * @brief Reads the logical state of a pin from cache
   * @note This works for all discrete pin types
   *
   * @param pin     Which pin to read
   * @return true   The pin is logic high
   * @return false  The pin is logic low
   */
  bool get( const GPIO::Pin pin );

  /**
   *  Register a callback to execute on key press
   *
   *  @param[in]  discrete        Which discrete to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onPress( const GPIO::InputPin discrete, Aurora::HMI::Button::EdgeCallback &cb );

  /**
   *  Register a callback to execute on key release
   *
   *  @param[in]  discrete        Which discrete to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onRelease( const GPIO::InputPin discrete, Aurora::HMI::Button::EdgeCallback &cb );

  /**
   *  Enable input processing for a particular key
   *
   *  @param[in]  discrete        Which discrete to enable
   *  @return bool
   */
  bool enable( const GPIO::InputPin discrete );

  /**
   *  Disable input processing for a particular key
   *
   *  @param[in]  discrete        Which discrete to disable
   *  @return void
   */
  void disable( const GPIO::InputPin discrete );

  /**
   * @brief Process all inputs to handle various events
   * @return void
   */
  void doPeriodicProcessing( void );

}  // namespace DC::HMI

#endif  /* !DC_HMI_DISCRETE_HPP */
