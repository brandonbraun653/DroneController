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
#include <Ripple/physical>

/* Project Includes */
#include <src/config/board_map.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_monitor.hpp>
#include <src/tasks/tsk_radio.hpp>


namespace DC::Tasks::RADIO
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void RadioThread( void *arg )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::SPI;
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------
    For now, build up a session object just for low
    level testing.
    -------------------------------------------------*/
    Ripple::NetStackHandle netHandle;
    Ripple::PHY::DeviceHandle devHandle;

    netHandle.physical = &devHandle;

    /*-------------------------------------------------------------------------------
    Physical Layer Settings
    -------------------------------------------------------------------------------*/
    /*-------------------------------------------------
    Radio properties
    -------------------------------------------------*/
    devHandle.cfg.hwAddressWidth   = Ripple::PHY::AddressWidth::AW_5Byte;
    devHandle.cfg.hwCRCLength      = Ripple::PHY::CRCLength::CRC_16;
    devHandle.cfg.hwDataRate       = Ripple::PHY::DataRate::DR_1MBPS;
    devHandle.cfg.hwISRMask        = Ripple::PHY::bfISRMask::ISR_MSK_ALL;
    devHandle.cfg.hwPowerAmplitude = Ripple::PHY::PowerAmplitude::PA_LOW;
    devHandle.cfg.hwRFChannel      = 96;
    devHandle.cfg.hwRTXDelay       = Ripple::PHY::ART_DELAY_500uS;

    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    devHandle.cfg.irq.clear();
    devHandle.cfg.irq.validity  = true;
    devHandle.cfg.irq.threaded  = true;
    devHandle.cfg.irq.alternate = Alternate::EXTERNAL_INTERRUPT;
    devHandle.cfg.irq.drive     = Drive::INPUT;
    devHandle.cfg.irq.pin       = DC::IO::Radio::pinIRQ_pin;
    devHandle.cfg.irq.port      = DC::IO::Radio::pinIRQ_port;
    devHandle.cfg.irq.pull      = Pull::PULL_DN;
    devHandle.cfg.irq.state     = State::LOW;

    // TODO: Configure the EXTI driver


    /*-------------------------------------------------
    GPIO: CE Input
    -------------------------------------------------*/
    devHandle.cfg.ce.clear();
    devHandle.cfg.ce.validity  = true;
    devHandle.cfg.ce.threaded  = true;
    devHandle.cfg.ce.alternate = Alternate::NONE;
    devHandle.cfg.ce.drive     = Drive::OUTPUT_PUSH_PULL;
    devHandle.cfg.ce.pin       = DC::IO::Radio::pinCE_pin;
    devHandle.cfg.ce.port      = DC::IO::Radio::pinCE_port;
    devHandle.cfg.ce.pull      = Pull::PULL_DN;
    devHandle.cfg.ce.state     = State::LOW;

    /*-------------------------------------------------
    GPIO: CS Input
    -------------------------------------------------*/
    devHandle.cfg.spi.CSInit.clear();
    devHandle.cfg.spi.CSInit.validity  = true;
    devHandle.cfg.spi.CSInit.threaded  = true;
    devHandle.cfg.spi.CSInit.alternate = Alternate::NONE;
    devHandle.cfg.spi.CSInit.drive     = Drive::OUTPUT_PUSH_PULL;
    devHandle.cfg.spi.CSInit.pin       = DC::IO::Radio::pinCS_pin;
    devHandle.cfg.spi.CSInit.port      = DC::IO::Radio::pinCS_port;
    devHandle.cfg.spi.CSInit.pull      = Pull::PULL_UP;
    devHandle.cfg.spi.CSInit.state     = State::HIGH;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    // SCK
    devHandle.cfg.spi.SCKInit.alternate = Alternate::SPI3_SCK;
    devHandle.cfg.spi.SCKInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    devHandle.cfg.spi.SCKInit.pin       = DC::IO::Radio::pinSCK;
    devHandle.cfg.spi.SCKInit.port      = DC::IO::Radio::spiPort;
    devHandle.cfg.spi.SCKInit.pull      = Pull::NO_PULL;
    devHandle.cfg.spi.SCKInit.state     = State::LOW;
    devHandle.cfg.spi.SCKInit.threaded  = true;
    devHandle.cfg.spi.SCKInit.validity  = true;

    // MOSI
    devHandle.cfg.spi.MOSIInit.alternate = Alternate::SPI3_MOSI;
    devHandle.cfg.spi.MOSIInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    devHandle.cfg.spi.MOSIInit.pin       = DC::IO::Radio::pinMOSI;
    devHandle.cfg.spi.MOSIInit.port      = DC::IO::Radio::spiPort;
    devHandle.cfg.spi.MOSIInit.pull      = Pull::NO_PULL;
    devHandle.cfg.spi.MOSIInit.state     = State::LOW;
    devHandle.cfg.spi.MOSIInit.threaded  = true;
    devHandle.cfg.spi.MOSIInit.validity  = true;


    // MISO
    devHandle.cfg.spi.MISOInit.alternate = Alternate::SPI3_MISO;
    devHandle.cfg.spi.MISOInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    devHandle.cfg.spi.MISOInit.pin       = DC::IO::Radio::pinMISO;
    devHandle.cfg.spi.MISOInit.port      = DC::IO::Radio::spiPort;
    devHandle.cfg.spi.MISOInit.pull      = Pull::NO_PULL;
    devHandle.cfg.spi.MISOInit.state     = State::LOW;
    devHandle.cfg.spi.MISOInit.threaded  = true;
    devHandle.cfg.spi.MISOInit.validity  = true;


    // SPI Parameters
    devHandle.cfg.spi.validity           = true;
    devHandle.cfg.spi.externalCS         = true;
    devHandle.cfg.spi.HWInit.bitOrder    = BitOrder::MSB_FIRST;
    devHandle.cfg.spi.HWInit.clockFreq   = 8000000;
    devHandle.cfg.spi.HWInit.clockMode   = ClockMode::MODE0;
    devHandle.cfg.spi.HWInit.controlMode = ControlMode::MASTER;
    devHandle.cfg.spi.HWInit.csMode      = CSMode::MANUAL;
    devHandle.cfg.spi.HWInit.dataSize    = DataSize::SZ_8BIT;
    devHandle.cfg.spi.HWInit.hwChannel   = DC::IO::Radio::spiChannel;
    devHandle.cfg.spi.HWInit.txfrMode    = DC::IO::Radio::spiTxfrMode;


    /*-------------------------------------------------
    Start the network stack
    -------------------------------------------------*/
    auto linkService = Ripple::DATALINK::Service();

    ThreadDelegate tFunc = ThreadDelegate::create<Ripple::DATALINK::Service, &Ripple::DATALINK::Service::run>( linkService );

    Thread datalink;
    datalink.initialize( tFunc, reinterpret_cast<void *>( &netHandle ), Priority::LEVEL_3, Ripple::DATALINK::THREAD_STACK,
                         Ripple::DATALINK::THREAD_NAME.cbegin() );
    auto tId = datalink.start();

    sendTaskMsg( tId, ITCMsg::ITC_WAKEUP, TIMEOUT_DONT_WAIT );

    while ( 1 )
    {
      MON::kickDog( TaskId::RADIO );
      Chimera::delayMilliseconds( 100 );
    }
  }

}  // namespace DC::Tasks::RADIO
