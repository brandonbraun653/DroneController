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
#include <Chimera/exti>
#include <Chimera/gpio>
#include <Chimera/spi>

// Until the full PCB is made, the dev board is a Nucleo-F446RE
#include <Chimera/bsp/nucleo/nucleo_f446re.hpp>

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
    static constexpr Chimera::GPIO::Pin pinHeartbeat   = 8;
    static constexpr Chimera::GPIO::Port portHeartbeat = Chimera::GPIO::Port::PORTA;
  }    // namespace LED

  /*-------------------------------------------------------------------------------
  NOR Flash - SPI1
  -------------------------------------------------------------------------------*/
  namespace NOR
  {
    /*-------------------------------------------------
    GPIO
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin sckPin        = BSP::Nucleo::F446RE::SPI::SPI1::sckPin;
    static constexpr Chimera::GPIO::Port sckPort      = BSP::Nucleo::F446RE::SPI::SPI1::sckPort;
    static constexpr Chimera::GPIO::Alternate sckAlt  = Chimera::GPIO::Alternate::SPI1_SCK;
    static constexpr Chimera::GPIO::Pin mosiPin       = BSP::Nucleo::F446RE::SPI::SPI1::mosiPin;
    static constexpr Chimera::GPIO::Port mosiPort     = BSP::Nucleo::F446RE::SPI::SPI1::mosiPort;
    static constexpr Chimera::GPIO::Alternate mosiAlt = Chimera::GPIO::Alternate::SPI1_MOSI;
    static constexpr Chimera::GPIO::Pin misoPin       = BSP::Nucleo::F446RE::SPI::SPI1::misoPin;
    static constexpr Chimera::GPIO::Port misoPort     = BSP::Nucleo::F446RE::SPI::SPI1::misoPort;
    static constexpr Chimera::GPIO::Alternate misoAlt = Chimera::GPIO::Alternate::SPI1_MISO;
    static constexpr Chimera::GPIO::Pin csPin         = BSP::Nucleo::F446RE::SPI::SPI1::csPin;
    static constexpr Chimera::GPIO::Port csPort       = BSP::Nucleo::F446RE::SPI::SPI1::csPort;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr Chimera::SPI::Channel spiChannel       = Chimera::SPI::Channel::SPI1;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::INTERRUPT;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 32000000;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = Chimera::SPI::ClockMode::MODE0;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = Chimera::SPI::CSMode::MANUAL;
    static constexpr Chimera::SPI::DataSize spiDataSize     = Chimera::SPI::DataSize::SZ_8BIT;
  }

  /*-------------------------------------------------------------------------------
  Graphics Hardware - SPI2
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
    static constexpr bool pinThreadMode = true;

    static constexpr Chimera::GPIO::Pin pinSCK  = 3;
    static constexpr Chimera::GPIO::Pin pinMOSI = 5;
    static constexpr Chimera::GPIO::Pin pinMISO = 4;

    static constexpr Chimera::SPI::Channel spiChannel = Chimera::SPI::Channel::SPI3;
    static constexpr Chimera::GPIO::Alternate altSCK  = Chimera::GPIO::Alternate::SPI3_SCK;
    static constexpr Chimera::GPIO::Alternate altMOSI = Chimera::GPIO::Alternate::SPI3_MOSI;
    static constexpr Chimera::GPIO::Alternate altMISO = Chimera::GPIO::Alternate::SPI3_MISO;

    static constexpr Chimera::GPIO::Port spiPort            = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 8000000;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = Chimera::SPI::ClockMode::MODE0;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = Chimera::SPI::CSMode::MANUAL;
    static constexpr Chimera::SPI::DataSize spiDataSize     = Chimera::SPI::DataSize::SZ_8BIT;
  }    // namespace GFX


  /*-------------------------------------------------------------------------------
  Radio Hardware - SPI3
  -------------------------------------------------------------------------------*/
  namespace Radio
  {
    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinIRQ_pin             = 1;
    static constexpr Chimera::GPIO::Port pinIRQ_port           = Chimera::GPIO::Port::PORTA;
    static constexpr Chimera::EXTI::EdgeTrigger pinIRQ_Trigger = Chimera::EXTI::EdgeTrigger::FALLING_EDGE;

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
    static constexpr bool pinThreadMode = GFX::pinThreadMode;

    static constexpr Chimera::GPIO::Pin pinSCK        = GFX::pinSCK;
    static constexpr Chimera::GPIO::Alternate altSCK  = GFX::altSCK;
    static constexpr Chimera::GPIO::Pin pinMOSI       = GFX::pinMOSI;
    static constexpr Chimera::GPIO::Alternate altMOSI = GFX::altMOSI;
    static constexpr Chimera::GPIO::Pin pinMISO       = GFX::pinMISO;
    static constexpr Chimera::GPIO::Alternate altMISO = GFX::altMISO;
    static constexpr Chimera::GPIO::Port spiPort      = GFX::spiPort;

    static constexpr Chimera::SPI::Channel spiChannel       = GFX::spiChannel;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = GFX::spiTxfrMode;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = GFX::spiBitOrder;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = GFX::spiClockFreq;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = GFX::spiClockMode;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = GFX::spiChipSelectMode;
    static constexpr Chimera::SPI::DataSize spiDataSize     = GFX::spiDataSize;
  }    // namespace Radio

}    // namespace DC::IO

#endif /* !DC_BOARD_MAP_HPP */
