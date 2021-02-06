/********************************************************************************
 *  File Name:
 *    hmi_encoder.hpp
 *
 *  Description:
 *    Rotary encoder input interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HMI_ROTARY_ENCODER_HPP
#define DC_HMI_ROTARY_ENCODER_HPP

/* STL Includes */
#include <cstdint>

/* Aurora Includes */
#include <Aurora/hmi>

namespace DC::HMI::Encoder
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  /**
   *  Aliases for the identifying the encoder modules by name
   */
  enum class Key : uint8_t
  {
    ENCODER_1,

    NUM_OPTIONS,
    INVALID
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Power up the GPIO inputs for processing inputs. By default
   *  this will leave all encoders disabled.
   *
   *  @return bool
   */
  bool initialize();

  /**
   *  Register a callback to execute on encoder center key press
   *
   *  @param[in]  encoder       Which encoder to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onCenterPress( const Key encoder, Aurora::HMI::Button::EdgeCallback &cb );

  /**
   *  Register a callback to execute on encoder center key release
   *
   *  @param[in]  encoder       Which encoder to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onCenterRelease( const Key encoder, Aurora::HMI::Button::EdgeCallback &cb );

  /**
   *  Register a callback to execute on encoder rotation
   *
   *  @param[in]  encoder       Which encoder to register against
   *  @param[in]  cb            The callback to execute
   *  @return bool
   */
  bool onRotate( const Key encoder, Aurora::HMI::Encoder::RotationCallback &cb );

  /**
   *  Enable input processing for a particular key
   *
   *  @param[in]  encoder       Which encoder to enable
   *  @return bool
   */
  bool enable( const Key encoder );

  /**
   *  Disable input processing for a particular key
   *
   *  @param[in]  encoder       Which encoder to disable
   *  @return void
   */
  void disable( const Key encoder );

}  // namespace DC::HMI::Encoder

#endif  /* !DC_HMI_ROTARY_ENCODER_HPP */
