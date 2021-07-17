/********************************************************************************
 *  File Name:
 *    pin_mapping.hpp
 *
 *  Description:
 *    Project's mapping for various IO that can be controlled or read
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_GPIO_PIN_MAPPING_HPP
#define DC_GPIO_PIN_MAPPING_HPP

/* STL Includes */
#include <cstdint>
#include <cstddef>
#include <limits>

namespace DC::GPIO
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  /**
   * @brief Indicates an invalid bit field return code.
   * No single pin will be represented by the maximum value of this data type.
   */
  static constexpr uint32_t INVALID_BIT_FIELD = std::numeric_limits<uint32_t>::max();

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  /**
   * @brief All available digital input signals read by a shift register
   */
  enum class InputPin : uint32_t
  {
    BATT_CHG_GOOD,
    BATT_PWR_GOOD,
    KEY_ENC_0,
    KEY_ENC_1,
    KEY_USER_0,
    KEY_USER_1,
    PITCH_TRIM_UP,
    PITCH_TRIM_DN,
    ROLL_TRIM_UP,
    ROLL_TRIM_DN,
    YAW_TRIM_UP,
    YAW_TRIM_DN,
    THROTTLE_TRIM_UP,
    THROTTLE_TRIM_DN,
    USER_SW_A,
    USER_SW_B,
    USER_SW_C,
    USER_SW_D,

    NUM_PINS,
    START_PIN = KEY_ENC_0
  };

  /**
   * @brief All available digital output signals controlled by a shift register
   */
  enum class OutputPin : uint32_t
  {
    RF24_PWR_EN,
    BT_PWR_EN,
    BATT_CHG_EN,
    DBG_LED_0,
    DBG_LED_1,
    DBG_LED_2,

    NUM_PINS
  };

  /**
   * @brief Unified listing of all IO pins
   */
  enum class Pin : uint32_t
  {
    FIRST_INPUT_PIN,
    BATT_CHG_GOOD = FIRST_INPUT_PIN,
    BATT_PWR_GOOD,
    KEY_ENC_0,
    KEY_ENC_1,
    KEY_USER_0,
    KEY_USER_1,
    PITCH_TRIM_UP,
    PITCH_TRIM_DN,
    ROLL_TRIM_UP,
    ROLL_TRIM_DN,
    YAW_TRIM_UP,
    YAW_TRIM_DN,
    THROTTLE_TRIM_UP,
    THROTTLE_TRIM_DN,
    USER_SW_A,
    USER_SW_B,
    USER_SW_C,
    USER_SW_D,
    LAST_INPUT_PIN = USER_SW_D,

    FIRST_OUTPUT_PIN,
    RF24_PWR_EN = FIRST_OUTPUT_PIN,
    BT_PWR_EN,
    BATT_CHG_EN,
    DBG_LED_0,
    DBG_LED_1,
    DBG_LED_2,
    LAST_OUTPUT_PIN = DBG_LED_2,

    NUM_PINS
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Initializes the shift register pin map
   */
  void initPinMap();

  /**
   * @brief Converts a logical InputPin to a literal bitfield
   *
   * The bit field corresponds to the physical location of the input
   * shift register chain.
   *
   * @param pin   Which pin to convert
   * @return uint32_t
   */
  uint32_t pinToBitField( const InputPin pin );

  /**
   * @brief Converts a literal bitfield into a logical InputPin
   *
   * @param bit_field   The bitfield to convert
   * @return InputPin
   */
  InputPin bitFieldToInputPin( const uint32_t bit_field );

  /**
   * @brief Converts a logical OutputPin to a literal bitfield
   *
   * The bit field corresponds to the physical location of the input
   * shift register chain.
   *
   * @param pin   Which pin to convert
   * @return uint32_t
   */
  uint32_t pinToBitField( const OutputPin pin );

  InputPin pinToInputId( const Pin pin );
  OutputPin pinToOutputId( const Pin pin );

}    // namespace DC::GPIO

#endif /* !DC_GPIO_PIN_MAPPING_HPP */
