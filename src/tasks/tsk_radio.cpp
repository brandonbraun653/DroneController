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
    using namespace Ripple;

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


    size_t lastTx    = Chimera::millis();
    size_t lastRx    = Chimera::millis();
    bool transmitted = false;

    std::array<uint8_t, 10> packet = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    /* Allocate a packet as if it were the real thing */
    MsgFrag txMsg;
    txMsg.fragmentData   = network->malloc( packet.size() );
    txMsg.fragmentLength = packet.size();
    txMsg.nextFragment   = nullptr;
    txMsg.totalLength    = packet.size();

    memcpy( txMsg.fragmentData, packet.data(), txMsg.fragmentLength );

    MsgFrag rxMsg;
    Chimera::Status_t result;

    while ( 1 )
    {
      /*-------------------------------------------------
      Periodically transmit data. Expects to talk with a
      python program that will simply echo the data back.
      -------------------------------------------------*/
      if ( ( ( Chimera::millis() - lastTx ) > 1000 ) && !transmitted )
      {
        result = netintf->send( txMsg, 0 );

        if ( result == Chimera::Status::READY )
        {
          lastTx      = Chimera::millis();
          lastRx      = Chimera::millis();
          transmitted = true;
        }
      }

      /*-------------------------------------------------
      Try and sample data. Expects to receive an echo of
      the transmit.
      -------------------------------------------------*/
      if ( transmitted && ( ( Chimera::millis() - lastRx ) > 100 ) )
      {
        result = netintf->recv( rxMsg );
        if ( ( result == Chimera::Status::READY ) && rxMsg.fragmentData && rxMsg.fragmentLength )
        {
          transmitted = false;
          lastRx      = Chimera::millis();
          getRootSink()->flog( Level::LVL_DEBUG, "Got data\r\n" );
        }
        else
        {
          getRootSink()->flog( Level::LVL_DEBUG, "Didn't receive data\r\n" );
        }
      }

      // Process the data pipes here?
      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
