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
#include <src/registry/reg_data.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/registry/reg_files.hpp>
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
#include <src/config/ripple/ripple_packet_contract_prj.hpp>

static etl::random_xorshift rng;

namespace DC::Tasks::RADIO
{
#if defined( EMBEDDED )
  std::array<uint8_t, 10 * 1024> netMemoryPool;
#else  /* SIMULATOR */
  std::array<uint8_t, 1024 * 1024> netMemoryPool;

#endif /* EMBEDDED */


  static void CmnHandler( const Ripple::PacketId id, const void *const data, const size_t size )
  {
    static uint32_t pkt_num = 0;
    LOG_INFO( "#%d -- Received pkt %d of size %d\r\n", pkt_num, id, size );
    pkt_num++;
  }

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
    Power up the Radio. Wait for the HMI task to grab
    -------------------------------------------------*/
    DC::RF::RF24::setPower( DC::RF::RF24::PowerState::ENABLED );
    Chimera::delayMilliseconds( 500 );

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
    DC::Files::RF24Config::DataType rfData;
    DC::REG::readSafe( DC::REG::DatabaseKeys::KEY_RF24_CONFIG, &rfData, sizeof( rfData  ) );

    Ripple::SocketConfig sock_cfg;
    sock_cfg.txFilter[ 0 ] = PKT_CMD_CONTROLLER_INPUTS;
    sock_cfg.rxFilter[ 0 ] = PKT_CMD_CONTROLLER_INPUTS;
    sock_cfg.devicePort = rfData.thisNodeIp;

    netif->addARPEntry( rfData.thisNodeIp, &rfData.thisNodeMAC, sizeof( rfData.thisNodeMAC ) );
    netif->addARPEntry( rfData.destNodeIp, &rfData.destNodeMAC, sizeof( rfData.destNodeMAC ) );
    netif->setRootMAC( rfData.thisNodeMAC );

    Socket_rPtr txSocket = context->socket( SocketType::PUSH, 2048 );
    txSocket->open( sock_cfg );
    txSocket->connect( rfData.destNodeIp, rfData.destNodeIp );

    Socket_rPtr rxSocket = context->socket( SocketType::PULL, 2048 );
    rxSocket->open( sock_cfg );
    rxSocket->connect( rfData.destNodeIp, rfData.destNodeIp );

#else
    /*-------------------------------------------------
    Create two sockets for a full duplex pipe
    -------------------------------------------------*/
    sock_cfg.devicePort = LOCAL_HOST_PORT;

    Socket_rPtr socket = context->socket( SocketType::PUSH, 2048 );
    socket->open( sock_cfg );
    socket->connect( LOCAL_HOST_IP, LOCAL_HOST_PORT );

    Socket_rPtr rxSocket = context->socket( SocketType::PULL, 2048 );
    rxSocket->open( sock_cfg );
    rxSocket->connect( LOCAL_HOST_IP, LOCAL_HOST_PORT );

    Ripple::onReceive( *rxSocket, CmnHandler );

#endif /* EMBEDDED */

    /*-------------------------------------------------------------------------
    Register default handlers for RX Data
    -------------------------------------------------------------------------*/
    Ripple::onReceive( *rxSocket, CmnHandler );

    /*-------------------------------------------------
    Create some random data to try and transfer
    -------------------------------------------------*/
    rng.initialise( Chimera::micros() );

    /*-------------------------------------------------
    Initialize some local data for the transfers
    -------------------------------------------------*/
    size_t lastTx    = Chimera::millis();
    size_t tx_count  = 0;

    while ( 1 )
    {
      /*-----------------------------------------------------------------------
      Transmit some data periodically
      -----------------------------------------------------------------------*/
      if ( ( Chimera::millis() - lastTx ) > 100 )
      {
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
        if( Ripple::transmit( PKT_CMD_CONTROLLER_INPUTS, *txSocket, &inputs, sizeof( ControllerInputs ) ) )
        {
          tx_count++;
        }
      }

      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
