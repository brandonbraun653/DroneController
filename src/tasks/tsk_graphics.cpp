/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the graphics thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_graphics.hpp>

namespace DC::Tasks::GFX
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void GraphicsThread( void *arg )
  {
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Wait for the background thread to wake us
    -------------------------------------------------*/
    waitInit();


    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();
      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::GFX

