/********************************************************************************
 *  File Name:
 *    tsk_kernel.cpp
 *
 *  Description:
 *    Main kernel thread implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>

/* Testing Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_kernel.hpp>
#include <src/tasks/tsk_background.hpp>

namespace DC::Tasks::KERNEL
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t KERNEL_TIMEOUT_1S = Chimera::Thread::TIMEOUT_1S / RUN_PERIOD;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void KernelThread( void *arg )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( TSK_KERNEL_START_DELAY_MS );
    LOG_INFO( "Starting Kernel\r\n" );

    /*-----------------------------------------------------------------
    Run the core of the kernel
    -----------------------------------------------------------------*/
    size_t lastWoken = Chimera::millis();
    size_t t1SecTimer = KERNEL_TIMEOUT_1S;

    while ( 1 )
    {
      lastWoken = Chimera::millis();

      /*-------------------------------------------------
      Execute functions at kernel tick rate
      -------------------------------------------------*/
      REG::doPeriodicProcessing();

      /*-------------------------------------------------
      Execute functions every second
      -------------------------------------------------*/
      t1SecTimer--;
      if( ( t1SecTimer == 0 ) || ( t1SecTimer > KERNEL_TIMEOUT_1S ) )
      {
        t1SecTimer = KERNEL_TIMEOUT_1S;
        //LOG_INFO( "Kernel 1 sec msg\r\n" );
      }

      Chimera::delayUntil( lastWoken + RUN_PERIOD );
    }
  }
}    // namespace DC::Tasks::KERNEL
