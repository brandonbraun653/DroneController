/********************************************************************************
 *  File Name:
 *    reg_data.hpp
 *
 *  Description:
 *    Registry data type declarations
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_REGISTRY_DATA_HPP
#define DC_REGISTRY_DATA_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/database>
#include <Aurora/datastore>
#include <Aurora/hmi>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t DFLT_OBSERVERS = 5; /**< Max number of registerable observers per key */

  /*-------------------------------------------------------------------------------
  Variables
  -------------------------------------------------------------------------------*/
  extern Aurora::Database::RAM Database;       /**< Database for storing system data */
  extern Aurora::Datastore::Manager Datastore; /**< Manages runtime operation of the registry */

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum DatabaseKeys : Aurora::Database::Key
  {
    /*-------------------------------------------------
    Simple Stored Data
    -------------------------------------------------*/
    KEY_SIMPLE_START,
    KEY_BOOT_COUNT = KEY_SIMPLE_START, /**< Boot count for the system */
    KEY_ANALOG_IN_PITCH,               /**< Pitch stick analog value */
    KEY_ANALOG_IN_ROLL,                /**< Roll stick analog value */
    KEY_ANALOG_IN_YAW,                 /**< Yaw stick analog value */
    KEY_ANALOG_IN_THROTTLE,            /**< Throttle stick analog value */
    KEY_BATT_POWER_GOOD,               /**< Battery charger PWR GOOD signal */
    KEY_BATT_CHARGE_GOOD,              /**< Battery charger CHG GOOD signal */
    KEY_BATT_VOLTAGE_SENSE,            /**< Battery analog voltage sense */
    KEY_ENCODER_0_STATE,               /**< State data for the first rotary encoder */
    KEY_ENCODER_1_STATE,               /**< State data for the second rotary encoder */
    KEY_RF24_CONFIG,                   /**< NRF24 radio configuration */
    KEY_UNIT_INFO,                     /**< Information about the unit */

    /*-------------------------------------------------
    Observable Data/Events
    -------------------------------------------------*/
    KEY_OBSERVABLE_START,
    KEY_PITCH_TRIM_UP = KEY_OBSERVABLE_START, /**< Pitch trim up discrete event */
    KEY_PITCH_TRIM_DN,                        /**< Pitch trim down discrete event */
    KEY_ROLL_TRIM_UP,                         /**< Roll trim up discrete event */
    KEY_ROLL_TRIM_DN,                         /**< Roll trim down discrete event */
    KEY_YAW_TRIM_UP,                          /**< Yaw trim up discrete event */
    KEY_YAW_TRIM_DN,                          /**< Yaw trim down discrete event */
    KEY_THROTTLE_TRIM_UP,                     /**< Throttle trim up discrete event */
    KEY_THROTTLE_TRIM_DN,                     /**< Throttle trim down discrete event */
    KEY_SWITCH_A_TOGGLE,                      /**< User switch A toggle state event */
    KEY_SWITCH_B_TOGGLE,                      /**< User switch B toggle state event */
    KEY_SWITCH_C_TOGGLE,                      /**< User switch C toggle state event */
    KEY_SWITCH_D_TOGGLE,                      /**< User switch D toggle state event */
    KEY_ENCODER_0_BTN,                        /**< Encoder 0 center button event */
    KEY_ENCODER_1_BTN,                        /**< Encoder 1 center button event */
    KEY_ENCODER_0_ROTATE,                     /**< Encoder 0 rotation event */
    KEY_ENCODER_1_ROTATE,                     /**< Encoder 1 rotation event */

    /*-------------------------------------------------
    Miscellaneous
    -------------------------------------------------*/
    NUM_DATABASE_KEYS,
    KEY_INVALID,

    /*-------------------------------------------------
    Aliases
    -------------------------------------------------*/
    KEY_OBSERVABLE_END = NUM_DATABASE_KEYS,
    KEY_SIMPLE_END     = KEY_OBSERVABLE_START,
  };

  /*-------------------------------------------------------------------------------
  Observable Data Class Declarations
                      Name              Type                      AccessKey               NumObservers      Rate  Timeout
  -------------------------------------------------------------------------------*/
  /* clang-format off */
  ObservableDeclare( PitchTrimUp,      bool,                           KEY_PITCH_TRIM_UP,      DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( PitchTrimDn,      bool,                           KEY_PITCH_TRIM_DN,      DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( RollTrimUp,       bool,                           KEY_ROLL_TRIM_UP,       DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( RollTrimDn,       bool,                           KEY_ROLL_TRIM_DN,       DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( YawTrimUp,        bool,                           KEY_YAW_TRIM_UP,        DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( YawTrimDn,        bool,                           KEY_YAW_TRIM_DN,        DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( ThrottleTrimUp,   bool,                           KEY_THROTTLE_TRIM_UP,   DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( ThrottleTrimDn,   bool,                           KEY_THROTTLE_TRIM_DN,   DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( SwitchAToggle,    Chimera::GPIO::State,           KEY_SWITCH_A_TOGGLE,    DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( SwitchBToggle,    Chimera::GPIO::State,           KEY_SWITCH_B_TOGGLE,    DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( SwitchCToggle,    Chimera::GPIO::State,           KEY_SWITCH_C_TOGGLE,    DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( SwitchDToggle,    Chimera::GPIO::State,           KEY_SWITCH_D_TOGGLE,    DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( Encoder0Btn,      bool,                           KEY_ENCODER_0_BTN,      DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( Encoder1Btn,      bool,                           KEY_ENCODER_1_BTN,      DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( Encoder0Rotation, Aurora::HMI::Encoder::State,    KEY_ENCODER_0_ROTATE,   DFLT_OBSERVERS,   50,   100 );
  ObservableDeclare( Encoder1Rotation, Aurora::HMI::Encoder::State,    KEY_ENCODER_1_ROTATE,   DFLT_OBSERVERS,   50,   100 );


  static Aurora::Datastore::IObservableAttr *const ObservableList[] = {
    ObservablePointer( PitchTrimUp ),
    ObservablePointer( PitchTrimDn ),
    ObservablePointer( RollTrimUp ),
    ObservablePointer( RollTrimDn ),
    ObservablePointer( YawTrimUp ),
    ObservablePointer( YawTrimDn ),
    ObservablePointer( ThrottleTrimUp ),
    ObservablePointer( ThrottleTrimDn ),
    ObservablePointer( SwitchAToggle ),
    ObservablePointer( SwitchBToggle ),
    ObservablePointer( SwitchCToggle ),
    ObservablePointer( SwitchDToggle ),
    ObservablePointer( Encoder0Btn ),
    ObservablePointer( Encoder1Btn ),
    ObservablePointer( Encoder0Rotation ),
    ObservablePointer( Encoder1Rotation ),
  };
  static_assert( ARRAY_COUNT( ObservableList ) == ( KEY_OBSERVABLE_END - KEY_OBSERVABLE_START ) );
  /* clang-format on */

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void loadRegistryFromFile();
}    // namespace DC::REG

#endif /* !DC_REGISTRY_DATA_HPP */
