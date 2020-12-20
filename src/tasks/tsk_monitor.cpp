/********************************************************************************
 *  File Name:
 *    tsk_monitor.cpp
 *
 *  Description:
 *    Implements a watchdog task that monitors all other system tasks. Inspired
 *    by the excellent Jack Ganssle: http://www.ganssle.com/watchdogs.htm
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/system>
#include <Chimera/thread>
#include <Chimera/watchdog>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::MON
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t QUEUE_SIZE = 300;  /**< Number of queue events to hold */
  static constexpr size_t TSK_PERIOD = 1000; /**< How often the MON task should run in ms */

  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  /**
   *  Tracks software watchdog kick characteristics for each task. The goal
   *  is to constrain task timing to an expected/acceptable range that
   *  exemplifies normal operating characteristics.
   */
  struct TaskTiming
  {
    const TaskId id;    /**< Task being measured */
    const size_t lower; /**< Minimum number of expected task kick events */
    const size_t upper; /**< Maximum number of expected task kick events */
    size_t exact;       /**< Last measured # kick events */
  };

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static TaskId s_queue_buffer[ QUEUE_SIZE ];
  static Chimera::Threading::Queue s_task_kicks;

  /**
   *  Tracks runtime timing data for all tasks. Order must match
   *  the definition of TaskId.
   */
  static TaskTiming s_timing_stats[] = {
    /* clang-format off */
    { .id = TaskId::MONITOR,    .lower = 0, .upper = 0,   .exact = 0 }, // Can't monitor this thread
    { .id = TaskId::HEART_BEAT, .lower = 1, .upper = 12,  .exact = 0 },
    { .id = TaskId::GRAPHICS,   .lower = 0, .upper = 0,   .exact = 0 }, // Can't monitor this thread
    /* clang-format on */
  };
  static_assert( ARRAY_COUNT( s_timing_stats ) == static_cast<size_t>( TaskId::NUM_OPTIONS ) );
  static_assert( static_cast<size_t>( TaskId::MONITOR ) == 0 );

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void MonitorThread( void *arg )
  {
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Initialize local memory
    -------------------------------------------------*/
    memset( s_queue_buffer, static_cast<size_t>( TaskId::UNKNOWN ), ARRAY_COUNT( s_queue_buffer ) );

    if ( !s_task_kicks.create( ARRAY_COUNT( s_queue_buffer ), sizeof( TaskId ), s_queue_buffer ) )
    {
      Chimera::insert_debug_breakpoint();
      Chimera::System::softwareReset();
    }

    for ( auto x = 0; x < ARRAY_COUNT( s_timing_stats ); x++ )
    {
      s_timing_stats[ x ].exact = 0;
    }

    /*-------------------------------------------------
    Initialize the hardware watchdog
    -------------------------------------------------*/
    // TODO: Size the WD such that it's just outside the periodic interval of this task

    /*-------------------------------------------------
    Start up system threads. Monitor thread is always
    the first task, so don't bother sending there.
    -------------------------------------------------*/
    for ( auto x = 1; x < ARRAY_COUNT( s_timing_stats ); x++ )
    {
      ThreadId threadId = getThreadId( s_timing_stats[ x ].id );
      Chimera::Threading::sendTaskMsg( threadId, ITCMsg::ITC_WAKEUP, TIMEOUT_DONT_WAIT );
    }

    /*-------------------------------------------------
    Monitor system threads
    -------------------------------------------------*/
    size_t laskTickWoken;
    Chimera::delayMilliseconds( TSK_PERIOD );

    while ( true )
    {
      laskTickWoken = Chimera::millis();

      /*-------------------------------------------------
      Process the task hits
      -------------------------------------------------*/
      s_task_kicks.lock();
      while ( s_task_kicks.size() )
      {
        TaskId tmp;
        s_task_kicks.pop( &tmp, TIMEOUT_DONT_WAIT );

        if ( tmp < TaskId::NUM_OPTIONS )
        {
          s_timing_stats[ static_cast<size_t>( tmp ) ].exact++;
        }
      }
      s_task_kicks.unlock();

      /*-------------------------------------------------
      Are the number of hits out of bounds?
      -------------------------------------------------*/
      for ( auto x = 0; x < ARRAY_COUNT( s_timing_stats ); x++ )
      {
        if ( ( s_timing_stats[ x ].exact < s_timing_stats[ x ].lower ) ||
             ( s_timing_stats[ x ].exact > s_timing_stats[ x ].upper ) )
        {
          Chimera::insert_debug_breakpoint();
          Chimera::System::softwareReset();
        }
        else
        {
          s_timing_stats[ x ].exact = 0;
        }
      }

      /*-------------------------------------------------
      Kick the hardware watchdog
      -------------------------------------------------*/
      // TODO

      /*-------------------------------------------------
      Only wake up at the desired period
      -------------------------------------------------*/
      Chimera::delayMilliseconds( laskTickWoken, TSK_PERIOD );
    }
  }


  void kickDog( const TaskId task )
  {
    s_task_kicks.lock();

    /*-------------------------------------------------
    The monitor thread must always be able to process
    through the queue, otherwise there is a problem.
    -------------------------------------------------*/
    if ( s_task_kicks.full() )
    {
      Chimera::insert_debug_breakpoint();
      Chimera::System::softwareReset();
    }

    /*-------------------------------------------------
    Otherwise push the task event and continue on
    -------------------------------------------------*/
    s_task_kicks.push( &task, Chimera::Threading::TIMEOUT_DONT_WAIT );
    s_task_kicks.unlock();
  }
}    // namespace DC::Tasks::MON
