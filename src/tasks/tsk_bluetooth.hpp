/********************************************************************************
 *  File Name:
 *    tsK_bluetooth.hpp
 *
 *  Description:
 *    Interface to the Bluetooth task
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_BLUETOOTH_HPP
#define DC_TASK_BLUETOOTH_HPP

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::BT
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                       = STACK_BYTES( 2048 );
  static constexpr std::string_view NAME              = "bluetooth";
  static constexpr Chimera::Thread::Priority PRIORITY = Chimera::Thread::Priority::LEVEL_3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void BluetoothThread( void *arg );

}    // namespace DC::Tasks::BT

#endif /* !DC_TASK_BLUETOOTH_HPP */
