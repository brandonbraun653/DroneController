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


  void doPeriodicProcessing( void );

}  // namespace DC::HMI

#endif  /* !DC_HMI_DISCRETE_HPP */
