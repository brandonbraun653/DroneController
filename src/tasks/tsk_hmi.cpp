/********************************************************************************
 *  File Name:
 *    tsk_hmi.cpp
 *
 *  Description:
 *    Implementation of the human-machine interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>
#include <Aurora/math>

/* Chimera Includes */
#include <Chimera/adc>
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_discrete_input.hpp>
#include <src/hmi/hmi_encoder.hpp>
#include <src/io/gpio_driver.hpp>
#include <src/io/shift_register_driver.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_common.hpp>

// Testing only
#include <etl/to_string.h>
#include <src/registry/reg_intf.hpp>



namespace DC::Tasks::HMI
{

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void HumanInterfaceThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;
    using namespace DC::HMI;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 100 );


    /*-------------------------------------------------
    Initialize the HMI drivers
    -------------------------------------------------*/
    auto adc              = Chimera::ADC::getDriver( Chimera::ADC::Peripheral::ADC_0 );
    size_t debugPrintTick = Chimera::millis();


    while ( true )
    {
      BKGD::kickDog( PrjTaskId::HMI );
      Chimera::delayMilliseconds( 10 );

      /*-------------------------------------------------
      Sample the ADC inputs as fast as this thread
      -------------------------------------------------*/
      DC::HMI::Discrete::doPeriodicProcessing();
      DC::HMI::Encoder::doPeriodicProcessing();
      adc->startSequence();


      /*-------------------------------------------------
      Print some debug info for testing
      -------------------------------------------------*/
      if ( ( Chimera::millis() - debugPrintTick ) > 100 )
      {
        debugPrintTick = Chimera::millis();

        float pitch = 0.0f;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_PITCH, &pitch, sizeof( pitch ) );

        float roll = 0.0f;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_ROLL, &roll, sizeof( roll ) );

        float yaw = 0.0f;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_YAW, &yaw, sizeof( yaw ) );

        float throttle = 0.0f;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_THROTTLE, &throttle, sizeof( throttle ) );

        LOG_DEBUG( "ADC -> Pitch: %fV, Roll: %fV, Yaw: %fV, Throttle: %fV\r\n", pitch, roll, yaw, throttle );
      }
    }
  }
}    // namespace DC::Tasks::HMI
