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
#include <Ripple/shared>
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

    /*-------------------------------------------------------------------------------
    Network testing
    -------------------------------------------------------------------------------*/
    /*-------------------------------------------------
    Create the interface driver
    -------------------------------------------------*/
    auto network = Ripple::create( netMemoryPool.data(), netMemoryPool.size() );
    auto netintf = Ripple::NetIf::NRF24::DataLink::createNetIf( network );

    Ripple::NetIf::NRF24::Physical::Handle cfg;
    DC::RF::genRadioCfg( cfg );

    netintf->assignConfig( cfg );
    netintf->powerUp( network );

    /*-------------------------------------------------
    Bind this node's address and some static RX address
    -------------------------------------------------*/
    IPAddress thisNode = constructIP( 127, 0, 0, 1 );
    uint64_t thisMAC = 0xB4B5B6B7B5;

    IPAddress destNode = constructIP( 192, 168, 1, 0 );
    uint64_t destMAC = 0xA4A5A6A7A0;

    netintf->addARPEntry( thisNode, &thisMAC, sizeof( thisMAC ) );
    netintf->addARPEntry( destNode, &destMAC, sizeof( destMAC ) );

    netintf->setRootMAC( thisMAC );

    /*-------------------------------------------------
    Allocate some some_data memory to try and transfer
    -------------------------------------------------*/
    std::array<uint8_t, 10> some_data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    MsgFrag txMsg;
    txMsg.fragmentData   = network->malloc( some_data.size() );
    txMsg.fragmentLength = some_data.size();
    txMsg.nextFragment   = nullptr;
    txMsg.totalLength    = some_data.size();
    txMsg.fragmentNumber = 0;

    memcpy( txMsg.fragmentData, some_data.data(), txMsg.fragmentLength );

    /*-------------------------------------------------
    Allocate memory for the reception
    -------------------------------------------------*/
    MsgFrag rxMsg;

    /*-------------------------------------------------
    Initialize some local data for the transfers
    -------------------------------------------------*/
    Chimera::Status_t result;

    size_t lastTx    = Chimera::millis();
    size_t lastRx    = Chimera::millis();
    bool transmitted = false;

    while ( 1 )
    {
      /*-------------------------------------------------
      Periodically transmit data. Expects to talk with a
      python program that will simply echo the data back.
      -------------------------------------------------*/
      if ( ( ( Chimera::millis() - lastTx ) > 1000 ) && !transmitted )
      {
        result = netintf->send( txMsg, destNode );

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
      if ( transmitted && ( ( Chimera::millis() - lastRx ) > 1000 ) )
      {
        result = netintf->recv( rxMsg );
        lastRx = Chimera::millis();

        if ( ( result == Chimera::Status::READY ) && rxMsg.fragmentData && rxMsg.fragmentLength )
        {
          transmitted = false;
          getRootSink()->flog( Level::LVL_DEBUG, "Got data\r\n" );
        }
        else
        {
          getRootSink()->flog( Level::LVL_DEBUG, "Didn't receive data: %d\r\n", Chimera::millis() );
        }
      }

      // Process the data pipes here?
      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
