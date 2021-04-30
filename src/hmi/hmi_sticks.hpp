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


namespace DC::HMI::JoyStick
{

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Initialize the Joystick driver
   */
  void initialize();

  /**
   * @brief Reads the pitch analog input
   *
   * @return float
   */
  float readPitch();

  /**
   * @brief Reads the roll analog input
   *
   * @return float
   */
  float readRoll();

  /**
   * @brief Reads the yaw analog input
   *
   * @return float
   */
  float readYaw();

  /**
   * @brief Reads the throttle analog input
   *
   * @return float
   */
  float readThrottle();

}    // namespace DC::HMI::JoyStick

#endif /* !DC_HMI_JOYSTICK_HPP */
