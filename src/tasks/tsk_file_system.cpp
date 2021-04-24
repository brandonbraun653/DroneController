/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the file system thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <filesystem>
#include <string>

/* Aurora Includes */
#include <Aurora/filesystem>
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/registry/reg_files.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/system/sys_config.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_file_system.hpp>


namespace DC::Tasks::FIL
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Thread;
    using namespace Chimera::Interrupt;
    using namespace Chimera::Peripheral;
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 500 );

    /*-------------------------------------------------
    Mount the filesystem
    -------------------------------------------------*/
    Aurora::FileSystem::mount();

    /*-------------------------------------------------
    Read out the boot information
    -------------------------------------------------*/
    SYS::updateBootCount();
    LOG_DEBUG( "Boot Count: %d\r\n", SYS::getBootCount() );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();
      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::FIL
