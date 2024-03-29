/********************************************************************************
 *  File Name:
 *    sys_debug.cpp
 *
 *  Description:
 *    Debug functionality implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Project Includes */
#include <src/registry/reg_intf.hpp>
#include <src/debug/sys_debug.hpp>
#include <src/debug/io_debug_observables.hpp>


namespace DC::DBG
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
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
  static Encoder0RotateObserver s_enc_0_rotate_observer;
  static Encoder1RotateObserver s_enc_1_rotate_observer;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void registerDebugObservers()
  {
    using namespace DC::REG;

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
    ObservablePointer( SwitchDToggle )->add_observer( s_switch_d_observer );
    ObservablePointer( Encoder0Btn )->add_observer( s_enc_0_observer );
    ObservablePointer( Encoder1Btn )->add_observer( s_enc_1_observer );
    ObservablePointer( Encoder0Rotation )->add_observer( s_enc_0_rotate_observer );
    ObservablePointer( Encoder1Rotation )->add_observer( s_enc_1_rotate_observer );
  }


  void doPeriodicDebugProcessing()
  {
  }

}    // namespace DC::DBG
