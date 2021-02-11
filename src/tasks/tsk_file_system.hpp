/********************************************************************************
 *  File Name:
 *    tsk_file_system.hpp
 *
 *  Description:
 *    Interface for the file system task
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_FILE_SYSTEM_THREAD_HPP
#define DC_FILE_SYSTEM_THREAD_HPP

/* STL Includes */
#include <cstddef>
#include <string_view>

/* Chimera Includes */
#include <Chimera/thread>

namespace DC::Tasks::FIL
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                          = STACK_BYTES( 2048 );
  static constexpr std::string_view NAME                 = "filesystem";
  static constexpr Chimera::Thread::Priority PRIORITY = Chimera::Thread::Priority::LEVEL_3;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void FileSystemThread( void *arg );

}    // namespace DC::Tasks::FIL

#endif /* !DC_FILE_SYSTEM_THREAD_HPP */
