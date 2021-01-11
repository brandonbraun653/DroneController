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

/*-------------------------------------------------------------------------------
Public Functions
-------------------------------------------------------------------------------*/
int main()
{
  /*-------------------------------------------------
  Perform peripheral driver system initalization
  -------------------------------------------------*/
  ChimeraInit();

  /*-------------------------------------------------
  Project level task power up
  -------------------------------------------------*/
  //DC::Tasks::initialize();

  /*-------------------------------------------------
  Start the system threads. Never returns.
  -------------------------------------------------*/
  Chimera::Threading::startScheduler();
  return 0;
}
