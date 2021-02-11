/********************************************************************************
 *  File Name:
 *    tsk_hmi.hpp
 *
 *  Description:
 *    Human machine interface threads
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_HUMAN_INTERFACE_HPP
#define DC_HUMAN_INTERFACE_HPP

/* STL Includes */
#include <cstddef>
#include <string_view>

/* Chimera Includes */
#include <Chimera/thread>

namespace DC::Tasks::HMI
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                          = STACK_BYTES( 4096 );
  static constexpr std::string_view NAME                 = "hmi";
  static constexpr Chimera::Thread::Priority PRIORITY = Chimera::Thread::Priority::LEVEL_3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void HumanInterfaceThread( void *arg );

}    // namespace DC::Tasks::FIL

#endif /* !DC_HUMAN_INTERFACE_HPP */
