/********************************************************************************
 *  File Name:
 *    tsk_system.cpp
 *
 *  Description:
 *    Main system thread implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>

/* Testing Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_system.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/debug/sys_debug.hpp>

namespace DC::Tasks::SYSTEM
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t TSK_TIMEOUT_100MS = Chimera::Thread::TIMEOUT_100MS / RUN_PERIOD;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void SystemThread( void *arg )
  {
    using namespace Chimera::Thread;

    /*-----------------------------------------------------------------
    Perform initialization procedures
    -----------------------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( TSK_SYSTEM_START_DELAY_MS );

    /*-------------------------------------------------
    Start debug processing
    -------------------------------------------------*/
    DC::DBG::registerDebugObservers();


    /*-----------------------------------------------------------------
    Run the core System functions
    -----------------------------------------------------------------*/
    size_t lastWoken = Chimera::millis();
    size_t t100MSTimer = TSK_TIMEOUT_100MS;

    while ( 1 )
    {
      lastWoken = Chimera::millis();

      /*-------------------------------------------------
      Execute functions every 100 ms
      -------------------------------------------------*/
      t100MSTimer--;
      if( ( t100MSTimer == 0 ) || ( t100MSTimer > TSK_TIMEOUT_100MS ) )
      {
        t100MSTimer = TSK_TIMEOUT_100MS;
        DC::DBG::doPeriodicDebugProcessing();
      }

      Chimera::delayUntil( lastWoken + RUN_PERIOD );
    }
  }
}    // namespace DC::Tasks::SYSTEM
