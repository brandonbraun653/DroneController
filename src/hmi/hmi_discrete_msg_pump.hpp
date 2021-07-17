/********************************************************************************
 *  File Name:
 *    hmi_discrete_msg_pump.hpp
 *
 *  Description:
 *    Discrete input pin events
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HMI_DISCRETE_MSG_PUMP_HPP
#define DC_HMI_DISCRETE_MSG_PUMP_HPP

/* Aurora Includes */
#include <Aurora/hmi>

/* Chimera Includes */
#include <Chimera/gpio>

namespace DC::HMI::Discrete
{
  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  /**
   * @brief Cached state object for all discrete pins
   */
  struct ReportedState
  {
    Chimera::GPIO::State PitchTrimUp;
    Chimera::GPIO::State PitchTrimDn;
    Chimera::GPIO::State RollTrimUp;
    Chimera::GPIO::State RollTrimDn;
    Chimera::GPIO::State YawTrimUp;
    Chimera::GPIO::State YawTrimDn;
    Chimera::GPIO::State ThrottleTrimUp;
    Chimera::GPIO::State ThrottleTrimDn;
    Chimera::GPIO::State SwitchAToggle;
    Chimera::GPIO::State SwitchBToggle;
    Chimera::GPIO::State SwitchCToggle;
    Chimera::GPIO::State SwitchDToggle;
    Chimera::GPIO::State Encoder0Center;
    Chimera::GPIO::State Encoder1Center;
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Registers notification callbacks with HW driver
   * @return void
   */
  void initMessagePump();

  /**
   * @brief Get the current state of all discrete pins
   *
   * @param state     Cached state object
   * @return void
   */
  void getCurrentState( ReportedState &state );

}    // namespace DC::HMI::Discrete

#endif /* !DC_HMI_DISCRETE_MSG_PUMP_HPP */
