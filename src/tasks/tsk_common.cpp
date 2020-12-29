/********************************************************************************
 *  File Name:
 *    tsk_common.cpp
 *
 *  Description:
 *    Implementation of common task functionality
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_graphics.hpp>
#include <src/tasks/tsk_heartbeat.hpp>
#include <src/tasks/tsk_monitor.hpp>
#include <src/tasks/tsk_radio.hpp>

namespace DC::Tasks
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::Threading::ThreadId s_thread_id[ static_cast<size_t>( TaskId::NUM_OPTIONS ) ];

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initialize()
  {
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Initialize local memory
    -------------------------------------------------*/
    memset( s_thread_id, THREAD_ID_INVALID, ARRAY_COUNT( s_thread_id ) );

    /*-------------------------------------------------
    System Thread: Heartbeat
    -------------------------------------------------*/
    Thread heartbeat;
    heartbeat.initialize( HB::HeartBeatThread, nullptr, HB::PRIORITY, HB::STACK, HB::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( TaskId::HEART_BEAT ) ] = heartbeat.start();

    /*-------------------------------------------------
    System Thread: Watchdog
    -------------------------------------------------*/
    Thread watchdog;
    watchdog.initialize( MON::MonitorThread, nullptr, MON::PRIORITY, MON::STACK, MON::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( TaskId::MONITOR ) ] = watchdog.start();

    /*-------------------------------------------------
    System Thread: Graphics
    -------------------------------------------------*/
    Thread graphics;
    graphics.initialize( GFX::GraphicsThread, nullptr, GFX::PRIORITY, GFX::STACK, GFX::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( TaskId::GRAPHICS ) ] = graphics.start();

    /*-------------------------------------------------
    System Thread: Radio
    -------------------------------------------------*/
    Thread radio;
    radio.initialize( RADIO::RadioThread, nullptr, RADIO::PRIORITY, RADIO::STACK, RADIO::NAME.cbegin() );
    s_thread_id[ static_cast<size_t>( TaskId::RADIO ) ] = radio.start();
  }


  void waitInit()
  {
    using namespace Chimera::Threading;

    ThreadMsg msg = ITCMsg::ITC_NOP;
    while ( true )
    {
      if ( this_thread::receiveTaskMsg( msg, TIMEOUT_BLOCK ) && ( msg == ITCMsg::ITC_WAKEUP ) )
      {
        break;
      }
      else
      {
        this_thread::yield();
      }
    }
  }


  Chimera::Threading::ThreadId getThreadId( const TaskId task )
  {
    if ( !( task < TaskId::NUM_OPTIONS ) )
    {
      return Chimera::Threading::THREAD_ID_INVALID;
    }

    return s_thread_id[ static_cast<size_t>( task ) ];
  }
}    // namespace DC::Tasks
