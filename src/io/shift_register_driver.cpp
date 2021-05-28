/********************************************************************************
 *  File Name:
 *    sr_driver.cpp
 *
 *  Description:
 *    Shift register driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Logging */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/gpio>
#include <Chimera/spi>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/io/shift_register_driver.hpp>
#include <src/io/pin_mapping.hpp>

namespace DC::GPIO::SR
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Chimera::GPIO::Driver_rPtr KeyInCS;
  static Chimera::GPIO::Driver_rPtr KeyInSample;
  static Chimera::GPIO::Driver_rPtr KeyOutCS;

  static Chimera::SPI::Driver_rPtr KeySPI;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void init()
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::SPI;
    using namespace DC::IO::SR;

    Chimera::SPI::DriverConfig spiCfg;
    Chimera::GPIO::PinInit pinCfg;
    Chimera::Status_t initResult = Chimera::Status::OK;

    /*-------------------------------------------------
    Configure the input shift register chip select
    -------------------------------------------------*/
    pinCfg.clear();

    pinCfg.alternate = Alternate::NONE;
    pinCfg.drive     = Drive::OUTPUT_PUSH_PULL;
    pinCfg.pin       = csPin_KeyIn;
    pinCfg.port      = csPort_KeyIn;
    pinCfg.pull      = Pull::NO_PULL;
    pinCfg.state     = State::LOW;
    pinCfg.threaded  = false;
    pinCfg.validity  = true;

    KeyInCS = Chimera::GPIO::getDriver( csPort_KeyIn, csPin_KeyIn );
    initResult = KeyInCS->init( pinCfg );
    LOG_IF_ERROR( initResult == Chimera::Status::OK, "Key input CS init fail\n" );

    /*-------------------------------------------------
    Configure the input shift register strobe pin
    -------------------------------------------------*/
    pinCfg.clear();

    pinCfg.alternate = Alternate::NONE;
    pinCfg.drive     = Drive::OUTPUT_PUSH_PULL;
    pinCfg.pin       = csPin_KeySample;
    pinCfg.port      = csPort_KeySample;
    pinCfg.pull      = Pull::NO_PULL;
    pinCfg.state     = State::LOW;
    pinCfg.threaded  = false;
    pinCfg.validity  = true;

    KeyInSample = Chimera::GPIO::getDriver( csPort_KeySample, csPin_KeySample );
    initResult = KeyInSample->init( pinCfg );
    LOG_IF_ERROR( initResult == Chimera::Status::OK, "Key input strobe init fail\n" );

    /*-------------------------------------------------
    Configure the input shift register strobe pin
    -------------------------------------------------*/
    pinCfg.clear();

    pinCfg.alternate = Alternate::NONE;
    pinCfg.drive     = Drive::OUTPUT_PUSH_PULL;
    pinCfg.pin       = csPin_KeyOut;
    pinCfg.port      = csPort_KeyOut;
    pinCfg.pull      = Pull::NO_PULL;
    pinCfg.state     = State::LOW;
    pinCfg.threaded  = false;
    pinCfg.validity  = true;

    KeyOutCS = Chimera::GPIO::getDriver( csPort_KeyOut, csPin_KeyOut );
    initResult = KeyOutCS->init( pinCfg );
    LOG_IF_ERROR( initResult == Chimera::Status::OK, "Key output CS init fail\n" );

    /*-------------------------------------------------
    Configure SPI pins
    -------------------------------------------------*/
    // SCK
    spiCfg.SCKInit.alternate = sckAlt;
    spiCfg.SCKInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    spiCfg.SCKInit.pin       = sckPin;
    spiCfg.SCKInit.port      = sckPort;
    spiCfg.SCKInit.pull      = Pull::NO_PULL;
    spiCfg.SCKInit.state     = State::LOW;
    spiCfg.SCKInit.threaded  = true;
    spiCfg.SCKInit.validity  = true;

    // MOSI
    spiCfg.MOSIInit.alternate = mosiAlt;
    spiCfg.MOSIInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    spiCfg.MOSIInit.pin       = mosiPin;
    spiCfg.MOSIInit.port      = mosiPort;
    spiCfg.MOSIInit.pull      = Pull::NO_PULL;
    spiCfg.MOSIInit.state     = State::LOW;
    spiCfg.MOSIInit.threaded  = true;
    spiCfg.MOSIInit.validity  = true;

    // MISO
    spiCfg.MISOInit.alternate = misoAlt;
    spiCfg.MISOInit.drive     = Drive::ALTERNATE_PUSH_PULL;
    spiCfg.MISOInit.pin       = misoPin;
    spiCfg.MISOInit.port      = misoPort;
    spiCfg.MISOInit.pull      = Pull::NO_PULL;
    spiCfg.MISOInit.state     = State::LOW;
    spiCfg.MISOInit.threaded  = true;
    spiCfg.MISOInit.validity  = true;

    /*-------------------------------------------------
    Configure the SPI driver
    -------------------------------------------------*/
    spiCfg.validity           = true;
    spiCfg.externalCS         = true;
    spiCfg.HWInit.bitOrder    = spiBitOrder;
    spiCfg.HWInit.clockFreq   = spiClockFreq;
    spiCfg.HWInit.clockMode   = spiClockMode;
    spiCfg.HWInit.controlMode = ControlMode::MASTER;
    spiCfg.HWInit.csMode      = spiChipSelectMode;
    spiCfg.HWInit.dataSize    = spiDataSize;
    spiCfg.HWInit.hwChannel   = spiChannel;
    spiCfg.HWInit.txfrMode    = spiTxfrMode;

    KeySPI = Chimera::SPI::getDriver( spiChannel );
    initResult = KeySPI->init( spiCfg );
    LOG_IF_ERROR( initResult == Chimera::Status::OK, "Shift register SPI init failed\n" );

    /*-------------------------------------------------
    Set the initial state of the IO
    -------------------------------------------------*/
    KeyInCS->setState( State::HIGH );
    KeyInSample->setState( State::HIGH );
    KeyOutCS->setState( State::HIGH );

    /*-------------------------------------------------
    Register the pin map
    -------------------------------------------------*/
    initPinMap();
  }


  void read( void *const buffer, const size_t bytes )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Guarantee access to the device
    -------------------------------------------------*/
    KeySPI->lock();

    /*-------------------------------------------------
    Strobe the sample pin to lock in a new measurement
    -------------------------------------------------*/
    KeyInSample->setState( State::LOW );
    Chimera::blockDelayMicroseconds( 1 );
    KeyInSample->setState( State::HIGH );
    Chimera::blockDelayMicroseconds( 1 );

    /*-------------------------------------------------
    Read out the requested number of bytes
    -------------------------------------------------*/
    KeyInCS->setState( State::LOW );
    KeySPI->readBytes( buffer, bytes );
    KeySPI->await( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE, TIMEOUT_BLOCK );
    KeyInCS->setState( State::HIGH );

    /*-------------------------------------------------
    Unlock the device
    -------------------------------------------------*/
    KeySPI->unlock();
  }


  void write( const void *const buffer, const uint32_t bytes )
  {
    using namespace Chimera::GPIO;
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Guarantee access to the device
    -------------------------------------------------*/
    KeySPI->lock();

    /*-------------------------------------------------
    Write out the requested number of bytes
    -------------------------------------------------*/
    KeyOutCS->setState( State::LOW );
    KeySPI->writeBytes( buffer, bytes );
    KeySPI->await( Chimera::Event::Trigger::TRIGGER_TRANSFER_COMPLETE, TIMEOUT_BLOCK );
    KeyOutCS->setState( State::HIGH );

    /*-------------------------------------------------
    Unlock the device
    -------------------------------------------------*/
    KeySPI->unlock();
  }
}    // namespace DC::GPIO::SR
