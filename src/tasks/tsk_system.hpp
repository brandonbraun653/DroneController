/********************************************************************************
 *  File Name:
 *    tsk_system.hpp
 *
 *  Description:
 *    Interface to the System task
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_SYSTEM_HPP
#define DC_TASK_SYSTEM_HPP

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::SYSTEM
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                           = STACK_BYTES( 4096 );
  static constexpr size_t RUN_PERIOD                      = 50 * Chimera::Thread::TIMEOUT_1MS;
  static constexpr std::string_view NAME                  = "system";
  static constexpr Chimera::Thread::TaskPriority PRIORITY = 3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void SystemThread( void *arg );

}    // namespace DC::Tasks::SYSTEM

#endif /* !DC_TASK_SYSTEM_HPP */
