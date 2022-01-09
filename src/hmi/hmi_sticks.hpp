/********************************************************************************
 *  File Name:
 *    hmi_sticks.hpp
 *
 *  Description:
 *    Interface to the analog joysticks used on the controller
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HMI_JOYSTICK_HPP
#define DC_HMI_JOYSTICK_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstdint>

namespace DC::HMI::JoyStick
{
  /*---------------------------------------------------------------------------
  Enumerations
  ---------------------------------------------------------------------------*/
  enum class Axis : uint8_t
  {
    PITCH,
    ROLL,
    YAW,
    THROTTLE,

    NUM_OPTIONS,
    UNKNOWN
  };

  /*-----------------------------------------------------------------------------
  Public Functions
  -----------------------------------------------------------------------------*/
  /**
   * @brief Initialize the Joystick driver
   */
  void initHWDriver();

}    // namespace DC::HMI::JoyStick

#endif /* !DC_HMI_JOYSTICK_HPP */
