/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the file system thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/filesystem>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_file_system.hpp>
#include <src/registry/reg_intf.hpp>


namespace DC::Tasks::FIL
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Threading;
    using namespace Chimera::Interrupt;
    using namespace Chimera::Peripheral;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    this_thread::pendTaskMsg( ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_BLOCK );
    Chimera::delayMilliseconds( 500 );

    /*-------------------------------------------------
    Mount the filesystem
    -------------------------------------------------*/
    Aurora::FileSystem::mount();

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();
      Chimera::delayMilliseconds( lastWoken, 100 );
    }
  }
}    // namespace DC::Tasks::FIL
