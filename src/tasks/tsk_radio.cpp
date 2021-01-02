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

/* Project Includes */
#include <src/config/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_monitor.hpp>
#include <src/tasks/tsk_radio.hpp>
#include <src/utility/logger.hpp>
#include <src/wireless/rf_driver.hpp>


//#define TEST_DEVICE
#include <Aurora/hmi>

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

  static void TXPassCallback( size_t id )
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
    Initialize the logging utility
    -------------------------------------------------*/
    DC::UTL::initializeLogger( uLog::Level::LVL_DEBUG );
    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "Power on device\r\n" );

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
    Ripple::PHY::MACAddress macTX = 0xB3B4B5B605;
    Ripple::PHY::MACAddress macRX = 0xB3B4B5B6CD;

    Ripple::Session::RadioConfig cfg;
    cfg.address     = 0;
    cfg.channel     = 96;
    cfg.networkBaud = 115200;

#if defined( TEST_DEVICE )
    cfg.advanced.mac = macTX;
#else
    cfg.advanced.mac = macRX;
#endif

    RF::initialize( cfg );

    /*-------------------------------------------------
    Try and send a test frame
    -------------------------------------------------*/
#if defined( TEST_DEVICE )
    Ripple::DATALINK::Frame frame;
    frame.clear();
    frame.nextHop = Ripple::constructIP( 192, 168, 1, 0 );
    frame.control |= Ripple::DATALINK::bfControlFlags::CTRL_PAYLOAD_ACK;
    frame.length = 12;
    memset( frame.payload, 0xA5, ARRAY_BYTES( frame.payload ) );

    RF::dataLinkService.addARPEntry( frame.nextHop, macRX );

    size_t lastTx = Chimera::millis();
    auto txFailCB = etl::delegate<void(size_t)>::create<TXFailCallback>();
    auto txPassCB = etl::delegate<void(size_t)>::create<TXPassCallback>();

    RF::dataLinkService.registerCallback( Ripple::DATALINK::CallbackId::CB_ERROR_TX_MAX_RETRY, txFailCB );
    RF::dataLinkService.registerCallback( Ripple::DATALINK::CallbackId::CB_TX_SUCCESS, txPassCB );
#endif

    while ( 1 )
    {
#if defined( TEST_DEVICE )
      if ( sendMessage && ( ( Chimera::millis() - lastTx ) > 500 ) )
      {
        lastTx      = Chimera::millis();
        sendMessage = false;
        RF::dataLinkService.enqueueFrame( frame );
        uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "%d: Transmit packet\r\n", Chimera::millis() );
      }
#endif

      // Process the data pipes here?
      MON::kickDog( TaskId::RADIO );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
