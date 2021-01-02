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

/* Ripple Includes */
#include <Ripple/shared>

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

    /*-------------------------------------------------
    Try and send a test frame
    -------------------------------------------------*/
    Ripple::DATALINK::Frame frame;
    frame.clear();
    frame.nextHop = Ripple::constructIP( 192, 168, 1, 0 );
    frame.control |= Ripple::DATALINK::bfControlFlags::CTRL_PAYLOAD_ACK;
    frame.length = 12;
    memset( frame.payload, 0xA5, ARRAY_BYTES( frame.payload ) );


    RF::dataLinkService.addARPEntry( frame.nextHop, 0 );
    RF::dataLinkService.enqueueFrame( frame );

    while ( 1 )
    {
      // Process the data pipes here?
      MON::kickDog( TaskId::RADIO );
      Chimera::delayMilliseconds( 100 );
    }
  }

}  // namespace DC::Tasks::RADIO
