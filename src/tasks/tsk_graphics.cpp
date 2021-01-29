/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the graphics thread
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_graphics.hpp>

/* uGFX Includes */
#include "gfx.h"

namespace DC::Tasks::GFX
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void GraphicsThread( void *arg )
  {
    /*-------------------------------------------------
    This function never returns and runs all the needed
    graphics functionality, provided by uGFX.
    -------------------------------------------------*/
    gfxInit();

    coord_t width  = gdispGetWidth();
    coord_t height = gdispGetHeight();
    gdispFillArea( 0, 0, width, height, GFX_BLUE );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      // Add debug leds to the project and set an error code

      Chimera::delayMilliseconds( lastWoken, 100 );
    }
  }
}    // namespace DC::Tasks::GFX
