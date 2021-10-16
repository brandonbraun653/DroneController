/********************************************************************************
 *  File Name:
 *    tsk_kernel.hpp
 *
 *  Description:
 *    Interface to the kernel task
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_KERNEL_HPP
#define DC_TASK_KERNEL_HPP

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::KERNEL
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                           = STACK_BYTES( 4096 );
  static constexpr size_t RUN_PERIOD                      = 10 * Chimera::Thread::TIMEOUT_1MS;
  static constexpr std::string_view NAME                  = "kernel";
  static constexpr Chimera::Thread::TaskPriority PRIORITY = 5;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void KernelThread( void *arg );

}    // namespace DC::Tasks::KERNEL

#endif /* !DC_TASK_KERNEL_HPP */
