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
#include <Chimera/serial>

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
    static constexpr Chimera::GPIO::Port portHeartbeat = Chimera::GPIO::Port::PORTC;
  }    // namespace LED

  namespace HMI
  {
    /*-------------------------------------------------
    Common input configuration structure. This needs to
    have the pin, port, and validity flags overriden.
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::PinInit CommonInputCfg = { .alternate = Chimera::GPIO::Alternate::NONE,
                                                               .drive     = Chimera::GPIO::Drive::INPUT,
                                                               .pin       = 0,
                                                               .port      = Chimera::GPIO::Port::UNKNOWN_PORT,
                                                               .pull      = Chimera::GPIO::Pull::PULL_UP,
                                                               .state     = Chimera::GPIO::State::HIGH,
                                                               .threaded  = true,
                                                               .validity  = false };

    // TODO: Need to redo these. Currently conflict with Radio.

    /*-------------------------------------------------
    Button/Key Input 0
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinKeyIn0   = 3;
    static constexpr Chimera::GPIO::Port portKeyIn0 = Chimera::GPIO::Port::PORTC;

    namespace Encoder
    {
      /*-------------------------------------------------
      Rotary Encoder 0
      -------------------------------------------------*/
      static constexpr Chimera::GPIO::Pin pinBtnIn0   = 0;
      static constexpr Chimera::GPIO::Port portBtnIn0 = Chimera::GPIO::Port::PORTC;

      static constexpr Chimera::GPIO::Pin pinA   = 1;
      static constexpr Chimera::GPIO::Port portA = Chimera::GPIO::Port::PORTC;

      static constexpr Chimera::GPIO::Pin pinB   = 2;
      static constexpr Chimera::GPIO::Port portB = Chimera::GPIO::Port::PORTC;
    }
  }    // namespace HMI

  /*-------------------------------------------------------------------------------
  NOR Flash - SPI3
  -------------------------------------------------------------------------------*/
  namespace NOR
  {
    /*-------------------------------------------------
    GPIO
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin sckPin        = BSP::Nucleo::F446RE::SPI::SPI3::sckPin;
    static constexpr Chimera::GPIO::Port sckPort      = BSP::Nucleo::F446RE::SPI::SPI3::sckPort;
    static constexpr Chimera::GPIO::Alternate sckAlt  = Chimera::GPIO::Alternate::SPI3_SCK;
    static constexpr Chimera::GPIO::Pin mosiPin       = BSP::Nucleo::F446RE::SPI::SPI3::mosiPin;
    static constexpr Chimera::GPIO::Port mosiPort     = BSP::Nucleo::F446RE::SPI::SPI3::mosiPort;
    static constexpr Chimera::GPIO::Alternate mosiAlt = Chimera::GPIO::Alternate::SPI3_MOSI;
    static constexpr Chimera::GPIO::Pin misoPin       = BSP::Nucleo::F446RE::SPI::SPI3::misoPin;
    static constexpr Chimera::GPIO::Port misoPort     = BSP::Nucleo::F446RE::SPI::SPI3::misoPort;
    static constexpr Chimera::GPIO::Alternate misoAlt = Chimera::GPIO::Alternate::SPI3_MISO;
    static constexpr Chimera::GPIO::Pin csPin         = BSP::Nucleo::F446RE::SPI::SPI3::csPin;
    static constexpr Chimera::GPIO::Port csPort       = BSP::Nucleo::F446RE::SPI::SPI3::csPort;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr Chimera::SPI::Channel spiChannel       = Chimera::SPI::Channel::SPI3;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 1 * 1000000;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = Chimera::SPI::ClockMode::MODE0;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = Chimera::SPI::CSMode::MANUAL;
    static constexpr Chimera::SPI::DataSize spiDataSize     = Chimera::SPI::DataSize::SZ_8BIT;
  }    // namespace NOR

  /*-------------------------------------------------------------------------------
  Graphics Hardware - SPI2
  -------------------------------------------------------------------------------*/
  namespace GFX
  {
    /*-------------------------------------------------
    GPIO: Data/Command
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinDC_pin   = 5;
    static constexpr Chimera::GPIO::Port pinDC_port = Chimera::GPIO::Port::PORTB;

    /*-------------------------------------------------
    GPIO: LCD Reset
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinRES_pin   = 3;
    static constexpr Chimera::GPIO::Port pinRES_port = Chimera::GPIO::Port::PORTB;

    /*-------------------------------------------------
    GPIO: LCD Chip Select
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCS_pin   = BSP::Nucleo::F446RE::SPI::SPI2::csPin;
    static constexpr Chimera::GPIO::Port pinCS_port = BSP::Nucleo::F446RE::SPI::SPI2::csPort;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr bool pinThreadMode = true;

    static constexpr Chimera::GPIO::Pin pinSCK  = BSP::Nucleo::F446RE::SPI::SPI2::sckPin;
    static constexpr Chimera::GPIO::Pin pinMOSI = BSP::Nucleo::F446RE::SPI::SPI2::mosiPin;
    static constexpr Chimera::GPIO::Pin pinMISO = BSP::Nucleo::F446RE::SPI::SPI2::misoPin;

    static constexpr Chimera::SPI::Channel spiChannel = Chimera::SPI::Channel::SPI2;
    static constexpr Chimera::GPIO::Alternate altSCK  = Chimera::GPIO::Alternate::SPI2_SCK;
    static constexpr Chimera::GPIO::Alternate altMOSI = Chimera::GPIO::Alternate::SPI2_MOSI;
    static constexpr Chimera::GPIO::Alternate altMISO = Chimera::GPIO::Alternate::SPI2_MISO;

    static constexpr Chimera::GPIO::Port spiPort            = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 8 * 1000000;
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
    static constexpr Chimera::GPIO::Pin pinIRQ_pin             = 13;
    static constexpr Chimera::GPIO::Port pinIRQ_port           = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::EXTI::EdgeTrigger pinIRQ_Trigger = Chimera::EXTI::EdgeTrigger::FALLING_EDGE;

    /*-------------------------------------------------
    GPIO: Chip Enable
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCE_pin   = 5;
    static constexpr Chimera::GPIO::Port pinCE_port = Chimera::GPIO::Port::PORTB;

    /*-------------------------------------------------
    GPIO: Chip Select
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCS_pin   = BSP::Nucleo::F446RE::SPI::SPI2::csPin;
    static constexpr Chimera::GPIO::Port pinCS_port = BSP::Nucleo::F446RE::SPI::SPI2::csPort;

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

  /*-------------------------------------------------------------------------------
  Debug Port
  -------------------------------------------------------------------------------*/
  namespace DBG
  {
    /*-------------------------------------------------
    USART serial output
    -------------------------------------------------*/
    static constexpr Chimera::Serial::Channel serialChannel = Chimera::Serial::Channel::SERIAL2;

    extern const Chimera::Serial::Config comConfig;
    extern const Chimera::GPIO::PinInit txPinInit;
    extern const Chimera::GPIO::PinInit rxPinInit;
  }    // namespace DBG
}    // namespace DC::IO

#endif /* !DC_BOARD_MAP_HPP */
