/********************************************************************************
 *  File Name:
 *    tsk_common.hpp
 *
 *  Description:
 *    Common header shared among task files. Mostly contains descriptive info.
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
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
  Enumerations
  -------------------------------------------------------------------------------*/
  /**
   *  List of threads that are running on the system. Can be used to
   *  index into various thread resources as well.
   */
  enum class TaskId : uint8_t
  {
    MONITOR,    /**< Task monitor thread to ensure everything is running on time */
    HEART_BEAT, /**< Heartbeat thread indicates the system is alive */
    GRAPHICS,   /**< Graphics processing */

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
   *  @return Chimera::Threading::ThreadId
   */
  Chimera::Threading::ThreadId getThreadId( const TaskId task );


}    // namespace DC::Tasks

#endif /* !DC_TASK_COMMON_HPP */
