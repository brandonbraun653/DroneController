/********************************************************************************
 *  File Name:
 *    startup.cpp
 *
 *  Description:
 *    Drone Controller firmware entry point
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>

/* Segger Includes */
#include "SEGGER_SYSVIEW.h"

/*-------------------------------------------------------------------------------
Public Functions
-------------------------------------------------------------------------------*/
int main()
{
  /*-------------------------------------------------
  Perform peripheral driver system initialization
  -------------------------------------------------*/
  ChimeraInit();

  /*-------------------------------------------------
  Project level task power up
  -------------------------------------------------*/
  DC::Tasks::initialize();

  /*-------------------------------------------------
  Initialize the SystemView driver
  -------------------------------------------------*/
  // SEGGER_SYSVIEW_Conf();

  /*-------------------------------------------------
  Start the system threads. Never returns.
  -------------------------------------------------*/
  Chimera::Thread::startScheduler();
  return 0;
}
