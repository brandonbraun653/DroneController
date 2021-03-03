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


// Testing only
#include <algorithm>
#include <etl/random.h>

static etl::random_xorshift rng;

namespace DC::Tasks::RADIO
{
  std::array<uint8_t, 10 * 1024> netMemoryPool;

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
    Create the network context
    -------------------------------------------------*/
    auto context = Ripple::create( netMemoryPool.data(), netMemoryPool.size() );

    /*-------------------------------------------------
    Create the interface driver
    -------------------------------------------------*/
    auto netif = Ripple::NetIf::NRF24::DataLink::createNetIf( context );

    Ripple::NetIf::NRF24::Physical::Handle cfg;
    DC::RF::genRadioCfg( cfg );

    netif->assignConfig( cfg );
    netif->powerUp( context );

    context->attachNetif( netif );

    /*-------------------------------------------------
    Inform the NRF ARP how to resolve addresses
    -------------------------------------------------*/
    std::string thisNode = "device123";
    uint64_t thisMAC = 0xB4B5B6B7B5;

    std::string destNode = "device321";
    uint64_t destMAC = 0xA4A5A6A7A0;

    netif->addARPEntry( thisNode, &thisMAC, sizeof( thisMAC ) );
    netif->addARPEntry( destNode, &destMAC, sizeof( destMAC ) );
    netif->setRootMAC( thisMAC );

    /*-------------------------------------------------
    Create two sockets for a full duplex pipe
    -------------------------------------------------*/
    Socket_rPtr txSocket = context->socket( SocketType::PUSH, 256 );
    txSocket->open( thisNode );
    txSocket->connect( destNode );

    Socket_rPtr rxSocket = context->socket( SocketType::PULL, 256 );
    rxSocket->open( thisNode );
    rxSocket->connect( destNode );

    /*-------------------------------------------------
    Create some random data to try and transfer
    -------------------------------------------------*/
    rng.initialise( Chimera::micros() );
    std::array<uint8_t, 100> some_data;
    std::generate( some_data.begin(), some_data.end(), rng );

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
        txSocket->write( some_data.data(), some_data.size() );
        lastTx      = Chimera::millis();
        lastRx      = Chimera::millis();
        transmitted = true;
      }

      /*-------------------------------------------------
      Try and sample data. Expects to receive an echo of
      the transmit.
      -------------------------------------------------*/
      if ( transmitted && ( ( Chimera::millis() - lastRx ) > 1000 ) )
      {
        auto bytesAvailable = rxSocket->available();
        lastRx = Chimera::millis();

        if( !bytesAvailable )
        {
          getRootSink()->flog( Level::LVL_DEBUG, "Didn't receive data: %d\r\n", Chimera::millis() );
          continue;
        }

        auto mem = context->malloc( bytesAvailable );

        result = rxSocket->read( mem, bytesAvailable );

        transmitted = false;
        getRootSink()->flog( Level::LVL_DEBUG, "Got %d bytes\r\n", bytesAvailable );
        context->free( mem );
      }

      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
