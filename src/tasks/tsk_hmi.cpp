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
  Aurora::HMI::SR::ShiftInput srInput;

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

    Aurora::HMI::SR::ShifterConfig srCfg;
    srCfg.byteWidth      = 3;
    srCfg.chipSelectPin  = DC::IO::SR::csPin_KeyIn;
    srCfg.chipSelectPort = DC::IO::SR::csPort_KeyIn;
    srCfg.sampleKeyPin   = DC::IO::SR::csPin_KeySample;
    srCfg.sampleKeyPort  = DC::IO::SR::csPort_KeySample;
    srCfg.spiChannel     = DC::IO::SR::spiChannel;
    srCfg.inputMask      = 0xFFFFFFFF;

    Aurora::HMI::SR::InputConfig bitCfg;
    bitCfg.bit          = DC::GPIO::SR::pinToBitField( DC::GPIO::SR::InputPin::KEY_USER_0 );
    bitCfg.polarity     = Aurora::HMI::SR::Polarity::ACTIVE_LOW;
    bitCfg.debounceTime = 25;

    srInput.init( srCfg );
    srInput.configureBit( bitCfg );

    Aurora::HMI::SR::InputEvent bitEvent;

    /*-------------------------------------------------
    Initialize the HMI drivers
    -------------------------------------------------*/
    Encoder::enable( Encoder::Key::ENCODER_0 );
    Encoder::enable( Encoder::Key::ENCODER_1 );

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

      srInput.processHardware();

      if ( srInput.nextEvent( bitEvent ) )
      {
        LOG_DEBUG( "Bit %d event\r\n", Aurora::Math::maxBitSet( bitEvent.bit ) );
      }

      /*-------------------------------------------------
      Dump the encoder data
      -------------------------------------------------*/
      Aurora::HMI::Encoder::State event;
      if ( Encoder::nextEvent( Encoder::Key::ENCODER_0, event ) )
      {
        LOG_DEBUG( "Encoder 0 Position: %d\r\n", event.absolutePosition );
      }

      if ( Encoder::nextEvent( Encoder::Key::ENCODER_1, event ) )
      {
        LOG_DEBUG( "Encoder 1 Position: %d\r\n", event.absolutePosition );
      }

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

        //LOG_DEBUG( "ADC -> Pitch: %sV, Roll: %sV, Yaw: %sV, Throttle: %sV\r\n", textP.data(), textR.data(), textY.data(), textT.data() );


        // if ( !DC::GPIO::getShiftRegister( DC::GPIO::SR::InputPin::KEY_USER_0 ) )
        // {
        //   LOG_DEBUG( "Key 0 press\r\n" );
        // }

        // if ( !DC::GPIO::getShiftRegister( DC::GPIO::SR::InputPin::KEY_USER_1 ) )
        // {
        //   LOG_DEBUG( "Key 1 press\r\n" );
        // }
      }
    }
  }
}    // namespace DC::Tasks::HMI
