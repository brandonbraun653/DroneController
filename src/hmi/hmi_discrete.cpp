/********************************************************************************
 *  File Name:
 *    hmi_button.cpp
 *
 *  Description:
 *    Button/key input processing
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/hmi>
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/exti>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_discrete.hpp>
#include <src/io/shift_register_driver.hpp>
#include <src/io/pin_mapping.hpp>

namespace DC::HMI::Discrete
{
  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using IOState = Chimera::GPIO::State;

  /*-------------------------------------------------------------------------------
  Private Structures
  -------------------------------------------------------------------------------*/
  /**
   * @brief Manages the state of input discrete pins
   */
  struct InputCB
  {
    bool enabled;                                /**< Key processing enabled */
    Aurora::HMI::Button::EdgeCallback onPress;   /**< Callback when key is pressed */
    Aurora::HMI::Button::EdgeCallback onRelease; /**< Callback when key is released */
    Chimera::Thread::RecursiveMutex mutex;       /**< Resource lock */

    void clear()
    {
      enabled   = false;
      onPress   = {};
      onRelease = {};
    }
  };


  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  /**
   * @brief Driver module enable flag
   */
  static bool s_driver_enabled = false;

  /**
   * @brief Input shift register driver
   */
  static Aurora::HMI::SR::ShiftInput s_input_shifter;

  /**
   * @brief State management of all input pins
   */
  static std::array<InputCB, EnumValue( GPIO::InputPin::NUM_PINS )> s_btn_ctrl;

  /**
   * @brief Global copy of all current IO states
   */
  static std::array<IOState, EnumValue( GPIO::Pin::NUM_PINS )> s_pin_states;
  static uint8_t s_last_output_sr_value;

  static Chimera::Thread::Mutex s_pin_state_lock;


  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static inline constexpr bool keyIsValid( const GPIO::InputPin button )
  {
    return button < GPIO::InputPin::NUM_PINS;
  }


  static void updateOutputPins()
  {
    using namespace Chimera::Thread;

    uint8_t output_state = 0;
    LockGuard lck( s_pin_state_lock );

    /*-------------------------------------------------------------------------
    Check the state of each output pin
    -------------------------------------------------------------------------*/
    for ( size_t pin = 0; pin < s_pin_states.size(); pin++ )
    {
      /*-----------------------------------------------------------------------
      Check if pin is an output type
      -----------------------------------------------------------------------*/
      auto outPin = GPIO::pinToOutputId( static_cast<GPIO::Pin>( pin ) );
      if ( outPin == GPIO::OutputPin::NUM_PINS )
      {
        continue;
      }

      /*-----------------------------------------------------------------------
      If the state is high, add it to the output data
      -----------------------------------------------------------------------*/
      if ( s_pin_states[ pin ] == Chimera::GPIO::State::HIGH )
      {
        uint8_t bitField = static_cast<uint8_t>( GPIO::pinToBitField( outPin ) );
        output_state |= bitField;
      }
    }

    /*-------------------------------------------------------------------------
    Update the output state if a change occurred
    -------------------------------------------------------------------------*/
    DC::GPIO::SR::write( &output_state, sizeof( output_state ) );
  }


  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  bool initialize()
  {
    using namespace Chimera::GPIO;
    using namespace Aurora::HMI::Button;

    Aurora::HMI::SR::ShifterConfig srCfg;
    Aurora::HMI::SR::InputConfig bitCfg;
    Chimera::Status_t result = Chimera::Status::OK;

    s_driver_enabled       = false;
    s_last_output_sr_value = 0;

    /*-------------------------------------------------
    Initialize module memory
    -------------------------------------------------*/
    for ( auto &cb : s_btn_ctrl )
    {
      cb.clear();
    }

    /*-------------------------------------------------
    Configure the core shift register input driver
    -------------------------------------------------*/
    srCfg.byteWidth      = 3;
    srCfg.chipSelectPin  = DC::IO::SR::csPin_KeyIn;
    srCfg.chipSelectPort = DC::IO::SR::csPort_KeyIn;
    srCfg.sampleKeyPin   = DC::IO::SR::csPin_KeySample;
    srCfg.sampleKeyPort  = DC::IO::SR::csPort_KeySample;
    srCfg.spiChannel     = DC::IO::SR::spiChannel;
    srCfg.inputMask      = 0xFFFFFFFF;

    result |= s_input_shifter.init( srCfg );

    /*-------------------------------------------------
    Loop through all the input pins and register them
    with the shift register processing.
    -------------------------------------------------*/
    for ( size_t pin = EnumValue( GPIO::InputPin::START_PIN ); pin < EnumValue( GPIO::InputPin::NUM_PINS ); pin++ )
    {
      bitCfg.bit          = GPIO::pinToBitField( static_cast<GPIO::InputPin>( pin ) );
      bitCfg.polarity     = Aurora::HMI::SR::Polarity::ACTIVE_LOW;
      bitCfg.debounceTime = 25;

      result |= s_input_shifter.configureBit( bitCfg );
    }

    /*-------------------------------------------------
    Initialize states of the IO cache
    -------------------------------------------------*/
    s_pin_states.fill( Chimera::GPIO::State::LOW );

    s_driver_enabled = ( result == Chimera::Status::OK );
    LOG_ERROR_IF( !s_driver_enabled, "Failed to initialize discrete input driver\r\n" );

    return s_driver_enabled;
  }


  bool set( const GPIO::Pin pin )
  {
    if ( ( pin < GPIO::Pin::FIRST_OUTPUT_PIN ) || ( pin > GPIO::Pin::LAST_OUTPUT_PIN ) )
    {
      return false;
    }

    Chimera::Thread::LockGuard lck( s_pin_state_lock );
    s_pin_states[ EnumValue( pin ) ] = Chimera::GPIO::State::HIGH;
    return true;
  }


  bool clear( const GPIO::Pin pin )
  {
    if ( ( pin < GPIO::Pin::FIRST_OUTPUT_PIN ) || ( pin > GPIO::Pin::LAST_OUTPUT_PIN ) )
    {
      return false;
    }

    Chimera::Thread::LockGuard lck( s_pin_state_lock );
    s_pin_states[ EnumValue( pin ) ] = Chimera::GPIO::State::LOW;
    return true;
  }


  bool get( const GPIO::Pin pin )
  {
    if ( pin >= GPIO::Pin::NUM_PINS )
    {
      return false;
    }

    Chimera::Thread::LockGuard lck( s_pin_state_lock );
    if ( s_pin_states[ EnumValue( pin ) ] == Chimera::GPIO::State::HIGH )
    {
      return true;
    }
    else
    {
      return false;
    }
  }


  bool onPress( const GPIO::InputPin button, Aurora::HMI::Button::EdgeCallback &cb )
  {
    if ( keyIsValid( button ) )
    {
      auto k = static_cast<size_t>( button );
      s_btn_ctrl[ k ].mutex.lock();
      s_btn_ctrl[ k ].onPress = cb;
      s_btn_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


  bool onRelease( const GPIO::InputPin button, Aurora::HMI::Button::EdgeCallback &cb )
  {
    if ( keyIsValid( button ) )
    {
      auto k = static_cast<size_t>( button );
      s_btn_ctrl[ k ].mutex.lock();
      s_btn_ctrl[ k ].onRelease = cb;
      s_btn_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


  bool enable( const GPIO::InputPin button )
  {
    auto k = static_cast<size_t>( button );
    if ( keyIsValid( button ) )
    {
      s_btn_ctrl[ k ].enabled = true;
      return true;
    }
    else
    {
      return false;
    }
  }


  void disable( const GPIO::InputPin button )
  {
    auto k = static_cast<size_t>( button );

    if ( keyIsValid( button ) )
    {
      s_btn_ctrl[ k ].enabled = false;
    }
  }


  void doPeriodicProcessing( void )
  {
    /*-------------------------------------------------
    Don't do anything before enabled
    -------------------------------------------------*/
    if ( !s_driver_enabled )
    {
      return;
    }

    /*-------------------------------------------------
    Update the output shift registers to new values
    -------------------------------------------------*/
    updateOutputPins();

    /*-------------------------------------------------
    Allow the HW to post new edge events on input pins
    -------------------------------------------------*/
    s_input_shifter.processHardware();

    /*-------------------------------------------------
    Process all generated input pin events
    -------------------------------------------------*/
    Aurora::HMI::SR::InputEvent bitEvent;

    while ( s_input_shifter.nextEvent( bitEvent ) )
    {
      /*-------------------------------------------------
      Validate that the bit exists
      -------------------------------------------------*/
      GPIO::InputPin pin = GPIO::bitFieldToInputPin( 1u << bitEvent.bit );
      if ( !( pin < GPIO::InputPin::NUM_PINS ) )
      {
        continue;
      }

      /*-------------------------------------------------
      Invoke the user callbacks if registered
      -------------------------------------------------*/
      Chimera::Thread::LockGuard lck( s_btn_ctrl[ EnumValue( pin ) ].mutex );

      switch ( bitEvent.edge )
      {
        case Aurora::HMI::SR::Edge::RISING:
          if ( s_btn_ctrl[ EnumValue( pin ) ].onPress )
          {
            s_btn_ctrl[ EnumValue( pin ) ].onPress( Aurora::HMI::Button::ActiveEdge::RISING_EDGE );
          }
          break;

        case Aurora::HMI::SR::Edge::FALLING:
          if ( s_btn_ctrl[ EnumValue( pin ) ].onRelease )
          {
            s_btn_ctrl[ EnumValue( pin ) ].onRelease( Aurora::HMI::Button::ActiveEdge::FALLING_EDGE );
          }
          break;

        default:
          break;
      };
    }
  }

}    // namespace DC::HMI::Discrete
