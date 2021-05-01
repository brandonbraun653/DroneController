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
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------
    Mount the filesystem
    -------------------------------------------------*/
    //Aurora::FileSystem::massErase();
    Aurora::FileSystem::mount();
    SYS::updateBootCount();

    /*-------------------------------------------------
    Test the file interface
    -------------------------------------------------*/
    TestStruct dataWrite, dataRead;

    memset( &dataRead, 0, sizeof( TestStruct ) );
    dataWrite.logThing = 14928;
    dataWrite.mySensor = 3.14159f;
    dataWrite.timestamp = Chimera::millis();


    Aurora::FileSystem::BinaryFile file;
    file.create( "test_file.bin" );
    file.open( "test_file.bin", "wb" );
    file.write( &dataWrite, sizeof( TestStruct ) );
    file.close();

    file.open( "test_file.bin", "rb" );
    file.read( &dataRead, sizeof( TestStruct ) );
    file.close();

    if( memcmp( &dataWrite, &dataRead, sizeof( TestStruct ) ) == 0 )
    {
      LOG_DEBUG( "File save PASS\r\n" );
    }
    else
    {
      LOG_DEBUG( "File save FAIL\r\n" );
    }

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();
      BKGD::kickDog( PrjTaskId::FILE_SYSTEM );
      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::FIL
