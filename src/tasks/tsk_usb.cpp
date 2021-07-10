/********************************************************************************
 *  File Name:
 *    tsk_usb.cpp
 *
 *  Description:
 *    Implements the USB thread
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/spi>
#include <Chimera/thread>

/* TinyUSB Includes */
#include <tusb.h>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_background.hpp>

namespace DC::Tasks::USB
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void USBThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 1000 );

    /*-------------------------------------------------
    Power up the USB stack
    -------------------------------------------------*/
    LOG_INFO( "Booting USB thread\r\n" );
    tusb_init();

    while( 1 )
    {
      /*-------------------------------------------------
      Periodically update the USB stack
      -------------------------------------------------*/
      tud_task();

      BKGD::kickDog( PrjTaskId::USB );
      Chimera::delayMilliseconds( 10 );
    }
  }

}  // namespace DC::Tasks::USB
