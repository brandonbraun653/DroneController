/********************************************************************************
 *  File Name:
 *    tsk_common.cpp
 *
 *  Description:
 *    Implementation of common task functionality
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_background.hpp>
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
    background.initialize( BKGD::BackgroundThread, nullptr, BKGD::PRIORITY, BKGD::STACK, BKGD::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( PrjTaskId::MONITOR ) ] = background.start();

    /*-------------------------------------------------
    System Thread: Heartbeat
    -------------------------------------------------*/
    Task heartbeat;
    heartbeat.initialize( HB::HeartBeatThread, nullptr, HB::PRIORITY, HB::STACK, HB::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( PrjTaskId::HEART_BEAT ) ] = heartbeat.start();

    /*-------------------------------------------------
    System Thread: Human Interface
    -------------------------------------------------*/
    Task hmi;
    hmi.initialize( HMI::HumanInterfaceThread, nullptr, HMI::PRIORITY, HMI::STACK, HMI::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( PrjTaskId::HMI ) ] = hmi.start();

    /*-------------------------------------------------
    System Thread: Radio
    -------------------------------------------------*/
    // Task radio;
    // radio.initialize( RADIO::RadioThread, nullptr, RADIO::PRIORITY, RADIO::STACK, RADIO::NAME.cbegin() );
    // s_thread_id[ static_cast<size_t>( PrjTaskId::RADIO ) ] = radio.start();

    /*-------------------------------------------------
    System Thread: File System
    -------------------------------------------------*/
    // Task file;
    // file.initialize( FIL::FileSystemThread, nullptr, FIL::PRIORITY, FIL::STACK, FIL::NAME.cbegin() );
    // s_thread_id[ static_cast<size_t>( PrjTaskId::FILE_SYSTEM ) ] = file.start();
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
