/********************************************************************************
 *  File Name:
 *    hmi_encoder_msg_pump.hpp
 *
 *  Description:
 *    Message pump API for the encoder
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HMI_ENCODER_MSG_PUMP_HPP
#define DC_HMI_ENCODER_MSG_PUMP_HPP

/* Aurora Includes */
#include <Aurora/hmi>


namespace DC::HMI::Encoder
{
  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  /**
   * @brief Cached encoder states
   */
  struct ReportedState
  {
    Aurora::HMI::Encoder::State encoder0;
    Aurora::HMI::Encoder::State encoder1;
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
   * @brief Get the current state of all encoders
   *
   * @param state     Cached state object
   * @return void
   */
  void getCurrentState( ReportedState &state );

}    // namespace DC::HMI::Encoder

#endif /* !DC_HMI_ENCODER_MSG_PUMP_HPP */
