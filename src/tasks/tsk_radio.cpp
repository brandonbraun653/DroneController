/********************************************************************************
 *  File Name:
 *    tsk_radio.cpp
 *
 *  Description:
 *    Implements the radio threading functions
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/spi>
#include <Chimera/thread>

/* Ripple Includes */
#include <Ripple/netstack>
#include <Ripple/netif/nrf24l01>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_radio.hpp>
#include <src/utility/logger.hpp>
#include <src/wireless/rf_driver.hpp>

namespace DC::Tasks::RADIO
{
  std::array<uint8_t, 4096> netMemoryPool;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void RadioThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------
    Network testing
    -------------------------------------------------*/
    auto network = Ripple::create( netMemoryPool.data(), netMemoryPool.size() );
    auto netintf = Ripple::NetIf::NRF24::DataLink::createNetIf( network );

    /* Create the netif */
    auto cfg = DC::RF::genRadioCfg();
    netintf->assignConfig( cfg );
    netintf->powerUp( network );


    Ripple::boot( *network, *netintf );

    while ( 1 )
    {
      // Process the data pipes here?
      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
