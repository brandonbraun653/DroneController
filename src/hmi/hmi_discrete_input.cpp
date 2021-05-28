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
#include <src/hmi/hmi_discrete_input.hpp>

namespace DC::HMI::Discrete
{
  /*-------------------------------------------------------------------------------
  Private Structures
  -------------------------------------------------------------------------------*/
  struct ControlBlock
  {
    bool enabled;                                /**< Key processing enabled */
    Aurora::HMI::Button::EdgeCallback onPress;   /**< Callback when key is pressed */
    Aurora::HMI::Button::EdgeCallback onRelease; /**< Callback when key is released */
    Chimera::Thread::RecursiveMutex mutex;       /**< Resource lock */

    void clear()
    {
      enabled     = false;
      onPress     = {};
      onRelease   = {};
    }
  };


  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_driver_enabled = false;
  static Aurora::HMI::SR::ShiftInput s_shift_reg;
  static std::array<ControlBlock, EnumValue( GPIO::InputPin::NUM_PINS )>s_btn_ctrl;


  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static inline bool keyIsValid( const GPIO::InputPin button )
  {
    return button < GPIO::InputPin::NUM_PINS;
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

    s_driver_enabled = false;

    /*-------------------------------------------------
    Initialize module memory
    -------------------------------------------------*/
    for( auto &cb : s_btn_ctrl )
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

    result |= s_shift_reg.init( srCfg );

    /*-------------------------------------------------
    Loop through all the input pins and register them
    with the shift register processing.
    -------------------------------------------------*/
    for( size_t pin = EnumValue( GPIO::InputPin::START_PIN ); pin < EnumValue( GPIO::InputPin::NUM_PINS ); pin++ )
    {
      bitCfg.bit          = GPIO::pinToBitField( static_cast<GPIO::InputPin>( pin ) );
      bitCfg.polarity     = Aurora::HMI::SR::Polarity::ACTIVE_LOW;
      bitCfg.debounceTime = 25;

      result |= s_shift_reg.configureBit( bitCfg );
    }

    s_driver_enabled = ( result == Chimera::Status::OK );
    LOG_IF_ERROR( s_driver_enabled, "Failed to initialize discrete input driver\r\n" );

    return s_driver_enabled;
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
    if( !s_driver_enabled )
    {
      return;
    }

    /*-------------------------------------------------
    Allow the HW to post new edge events
    -------------------------------------------------*/
    s_shift_reg.processHardware();

    /*-------------------------------------------------
    Process all generated events
    -------------------------------------------------*/
    Aurora::HMI::SR::InputEvent bitEvent;

    while( s_shift_reg.nextEvent( bitEvent ) )
    {
      /*-------------------------------------------------
      Validate that the bit exists
      -------------------------------------------------*/
      GPIO::InputPin pin = GPIO::bitFieldToInputPin( 1u << bitEvent.bit );
      if( !( pin < GPIO::InputPin::NUM_PINS ) )
      {
        continue;
      }

      /*-------------------------------------------------
      Some helpful debugging logic
      -------------------------------------------------*/
      if ( bitEvent.state == Aurora::HMI::SR::State::ACTIVE )
      {
        LOG_DEBUG( "Bit %d pressed\r\n", bitEvent.bit );
      }
      else
      {
        LOG_DEBUG( "Bit %d released\r\n", bitEvent.bit );
      }

      /*-------------------------------------------------
      Invoke the user callbacks if registered
      -------------------------------------------------*/
      Chimera::Thread::LockGuard lck( s_btn_ctrl[ EnumValue( pin ) ].mutex );

      switch( bitEvent.edge )
      {
        case Aurora::HMI::SR::Edge::RISING:
          if( s_btn_ctrl[ EnumValue( pin ) ].onPress )
          {
            s_btn_ctrl[ EnumValue( pin ) ].onPress( Aurora::HMI::Button::ActiveEdge::RISING_EDGE );
          }
          break;

        case Aurora::HMI::SR::Edge::FALLING:
          if( s_btn_ctrl[ EnumValue( pin ) ].onRelease )
          {
            s_btn_ctrl[ EnumValue( pin ) ].onRelease( Aurora::HMI::Button::ActiveEdge::FALLING_EDGE );
          }
          break;

        default:
          break;
      };
    }
  }

}    // namespace DC::HMI::Button
