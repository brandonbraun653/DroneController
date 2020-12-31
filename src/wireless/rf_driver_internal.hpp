/********************************************************************************
 *  File Name:
 *    rf_driver_internal.hpp
 *
 *  Description:
 *    RF driver interface that is expected to be used internal to the module.
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_WIRELESS_DRIVER_INTERNAL_HPP
#define DC_WIRELESS_DRIVER_INTERNAL_HPP

/* STL Includes */
#include <cstdint>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Ripple Includes */
#include <Ripple/session>
#include <Ripple/datalink>
#include <Ripple/physical>

/* Project Includes */
#include <src/wireless/rf_system_types.hpp>

namespace DC::RF
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum NetTaskId : uint8_t
  {
    TSK_ID_DATALINK,

    TSK_ID_NUM_TASKS,
    TSK_ID_INVALID
  };

  /*-------------------------------------------------------------------------------
  Public Data
  -------------------------------------------------------------------------------*/
  extern Ripple::NetStackHandle netHandle;    /* Network device object */
  extern Ripple::PHY::Handle hPhysical; /* Physical layer handle */

  /* Identifiers for the network threads */
  extern Chimera::Threading::ThreadId netThreadId[ TSK_ID_NUM_TASKS ];

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Starts the networking threads that handle all the runtime processing
   *  of the network stack.
   *
   *  @warning Must have completed the initialization sequence first.
   *  @return Chimera::Status_t
   */
  Chimera::Status_t runNetThreads();

  /**
   *  Prepares the networking services for operation
   *
   *  @param[in]  cfg       User configuration
   *  @return Chimera::Status_t
   */
  Chimera::Status_t initNetStack( const RadioConfig &cfg );

  /**
   *  Initializes the physical layer for the project
   *
   *  @param[in]  cfg       User configuration
   *  @return Chimera::Status_t
   */
  Chimera::Status_t initNetStack_PHY( const RadioConfig &cfg );

  /**
   *  Initializes the datalink layer for the project
   *
   *  @param[in]  cfg       User configuration
   *  @return Chimera::Status_t
   */
  Chimera::Status_t initNetStack_DATALINK( const RadioConfig &cfg );

}  // namespace DC::RF

#endif  /* !DC_WIRELESS_DRIVER_INTERNAL_HPP */
