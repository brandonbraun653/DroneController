/********************************************************************************
 *  File Name:
 *    hmi_sticks.cpp
 *
 *  Description:
 *    Reads the joysticks and populates the information into the global registry
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/adc>
#include <Chimera/gpio>

/* Project Includes */
#include <src/registry/reg_intf.hpp>
#include <src/hmi/hmi_sticks.hpp>
#include <src/config/bsp/board_map.hpp>


namespace DC::HMI::JoyStick
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::ADC::SampleList s_adc_samples;
  static Chimera::ADC::ChannelList s_adc_channels;

  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static void adc_isr_handler( const Chimera::ADC::InterruptDetail &detail );

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initialize()
  {
    using namespace Aurora::Logging;
    using namespace Chimera;
    using namespace DC::IO::HMI;

    /*-------------------------------------------------
    Initialize Module Memory
    -------------------------------------------------*/
    s_adc_samples.fill( {} );
    s_adc_channels.fill( ADC::Channel::UNKNOWN );

    /*-------------------------------------------------
    Initialize the GPIO to act as analog inputs
    -------------------------------------------------*/
    {
      GPIO::Driver_rPtr gpio;
      GPIO::PinInit cfg;

      /* Pitch */
      cfg          = DC::IO::HMI::CommonAnalogCfg;
      cfg.port     = DC::IO::HMI::JoyStick::portPitch;
      cfg.pin      = DC::IO::HMI::JoyStick::pinPitch;
      cfg.validity = true;

      gpio = GPIO::getDriver( cfg.port, cfg.pin );
      gpio->init( cfg );

      /* Roll */
      cfg          = DC::IO::HMI::CommonAnalogCfg;
      cfg.port     = DC::IO::HMI::JoyStick::portRoll;
      cfg.pin      = DC::IO::HMI::JoyStick::pinRoll;
      cfg.validity = true;

      gpio = GPIO::getDriver( cfg.port, cfg.pin );
      gpio->init( cfg );

      /* Yaw */
      cfg          = DC::IO::HMI::CommonAnalogCfg;
      cfg.port     = DC::IO::HMI::JoyStick::portYaw;
      cfg.pin      = DC::IO::HMI::JoyStick::pinYaw;
      cfg.validity = true;

      gpio = GPIO::getDriver( cfg.port, cfg.pin );
      gpio->init( cfg );

      /* Throttle */
      cfg          = DC::IO::HMI::CommonAnalogCfg;
      cfg.port     = DC::IO::HMI::JoyStick::portThrottle;
      cfg.pin      = DC::IO::HMI::JoyStick::pinThrottle;
      cfg.validity = true;

      gpio = GPIO::getDriver( cfg.port, cfg.pin );
      gpio->init( cfg );
    }

    /*-------------------------------------------------
    Configure the ADC driver
    -------------------------------------------------*/
    {
      ADC::Driver_rPtr adc;
      ADC::DriverConfig cfg;
      ADC::SequenceInit seq;

      /* Core configuration */
      cfg.clear();
      cfg.bmISREnable         = ADC::Interrupt::EOC_SEQUENCE | ADC::Interrupt::EOC_SINGLE | ADC::Interrupt::OVERRUN;
      cfg.clockPrescale       = ADC::Prescaler::DIV_2;
      cfg.clockSource         = Chimera::Clock::Bus::PCLK2;
      cfg.defaultSampleCycles = 24;
      cfg.oversampleRate      = ADC::Oversampler::OS_NONE;
      cfg.periph              = ADC::Peripheral::ADC_0;
      cfg.resolution          = ADC::Resolution::BIT_12;
      cfg.transferMode        = ADC::TransferMode::INTERRUPT;

      adc = ADC::getDriver( cfg.periph );
      LOG_ERROR_IF( adc->open( cfg ) != Chimera::Status::OK, "Failed ADC driver init\r\n" );

      /* Attach project side interrupt handler */
      adc->onInterrupt( cfg.bmISREnable, ADC::ISRCallback::create<adc_isr_handler>() );

      /* Configure the sequence conversion */
      s_adc_channels[ 0 ] = DC::IO::HMI::JoyStick::adcPitch;
      s_adc_channels[ 1 ] = DC::IO::HMI::JoyStick::adcRoll;
      s_adc_channels[ 2 ] = DC::IO::HMI::JoyStick::adcYaw;
      s_adc_channels[ 3 ] = DC::IO::HMI::JoyStick::adcThrottle;

      seq.clear();
      seq.channels    = &s_adc_channels;
      seq.numChannels = 4;
      seq.mode        = ADC::SamplingMode::ONE_SHOT;

      adc->configSequence( seq );
      adc->onInterrupt( ADC::Interrupt::EOC_SEQUENCE, ADC::ISRCallback::create<adc_isr_handler>() );
    }
  }


  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  /**
   * @brief Processes sampled ADC data
   *
   * This function is registered as a callback with the ADC driver's userspace
   * interrupt handler, allowing normal multi-tasking operations to be used
   * safely.
   *
   * @param detail    Details about the interrupt event
   */
  static void adc_isr_handler( const Chimera::ADC::InterruptDetail &detail )
  {
    using namespace DC::REG;

    /*-------------------------------------------------
    Grab the ADC driver
    -------------------------------------------------*/
    auto adc = Chimera::ADC::getDriver( Chimera::ADC::Peripheral::ADC_0 );
    if( !adc )
    {
      return;
    }

    /*-------------------------------------------------
    Populate the registry with the new data
    -------------------------------------------------*/
    float voltage = adc->toVoltage( detail.data );


    switch( detail.channel )
    {
      case DC::IO::HMI::JoyStick::adcPitch:
        DC::REG::writeSafe( KEY_ANALOG_IN_PITCH, &voltage, sizeof( voltage ) );
        break;

      case DC::IO::HMI::JoyStick::adcRoll:
        DC::REG::writeSafe( KEY_ANALOG_IN_ROLL, &voltage, sizeof( voltage ) );
        break;

      case DC::IO::HMI::JoyStick::adcYaw:
        DC::REG::writeSafe( KEY_ANALOG_IN_YAW, &voltage, sizeof( voltage ) );
        break;

      case DC::IO::HMI::JoyStick::adcThrottle:
        DC::REG::writeSafe( KEY_ANALOG_IN_THROTTLE, &voltage, sizeof( voltage ) );
        break;

      default:
        break;
    };
  }
}    // namespace DC::HMI::JoyStick
