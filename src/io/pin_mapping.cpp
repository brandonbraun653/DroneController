/********************************************************************************
 *  File Name:
 *    pin_mapping.cpp
 *
 *  Description:
 *    Maps generic pins into hardware specific values
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <array>
#include <cstdint>

/* Aurora Includes */
#include <Aurora/utility>

/* Project Includes */
#include <src/io/pin_mapping.hpp>

namespace DC::GPIO::SR
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static std::array<uint32_t, EnumValue( InputPin::NUM_PINS )> s_input_pin_map;
  static std::array<uint32_t, EnumValue( OutputPin::NUM_PINS )> s_output_pin_map;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initPinMap()
  {
    /*-------------------------------------------------
    Initialize the Input shift register pin map. Per
    the schematic as of 83ca7145e2e521ed on main:

        U1         U2         U3
    d16 --> 0  d8  --> 8   d0 --> 16
    d17 --> 1  d9  --> 9   d1 --> 17
    d18 --> 2  d10 --> 10  d2 --> 18
    d19 --> 3  d11 --> 11  d3 --> 19
    d20 --> 4  d12 --> 12  d4 --> 20
    d21 --> 5  d13 --> 13  d5 --> 21
    d22 --> 6  d14 --> 14  d6 --> 22
    d23 --> 7  d15 --> 15  d7 --> 23
    -------------------------------------------------*/
    s_input_pin_map.fill( INVALID_BIT_FIELD );

    s_input_pin_map[ EnumValue( InputPin::BATT_CHG_GOOD ) ]    = ( 1u << 17 );
    s_input_pin_map[ EnumValue( InputPin::BATT_PWR_GOOD ) ]    = ( 1u << 16 );
    s_input_pin_map[ EnumValue( InputPin::KEY_ENC_0 ) ]        = ( 1u << 23 );
    s_input_pin_map[ EnumValue( InputPin::KEY_ENC_1 ) ]        = ( 1u << 22 );
    s_input_pin_map[ EnumValue( InputPin::KEY_USER_0 ) ]       = ( 1u << 20 );
    s_input_pin_map[ EnumValue( InputPin::KEY_USER_1 ) ]       = ( 1u << 21 );
    s_input_pin_map[ EnumValue( InputPin::PITCH_TRIM_UP ) ]    = ( 1u << 14 );
    s_input_pin_map[ EnumValue( InputPin::PITCH_TRIM_DN ) ]    = ( 1u << 12 );
    s_input_pin_map[ EnumValue( InputPin::ROLL_TRIM_UP ) ]     = ( 1u << 19 );
    s_input_pin_map[ EnumValue( InputPin::ROLL_TRIM_DN ) ]     = ( 1u << 15 );
    s_input_pin_map[ EnumValue( InputPin::YAW_TRIM_UP ) ]      = ( 1u << 8 );
    s_input_pin_map[ EnumValue( InputPin::YAW_TRIM_DN ) ]      = ( 1u << 10 );
    s_input_pin_map[ EnumValue( InputPin::THROTTLE_TRIM_UP ) ] = ( 1u << 11 );
    s_input_pin_map[ EnumValue( InputPin::THROTTLE_TRIM_DN ) ] = ( 1u << 6 );
    s_input_pin_map[ EnumValue( InputPin::USER_SW_A ) ]        = ( 1u << 7 );
    s_input_pin_map[ EnumValue( InputPin::USER_SW_B ) ]        = ( 1u << 9 );
    s_input_pin_map[ EnumValue( InputPin::USER_SW_C ) ]        = ( 1u << 13 );
    s_input_pin_map[ EnumValue( InputPin::USER_SW_D ) ]        = ( 1u << 18 );

    /*-------------------------------------------------
    Initialize the Output shift register pin map.
    -------------------------------------------------*/
    s_output_pin_map.fill( INVALID_BIT_FIELD );

    /* Assumes SPI transfers are MSB */
    s_output_pin_map[ EnumValue( OutputPin::DBG_LED_2 ) ]   = ( 1u << 7 );
    s_output_pin_map[ EnumValue( OutputPin::DBG_LED_1 ) ]   = ( 1u << 6 );
    s_output_pin_map[ EnumValue( OutputPin::DBG_LED_0 ) ]   = ( 1u << 5 );
    s_output_pin_map[ EnumValue( OutputPin::BATT_CHG_EN ) ] = ( 1u << 4 );
    s_output_pin_map[ EnumValue( OutputPin::BT_PWR_EN ) ]   = ( 1u << 1 );
    s_output_pin_map[ EnumValue( OutputPin::RF24_PWR_EN ) ] = ( 1u << 0 );
  }


  uint32_t pinToBitField( const InputPin pin )
  {
    return ( pin < InputPin::NUM_PINS ) ? s_input_pin_map[ EnumValue( pin ) ] : INVALID_BIT_FIELD;
  }


  uint32_t pinToBitField( const OutputPin pin )
  {
    return ( pin < OutputPin::NUM_PINS ) ? s_output_pin_map[ EnumValue( pin ) ] : INVALID_BIT_FIELD;
  }
}  // namespace DC::GPIO
