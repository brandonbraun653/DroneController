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
  Static Data
  -------------------------------------------------------------------------------*/
  static Ripple::NetStackHandle netHandle;    /* Network device object */
  static Ripple::PHY::DeviceHandle hPhysical; /* Physical layer handle */

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

    netHandle.physical = &hPhysical;

    /*-------------------------------------------------------------------------------
    Physical Layer Settings
    -------------------------------------------------------------------------------*/
    /*-------------------------------------------------
    Radio properties
    -------------------------------------------------*/
    hPhysical.cfg.hwAddressWidth   = Ripple::PHY::AddressWidth::AW_5Byte;
    hPhysical.cfg.hwCRCLength      = Ripple::PHY::CRCLength::CRC_16;
    hPhysical.cfg.hwDataRate       = Ripple::PHY::DataRate::DR_1MBPS;
    hPhysical.cfg.hwISRMask        = Ripple::PHY::bfISRMask::ISR_MSK_ALL;
    hPhysical.cfg.hwPowerAmplitude = Ripple::PHY::PowerAmplitude::PA_LOW;
    hPhysical.cfg.hwRFChannel      = 96;
    hPhysical.cfg.hwRTXDelay       = Ripple::PHY::ART_DELAY_500uS;

    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    hPhysical.cfg.irq.clear();
    hPhysical.cfg.irq.validity  = true;
    hPhysical.cfg.irq.threaded  = true;
    hPhysical.cfg.irq.alternate = Alternate::EXTERNAL_INTERRUPT;
    hPhysical.cfg.irq.drive     = Drive::INPUT;
    hPhysical.cfg.irq.pin       = DC::IO::Radio::pinIRQ_pin;
    hPhysical.cfg.irq.port      = DC::IO::Radio::pinIRQ_port;
    hPhysical.cfg.irq.pull      = Pull::PULL_DN;
    hPhysical.cfg.irq.state     = State::LOW;

    // TODO: Configure the EXTI driver


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
    SPI
    -------------------------------------------------*/
    // SCK
    hPhysical.cfg.spi.SCKInit.alternate = Alternate::SPI3_SCK;
    hPhysical.cfg.spi.SCKInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    hPhysical.cfg.spi.SCKInit.pin       = DC::IO::Radio::pinSCK;
    hPhysical.cfg.spi.SCKInit.port      = DC::IO::Radio::spiPort;
    hPhysical.cfg.spi.SCKInit.pull      = Pull::NO_PULL;
    hPhysical.cfg.spi.SCKInit.state     = State::LOW;
    hPhysical.cfg.spi.SCKInit.threaded  = true;
    hPhysical.cfg.spi.SCKInit.validity  = true;

    // MOSI
    hPhysical.cfg.spi.MOSIInit.alternate = Alternate::SPI3_MOSI;
    hPhysical.cfg.spi.MOSIInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    hPhysical.cfg.spi.MOSIInit.pin       = DC::IO::Radio::pinMOSI;
    hPhysical.cfg.spi.MOSIInit.port      = DC::IO::Radio::spiPort;
    hPhysical.cfg.spi.MOSIInit.pull      = Pull::NO_PULL;
    hPhysical.cfg.spi.MOSIInit.state     = State::LOW;
    hPhysical.cfg.spi.MOSIInit.threaded  = true;
    hPhysical.cfg.spi.MOSIInit.validity  = true;


    // MISO
    hPhysical.cfg.spi.MISOInit.alternate = Alternate::SPI3_MISO;
    hPhysical.cfg.spi.MISOInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    hPhysical.cfg.spi.MISOInit.pin       = DC::IO::Radio::pinMISO;
    hPhysical.cfg.spi.MISOInit.port      = DC::IO::Radio::spiPort;
    hPhysical.cfg.spi.MISOInit.pull      = Pull::NO_PULL;
    hPhysical.cfg.spi.MISOInit.state     = State::LOW;
    hPhysical.cfg.spi.MISOInit.threaded  = true;
    hPhysical.cfg.spi.MISOInit.validity  = true;


    // SPI Parameters
    hPhysical.cfg.spi.validity           = true;
    hPhysical.cfg.spi.externalCS         = true;
    hPhysical.cfg.spi.HWInit.bitOrder    = BitOrder::MSB_FIRST;
    hPhysical.cfg.spi.HWInit.clockFreq   = 8000000;
    hPhysical.cfg.spi.HWInit.clockMode   = ClockMode::MODE0;
    hPhysical.cfg.spi.HWInit.controlMode = ControlMode::MASTER;
    hPhysical.cfg.spi.HWInit.csMode      = CSMode::MANUAL;
    hPhysical.cfg.spi.HWInit.dataSize    = DataSize::SZ_8BIT;
    hPhysical.cfg.spi.HWInit.hwChannel   = DC::IO::Radio::spiChannel;
    hPhysical.cfg.spi.HWInit.txfrMode    = DC::IO::Radio::spiTxfrMode;


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
