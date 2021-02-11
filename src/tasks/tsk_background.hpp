/********************************************************************************
 *  File Name:
 *    tsk_monitor.hpp
 *
 *  Description:
 *    Interface to the Monitor task
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_MONITOR_HPP
#define DC_TASK_MONITOR_HPP

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::BKGD
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                          = STACK_BYTES( 2048 );
  static constexpr std::string_view NAME                 = "watchdog";
  static constexpr Chimera::Thread::Priority PRIORITY = Chimera::Thread::Priority::LEVEL_0;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void BackgroundThread( void *arg );

  /**
   *  Kicks the software watchdog for the given task
   *
   *  @param[in]  task        Which task to kick
   *  @return void
   */
  void kickDog( const PrjTaskId task );

}    // namespace DC::Tasks::BKGD

#endif /* !DC_TASK_MONITOR_HPP */
