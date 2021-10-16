/********************************************************************************
 *  File Name:
 *    tsk_usb.hpp
 *
 *  Description:
 *    Interface to the USB task
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_USB_HPP
#define DC_TASK_USB_HPP

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::USB
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                           = STACK_BYTES( 4096 );
  static constexpr std::string_view NAME                  = "usb";
  static constexpr Chimera::Thread::TaskPriority PRIORITY = 3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void USBThread( void *arg );

}    // namespace DC::Tasks::USB

#endif /* !DC_TASK_USB_HPP */
