/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the graphics thread
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

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
  }
}    // namespace DC::Tasks::GFX
