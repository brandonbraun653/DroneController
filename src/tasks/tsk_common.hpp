/********************************************************************************
 *  File Name:
 *    tsk_common.hpp
 *
 *  Description:
 *    Common header shared among task files. Mostly contains descriptive info.
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_COMMON_HPP
#define DC_TASK_COMMON_HPP

/* STL Includes */
#include <cstdint>

/* Chimera Includes */
#include <Chimera/thread>

namespace DC::Tasks
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t TSK_KERNEL_START_DELAY_MS = 1000;
  static constexpr size_t TSK_SYSTEM_START_DELAY_MS = 1500;

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  /**
   *  List of threads that are running on the system. Can be used to
   *  index into various thread resources as well.
   */
  enum class PrjTaskId : uint8_t
  {
    /* System Thread (Must be first) */
    MONITOR,     /**< Task monitor thread to ensure everything is running on time */

    /* User Threads */
    FILE_SYSTEM, /**< File system processing */
    HEART_BEAT,  /**< Heartbeat thread indicates the system is alive */
    HMI,         /**< Human machine interface processing */
    RADIO,       /**< NRF24L01 Radio processing */
    BLUETOOTH,   /**< RN4871 bluetooth processing */
    USB,         /**< USB processing */
    SYSTEM,      /**< System level processing */
    KERNEL,      /**< Handles critical functions */

    NUM_OPTIONS,
    UNKNOWN
  };

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Creates the system tasks and initializes thread resources
   *  @return void
   */
  void initialize();

  /**
   *  Helper function to instruct the current task to wait for
   *  an initialization message to be passed to it.
   *
   *  @return void
   */
  void waitInit();

  /**
   *  Gets the system thread identifier, assigned during boot.
   *
   *  @param[in]  task        Which task to look up
   *  @return Chimera::Thread::TaskId
   */
  Chimera::Thread::TaskId getTaskId( const PrjTaskId task );

}    // namespace DC::Tasks

#endif /* !DC_TASK_COMMON_HPP */
