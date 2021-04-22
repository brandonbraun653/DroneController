/********************************************************************************
 *  File Name:
 *    tsk_common.cpp
 *
 *  Description:
 *    Implementation of common task functionality
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/utility>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_bluetooth.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_file_system.hpp>
#include <src/tasks/tsk_heartbeat.hpp>
#include <src/tasks/tsk_hmi.hpp>
#include <src/tasks/tsk_radio.hpp>

namespace DC::Tasks
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::Thread::TaskId s_thread_id[ static_cast<size_t>( PrjTaskId::NUM_OPTIONS ) ];

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initialize()
  {
    using namespace Chimera::Thread;

    TaskConfig cfg;

    /*-------------------------------------------------
    Initialize local memory
    -------------------------------------------------*/
    for ( size_t x = 0; x < ARRAY_COUNT( s_thread_id ); x++ )
    {
      s_thread_id[ x ] = THREAD_ID_INVALID;
    }

    /*-------------------------------------------------
    System Thread: Background
    -------------------------------------------------*/
    Task background;

    cfg.arg        = nullptr;
    cfg.function   = BKGD::BackgroundThread;
    cfg.priority   = BKGD::PRIORITY;
    cfg.stackWords = BKGD::STACK;
    cfg.type       = TaskInitType::DYNAMIC;

    cfg.name.clear();
    memcpy( cfg.name.data(), BKGD::NAME.cbegin(), BKGD::NAME.size() );

    background.create( cfg );
    s_thread_id[ EnumValue( PrjTaskId::MONITOR ) ] = background.start();

    /*-------------------------------------------------
    System Thread: Heartbeat
    -------------------------------------------------*/
    Task heartbeat;

    cfg.arg        = nullptr;
    cfg.function   = HB::HeartBeatThread;
    cfg.priority   = HB::PRIORITY;
    cfg.stackWords = HB::STACK;
    cfg.type       = TaskInitType::DYNAMIC;

    cfg.name.clear();
    memcpy( cfg.name.data(), HB::NAME.cbegin(), HB::NAME.size() );

    heartbeat.create( cfg );
    s_thread_id[ EnumValue( PrjTaskId::HEART_BEAT ) ] = heartbeat.start();

    /*-------------------------------------------------
    System Thread: Human Interface
    -------------------------------------------------*/
    Task hmi;

    cfg.arg        = nullptr;
    cfg.function   = HMI::HumanInterfaceThread;
    cfg.priority   = HMI::PRIORITY;
    cfg.stackWords = HMI::STACK;
    cfg.type       = TaskInitType::DYNAMIC;

    cfg.name.clear();
    memcpy( cfg.name.data(), HMI::NAME.cbegin(), HMI::NAME.size() );

    hmi.create( cfg );
    s_thread_id[ EnumValue( PrjTaskId::HMI ) ] = hmi.start();

    /*-------------------------------------------------
    System Thread: Bluetooth
    -------------------------------------------------*/
    Task bt;

    cfg.arg        = nullptr;
    cfg.function   = BT::BluetoothThread;
    cfg.priority   = BT::PRIORITY;
    cfg.stackWords = BT::STACK;
    cfg.type       = TaskInitType::DYNAMIC;

    cfg.name.clear();
    memcpy( cfg.name.data(), BT::NAME.cbegin(), BT::NAME.size() );

    bt.create( cfg );
    s_thread_id[ EnumValue( PrjTaskId::BLUETOOTH ) ] = bt.start();

    /*-------------------------------------------------
    System Thread: Radio
    -------------------------------------------------*/
    Task radio;

    cfg.arg        = nullptr;
    cfg.function   = RADIO::RadioThread;
    cfg.priority   = RADIO::PRIORITY;
    cfg.stackWords = RADIO::STACK;
    cfg.type       = TaskInitType::DYNAMIC;

    cfg.name.clear();
    memcpy( cfg.name.data(), RADIO::NAME.cbegin(), RADIO::NAME.size() );

    radio.create( cfg );
    s_thread_id[ EnumValue( PrjTaskId::RADIO ) ] = radio.start();

    /*-------------------------------------------------
    System Thread: File System
    -------------------------------------------------*/
    Task file;

    cfg.arg        = nullptr;
    cfg.function   = FIL::FileSystemThread;
    cfg.priority   = FIL::PRIORITY;
    cfg.stackWords = FIL::STACK;
    cfg.type       = TaskInitType::DYNAMIC;

    cfg.name.clear();
    memcpy( cfg.name.data(), FIL::NAME.cbegin(), FIL::NAME.size() );

    file.create( cfg );
    s_thread_id[ EnumValue( PrjTaskId::FILE_SYSTEM ) ] = file.start();
  }


  void waitInit()
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Wait for task registration to complete. On the sim
    this happens so fast that trying to receive a task
    message will cause a fault. This is due to tasks
    starting at creation on PCs, but not on embedded.
    -------------------------------------------------*/
#if defined( CHIMERA_SIMULATOR )
    Chimera::delayMilliseconds( 50 );
#endif

    /*-------------------------------------------------
    Wait for the expected task message to arrive
    -------------------------------------------------*/
    TaskMsg msg = ITCMsg::TSK_MSG_NOP;
    while ( true )
    {
      if ( this_thread::receiveTaskMsg( msg, TIMEOUT_BLOCK ) && ( msg == ITCMsg::TSK_MSG_WAKEUP ) )
      {
        break;
      }
      else
      {
        this_thread::yield();
      }
    }
  }


  Chimera::Thread::TaskId getTaskId( const PrjTaskId task )
  {
    if ( !( task < PrjTaskId::NUM_OPTIONS ) )
    {
      return Chimera::Thread::THREAD_ID_INVALID;
    }

    return s_thread_id[ static_cast<size_t>( task ) ];
  }
}    // namespace DC::Tasks
