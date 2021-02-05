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

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/exti>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_button.hpp>

namespace DC::HMI::Button
{
  /*-------------------------------------------------------------------------------
  Private Structures
  -------------------------------------------------------------------------------*/
  struct ControlBlock
  {
    bool enabled;                               /**< Key processing enabled */
    Key thisKey;                                /**< Which key this is */
    EventCallback onPress;                      /**< Callback when key is pressed */
    EventCallback onRelease;                    /**< Callback when key is released */
    EventCallback onHold;                       /**< Callback when key is held */
    Chimera::GPIO::State activeState;           /**< GPIO state that is considered as active */
    Chimera::Threading::RecursiveMutex mutex;   /**< Resource lock */
    Aurora::HMI::Button::EdgeTrigger debouncer; /**< GPIO debouncer */

    void clear()
    {
      enabled   = false;
      onPress   = {};
      onRelease = {};
      onHold    = {};
      activeState = Chimera::GPIO::State::LOW;
      debouncer.reset();
    }

    void edgeCallback( Aurora::HMI::Button::ActiveEdge edge )
    {
      using namespace Aurora::HMI::Button;
      using namespace Chimera::GPIO;

      switch( edge )
      {
        case ActiveEdge::RISING_EDGE:
          if( ( activeState == State::HIGH ) && onPress )
          {
            onPress( thisKey );
          }
          else if( onRelease ) // activeState == LOW
          {
            onRelease( thisKey );
          }
          // else no registered callbacks
          break;

        case ActiveEdge::FALLING_EDGE:
          if( ( activeState == State::LOW ) && onPress )
          {
            onPress( thisKey );
          }
          else if( onRelease ) // activeState == HIGH
          {
            onRelease( thisKey );
          }
          // else no registered callbacks
          break;

        default:
          break;
      };
    }
  };

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static ControlBlock s_key_ctrl[ static_cast<size_t>( Key::NUM_OPTIONS ) ];

  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static inline bool keyIsValid( const Key button )
  {
    return button < Key::NUM_OPTIONS;
  }

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  bool initialize()
  {
    using namespace Chimera::GPIO;
    using namespace Aurora::HMI::Button;

    /*-------------------------------------------------
    Reset and then initialize the GPIO for each block
    -------------------------------------------------*/
    for ( auto x = 0; x < ARRAY_COUNT( s_key_ctrl ); x++ )
    {
      Chimera::Status_t result = Chimera::Status::OK;

      /*-------------------------------------------------
      Control block reset
      -------------------------------------------------*/
      s_key_ctrl[ x ].clear();
      s_key_ctrl[ x ].thisKey = static_cast<Key>( x );

      /*-------------------------------------------------
      Prepare the input configuration
      -------------------------------------------------*/
      EdgeConfig config;
      config.gpioConfig = DC::IO::HMI::CommonInputCfg;

      /*-------------------------------------------------
      Set up each key config. The default case will make
      it very obvious at runtime if a key was added but
      not initialized in this function.
      -------------------------------------------------*/
      switch ( s_key_ctrl[ x ].thisKey )
      {
        case Key::TOUCH_KEY_1:
          s_key_ctrl[ x ].activeState = State::LOW;
          config.gpioConfig.pin       = DC::IO::HMI::pinKeyIn0;
          config.gpioConfig.port      = DC::IO::HMI::portKeyIn0;
          config.gpioConfig.validity  = true;
          config.activeEdge           = ActiveEdge::BOTH_EDGES;
          config.debounceTime         = 50;
          config.sampleRate           = 10;
          config.stableSamples        = 3;
          break;

        default:
          RT_HARD_ASSERT( false );
          break;
      };

      /*-------------------------------------------------
      Initialize the GPIO debouncer
      -------------------------------------------------*/
      EdgeCallback cb = EdgeCallback::create<ControlBlock, &ControlBlock::edgeCallback>( s_key_ctrl[ x ] );

      if( s_key_ctrl[ x ].debouncer.initialize( config ) )
      {
        s_key_ctrl[ x ].debouncer.disable();
        s_key_ctrl[ x ].debouncer.onActiveEdge( cb );
      }
      else
      {
        Chimera::insert_debug_breakpoint();
      }
    }

    return true;
  }


  bool onPress( const Key button, EventCallback &cb )
  {
    if ( keyIsValid( button ) )
    {
      auto k = static_cast<size_t>( button );
      s_key_ctrl[ k ].mutex.lock();
      s_key_ctrl[ k ].onPress = cb;
      s_key_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


  bool onRelease( const Key button, EventCallback &cb )
  {
    if ( keyIsValid( button ) )
    {
      auto k = static_cast<size_t>( button );
      s_key_ctrl[ k ].mutex.lock();
      s_key_ctrl[ k ].onRelease = cb;
      s_key_ctrl[ k ].mutex.unlock();
      return true;
    }
    else
    {
      return false;
    }
  }


  bool enable( const Key button )
  {
    auto k = static_cast<size_t>( button );
    if ( keyIsValid( button ) )
    {
      s_key_ctrl[ k ].enabled = true;
      s_key_ctrl[ k ].debouncer.enable();
      return true;
    }
    else
    {
      return false;
    }
  }


  void disable( const Key button )
  {
    auto k = static_cast<size_t>( button );

    if ( keyIsValid( button ) )
    {
      s_key_ctrl[ k ].debouncer.disable();
      s_key_ctrl[ k ].enabled = false;
    }
  }

}    // namespace DC::HMI::Button
