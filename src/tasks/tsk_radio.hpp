/********************************************************************************
 *  File Name:
 *    tsk_radio.hpp
 *
 *  Description:
 *    Interface to the Monitor task
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_RADIO_HPP
#define DC_TASK_RADIO_HPP

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::RADIO
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                           = STACK_BYTES( 4096 );
  static constexpr std::string_view NAME                  = "radio";
  static constexpr Chimera::Thread::TaskPriority PRIORITY = 3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void RadioThread( void *arg );

}    // namespace DC::Tasks::RADIO

#endif /* !DC_TASK_RADIO_HPP */
