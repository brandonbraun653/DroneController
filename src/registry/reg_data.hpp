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

/* Aurora Includes */
#include <Aurora/database>
#include <Aurora/datastore>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t DFLT_OBSERVERS = 5;

  /*-------------------------------------------------------------------------------
  Variables
  -------------------------------------------------------------------------------*/
  extern Aurora::Database::RAM Database;  /**< Database for storing system data */
  extern Aurora::Datastore::Manager Datastore;  /**< */

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum DatabaseKeys : Aurora::Database::Key
  {
    /*-------------------------------------------------
    Simple Stored Data
    -------------------------------------------------*/
    KEY_SIMPLE_START,
    KEY_BOOT_COUNT = KEY_SIMPLE_START,

    KEY_ANALOG_IN_PITCH,
    KEY_ANALOG_IN_ROLL,
    KEY_ANALOG_IN_YAW,
    KEY_ANALOG_IN_THROTTLE,

    /*-------------------------------------------------
    Observable Data
    -------------------------------------------------*/
    KEY_OBSERVABLE_START,
    KEY_BUTTON_UP = KEY_OBSERVABLE_START,
    KEY_BUTTON_DOWN,


    /*-------------------------------------------------
    Miscellaneous
    -------------------------------------------------*/
    NUM_DATABASE_KEYS,
    KEY_INVALID,

    /*-------------------------------------------------
    Aliases
    -------------------------------------------------*/
    KEY_OBSERVABLE_END  = NUM_DATABASE_KEYS,
    KEY_SIMPLE_END = KEY_OBSERVABLE_START,
  };

  /*-------------------------------------------------------------------------------
  Observable Data Class Declarations
  -------------------------------------------------------------------------------*/
  /* clang-format off */
  DECLARE_OBSERVABLE( ButtonDown, uint32_t, KEY_BUTTON_DOWN,  DFLT_OBSERVERS, 50, 100 );
  DECLARE_OBSERVABLE( ButtonUp,   uint32_t, KEY_BUTTON_UP,    DFLT_OBSERVERS, 50, 100 );
  /* clang-format on */

  static Aurora::Datastore::IObservableAttr *const ObservableList[] = {
    OBSERVABLE_PTR( ButtonDown ),
    OBSERVABLE_PTR( ButtonUp ),
  };

}    // namespace DC::REG

#endif /* !DC_REGISTRY_DATA_HPP */
