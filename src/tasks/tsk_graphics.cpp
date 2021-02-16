/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the graphics thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_graphics.hpp>



// TESTING ONLY
#include <filesystem>
#include <ChimeraSim/transport>

namespace DC::Tasks::GFX
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void GraphicsThread( void *arg )
  {
    using namespace Chimera::Thread;
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Wait for the background thread to wake us
    -------------------------------------------------*/
    waitInit();

    std::filesystem::path cfgFile = "./lib/ChimeraSim/source/peripherals/spi/spi_config.json";


    Chimera::SIM::Transport::SynchMasterSlave server;
    server.bootServer( cfgFile.string(), 0 );
    getRootSink()->flog( Level::LVL_DEBUG, "Server initialized\r\n" );


    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::GFX

