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
#include <Ripple/session>
#include <Ripple/datalink>
#include <Ripple/network>
#include <Ripple/physical>
#include <Ripple/transport>
#include <Ripple/shared>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_radio.hpp>
#include <src/utility/logger.hpp>
#include <src/wireless/rf_driver.hpp>


//#define TEST_DEVICE
#include <Aurora/hmi>
#include <src/wireless/rf_driver_internal.hpp>

namespace DC::Tasks::RADIO
{
  static volatile bool sendMessage = false;
  static void buttonCallback( Aurora::HMI::Button::ActiveEdge edge )
  {
    sendMessage = true;
  }

  static void TXFailCallback( size_t id )
  {
    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "%d: Transmit FAILED\r\n", Chimera::millis() );
  }

  static void TXPassCallback( Ripple::DataLink::Endpoint ep )
  {
    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "%d: Transmit SUCCEEDED\r\n", Chimera::millis() );
  }

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void RadioThread( void *arg )
  {
    using namespace Aurora::HMI::Button;
    using namespace Chimera::GPIO;
    using namespace Chimera::SPI;
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------
    Configure the HMI device for TX triggering
    -------------------------------------------------*/
#if defined( TEST_DEVICE )
    EdgeTrigger button;
    EdgeConfig btnCfg;
    EdgeCallback btnCallback = EdgeCallback::create<buttonCallback>();

    btnCfg.activeEdge    = ActiveEdge::RISING_EDGE;
    btnCfg.debounceTime  = 100;
    btnCfg.sampleRate    = 5;
    btnCfg.stableSamples = 10;

    btnCfg.gpioConfig.alternate = Alternate::NONE;
    btnCfg.gpioConfig.drive     = Drive::INPUT;
    btnCfg.gpioConfig.pin       = 2;
    btnCfg.gpioConfig.port      = Port::PORTA;
    btnCfg.gpioConfig.pull      = Pull::NO_PULL;
    btnCfg.gpioConfig.threaded  = true;
    btnCfg.gpioConfig.validity  = true;

    button.initialize( btnCfg );
    button.onActiveEdge( btnCallback );
    button.enable();
#endif

    /*-------------------------------------------------
    Start the network stack
    -------------------------------------------------*/
    Ripple::Physical::MACAddress macTX = 0xB3B4B5B605;
    Ripple::Physical::MACAddress macRX = 0xB3B4B5B6CD;

    Ripple::Session::RadioConfig cfg;
    cfg.clear();

    cfg.address                    = 0;
    cfg.channel                    = 96;
    cfg.networkBaud                = 115200;
    cfg.advanced.staticPayloads    = true;
    cfg.advanced.staticPayloadSize = Ripple::Physical::MAX_TX_PAYLOAD_SIZE;
    cfg.advanced.verifyRegisters   = true;

#if defined( TEST_DEVICE )
    cfg.advanced.mac = macTX;
#else
    cfg.advanced.mac = macRX;
#endif

    //RF::initialize( cfg );

    /*-------------------------------------------------
    Try and send a test frame
    -------------------------------------------------*/
#if defined( TEST_DEVICE )
    auto destDevice = Ripple::constructIP( 192, 168, 1, 0 );
    RF::datalinkService.addARPEntry( destDevice, macRX );


    std::array<uint8_t, 128> randomData;
    for( auto x=0; x<randomData.size(); x++)
    {
      randomData[ x ] = rand() % 255;
    }

    size_t lastTx = Chimera::millis();

    auto writeCB = Ripple::Transport::EPCallback::create<TXPassCallback>();

#else

    //RF::datalinkService.setRootEndpointMAC( macRX );

#endif

    while ( 1 )
    {
#if defined( TEST_DEVICE )
      if ( sendMessage && ( ( Chimera::millis() - lastTx ) > 500 ) )
      {
        lastTx      = Chimera::millis();
        sendMessage = false;
        RF::transportService.writeEndpoint( Ripple::DataLink::Endpoint::EP_DEVICE_ROOT, randomData.data(), randomData.size(), writeCB );
        uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "%d: Transmit packet\r\n", Chimera::millis() );
      }
#endif

      // Process the data pipes here?
      BKGD::kickDog( TaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
