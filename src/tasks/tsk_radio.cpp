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
#include <Ripple/user>
#include <Ripple/netif/nrf24l01>
#include <Ripple/netif/loopback>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_radio.hpp>
#include <src/utility/logger.hpp>
#include <src/wireless/rf24/rf_driver.hpp>


// Testing only
#include <algorithm>
#include <etl/random.h>
#include <etl/crc32.h>
#include "controller.pb.h"

static etl::random_xorshift rng;

#define CONTROLLER_DEVICE 0

struct DataPacket
{
  uint32_t crc;
  uint8_t data[ 100 ];
};

namespace DC::Tasks::RADIO
{
#if defined( EMBEDDED )
  std::array<uint8_t, 10 * 1024> netMemoryPool;
#else  /* SIMULATOR */
  std::array<uint8_t, 1024 * 1024> netMemoryPool;

#endif /* EMBEDDED */

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
    Power up the Radio
    -------------------------------------------------*/
    DC::RF::RF24::setPower( DC::RF::RF24::PowerState::ENABLED );

    /*-------------------------------------------------------------------------------
    Network testing
    -------------------------------------------------------------------------------*/
    /*-------------------------------------------------
    Create the network context
    -------------------------------------------------*/
    auto context = Ripple::create( netMemoryPool.data(), netMemoryPool.size() );
    context->setIPAddress( LOCAL_HOST_IP );

#if defined( EMBEDDED )
    /*-------------------------------------------------
    Create the interface driver
    -------------------------------------------------*/
    auto netif = Ripple::NetIf::NRF24::DataLink::createNetIf( context );

    Ripple::NetIf::NRF24::Physical::Handle cfg;
    DC::RF::RF24::genRadioCfg( cfg );

    netif->assignConfig( cfg );
    netif->powerUp( context );
    context->attachNetif( netif );

#else
    auto netif = Ripple::NetIf::Loopback::createNetIf( context );
    netif->powerUp( context );
    context->attachNetif( netif );
#endif /* EMBEDDED */

    /*-------------------------------------------------
    Inform the NRF ARP how to resolve addresses
    -------------------------------------------------*/
#if defined( EMBEDDED )
#if ( CONTROLLER_DEVICE == 1 )
    IPAddress thisNode = 35;
    uint64_t thisMAC   = 0xB4B5B6B7B5;

    IPAddress destNode = 23;
    uint64_t destMAC   = 0xA4A5A6A7A0;

#else
    IPAddress destNode = 23;
    uint64_t destMAC   = 0xB4B5B6B7B5;

    IPAddress thisNode = 35;
    uint64_t thisMAC   = 0xA4A5A6A7A0;

#endif /* CONTROLLER_DEVICE */
#else
#endif

#if defined( EMBEDDED )
    netif->addARPEntry( thisNode, &thisMAC, sizeof( thisMAC ) );
    netif->addARPEntry( destNode, &destMAC, sizeof( destMAC ) );
    netif->setRootMAC( thisMAC );

    Socket_rPtr txSocket = context->socket( SocketType::PUSH, 512 );
    txSocket->open( thisNode );
    txSocket->connect( destNode, thisNode );

    Socket_rPtr rxSocket = context->socket( SocketType::PULL, 512 );
    rxSocket->open( thisNode );
    rxSocket->connect( destNode, destNode );

#else
    /*-------------------------------------------------
    Create two sockets for a full duplex pipe
    -------------------------------------------------*/
    Socket_rPtr txSocket = context->socket( SocketType::PUSH, 1024 );
    txSocket->open( LOCAL_HOST_PORT );
    txSocket->connect( LOCAL_HOST_IP, LOCAL_HOST_PORT );

    Socket_rPtr rxSocket = context->socket( SocketType::PULL, 1024 );
    rxSocket->open( LOCAL_HOST_PORT );
    rxSocket->connect( LOCAL_HOST_IP, LOCAL_HOST_PORT );

#endif /* EMBEDDED */

    /*-------------------------------------------------
    Create some random data to try and transfer
    -------------------------------------------------*/
    rng.initialise( Chimera::micros() );

    /*-------------------------------------------------
    Initialize some local data for the transfers
    -------------------------------------------------*/
    Chimera::Status_t result;
    size_t lastTx    = Chimera::millis();
    size_t lastRx    = Chimera::millis();
    bool transmitted = false;
    size_t tx_count  = 0;
    size_t rx_count  = 0;


#if ( CONTROLLER_DEVICE == 1 )
    etl::crc32 crc;
    crc.reset();

    DataPacket txData;
    memset( &txData, 0, sizeof( DataPacket ) );

    std::generate( txData.data, txData.data + sizeof( txData.data ), rng );
    crc.add( txData.data, txData.data + sizeof( txData.data ) );
    txData.crc = crc.value();

    txSocket->write( &txData, sizeof( txData ) );
#endif /* CONTROLLER_DEVICE == 1 */

    while ( 1 )
    {
#if defined( EMBEDDED )
/*-------------------------------------------------
Periodically transmit data. Expects to talk with a
python program that will simply echo the data back.
-------------------------------------------------*/
#if ( CONTROLLER_DEVICE == 1 )
      // if ( ( ( Chimera::millis() - lastTx ) > 1000 ) )
      // {
      //   lastTx = Chimera::millis();
      //   std::generate( some_data.begin(), some_data.end(), rng );
      //   txSocket->write( some_data.data(), some_data.size() );
      // }
#endif /* CONTROLLER_DEVICE == 1 */

      /*-------------------------------------------------
      Try and sample data. Expects to receive an echo of
      the transmit.
      -------------------------------------------------*/
#if ( CONTROLLER_DEVICE == 0 )
      if ( auto bytesAvailable = rxSocket->available(); bytesAvailable )
      {
        RT_HARD_ASSERT( bytesAvailable == sizeof( DataPacket ) );
        DataPacket rxData;
        etl::crc32 crc;
        crc.reset();

        result = rxSocket->read( &rxData, bytesAvailable );
        crc.add( rxData.data, rxData.data + sizeof( rxData.data ) );

        if ( crc.value() == rxData.crc )
        {
          LOG_INFO( "Received, CRC match\r\n" );
          rx_count++;
        }
        else
        {
          LOG_INFO( "Received, CRC fail\r\n" );
        }
      }
#endif /* CONTROLLER_DEVICE == 0 */
#endif /* EMBEDDED */

#if defined( SIMULATOR )
      /*-------------------------------------------------
      Transmit some data
      -------------------------------------------------*/
      if ( ( tx_count < 100 ) && ( ( Chimera::millis() - lastTx ) > 25 ) )
      {
        LOG_INFO( "Transmitting\r\n" );
        lastTx = Chimera::millis();

        /*-----------------------------------------------------------------
        Initialize some protobuf data
        -----------------------------------------------------------------*/
        ControllerInputs inputs;
        inputs.encoder_inputs = 1;
        inputs.stick_inputs = 2;
        inputs.switch_inputs = 3;
        inputs.timestamp = 4;

        /*-----------------------------------------------------------------
        Pack the protobuf data into a packet
        -----------------------------------------------------------------*/
        auto encoder = PacketEncoder<ControllerInputs, ControllerInputs_size>();
        auto encoded_data = encoder.encode( inputs, ControllerInputs_fields );


        txSocket->write( encoded_data.data(), encoded_data.size() );
        tx_count++;

        if ( tx_count == 100 )
        {
          LOG_INFO( "Finished transmitting all data\r\n" );
        }
      }

      /*-------------------------------------------------
      Receive some data
      -------------------------------------------------*/
      if ( ( Chimera::millis() - lastRx ) > 100 )
      {
        lastRx              = Chimera::millis();
        auto bytesAvailable = rxSocket->available();

        while ( bytesAvailable )
        {
          RT_HARD_ASSERT( sizeof( ControllerInputs ) == bytesAvailable );
          ControllerInputs rxData;
          result = rxSocket->read( &rxData, bytesAvailable );

          LOG_INFO( "Read %d bytes\r\n", bytesAvailable );
          rx_count++;

          bytesAvailable = rxSocket->available();
        }

        if ( ( tx_count == 100 ) && ( bytesAvailable == 0 ) )
        {
          LOG_INFO( "Total TX: %d, Total RX: %d\r\n", tx_count, rx_count );
          tx_count++;
        }
      }
#endif /* SIMULATOR */

      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
