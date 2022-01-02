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
#include "ahrs.pb.h"
#include "controller.pb.h"
#include <src/config/ripple/ripple_packet_contract_prj.hpp>

static etl::random_xorshift rng;

namespace DC::Tasks::RADIO
{
#if defined( EMBEDDED )
  std::array<uint8_t, 16 * 1024> netMemoryPool;
#else  /* SIMULATOR */
  std::array<uint8_t, 100 * 1024> netMemoryPool;
#endif /* EMBEDDED */


  static void CmnHandler( const Ripple::PacketId id, const void *const data, const size_t size )
  {
    static uint32_t pkt_num = 0;
    LOG_INFO_IF( false, "#%d -- Received pkt %d of size %d\r\n", pkt_num, id, size );
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
    bool                 transmit_node = false;
    Ripple::SocketConfig sock_cfg;
    sock_cfg.txFilter[ 0 ] = PKT_CMD_CONTROLLER_INPUTS;
    sock_cfg.txFilter[ 1 ] = PKT_AHRS_ACCEL_DATA;
    sock_cfg.txFilter[ 2 ] = PKT_AHRS_GYRO_DATA;
    sock_cfg.txFilter[ 3 ] = PKT_AHRS_MAG_DATA;

    sock_cfg.rxFilter[ 0 ] = PKT_CMD_CONTROLLER_INPUTS;
    sock_cfg.rxFilter[ 1 ] = PKT_AHRS_ACCEL_DATA;
    sock_cfg.rxFilter[ 2 ] = PKT_AHRS_GYRO_DATA;
    sock_cfg.rxFilter[ 3 ] = PKT_AHRS_MAG_DATA;

#if defined( EMBEDDED )
    DC::Files::RF24Config::DataType rfData;
    DC::REG::readSafe( DC::REG::DatabaseKeys::KEY_RF24_CONFIG, &rfData, sizeof( rfData ) );

    DC::Files::UnitInfo::DataType unitInfo;
    DC::REG::readSafe( DC::REG::DatabaseKeys::KEY_UNIT_INFO, &unitInfo, sizeof( unitInfo ) );

    sock_cfg.devicePort = rfData.thisNodeIp;
    transmit_node       = strcmp( unitInfo.name, "Onyx" ) == 0;

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
    transmit_node       = true;
    sock_cfg.devicePort = LOCAL_HOST_PORT;

    Socket_rPtr txSocket = context->socket( SocketType::PUSH, 2048 );
    txSocket->open( sock_cfg );
    txSocket->connect( LOCAL_HOST_IP, LOCAL_HOST_PORT );

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
    size_t lastPrint = Chimera::millis();
    size_t txCount   = 0;

    while ( 1 )
    {
      /*-----------------------------------------------------------------------
      Transmit some data periodically
      -----------------------------------------------------------------------*/
      if ( transmit_node && ( ( Chimera::millis() - lastTx ) > 25 ) )
      {
        lastTx = Chimera::millis();

        /*-----------------------------------------------------------------
        Initialize some protobuf data
        -----------------------------------------------------------------*/
        ControllerInputs inputs;
        inputs.encoder_inputs = static_cast<uint32_t>( rand() );
        inputs.stick_inputs   = static_cast<uint32_t>( rand() );
        inputs.switch_inputs  = static_cast<uint32_t>( rand() );
        inputs.timestamp      = Chimera::millis();

        AccelSample accel;
        accel.x         = static_cast<float>( rand() );
        accel.y         = static_cast<float>( rand() );
        accel.z         = static_cast<float>( rand() );
        accel.timestamp = Chimera::millis();

        GyroSample gyro;
        gyro.x         = static_cast<float>( rand() );
        gyro.y         = static_cast<float>( rand() );
        gyro.z         = static_cast<float>( rand() );
        gyro.timestamp = Chimera::millis();

        MagSample mag;
        mag.x         = static_cast<float>( rand() );
        mag.y         = static_cast<float>( rand() );
        mag.z         = static_cast<float>( rand() );
        mag.timestamp = Chimera::millis();

        /*-----------------------------------------------------------------
        Pack the protobuf data into a packet
        -----------------------------------------------------------------*/
        // Ripple::transmit( PKT_CMD_CONTROLLER_INPUTS, *txSocket, &inputs, sizeof( ControllerInputs ) );
        // Ripple::transmit( PKT_AHRS_ACCEL_DATA, *txSocket, &accel, sizeof( AccelSample ) );
        // Ripple::transmit( PKT_AHRS_GYRO_DATA, *txSocket, &gyro, sizeof( GyroSample ) );
        // Ripple::transmit( PKT_AHRS_MAG_DATA, *txSocket, &mag, sizeof( MagSample ) );

        txCount++;
      }

      if ( ( Chimera::millis() - lastPrint ) > 1000 )
      {
        lastPrint = Chimera::millis();
        //context->printStats();
      }

      BKGD::kickDog( PrjTaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
