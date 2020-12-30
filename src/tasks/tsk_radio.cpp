/********************************************************************************
 *  File Name:
 *    tsk_radio.cpp
 *
 *  Description:
 *    Implements the radio threading functions
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/spi>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_monitor.hpp>
#include <src/tasks/tsk_radio.hpp>
#include <src/wireless/rf_driver.hpp>

namespace DC::Tasks::RADIO
{

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void RadioThread( void *arg )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::SPI;
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();


    /*-------------------------------------------------
    Start the network stack
    -------------------------------------------------*/
    RF::RadioConfig cfg;
    cfg.address = 0;
    cfg.channel = 96;
    cfg.networkBaud = 115200;

    RF::initialize( cfg );

    while ( 1 )
    {
      // Process the data pipes here?
      MON::kickDog( TaskId::RADIO );
      Chimera::delayMilliseconds( 100 );
    }
  }

}  // namespace DC::Tasks::RADIO
