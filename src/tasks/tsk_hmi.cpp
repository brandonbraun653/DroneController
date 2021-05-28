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
      adc->startSequence();
      DC::HMI::Discrete::doPeriodicProcessing();
      DC::HMI::Encoder::doPeriodicProcessing();

      /*-------------------------------------------------
      Print some debug info for testing
      -------------------------------------------------*/
      if ( ( Chimera::millis() - debugPrintTick ) > 100 )
      {
        debugPrintTick = Chimera::millis();

        etl::format_spec format;
        format.width( 5 ).precision( 4 );

        float pitch = 0.0f;
        etl::string<5> textP;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_PITCH, &pitch, sizeof( pitch ) );
        etl::to_string( pitch, textP, format );

        float roll = 0.0f;
        etl::string<5> textR;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_ROLL, &roll, sizeof( roll ) );
        etl::to_string( roll, textR, format );

        float yaw = 0.0f;
        etl::string<5> textY;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_YAW, &yaw, sizeof( yaw ) );
        etl::to_string( yaw, textY, format );

        float throttle = 0.0f;
        etl::string<5> textT;
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_THROTTLE, &throttle, sizeof( throttle ) );
        etl::to_string( throttle, textT, format );

        // LOG_DEBUG( "ADC -> Pitch: %sV, Roll: %sV, Yaw: %sV, Throttle: %sV\r\n", textP.data(), textR.data(), textY.data(),
        // textT.data() );
      }
    }
  }
}    // namespace DC::Tasks::HMI
