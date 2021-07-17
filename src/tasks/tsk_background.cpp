/********************************************************************************
 *  File Name:
 *    tsk_monitor.cpp
 *
 *  Description:
 *    Implements a watchdog task that monitors all other system tasks. Also used
 *    as the background task if no other tasks can execute.
 *
 *    Inspired by the excellent Jack Ganssle:
 *    http://www.ganssle.com/watchdogs.htm
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/system>
#include <Chimera/thread>
#include <Chimera/watchdog>

/* ETL Includes */
#include <etl/queue.h>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/system/power_up.hpp>


namespace DC::Tasks::BKGD
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t QUEUE_SIZE       = 300;  /**< Number of queue events to hold */
  static constexpr size_t TSK_PERIOD       = 100;  /**< How often the BKGD task should run in ms */
  static constexpr size_t HW_WDG_TIMEOUT   = 5000; /**< Max timeout before hardware reset */
  static constexpr size_t HW_WDG_KICK_RATE = 150;  /**< How often the hardware watchdog should be kicked */

  static constexpr Chimera::Watchdog::IChannel WDG_CHANNEL = Chimera::Watchdog::IChannel::WATCHDOG0;

  /*-------------------------------------------------
  Verify timing assumptions
  -------------------------------------------------*/
  static_assert( HW_WDG_TIMEOUT > ( 2 * TSK_PERIOD ) );
  static_assert( HW_WDG_TIMEOUT > ( 2 * HW_WDG_KICK_RATE ) );
  static_assert( HW_WDG_KICK_RATE > TSK_PERIOD );


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
    const PrjTaskId id; /**< Task being measured */
    const size_t lower; /**< Minimum number of expected task kick events */
    const size_t upper; /**< Maximum number of expected task kick events */
    size_t exact;       /**< Last measured # kick events */
  };

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::Thread::Mutex s_task_lock;
  static etl::queue<PrjTaskId, QUEUE_SIZE> s_task_kicks; /**< Event queue for tasks to push "kicks" to */
  static Chimera::Watchdog::Independent_sPtr s_watchdog; /**< Hardware watchdog */

  /**
   *  Tracks runtime timing data for all tasks. Order must match
   *  the definition of TaskId.
   */
  static TaskTiming s_timing_stats[] = {
    /* clang-format off */
    { .id = PrjTaskId::BLUETOOTH,    .lower = 0, .upper = 0,   .exact = 0 },
    { .id = PrjTaskId::FILE_SYSTEM,  .lower = 0, .upper = 0,   .exact = 0 }, // Choosing not to monitor just yet
    { .id = PrjTaskId::HEART_BEAT,   .lower = 0, .upper = 12,  .exact = 0 },
    { .id = PrjTaskId::HMI,          .lower = 0, .upper = 0,   .exact = 0 }, // Choosing not to monitor just yet
    { .id = PrjTaskId::KERNEL,       .lower = 0, .upper = 0,   .exact = 0 },
    { .id = PrjTaskId::MONITOR,      .lower = 0, .upper = 0,   .exact = 0 }, // Can't monitor this thread
    { .id = PrjTaskId::RADIO,        .lower = 0, .upper = 50,  .exact = 0 },
    { .id = PrjTaskId::SYSTEM,       .lower = 0, .upper = 0,   .exact = 0 },
    { .id = PrjTaskId::USB,          .lower = 0, .upper = 0,   .exact = 0 },
    /* clang-format on */
  };
  static_assert( ARRAY_COUNT( s_timing_stats ) == static_cast<size_t>( PrjTaskId::NUM_OPTIONS ) );
  static_assert( static_cast<size_t>( PrjTaskId::MONITOR ) == 0 );

  /*-------------------------------------------------------------------------------
  Private Functions
  -------------------------------------------------------------------------------*/
  static void initializeMonitor();

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void BackgroundThread( void *arg )
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Power up the various hardware modules
    -------------------------------------------------*/
    SYS::powerUpModules();

    /*-------------------------------------------------
    Monitor system threads
    -------------------------------------------------*/
    initializeMonitor();
    size_t lastTickWoken;
    size_t lastKick = 0;
    Chimera::delayMilliseconds( TSK_PERIOD );

    while ( true )
    {
      lastTickWoken = Chimera::millis();

      // /*-------------------------------------------------
      // Process the task hits
      // -------------------------------------------------*/
      // s_task_lock.lock();
      // while ( s_task_kicks.size() )
      // {
      //   PrjTaskId tmp = s_task_kicks.front();
      //   s_task_kicks.pop();

      //   if ( tmp < PrjTaskId::NUM_OPTIONS )
      //   {
      //     s_timing_stats[ static_cast<size_t>( tmp ) ].exact++;
      //   }
      // }
      // s_task_lock.unlock();

      // /*-------------------------------------------------
      // Are the number of hits out of bounds?
      // -------------------------------------------------*/
      // for ( auto x = 0; x < ARRAY_COUNT( s_timing_stats ); x++ )
      // {
      //   if ( ( s_timing_stats[ x ].exact < s_timing_stats[ x ].lower ) ||
      //        ( s_timing_stats[ x ].exact > s_timing_stats[ x ].upper ) )
      //   {
      //     Chimera::insert_debug_breakpoint();
      //     Chimera::System::softwareReset();
      //   }
      //   else
      //   {
      //     s_timing_stats[ x ].exact = 0;
      //   }
      // }

      /*-------------------------------------------------
      Periodically kick the hardware watchdog
      -------------------------------------------------*/
      if ( ( lastTickWoken - lastKick ) > HW_WDG_KICK_RATE )
      {
        s_watchdog->kick();
        lastKick = Chimera::millis();
      }

      /*-------------------------------------------------
      Only wake up at the desired period
      -------------------------------------------------*/
      Chimera::delayMilliseconds( lastTickWoken, TSK_PERIOD );
    }
  }


  void kickDog( const PrjTaskId task )
  {
    s_task_lock.lock();

    /*-------------------------------------------------
    The monitor thread must always be able to process
    through the queue, otherwise there is a problem.
    -------------------------------------------------*/
    //RT_HARD_ASSERT( !s_task_kicks.full() );

    /*-------------------------------------------------
    Otherwise push the task event and continue on
    -------------------------------------------------*/
    s_task_kicks.push( task );
    s_task_lock.unlock();
  }


  static void initializeMonitor()
  {
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Initialize local memory
    -------------------------------------------------*/
    for ( size_t x = 0; x < ARRAY_COUNT( s_timing_stats ); x++ )
    {
      s_timing_stats[ x ].exact = 0;
    }

    /*-------------------------------------------------
    Initialize the hardware watchdog
    -------------------------------------------------*/
    s_watchdog = Chimera::Watchdog::getDriver( WDG_CHANNEL );

    if ( s_watchdog->initialize( WDG_CHANNEL, HW_WDG_TIMEOUT ) == Chimera::Status::OK )
    {
      s_watchdog->pauseOnDebugHalt( true );
      s_watchdog->start();
    }
    else
    {
    #if !defined( CHIMERA_SIMULATOR )
      Chimera::insert_debug_breakpoint();
      Chimera::System::softwareReset();
    #endif
    }

#if defined( CHIMERA_SIMULATOR )
    /*-------------------------------------------------
    Wait for all the threads to register themselves.
    -------------------------------------------------*/
    Chimera::delayMilliseconds( 150 );
#endif /* CHIMERA_SIMULATOR */

    /*-------------------------------------------------
    Start up system threads. Monitor thread is always
    the first task, so don't bother sending msg there.
    -------------------------------------------------*/
    for ( size_t x = 1; x < ARRAY_COUNT( s_timing_stats ); x++ )
    {
      TaskId threadId = getTaskId( s_timing_stats[ x ].id );
      if( threadId == THREAD_ID_INVALID )
      {
        continue;
      }

      Chimera::Thread::sendTaskMsg( threadId, ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_DONT_WAIT );
      Chimera::delayMilliseconds( 53 );
    }
  }
}    // namespace DC::Tasks::BKGD
