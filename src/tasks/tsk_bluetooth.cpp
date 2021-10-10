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
#include <src/wireless/bluetooth/rn4871/rn_device.hpp>

namespace DC::Tasks::BT
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void BluetoothThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;

    /*-------------------------------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------------------------------
    Power up the bluetooth manager stack
    -------------------------------------------------------------------------*/
    RN4871::DeviceDriver *bt = nullptr;
    RF::BT::getDevice( &bt );

    TaskId tsk = RN4871::startDevice( *bt, nullptr );
    if( tsk == THREAD_ID_INVALID )
    {
      RT_HARD_ASSERT( false );
    }

    /*-------------------------------------------------------------------------
    Power on the hardware
    -------------------------------------------------------------------------*/
    RF::BT::doPowerOnReset( tsk );

    while ( 1 )
    {
      BKGD::kickDog( PrjTaskId::BLUETOOTH );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
