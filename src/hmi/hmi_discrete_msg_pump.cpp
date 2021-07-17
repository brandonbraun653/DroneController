/********************************************************************************
 *  File Name:
 *    hmi_discrete_msg_pump.cpp
 *
 *  Description:
 *    Message pump for discrete IO events. Locally caches the latest discrete
 *    input edge transition data via a registered callback with the HW driver.
 *    The update function for a system observable will then grab the latest data
 *    and propagate any state changes to registered listeners.
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/hmi>
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/io/pin_mapping.hpp>
#include <src/registry/reg_data.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/hmi/hmi_discrete.hpp>
#include <src/hmi/hmi_discrete_msg_pump.hpp>


namespace DC::HMI::Discrete
{
  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  /**
   * @brief Helper structure for simplifying discrete callback registration
   */
  struct FunctionMap
  {
    DC::GPIO::InputPin pin;
    Aurora::HMI::Button::EdgeCallback func;
  };

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::Thread::Mutex s_data_lock; /**< Thread safety access */
  static ReportedState s_all_states;         /**< Cached IO state */

  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static void notifyPitchTrimUp( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.PitchTrimUp = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.PitchTrimUp = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyPitchTrimDn( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.PitchTrimDn = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.PitchTrimDn = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyRollTrimUp( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.RollTrimUp = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.RollTrimUp = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyRollTrimDn( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.RollTrimDn = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.RollTrimDn = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyYawTrimUp( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.YawTrimUp = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.YawTrimUp = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyYawTrimDn( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.YawTrimDn = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.YawTrimDn = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyThrottleTrimUp( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.ThrottleTrimUp = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.ThrottleTrimUp = Chimera::GPIO::State::LOW;
    }
  }

  static void notifyThrottleTrimDn( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.ThrottleTrimDn = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.ThrottleTrimDn = Chimera::GPIO::State::LOW;
    }
  }


  static void notifySwitchA( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.SwitchAToggle = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.SwitchAToggle = Chimera::GPIO::State::LOW;
    }
  }


  static void notifySwitchB( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.SwitchBToggle = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.SwitchBToggle = Chimera::GPIO::State::LOW;
    }
  }


  static void notifySwitchC( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.SwitchCToggle = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.SwitchCToggle = Chimera::GPIO::State::LOW;
    }
  }


  static void notifySwitchD( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.SwitchDToggle = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.SwitchDToggle = Chimera::GPIO::State::LOW;
    }
  }


  static void notifyEncoder0CenterButton( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.Encoder0Center = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.Encoder0Center = Chimera::GPIO::State::LOW;
    }
  }


  static void notifyEncoder1CenterButton( Aurora::HMI::Button::ActiveEdge edge )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    if ( edge == Aurora::HMI::Button::ActiveEdge::RISING_EDGE )
    {
      s_all_states.Encoder1Center = Chimera::GPIO::State::HIGH;
    }
    else
    {
      s_all_states.Encoder1Center = Chimera::GPIO::State::LOW;
    }
  }

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initMessagePump()
  {
    using namespace Aurora::HMI::Button;
    using namespace DC::GPIO;

    /*-----------------------------------------------------------------
    Locally create the callback functions
    -----------------------------------------------------------------*/
    std::array<FunctionMap, EnumValue( InputPin::NUM_PINS )> init_map = {
      { { InputPin::PITCH_TRIM_UP, EdgeCallback::create<notifyPitchTrimUp>() },
        { InputPin::PITCH_TRIM_DN, EdgeCallback::create<notifyPitchTrimDn>() },
        { InputPin::ROLL_TRIM_DN, EdgeCallback::create<notifyRollTrimDn>() },
        { InputPin::ROLL_TRIM_UP, EdgeCallback::create<notifyRollTrimUp>() },
        { InputPin::YAW_TRIM_UP, EdgeCallback::create<notifyYawTrimUp>() },
        { InputPin::YAW_TRIM_DN, EdgeCallback::create<notifyYawTrimDn>() },
        { InputPin::THROTTLE_TRIM_UP, EdgeCallback::create<notifyThrottleTrimUp>() },
        { InputPin::THROTTLE_TRIM_DN, EdgeCallback::create<notifyThrottleTrimDn>() },
        { InputPin::USER_SW_A, EdgeCallback::create<notifySwitchA>() },
        { InputPin::USER_SW_B, EdgeCallback::create<notifySwitchB>() },
        { InputPin::USER_SW_C, EdgeCallback::create<notifySwitchC>() },
        { InputPin::USER_SW_D, EdgeCallback::create<notifySwitchD>() },
        { InputPin::KEY_ENC_0, EdgeCallback::create<notifyEncoder0CenterButton>() },
        { InputPin::KEY_ENC_1, EdgeCallback::create<notifyEncoder1CenterButton>() } }
    };

    /*-----------------------------------------------------------------
    Register callbacks with the hardware driver
    -----------------------------------------------------------------*/
    for ( size_t x = 0; x < init_map.size(); x++ )
    {
      onPress( init_map[ x ].pin, init_map[ x ].func );
      onRelease( init_map[ x ].pin, init_map[ x ].func );
    }
  }


  void getCurrentState( ReportedState &state )
  {
    Chimera::Thread::LockGuard lck( s_data_lock );
    state = s_all_states;
  }

}    // namespace DC::HMI::Discrete
