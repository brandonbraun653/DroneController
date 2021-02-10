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
#include <Chimera/common>
#include <Chimera/system>
#include <Chimera/thread>
#include <Chimera/watchdog>

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
    const TaskId id;    /**< Task being measured */
    const size_t lower; /**< Minimum number of expected task kick events */
    const size_t upper; /**< Maximum number of expected task kick events */
    size_t exact;       /**< Last measured # kick events */
  };

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static TaskId s_queue_buffer[ QUEUE_SIZE ];            /**< Buffer for the monitor thread queue */
  static Chimera::Threading::Queue s_task_kicks;         /**< Event queue for tasks to push "kicks" to */
  static Chimera::Watchdog::Independent_sPtr s_watchdog; /**< Hardware watchdog */

  /**
   *  Tracks runtime timing data for all tasks. Order must match
   *  the definition of TaskId.
   */
  static TaskTiming s_timing_stats[] = {
    /* clang-format off */
    { .id = TaskId::MONITOR,      .lower = 0, .upper = 0,   .exact = 0 }, // Can't monitor this thread
    { .id = TaskId::FILE_SYSTEM,  .lower = 0, .upper = 0,   .exact = 0 }, // Choosing not to monitor just yet
    { .id = TaskId::GRAPHICS,     .lower = 0, .upper = 0,   .exact = 0 }, // Can't monitor this thread
    { .id = TaskId::HEART_BEAT,   .lower = 0, .upper = 12,  .exact = 0 },
    { .id = TaskId::HMI,          .lower = 0, .upper = 0,   .exact = 0 }, // Choosing not to monitor just yet
    { .id = TaskId::RADIO,        .lower = 0, .upper = 50,  .exact = 0 },
    /* clang-format on */
  };
  static_assert( ARRAY_COUNT( s_timing_stats ) == static_cast<size_t>( TaskId::NUM_OPTIONS ) );
  static_assert( static_cast<size_t>( TaskId::MONITOR ) == 0 );

  /*-------------------------------------------------------------------------------
  Private Functions
  -------------------------------------------------------------------------------*/
  static void initializeMonitor();

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void BackgroundThread( void *arg )
  {
    using namespace Chimera::Threading;

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


  static void initializeMonitor()
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
    s_watchdog = Chimera::Watchdog::getDriver( WDG_CHANNEL );

    if ( s_watchdog->initialize( WDG_CHANNEL, HW_WDG_TIMEOUT ) == Chimera::Status::OK )
    {
      s_watchdog->pauseOnDebugHalt( true );
      s_watchdog->start();
    }
    else
    {
      Chimera::insert_debug_breakpoint();
      Chimera::System::softwareReset();
    }

    /*-------------------------------------------------
    Wait for all the threads to register themselves
    -------------------------------------------------*/
    #if defined( CHIMERA_SIMULATOR )
    while( true )
    {
      bool allRegistered = true;

      for ( auto x = 1; x < ARRAY_COUNT( s_timing_stats ); x++ )
      {
        if( getThreadId( s_timing_stats[ x ].id ) == THREAD_ID_INVALID )
        {
          allRegistered = false;
        }

        Chimera::delayMilliseconds( 25 );
      }

      if( allRegistered )
      {
        break;
      }
    }
    #endif /* CHIMERA_SIMULATOR */

    /*-------------------------------------------------
    Start up system threads. Monitor thread is always
    the first task, so don't bother sending msg there.
    -------------------------------------------------*/
    for ( auto x = 1; x < ARRAY_COUNT( s_timing_stats ); x++ )
    {
      ThreadId threadId = getThreadId( s_timing_stats[ x ].id );
      Chimera::Threading::sendTaskMsg( threadId, ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_DONT_WAIT );
      Chimera::delayMilliseconds( 3 );
    }
  }
}    // namespace DC::Tasks::BKGD
