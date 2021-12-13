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
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_file_system.hpp>


struct TestStruct
{
  float mySensor;
  uint32_t timestamp;
  uint32_t logThing;
};

namespace DC::Tasks::FIL
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Thread;
    using namespace Chimera::Interrupt;
    using namespace Chimera::Peripheral;
    using namespace Aurora::Logging;

    /*-------------------------------------------------------------------------
    Wait for the initialization command
    -------------------------------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------------------------------
    Mount the filesystem
    -------------------------------------------------------------------------*/
    //Aurora::FileSystem::massErase();
    Aurora::FileSystem::mount();
    DC::REG::loadRegistryFromFile();
    SYS::updateBootCount();

    /*-------------------------------------------------------------------------
    Program the device configuration
    -------------------------------------------------------------------------*/
    //DC::SYS::configureDevice( DC::SYS::DEV_1 );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();
      BKGD::kickDog( PrjTaskId::FILE_SYSTEM );
      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::FIL
