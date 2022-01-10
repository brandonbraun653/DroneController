/******************************************************************************
 *  File Name:
 *    ctrl_intf.cpp
 *
 *  Description:
 *    Controller public facing hardware component interface implementation
 *
 *  2022 | Brandon Braun | brandonbraun653@gmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/utility>
#include <src/controller/ctrl_intf.hpp>
#include <src/controller/ctrl_observers.hpp>
#include <src/registry/reg_data.hpp>

namespace DC::CTRL
{
  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  static JoyStick s_sticks[ EnumValue( DC::HMI::JoyStick::Axis::NUM_OPTIONS ) ]{
    { DC::HMI::JoyStick::Axis::PITCH },
    { DC::HMI::JoyStick::Axis::ROLL },
    { DC::HMI::JoyStick::Axis::YAW },
    { DC::HMI::JoyStick::Axis::THROTTLE },
  };

  static PitchTrimUpObserver s_pitch_trim_up_observer;
  static PitchTrimDnObserver s_pitch_trim_dn_observer;
  static RollTrimUpObserver s_roll_trim_up_observer;
  static RollTrimDnObserver s_roll_trim_dn_observer;
  static YawTrimUpObserver s_yaw_trim_up_observer;
  static YawTrimDnObserver s_yaw_trim_dn_observer;
  static ThrottleTrimUpObserver s_throttle_trim_up_observer;
  static ThrottleTrimDnObserver s_throttle_trim_dn_observer;
  static SwitchAObserver s_switch_a_observer;
  static SwitchBObserver s_switch_b_observer;
  static SwitchCObserver s_switch_c_observer;
  static SwitchDObserver s_switch_d_observer;
  static Encoder0CenterButtonObserver s_enc_0_observer;
  static Encoder1CenterButtonObserver s_enc_1_observer;

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void initController()
  {
    using namespace DC::REG;

    /*-------------------------------------------------------------------------
    Register all observers with their observable. These will generate NET IO
    events to inform the quadrotor that something has occurred from the pilot.
    -------------------------------------------------------------------------*/
    ObservablePointer( PitchTrimUp )->add_observer( s_pitch_trim_up_observer );
    ObservablePointer( PitchTrimDn )->add_observer( s_pitch_trim_dn_observer );
    ObservablePointer( RollTrimUp )->add_observer( s_roll_trim_up_observer );
    ObservablePointer( RollTrimDn )->add_observer( s_roll_trim_dn_observer );
    ObservablePointer( YawTrimUp )->add_observer( s_yaw_trim_up_observer );
    ObservablePointer( YawTrimDn )->add_observer( s_yaw_trim_dn_observer );
    ObservablePointer( ThrottleTrimUp )->add_observer( s_throttle_trim_up_observer );
    ObservablePointer( ThrottleTrimDn )->add_observer( s_throttle_trim_dn_observer );
    ObservablePointer( SwitchAToggle )->add_observer( s_switch_a_observer );
    ObservablePointer( SwitchBToggle )->add_observer( s_switch_b_observer );
    ObservablePointer( SwitchCToggle )->add_observer( s_switch_c_observer );
    ObservablePointer( SwitchDToggle )->add_observer( s_switch_d_observer );
    ObservablePointer( Encoder0Btn )->add_observer( s_enc_0_observer );
    ObservablePointer( Encoder1Btn )->add_observer( s_enc_1_observer );
  }


  JoyStick *getJoyStick( const DC::HMI::JoyStick::Axis type )
  {
    if( type < DC::HMI::JoyStick::Axis::NUM_OPTIONS )
    {
      return &s_sticks[ EnumValue( type ) ];
    }
    else
    {
      return nullptr;
    }
  }

}  // namespace DC::CTRL
