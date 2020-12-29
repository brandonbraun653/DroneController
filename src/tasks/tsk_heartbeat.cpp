/********************************************************************************
 *  File Name:
 *    tsk_heartbeat.cpp
 *
 *  Description:
 *    Test harness blinky thread implementation
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/gpio>

/* Testing Includes */
#include <src/config/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_heartbeat.hpp>
#include <src/tasks/tsk_monitor.hpp>

namespace DC::Tasks::HB
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void HeartBeatThread( void *arg )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------
    Configure the GPIO
    -------------------------------------------------*/
    PinInit cfg;
    cfg.clear();
    cfg.validity  = true;
    cfg.threaded  = true;
    cfg.alternate = Alternate::NONE;
    cfg.drive     = Drive::OUTPUT_PUSH_PULL;
    cfg.pin       = DC::IO::LED::pinHeartbeat;
    cfg.port      = DC::IO::LED::portHeartbeat;
    cfg.pull      = Pull::NO_PULL;
    cfg.state     = State::LOW;

    auto pin = getDriver( cfg.port, cfg.pin );
    pin->init( cfg );
    pin->setState( State::LOW );

    /*-------------------------------------------------
    Do a rapid boot sequence
    -------------------------------------------------*/
    for ( auto x = 0; x < 8; x++ )
    {
      pin->toggle();
      Chimera::delayMilliseconds( 35 );
      MON::kickDog( TaskId::HEART_BEAT );
    }

    MON::kickDog( TaskId::HEART_BEAT );
    Chimera::delayMilliseconds( 500 );
    MON::kickDog( TaskId::HEART_BEAT );

    /*-------------------------------------------------
    Run the heartbeat animation
    -------------------------------------------------*/
    while ( 1 )
    {
      /*-------------------------------------------------
      High pulse #1
      -------------------------------------------------*/
      pin->setState( State::HIGH );
      Chimera::delayMilliseconds( 100 );
      pin->setState( State::LOW );
      Chimera::delayMilliseconds( 100 );
      MON::kickDog( TaskId::HEART_BEAT );

      /*-------------------------------------------------
      High pulse #2
      -------------------------------------------------*/
      pin->setState( State::HIGH );
      Chimera::delayMilliseconds( 100 );
      pin->setState( State::LOW );
      Chimera::delayMilliseconds( 100 );
      MON::kickDog( TaskId::HEART_BEAT );

      /*-------------------------------------------------
      Hold longer time in off state
      -------------------------------------------------*/
      Chimera::delayMilliseconds( 450 );
      MON::kickDog( TaskId::HEART_BEAT );
    }
  }
}    // namespace DC::Tasks::HB
