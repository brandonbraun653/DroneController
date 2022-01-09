/********************************************************************************
 *  File Name:
 *    tsk_kernel.cpp
 *
 *  Description:
 *    Main kernel thread implementation
 *
 *  2021-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/logging>
#include <Chimera/common>
#include <src/config/bsp/board_map.hpp>
#include <src/network/net_data_package.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_kernel.hpp>

namespace DC::Tasks::KERNEL
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr int KERNEL_TIMEOUT_50MS  = ( 50 * Chimera::Thread::TIMEOUT_1MS ) / RUN_PERIOD;
  static constexpr int KERNEL_TIMEOUT_250MS = ( 250 * Chimera::Thread::TIMEOUT_1MS ) / RUN_PERIOD;
  static constexpr int KERNEL_TIMEOUT_1S    = Chimera::Thread::TIMEOUT_1S / RUN_PERIOD;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void KernelThread( void *arg )
  {
    /*-------------------------------------------------------------------------
    Block until system initialization is complete
    -------------------------------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( TSK_KERNEL_START_DELAY_MS );
    LOG_INFO( "Starting Kernel\r\n" );

    /*-------------------------------------------------------------------------
    Run the core of the kernel
    -------------------------------------------------------------------------*/
    size_t lastWoken   = Chimera::millis();
    int    t50msTimer  = KERNEL_TIMEOUT_50MS;
    int    t250msTimer = KERNEL_TIMEOUT_250MS;
    int    t1SecTimer  = KERNEL_TIMEOUT_1S;

    while ( 1 )
    {
      lastWoken = Chimera::millis();

      /*-----------------------------------------------------------------------
      Execute functions at the kernel tick rate
      -----------------------------------------------------------------------*/
      REG::doPeriodicProcessing();

      /*-----------------------------------------------------------------------
      Execute functions at 50ms intervals
      -----------------------------------------------------------------------*/
      t50msTimer--;
      if( t50msTimer <0 )
      {
        t50msTimer = KERNEL_TIMEOUT_50MS;
        DC::NET::procStickInputs();
      }

      /*-----------------------------------------------------------------------
      Execute functions at 250ms intervals
      -----------------------------------------------------------------------*/
      t250msTimer--;
      if ( t250msTimer < 0 )
      {
        t250msTimer = KERNEL_TIMEOUT_250MS;
        DC::NET::procStateData();
      }

      /*-----------------------------------------------------------------------
      Execute functions at 1 second intervals
      -----------------------------------------------------------------------*/
      t1SecTimer--;
      if ( t1SecTimer < 0 )
      {
        t1SecTimer = KERNEL_TIMEOUT_1S;
        // LOG_INFO( "Kernel 1 sec msg\r\n" );
      }

      Chimera::delayUntil( lastWoken + RUN_PERIOD );
    }
  }
}    // namespace DC::Tasks::KERNEL
