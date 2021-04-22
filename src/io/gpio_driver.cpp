/********************************************************************************
 *  File Name:
 *    gpio_driver.cpp
 *
 *  Description:
 *    Hardware driver for accessing board GPIO on the Drone Controller
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <type_traits>

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/io/gpio_driver.hpp>
#include <src/io/pin_mapping.hpp>
#include <src/io/sr_driver.hpp>

namespace DC::GPIO
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr uint32_t INPUT_MASK = 0x00FFFFFF;

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  /*-------------------------------------------------
  Technically there are multiple shift registers, but
  due to them sharing a single SPI bus, they will be
  forced to serialize anyways. One lock is enough to
  protect both sets of IO state data.
  -------------------------------------------------*/
  static Chimera::Thread::RecursiveMutex s_sr_lock;

  /*-------------------------------------------------
  IO State Data
  -------------------------------------------------*/
  static uint8_t s_ouput_state;   /**< Single SR output */
  static uint32_t s_input_state;  /**< Triple SR inputs */

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void setShiftRegister( const SR::OutputPin pin )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    uint32_t bitField = SR::pinToBitField( pin );
    if ( ( bitField == SR::INVALID_BIT_FIELD ) || ( bitField > std::numeric_limits<decltype( s_ouput_state )>::max() ) )
    {
      /* Bit didn't exist or the configuration was wrong */
      return;
    }

    /*-------------------------------------------------
    Update the output state
    -------------------------------------------------*/
    s_sr_lock.lock();
    s_ouput_state |= bitField;
    SR::write( &s_ouput_state, sizeof( s_ouput_state ) );
    s_sr_lock.unlock();
  }


  void clearShiftRegister( const SR::OutputPin pin )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    uint32_t bitField = SR::pinToBitField( pin );
    if ( ( bitField == SR::INVALID_BIT_FIELD ) || ( bitField > std::numeric_limits<decltype( s_ouput_state )>::max() ) )
    {
      /* Bit didn't exist or the configuration was wrong */
      return;
    }

    /*-------------------------------------------------
    Update the output state
    -------------------------------------------------*/
    s_sr_lock.lock();
    s_ouput_state &= ~bitField;
    SR::write( &s_ouput_state, sizeof( s_ouput_state ) );
    s_sr_lock.unlock();
  }


  bool getShiftRegister( const SR::InputPin pin )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    uint32_t bitField = SR::pinToBitField( pin );
    if ( ( bitField == SR::INVALID_BIT_FIELD ) || ( bitField > std::numeric_limits<decltype( s_input_state )>::max() ) )
    {
      /* Bit didn't exist or the configuration was wrong */
      return false;
    }

    /*-------------------------------------------------
    Read the current state of the SR
    -------------------------------------------------*/
    s_sr_lock.lock();
    SR::read( &s_input_state, 3 );
    s_input_state &= INPUT_MASK;
    s_sr_lock.unlock();

    /*-------------------------------------------------
    Check if the IO is set
    -------------------------------------------------*/
    return s_input_state & bitField;
  }

}  // namespace DC::GPIO
