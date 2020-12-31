/********************************************************************************
 *  File Name:
 *    rf_driver_internal.cpp
 *
 *  Description:
 *    Implementation of the RF driver's internal interface
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
#include <Ripple/physical>

/* Project Includes */
#include <src/config/board_map.hpp>
#include <src/wireless/rf_driver_internal.hpp>

namespace DC::RF
{
  /*-------------------------------------------------------------------------------
  Public Data
  -------------------------------------------------------------------------------*/
  Ripple::NetStackHandle netHandle;
  Ripple::PHY::Handle hPhysical;
  Ripple::DATALINK::Handle hDatalink;

  Chimera::Threading::ThreadId netThreadId[ TSK_ID_NUM_TASKS ];

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  /*-------------------------------------------------
  Network Driver Thread Classes
  -------------------------------------------------*/
  Ripple::DATALINK::Service dataLinkService;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  Chimera::Status_t runNetThreads()
  {
    using namespace Chimera::Threading;
    using namespace Ripple;

    auto result = Chimera::Status::OK;

    /*-------------------------------------------------
    Start the DataLink Service
    -------------------------------------------------*/
    ThreadDelegate dlFunc = ThreadDelegate::create<DATALINK::Service, &DATALINK::Service::run>( dataLinkService );

    Thread dl;
    dl.initialize( dlFunc, reinterpret_cast<void *>( &netHandle ), Priority::LEVEL_3, DATALINK::THREAD_STACK,
                   DATALINK::THREAD_NAME.cbegin() );
    netThreadId[ TSK_ID_DATALINK ] = dl.start();
    sendTaskMsg( netThreadId[ TSK_ID_DATALINK ], ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_DONT_WAIT );

    /* Give the hardware time to boot */
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------
    TBD?
    -------------------------------------------------*/

    /*-------------------------------------------------
    Verify all threads were started
    -------------------------------------------------*/
    for ( auto x = 0; x < ARRAY_COUNT( netThreadId ); x++ )
    {
      if( netThreadId[ x ] == THREAD_ID_INVALID )
      {
        return Chimera::Status::FAIL;
      }
    }

    return result;
  }


  Chimera::Status_t initNetStack( const RadioConfig &cfg )
  {
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Clear local memory
    -------------------------------------------------*/
    for ( auto x = 0; x < ARRAY_COUNT( netThreadId ); x++ )
    {
      netThreadId[ x ] = THREAD_ID_INVALID;
    }

    /*-------------------------------------------------
    Initialize the layers in order
    -------------------------------------------------*/
    auto result = Chimera::Status::OK;
    result |= initNetStack_PHY( cfg );
    result |= initNetStack_DATALINK( cfg );

    return result;
  }


  Chimera::Status_t initNetStack_PHY( const RadioConfig &cfg )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::SPI;
    using namespace Chimera::Threading;

    /*-------------------------------------------------------------------------------
    Hardware Configuration
    -------------------------------------------------------------------------------*/
    /*-------------------------------------------------
    Destroy old configuration data
    -------------------------------------------------*/
    hPhysical.clear();

    /*-------------------------------------------------
    Radio properties
    -------------------------------------------------*/
    hPhysical.cfg.hwAddressWidth   = Ripple::PHY::AddressWidth::AW_5Byte;
    hPhysical.cfg.hwCRCLength      = Ripple::PHY::CRCLength::CRC_16;
    hPhysical.cfg.hwDataRate       = Ripple::PHY::DataRate::DR_1MBPS;
    hPhysical.cfg.hwISRMask        = Ripple::PHY::bfISRMask::ISR_MSK_ALL;
    hPhysical.cfg.hwPowerAmplitude = Ripple::PHY::PowerAmplitude::PA_LOW;
    hPhysical.cfg.hwRFChannel      = cfg.channel;
    hPhysical.cfg.hwRTXDelay       = Ripple::PHY::ART_DELAY_500uS;

    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    hPhysical.cfg.irqEdge = DC::IO::Radio::pinIRQ_Trigger;

    hPhysical.cfg.irq.clear();
    hPhysical.cfg.irq.validity  = true;
    hPhysical.cfg.irq.threaded  = true;
    hPhysical.cfg.irq.alternate = Alternate::EXTERNAL_INTERRUPT;
    hPhysical.cfg.irq.drive     = Drive::INPUT;
    hPhysical.cfg.irq.pin       = DC::IO::Radio::pinIRQ_pin;
    hPhysical.cfg.irq.port      = DC::IO::Radio::pinIRQ_port;
    hPhysical.cfg.irq.pull      = Pull::PULL_DN;
    hPhysical.cfg.irq.state     = State::LOW;

    /*-------------------------------------------------
    GPIO: CE Input
    -------------------------------------------------*/
    hPhysical.cfg.ce.clear();
    hPhysical.cfg.ce.validity  = true;
    hPhysical.cfg.ce.threaded  = true;
    hPhysical.cfg.ce.alternate = Alternate::NONE;
    hPhysical.cfg.ce.drive     = Drive::OUTPUT_PUSH_PULL;
    hPhysical.cfg.ce.pin       = DC::IO::Radio::pinCE_pin;
    hPhysical.cfg.ce.port      = DC::IO::Radio::pinCE_port;
    hPhysical.cfg.ce.pull      = Pull::PULL_DN;
    hPhysical.cfg.ce.state     = State::LOW;

    /*-------------------------------------------------
    GPIO: CS Input
    -------------------------------------------------*/
    hPhysical.cfg.spi.CSInit.clear();
    hPhysical.cfg.spi.CSInit.validity  = true;
    hPhysical.cfg.spi.CSInit.threaded  = true;
    hPhysical.cfg.spi.CSInit.alternate = Alternate::NONE;
    hPhysical.cfg.spi.CSInit.drive     = Drive::OUTPUT_PUSH_PULL;
    hPhysical.cfg.spi.CSInit.pin       = DC::IO::Radio::pinCS_pin;
    hPhysical.cfg.spi.CSInit.port      = DC::IO::Radio::pinCS_port;
    hPhysical.cfg.spi.CSInit.pull      = Pull::PULL_UP;
    hPhysical.cfg.spi.CSInit.state     = State::HIGH;

    /*-------------------------------------------------
    SPI: These options are shared with GFX
    -------------------------------------------------*/
    // SCK
    hPhysical.cfg.spi.SCKInit.alternate = DC::IO::Radio::altSCK;
    hPhysical.cfg.spi.SCKInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    hPhysical.cfg.spi.SCKInit.pin       = DC::IO::Radio::pinSCK;
    hPhysical.cfg.spi.SCKInit.port      = DC::IO::Radio::spiPort;
    hPhysical.cfg.spi.SCKInit.pull      = Pull::NO_PULL;
    hPhysical.cfg.spi.SCKInit.state     = State::LOW;
    hPhysical.cfg.spi.SCKInit.threaded  = DC::IO::Radio::pinThreadMode;
    hPhysical.cfg.spi.SCKInit.validity  = true;

    // MOSI
    hPhysical.cfg.spi.MOSIInit.alternate = DC::IO::Radio::altMOSI;
    hPhysical.cfg.spi.MOSIInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    hPhysical.cfg.spi.MOSIInit.pin       = DC::IO::Radio::pinMOSI;
    hPhysical.cfg.spi.MOSIInit.port      = DC::IO::Radio::spiPort;
    hPhysical.cfg.spi.MOSIInit.pull      = Pull::NO_PULL;
    hPhysical.cfg.spi.MOSIInit.state     = State::LOW;
    hPhysical.cfg.spi.MOSIInit.threaded  = DC::IO::Radio::pinThreadMode;
    hPhysical.cfg.spi.MOSIInit.validity  = true;


    // MISO
    hPhysical.cfg.spi.MISOInit.alternate = DC::IO::Radio::altMISO;
    hPhysical.cfg.spi.MISOInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    hPhysical.cfg.spi.MISOInit.pin       = DC::IO::Radio::pinMISO;
    hPhysical.cfg.spi.MISOInit.port      = DC::IO::Radio::spiPort;
    hPhysical.cfg.spi.MISOInit.pull      = Pull::NO_PULL;
    hPhysical.cfg.spi.MISOInit.state     = State::LOW;
    hPhysical.cfg.spi.MISOInit.threaded  = DC::IO::Radio::pinThreadMode;
    hPhysical.cfg.spi.MISOInit.validity  = true;


    // SPI Parameters
    hPhysical.cfg.spi.validity           = true;
    hPhysical.cfg.spi.externalCS         = true;
    hPhysical.cfg.spi.HWInit.bitOrder    = DC::IO::Radio::spiBitOrder;
    hPhysical.cfg.spi.HWInit.clockFreq   = DC::IO::Radio::spiClockFreq;
    hPhysical.cfg.spi.HWInit.clockMode   = DC::IO::Radio::spiClockMode;
    hPhysical.cfg.spi.HWInit.controlMode = ControlMode::MASTER;
    hPhysical.cfg.spi.HWInit.csMode      = DC::IO::Radio::spiChipSelectMode;
    hPhysical.cfg.spi.HWInit.dataSize    = DC::IO::Radio::spiDataSize;
    hPhysical.cfg.spi.HWInit.hwChannel   = DC::IO::Radio::spiChannel;
    hPhysical.cfg.spi.HWInit.txfrMode    = DC::IO::Radio::spiTxfrMode;


    /*-------------------------------------------------------------------------------
    Hardware Driver Initialization
    -------------------------------------------------------------------------------*/
    auto result = Chimera::Status::OK;

    /*-------------------------------------------------
    Discrete GPIO: Chip Enable Pin
    -------------------------------------------------*/
    hPhysical.cePin = Chimera::GPIO::getDriver( hPhysical.cfg.ce.port, hPhysical.cfg.ce.pin );
    result |= hPhysical.cePin->init( hPhysical.cfg.ce );

    /*-------------------------------------------------
    Discrete GPIO: IRQ Pin
    -------------------------------------------------*/
    hPhysical.irqPin = Chimera::GPIO::getDriver( hPhysical.cfg.irq.port, hPhysical.cfg.irq.pin );
    result |= hPhysical.irqPin->init( hPhysical.cfg.irq );

    /*-------------------------------------------------
    SPI: Chip Select Pin
    -------------------------------------------------*/
    hPhysical.csPin = Chimera::GPIO::getDriver( hPhysical.cfg.spi.CSInit.port, hPhysical.cfg.spi.CSInit.pin );
    result |= hPhysical.csPin->init( hPhysical.cfg.spi.CSInit );

    /*-------------------------------------------------
    SPI: Protocol Settings
    -------------------------------------------------*/
    hPhysical.spi = Chimera::SPI::getDriver( hPhysical.cfg.spi.HWInit.hwChannel );
    result |= hPhysical.spi->init( hPhysical.cfg.spi );

    /*-------------------------------------------------
    Only register if the init was successful
    -------------------------------------------------*/
    if( result == Chimera::Status::OK )
    {
      netHandle.physical = &hPhysical;
    }

    return result;
  }


  Chimera::Status_t initNetStack_DATALINK( const RadioConfig &cfg )
  {
    /*-------------------------------------------------
    Initialize the config
    -------------------------------------------------*/
    hDatalink.clear();
    hDatalink.hwIRQEventTimeout = Chimera::Threading::TIMEOUT_25MS;

    /*-------------------------------------------------
    Register config with the network
    -------------------------------------------------*/
    netHandle.datalink = &hDatalink;
    return Chimera::Status::OK;
  }
}  // namespace DC::RF
