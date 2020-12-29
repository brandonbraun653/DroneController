/********************************************************************************
 *  File Name:
 *    board_map.hpp
 *
 *  Description:
 *    Maps system hardware resources for various development boards
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_BOARD_MAP_HPP
#define DC_BOARD_MAP_HPP

/* Chimera Includes */
#include <Chimera/gpio>
#include <Chimera/spi>

namespace DC::IO
{
  /*-------------------------------------------------------------------------------
  General GPIO
  -------------------------------------------------------------------------------*/
  namespace LED
  {
    /*-------------------------------------------------
    Heartbeat
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinHeartbeat   = 14;
    static constexpr Chimera::GPIO::Port portHeartbeat = Chimera::GPIO::Port::PORTC;
  }

  /*-------------------------------------------------------------------------------
  Graphics Hardware
  -------------------------------------------------------------------------------*/
  namespace GFX
  {
    /*-------------------------------------------------
    GPIO: Data/Command
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinDC_pin   = 1;
    static constexpr Chimera::GPIO::Port pinDC_port = Chimera::GPIO::Port::PORTB;

    /*-------------------------------------------------
    GPIO: LCD Reset
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinRES_pin   = 8;
    static constexpr Chimera::GPIO::Port pinRES_port = Chimera::GPIO::Port::PORTA;

    /*-------------------------------------------------
    GPIO: LCD Chip Select
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCS_pin   = 15;
    static constexpr Chimera::GPIO::Port pinCS_port = Chimera::GPIO::Port::PORTA;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinSCK              = 3;
    static constexpr Chimera::GPIO::Pin pinMOSI             = 5;
    static constexpr Chimera::GPIO::Pin pinMISO             = 4;
    static constexpr Chimera::GPIO::Port spiPort            = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::SPI::Channel spiChannel       = Chimera::SPI::Channel::SPI3;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
  }


  /*-------------------------------------------------------------------------------
  Radio Hardware
  -------------------------------------------------------------------------------*/
  namespace Radio
  {
    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinIRQ_pin   = 1;
    static constexpr Chimera::GPIO::Port pinIRQ_port = Chimera::GPIO::Port::PORTA;

    /*-------------------------------------------------
    GPIO: Chip Enable
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCE_pin   = 7;
    static constexpr Chimera::GPIO::Port pinCE_port = Chimera::GPIO::Port::PORTB;

    /*-------------------------------------------------
    GPIO: Chip Select
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCS_pin   = 6;
    static constexpr Chimera::GPIO::Port pinCS_port = Chimera::GPIO::Port::PORTB;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinSCK              = GFX::pinSCK;
    static constexpr Chimera::GPIO::Pin pinMOSI             = GFX::pinMOSI;
    static constexpr Chimera::GPIO::Pin pinMISO             = GFX::pinMISO;
    static constexpr Chimera::GPIO::Port spiPort            = GFX::spiPort;
    static constexpr Chimera::SPI::Channel spiChannel       = GFX::spiChannel;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = GFX::spiTxfrMode;
  } // namespace Radio

}

#endif  /* !DC_BOARD_MAP_HPP */
