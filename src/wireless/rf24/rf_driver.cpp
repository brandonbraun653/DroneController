/********************************************************************************
 *  File Name:
 *    rf_driver.cpp
 *
 *  Description:
 *    Implementation of the RF driver
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Ripple Includes */
#include <Ripple/netif/nrf24l01>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_discrete.hpp>
#include <src/io/pin_mapping.hpp>
#include <src/wireless/rf24/rf_driver.hpp>

namespace DC::RF::RF24
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_is_enabled = false;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initDriver()
  {
    /*-------------------------------------------------
    Initialize local data
    -------------------------------------------------*/
    s_is_enabled = false;
  }


  void setPower( const PowerState state )
  {
    if( state == PowerState::ENABLED )
    {
      HMI::Discrete::set( GPIO::Pin::RF24_PWR_EN );
      s_is_enabled = true;
    }
    else
    {
      HMI::Discrete::clear( GPIO::Pin::RF24_PWR_EN );
      s_is_enabled = false;
    }

    /*-------------------------------------------------
    Due to the asynchronous nature of HMI, wait a bit
    for this to take effect.
    -------------------------------------------------*/
    Chimera::delayMilliseconds( 25 );
  }


  void genRadioCfg( Ripple::NetIf::NRF24::Physical::Handle &config )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::SPI;
    using namespace Chimera::Thread;

    using namespace Ripple::NetIf::NRF24::Physical;

    config.clear();
    config.cfg.verifyRegisters      = true;
    config.cfg.hwRFChannel          = 150;
    config.cfg.hwAddressWidth       = AddressWidth::AW_5Byte;
    config.cfg.hwDataRate           = DataRate::DR_2MBPS;
    config.cfg.hwPowerAmplitude     = RFPower::PA_LVL_0;
    config.cfg.hwStaticPayloadWidth = 32;
    config.cfg.hwCRCLength          = CRCLength::CRC_16;
    config.cfg.hwISRMask            = bfISRMask::ISR_MSK_ALL;
    config.cfg.hwRTXDelay           = ART_DELAY_250uS;
    config.cfg.hwRTXCount           = ART_COUNT_3;

    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    config.cfg.irqEdge = DC::IO::Radio::pinIRQ_Trigger;

    config.cfg.irq.clear();
    config.cfg.irq.validity  = true;
    config.cfg.irq.threaded  = true;
    config.cfg.irq.alternate = Alternate::EXTERNAL_INTERRUPT;
    config.cfg.irq.drive     = Drive::INPUT;
    config.cfg.irq.pin       = DC::IO::Radio::pinIRQ_pin;
    config.cfg.irq.port      = DC::IO::Radio::pinIRQ_port;
    config.cfg.irq.pull      = Pull::PULL_DN;
    config.cfg.irq.state     = State::LOW;

    /*-------------------------------------------------
    GPIO: CE Input
    -------------------------------------------------*/
    config.cfg.ce.clear();
    config.cfg.ce.validity  = true;
    config.cfg.ce.threaded  = true;
    config.cfg.ce.alternate = Alternate::NONE;
    config.cfg.ce.drive     = Drive::OUTPUT_PUSH_PULL;
    config.cfg.ce.pin       = DC::IO::Radio::pinCE_pin;
    config.cfg.ce.port      = DC::IO::Radio::pinCE_port;
    config.cfg.ce.pull      = Pull::PULL_DN;
    config.cfg.ce.state     = State::LOW;

    /*-------------------------------------------------
    GPIO: CS Input
    -------------------------------------------------*/
    config.cfg.spi.CSInit.clear();
    config.cfg.spi.CSInit.validity  = true;
    config.cfg.spi.CSInit.threaded  = true;
    config.cfg.spi.CSInit.alternate = Alternate::NONE;
    config.cfg.spi.CSInit.drive     = Drive::OUTPUT_PUSH_PULL;
    config.cfg.spi.CSInit.pin       = DC::IO::Radio::pinCS_pin;
    config.cfg.spi.CSInit.port      = DC::IO::Radio::pinCS_port;
    config.cfg.spi.CSInit.pull      = Pull::PULL_UP;
    config.cfg.spi.CSInit.state     = State::HIGH;

    /*-------------------------------------------------
    SPI: These options are shared with GFX
    -------------------------------------------------*/
    // SCK
    config.cfg.spi.SCKInit.alternate = DC::IO::Radio::altSCK;
    config.cfg.spi.SCKInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    config.cfg.spi.SCKInit.pin       = DC::IO::Radio::pinSCK;
    config.cfg.spi.SCKInit.port      = DC::IO::Radio::spiPort;
    config.cfg.spi.SCKInit.pull      = Pull::NO_PULL;
    config.cfg.spi.SCKInit.state     = State::LOW;
    config.cfg.spi.SCKInit.threaded  = DC::IO::Radio::pinThreadMode;
    config.cfg.spi.SCKInit.validity  = true;

    // MOSI
    config.cfg.spi.MOSIInit.alternate = DC::IO::Radio::altMOSI;
    config.cfg.spi.MOSIInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    config.cfg.spi.MOSIInit.pin       = DC::IO::Radio::pinMOSI;
    config.cfg.spi.MOSIInit.port      = DC::IO::Radio::spiPort;
    config.cfg.spi.MOSIInit.pull      = Pull::NO_PULL;
    config.cfg.spi.MOSIInit.state     = State::LOW;
    config.cfg.spi.MOSIInit.threaded  = DC::IO::Radio::pinThreadMode;
    config.cfg.spi.MOSIInit.validity  = true;


    // MISO
    config.cfg.spi.MISOInit.alternate = DC::IO::Radio::altMISO;
    config.cfg.spi.MISOInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    config.cfg.spi.MISOInit.pin       = DC::IO::Radio::pinMISO;
    config.cfg.spi.MISOInit.port      = DC::IO::Radio::spiPort;
    config.cfg.spi.MISOInit.pull      = Pull::NO_PULL;
    config.cfg.spi.MISOInit.state     = State::LOW;
    config.cfg.spi.MISOInit.threaded  = DC::IO::Radio::pinThreadMode;
    config.cfg.spi.MISOInit.validity  = true;


    // SPI Parameters
    config.cfg.spi.validity           = true;
    config.cfg.spi.externalCS         = true;
    config.cfg.spi.HWInit.validity    = true;
    config.cfg.spi.HWInit.bitOrder    = DC::IO::Radio::spiBitOrder;
    config.cfg.spi.HWInit.clockFreq   = DC::IO::Radio::spiClockFreq;
    config.cfg.spi.HWInit.clockMode   = DC::IO::Radio::spiClockMode;
    config.cfg.spi.HWInit.controlMode = ControlMode::MASTER;
    config.cfg.spi.HWInit.csMode      = DC::IO::Radio::spiChipSelectMode;
    config.cfg.spi.HWInit.dataSize    = DC::IO::Radio::spiDataSize;
    config.cfg.spi.HWInit.hwChannel   = DC::IO::Radio::spiChannel;
    config.cfg.spi.HWInit.txfrMode    = DC::IO::Radio::spiTxfrMode;

  }
}  // namespace DC::RF
