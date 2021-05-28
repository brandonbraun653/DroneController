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
#include <Aurora/utility>

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
    ENCODER_0,
    ENCODER_1,

    NUM_OPTIONS,
    INVALID
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  bool initialize();
  bool onRotate( const Key encoder, Aurora::HMI::Encoder::RotationCallback &cb );
  bool enable( const Key encoder );
  void disable( const Key encoder );
  bool nextEvent( const Key encoder, Aurora::HMI::Encoder::State &event );
  void doPeriodicProcessing();

}  // namespace DC::HMI::Encoder

#endif  /* !DC_HMI_ROTARY_ENCODER_HPP */
