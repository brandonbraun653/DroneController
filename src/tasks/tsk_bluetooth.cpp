/********************************************************************************
 *  File Name:
 *    tsk_bluetooth.cpp
 *
 *  Description:
 *    Implements the bluetooth threading functions
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_bluetooth.hpp>
#include <src/wireless/bluetooth/bt_driver.hpp>

namespace DC::Tasks::BT
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void BluetoothThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------
    Power up the bluetooth driver
    -------------------------------------------------*/
    //RF::BT::doPowerOnReset();

    while ( 1 )
    {
      BKGD::kickDog( PrjTaskId::BLUETOOTH );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
