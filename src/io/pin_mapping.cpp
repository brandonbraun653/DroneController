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
    Initialize the Input shift register pin map
    -------------------------------------------------*/
    s_input_pin_map.fill( INVALID_BIT_FIELD );

    //s_input_pin_map[ EnumValue( InputPin::BATT_CHG_GOOD ) ] = 0;

    /*-------------------------------------------------
    Initialize the Output shift register pin map
    -------------------------------------------------*/
    s_output_pin_map.fill( INVALID_BIT_FIELD );

    s_output_pin_map[ EnumValue( OutputPin::DBG_LED_2 ) ]   = ( 1u << 0 );
    s_output_pin_map[ EnumValue( OutputPin::DBG_LED_1 ) ]   = ( 1u << 1 );
    s_output_pin_map[ EnumValue( OutputPin::DBG_LED_0 ) ]   = ( 1u << 2 );
    s_output_pin_map[ EnumValue( OutputPin::BATT_CHG_EN ) ] = ( 1u << 3 );
    s_output_pin_map[ EnumValue( OutputPin::BT_PWR_EN ) ]   = ( 1u << 6 );
    s_output_pin_map[ EnumValue( OutputPin::RF24_PWR_EN ) ] = ( 1u << 7 );

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
