/********************************************************************************
 *  File Name:
 *    board_ST7735.cpp
 *
 *  Description:
 *    Implements hooks for the uGFX ST7735 low level driver.
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/event>
#include <Chimera/gpio>
#include <Chimera/spi>
#include <Chimera/thread>

/* Graphics Includes */
#include "gfx.h"
#include "board_ST7735.h"

/* Project Includes */
#include <src/config/board_map.hpp>

/*-------------------------------------------------------------------------------
Static Data
-------------------------------------------------------------------------------*/
/*-------------------------------------------------
GPIO: Data/Command
-------------------------------------------------*/
static constexpr Chimera::GPIO::Pin pinDC_pin   = DC::IO::GFX::pinDC_pin;
static constexpr Chimera::GPIO::Port pinDC_port = DC::IO::GFX::pinDC_port;
static Chimera::GPIO::Driver_rPtr pinDC;

/*-------------------------------------------------
GPIO: LCD Reset
-------------------------------------------------*/
static constexpr Chimera::GPIO::Pin pinRES_pin   = DC::IO::GFX::pinRES_pin;
static constexpr Chimera::GPIO::Port pinRES_port = DC::IO::GFX::pinRES_port;

/*-------------------------------------------------
GPIO: LCD Chip Select
-------------------------------------------------*/
static constexpr Chimera::GPIO::Pin pinCS_pin   = DC::IO::GFX::pinCS_pin;
static constexpr Chimera::GPIO::Port pinCS_port = DC::IO::GFX::pinCS_port;
static Chimera::GPIO::Driver_rPtr pinCS;

/*-------------------------------------------------
SPI
-------------------------------------------------*/
static constexpr Chimera::GPIO::Pin pinSCK              = DC::IO::GFX::pinSCK;
static constexpr Chimera::GPIO::Pin pinMOSI             = DC::IO::GFX::pinMOSI;
static constexpr Chimera::GPIO::Pin pinMISO             = DC::IO::GFX::pinMISO;
static constexpr Chimera::GPIO::Port spiPort            = DC::IO::GFX::spiPort;
static constexpr Chimera::SPI::Channel spiChannel       = DC::IO::GFX::spiChannel;
static constexpr Chimera::SPI::TransferMode spiTxfrMode = DC::IO::GFX::spiTxfrMode;
static Chimera::SPI::Driver_rPtr spi;


/*-------------------------------------------------------------------------------
Public Functions
-------------------------------------------------------------------------------*/
void init_board( GDisplay *g )
{
  using namespace Chimera;
  using namespace Chimera::GPIO;
  using namespace Chimera::SPI;

  /*-------------------------------------------------
  Initialize the various GPIO pins
  -------------------------------------------------*/
  PinInit tmp;
  auto initResult = Chimera::Status::OK;

  // Initialize the Data/Command pin
  tmp.clear();
  tmp.alternate = Alternate::NONE;
  tmp.drive     = Drive::OUTPUT_PUSH_PULL;
  tmp.pin       = pinDC_pin;
  tmp.port      = pinDC_port;
  tmp.pull      = Pull::NO_PULL;
  tmp.state     = State::LOW;
  tmp.threaded  = false;
  tmp.validity  = true;

  pinDC = GPIO::getDriver( tmp.port, tmp.pin );
  initResult |= pinDC->init( tmp );

  // Initialize the LCD reset pin
  tmp.clear();
  tmp.alternate = Alternate::NONE;
  tmp.drive     = Drive::OUTPUT_PUSH_PULL;
  tmp.pin       = pinRES_pin;
  tmp.port      = pinRES_port;
  tmp.pull      = Pull::NO_PULL;
  tmp.state     = State::LOW;
  tmp.threaded  = false;
  tmp.validity  = true;

  initResult |= GPIO::getDriver( tmp.port, tmp.pin )->init( tmp );

  // Initialize the LCD chip select pin
  tmp.clear();
  tmp.alternate = Alternate::NONE;
  tmp.drive     = Drive::OUTPUT_PUSH_PULL;
  tmp.pin       = pinCS_pin;
  tmp.port      = pinCS_port;
  tmp.pull      = Pull::NO_PULL;
  tmp.state     = State::LOW;
  tmp.threaded  = false;
  tmp.validity  = true;

  pinCS = GPIO::getDriver( tmp.port, tmp.pin );
  initResult |= pinCS->init( tmp );

  /*-------------------------------------------------
  Initialize the SPI driver
  -------------------------------------------------*/
  DriverConfig cfg;
  cfg.clear();

  // SCK
  cfg.SCKInit.alternate = Alternate::SPI3_SCK;
  cfg.SCKInit.drive     = Drive::ALTERNATE_PUSH_PULL;
  cfg.SCKInit.pin       = pinSCK;
  cfg.SCKInit.port      = spiPort;
  cfg.SCKInit.pull      = Pull::NO_PULL;
  cfg.SCKInit.state     = State::LOW;
  cfg.SCKInit.threaded  = true;
  cfg.SCKInit.validity  = true;

  // MOSI
  cfg.MOSIInit.alternate = Alternate::SPI3_MOSI;
  cfg.MOSIInit.drive     = Drive::ALTERNATE_PUSH_PULL;
  cfg.MOSIInit.pin       = pinMOSI;
  cfg.MOSIInit.port      = spiPort;
  cfg.MOSIInit.pull      = Pull::NO_PULL;
  cfg.MOSIInit.state     = State::LOW;
  cfg.MOSIInit.threaded  = true;
  cfg.MOSIInit.validity  = true;


  // MISO
  cfg.MISOInit.alternate = Alternate::SPI3_MISO;
  cfg.MISOInit.drive     = Drive::ALTERNATE_PUSH_PULL;
  cfg.MISOInit.pin       = pinMISO;
  cfg.MISOInit.port      = spiPort;
  cfg.MISOInit.pull      = Pull::NO_PULL;
  cfg.MISOInit.state     = State::LOW;
  cfg.MISOInit.threaded  = true;
  cfg.MISOInit.validity  = true;


  // SPI Parameters
  cfg.validity           = true;
  cfg.externalCS         = true;
  cfg.HWInit.bitOrder    = BitOrder::MSB_FIRST;
  cfg.HWInit.clockFreq   = 16000000;
  cfg.HWInit.clockMode   = ClockMode::MODE0;
  cfg.HWInit.controlMode = ControlMode::MASTER;
  cfg.HWInit.csMode      = CSMode::MANUAL;
  cfg.HWInit.dataSize    = DataSize::SZ_8BIT;
  cfg.HWInit.hwChannel   = spiChannel;
  cfg.HWInit.txfrMode    = spiTxfrMode;

  spi = Chimera::SPI::getDriver( cfg.HWInit.hwChannel );
  initResult |= spi->init( cfg );

  /*-------------------------------------------------
  Trap configuration issues
  -------------------------------------------------*/
  if ( initResult != Chimera::Status::OK )
  {
    Chimera::insert_debug_breakpoint();
    while ( 1 )
    {
      continue;
    }
  }

  /*-------------------------------------------------
  Set GPIO to their default states
  -------------------------------------------------*/
  pinCS->setState( GPIO::State::HIGH );
  pinDC->setState( GPIO::State::HIGH );
}


void post_init_board( GDisplay *g )
{
}


void setpin_reset( GDisplay *g, gBool state )
{
  /*-------------------------------------------------
  Reset is active high
  -------------------------------------------------*/
  auto driver = Chimera::GPIO::getDriver( pinRES_port, pinRES_pin );
  if ( state == gTrue )
  {
    driver->setState( Chimera::GPIO::State::LOW );
  }
  else
  {
    driver->setState( Chimera::GPIO::State::HIGH );
  }
}


void acquire_bus( GDisplay *g )
{
  spi->lock();
  pinCS->setState( Chimera::GPIO::State::LOW );
}


void release_bus( GDisplay *g )
{
  pinCS->setState( Chimera::GPIO::State::HIGH );
  spi->unlock();
}


void write_cmd( GDisplay *g, gU8 cmd )
{
  using namespace Chimera;

  /*-------------------------------------------------
  Command transactions have this pin low
  -------------------------------------------------*/
  pinDC->setState( GPIO::State::LOW );

  /*-------------------------------------------------
  Pump out the data
  -------------------------------------------------*/
  spi->readWriteBytes( &cmd, nullptr, sizeof( cmd ) );
  if constexpr ( spiTxfrMode != SPI::TransferMode::BLOCKING )
  {
    spi->await( Event::Trigger::TRIGGER_WRITE_COMPLETE, Threading::TIMEOUT_BLOCK );
  }
}


void write_data( GDisplay *g, gU16 data )
{
  using namespace Chimera;

  /*-------------------------------------------------
  Data transactions have this pin high
  -------------------------------------------------*/
  pinDC->setState( GPIO::State::HIGH );

  /*-------------------------------------------------
  Pump out the data. Data has to be swapped so that
  it comes out in the correct order for the chip.
  -------------------------------------------------*/
  gU16 swapped = ( ( data << 8 ) & 0xFF00 ) | ( ( data >> 8 ) & 0x00FF );

  spi->readWriteBytes( &swapped, nullptr, sizeof( swapped ) );
  if constexpr ( spiTxfrMode != SPI::TransferMode::BLOCKING )
  {
    spi->await( Event::Trigger::TRIGGER_WRITE_COMPLETE, Threading::TIMEOUT_BLOCK );
  }
}


void write_data_byte( GDisplay *g, gU8 data )
{
  using namespace Chimera;

  /*-------------------------------------------------
  Data transactions have this pin high
  -------------------------------------------------*/
  pinDC->setState( GPIO::State::HIGH );

  /*-------------------------------------------------
  Pump out the data
  -------------------------------------------------*/
  spi->readWriteBytes( &data, nullptr, sizeof( data ) );
  if constexpr ( spiTxfrMode != SPI::TransferMode::BLOCKING )
  {
    spi->await( Event::Trigger::TRIGGER_WRITE_COMPLETE, Threading::TIMEOUT_BLOCK );
  }
}

void set_backlight( GDisplay *g, gU8 percent )
{
  // Can't control this
}
