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

/* Chimera Includes */
#include <Chimera/adc>
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_button.hpp>
#include <src/hmi/hmi_encoder.hpp>
#include <src/io/gpio_driver.hpp>
#include <src/io/sr_driver.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_common.hpp>

// Testing only
#include <etl/to_string.h>
#include <src/registry/reg_intf.hpp>


namespace DC::Tasks::HMI
{
  volatile int currentPosition = 0;
  volatile bool updated        = false;

  void keyPress( Aurora::HMI::Button::ActiveEdge key )
  {
    using namespace Aurora::Logging;
    LOG_DEBUG( "Key pressed! \r\n" );
  }

  void keyRelease( Aurora::HMI::Button::ActiveEdge key )
  {
    using namespace Aurora::Logging;
    LOG_DEBUG( "Key release! \r\n" );
  }

  void rotate( Aurora::HMI::Encoder::State &state )
  {
    currentPosition = state.absolutePosition;
    updated = true;
  }

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
    // auto pressCB    = Aurora::HMI::Button::EdgeCallback::create<keyPress>();
    // auto releaseCB  = Aurora::HMI::Button::EdgeCallback::create<keyRelease>();
    // auto rotateCB   = Aurora::HMI::Encoder::RotationCallback::create<rotate>();
    // bool initResult = DC::HMI::Encoder::initialize();
    // RT_HARD_ASSERT( initResult );

    // Encoder::onCenterPress( Encoder::Key::ENCODER_1, pressCB );
    // Encoder::onCenterRelease( Encoder::Key::ENCODER_1, releaseCB );
    // Encoder::onRotate( Encoder::Key::ENCODER_1, rotateCB );

    // Encoder::enable( Encoder::Key::ENCODER_1 );

    auto adc = Chimera::ADC::getDriver( Chimera::ADC::Peripheral::ADC_0 );


    size_t debugPrintTick = Chimera::millis();

    while ( true )
    {
      BKGD::kickDog( PrjTaskId::HMI );
      Chimera::delayMilliseconds( 10 );

      /*-------------------------------------------------
      Sample the ADC inputs as fast as this thread
      -------------------------------------------------*/
      adc->startSequence();


      /*-------------------------------------------------
      Print some debug info for testing
      -------------------------------------------------*/
      if( ( Chimera::millis() - debugPrintTick ) > 100 )
      {
        debugPrintTick = Chimera::millis();

        etl::format_spec format;
        format.width(5).precision(4);

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

        //LOG_DEBUG( "ADC -> Pitch: %sV, Roll: %sV, Yaw: %sV, Throttle: %sV\r\n", textP.data(), textR.data(), textY.data(), textT.data() );


        if( !DC::GPIO::getShiftRegister( DC::GPIO::SR::InputPin::KEY_USER_0 ) )
        {
          LOG_DEBUG( "Key 0 press\r\n" );
        }

        if( !DC::GPIO::getShiftRegister( DC::GPIO::SR::InputPin::KEY_USER_1 ) )
        {
          LOG_DEBUG( "Key 1 press\r\n" );
        }
      }

    }
  }
}    // namespace DC::Tasks::HMI
