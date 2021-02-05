/********************************************************************************
 *  File Name:
 *    hmi_button.hpp
 *
 *  Description:
 *    Button input interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HMI_BUTTON_HPP
#define DC_HMI_BUTTON_HPP

/* STL Includes */
#include <cstdint>

/* ETL Includes */
#include <etl/delegate.h>

namespace DC::HMI::Button
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  /**
   *  Aliases for the identifying the key inputs by name
   */
  enum class Key : uint8_t
  {
    TOUCH_KEY_1,

    NUM_OPTIONS,
    INVALID
  };

  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using EventCallback = etl::delegate<void(const Key)>;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Power up the GPIO inputs for processing inputs. By default
   *  this will leave all buttons disabled.
   *
   *  @return bool
   */
  bool initialize();

  /**
   *  Register a callback to execute on key press
   *
   *  @param[in]  button        Which button to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onPress( const Key button, EventCallback &cb );

  /**
   *  Register a callback to execute on key release
   *
   *  @param[in]  button        Which button to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onRelease( const Key button, EventCallback &cb );

  /**
   *  Enable input processing for a particular key
   *
   *  @param[in]  button        Which button to enable
   *  @return bool
   */
  bool enable( const Key button );

  /**
   *  Disable input processing for a particular key
   *
   *  @param[in]  button        Which button to disable
   *  @return void
   */
  void disable( const Key button );

}  // namespace DC::HMI

#endif  /* !DC_HMI_BUTTON_HPP */
