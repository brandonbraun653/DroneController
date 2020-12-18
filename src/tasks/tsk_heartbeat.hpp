/********************************************************************************
 *  File Name:
 *    tsk_heartbeat.hpp
 *
 *  Description:
 *    Blinky thread to let tester know the hardware hasn't died
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_HEARTBEAT_HPP
#define DC_TASK_HEARTBEAT_HPP

/* STL Includes */
#include <cstddef>
#include <string_view>

/* Chimera Includes */
#include <Chimera/thread>

namespace DC::Tasks::HB
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                          = STACK_BYTES( 250 );
  static constexpr std::string_view NAME                 = "heartbeat";
  static constexpr Chimera::Threading::Priority PRIORITY = Chimera::Threading::Priority::LEVEL_1;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void HeartBeatThread( void *arg );

}    // namespace DC::Tasks::HB

#endif /* !DC_TASK_HEARTBEAT_HPP */
