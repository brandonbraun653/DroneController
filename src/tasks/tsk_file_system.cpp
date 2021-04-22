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
#include <Aurora/filesystem_spiffs>
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
    //Aurora::FileSystem::mount();

    /*-------------------------------------------------
    Read out the boot information
    -------------------------------------------------*/
    // SYS::updateBootCount();
    // LOG_DEBUG( "Boot Count: %d\r\n", SYS::getBootCount() );

    std::array<uint8_t, 256> pageDataWrite;
    std::array<uint8_t, 256> pageDataRead;

    auto nor = Aurora::FileSystem::SPIFFS::getDriver();
    nor->erase();

    size_t currentChunk = 0;
    size_t totalErrors = 0;
    size_t totalSuccess = 0;

    size_t lastWoken;
    while ( true )
    {
      /*-------------------------------------------------
      Fill with data
      -------------------------------------------------*/
      std::generate( pageDataWrite.begin(), pageDataWrite.end(), std::rand );
      pageDataRead.fill( 0 );

      /*-------------------------------------------------
      Write data
      -------------------------------------------------*/
      nor->write( currentChunk, 0, pageDataWrite.data(), pageDataWrite.size() );
      nor->read( currentChunk, 0, pageDataRead.data(), pageDataRead.size() );
      if( pageDataRead != pageDataWrite )
      {
        totalErrors++;
        LOG_ERROR( "Failed compare on chunk: %d; Errors: %d; Success: %d\r\n", currentChunk, totalErrors, totalSuccess );
      }
      else
      {
        totalSuccess++;
      }

      currentChunk++;
      if( currentChunk >= 4096 )
      {
        currentChunk = 0;
        nor->erase();
      }

      lastWoken = Chimera::millis();
      Chimera::delayMilliseconds( lastWoken, 100 );
    }
  }
}    // namespace DC::Tasks::FIL
