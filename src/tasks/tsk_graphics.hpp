/********************************************************************************
 *  File Name:
 *    tsk_graphics.hpp
 *
 *  Description:
 *    Interface for the graphics task
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_GRAPHICS_THREAD_HPP
#define DC_GRAPHICS_THREAD_HPP

/* STL Includes */
#include <cstddef>
#include <string_view>

/* Chimera Includes */
#include <Chimera/thread>

namespace DC::Tasks::GFX
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                          = STACK_BYTES( 5024 );
  static constexpr std::string_view NAME                 = "graphics";
  static constexpr Chimera::Thread::Priority PRIORITY = Chimera::Thread::Priority::LEVEL_3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void GraphicsThread( void *arg );

}    // namespace DC::Tasks::GFX

#endif /* !DC_GRAPHICS_THREAD_HPP */
