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

    /*-------------------------------------------------
    Rotary Encoder 0
    -------------------------------------------------*/
    namespace Encoder0
    {
      static constexpr Chimera::GPIO::Pin pinA   = 12;
      static constexpr Chimera::GPIO::Port portA = Chimera::GPIO::Port::PORTC;

      static constexpr Chimera::GPIO::Pin pinB   = 13;
      static constexpr Chimera::GPIO::Port portB = Chimera::GPIO::Port::PORTC;
    }    // namespace Encoder0

    /*-------------------------------------------------
    Rotary Encoder 1
    -------------------------------------------------*/
    namespace Encoder1
    {
      static constexpr Chimera::GPIO::Pin pinA   = 9;
      static constexpr Chimera::GPIO::Port portA = Chimera::GPIO::Port::PORTA;

      static constexpr Chimera::GPIO::Pin pinB   = 10;
      static constexpr Chimera::GPIO::Port portB = Chimera::GPIO::Port::PORTA;
    }    // namespace Encoder1

  }    // namespace HMI

  /*-------------------------------------------------------------------------------
  Discrete IO via Shift Registers - SPI3
  -------------------------------------------------------------------------------*/
  namespace SR
  {
    /*-------------------------------------------------
    GPIO
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin csPin_KeyIn       = 9;
    static constexpr Chimera::GPIO::Port csPort_KeyIn     = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::GPIO::Pin csPin_KeySample   = 8;
    static constexpr Chimera::GPIO::Port csPort_KeySample = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::GPIO::Pin csPin_KeyOut      = 5;
    static constexpr Chimera::GPIO::Port csPort_KeyOut    = Chimera::GPIO::Port::PORTB;

    static constexpr Chimera::GPIO::Pin sckPin       = 10;
    static constexpr Chimera::GPIO::Port sckPort     = Chimera::GPIO::Port::PORTC;
    static constexpr Chimera::GPIO::Alternate sckAlt = Chimera::GPIO::Alternate::SPI3_SCK;

    static constexpr Chimera::GPIO::Pin misoPin       = 11;
    static constexpr Chimera::GPIO::Port misoPort     = Chimera::GPIO::Port::PORTC;
    static constexpr Chimera::GPIO::Alternate misoAlt = Chimera::GPIO::Alternate::SPI3_MISO;

    static constexpr Chimera::GPIO::Pin mosiPin       = 0;
    static constexpr Chimera::GPIO::Port mosiPort     = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::GPIO::Alternate mosiAlt = Chimera::GPIO::Alternate::SPI3_MOSI;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr Chimera::SPI::Channel spiChannel       = Chimera::SPI::Channel::SPI3;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 8 * 1000000;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = Chimera::SPI::ClockMode::MODE0;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = Chimera::SPI::CSMode::MANUAL;
    static constexpr Chimera::SPI::DataSize spiDataSize     = Chimera::SPI::DataSize::SZ_8BIT;
  }    // namespace SR

  /*-------------------------------------------------------------------------------
  NOR Flash - SPI2
  -------------------------------------------------------------------------------*/
  namespace NOR
  {
    /*-------------------------------------------------
    GPIO
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin csPin   = 12;
    static constexpr Chimera::GPIO::Port csPort = Chimera::GPIO::Port::PORTB;

    static constexpr Chimera::GPIO::Pin sckPin       = 13;
    static constexpr Chimera::GPIO::Port sckPort     = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::GPIO::Alternate sckAlt = Chimera::GPIO::Alternate::SPI2_SCK;

    static constexpr Chimera::GPIO::Pin misoPin       = 14;
    static constexpr Chimera::GPIO::Port misoPort     = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::GPIO::Alternate misoAlt = Chimera::GPIO::Alternate::SPI2_MISO;

    static constexpr Chimera::GPIO::Pin mosiPin       = 15;
    static constexpr Chimera::GPIO::Port mosiPort     = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::GPIO::Alternate mosiAlt = Chimera::GPIO::Alternate::SPI2_MOSI;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr Chimera::SPI::Channel spiChannel       = Chimera::SPI::Channel::SPI2;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 1 * 1000000;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = Chimera::SPI::ClockMode::MODE0;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = Chimera::SPI::CSMode::MANUAL;
    static constexpr Chimera::SPI::DataSize spiDataSize     = Chimera::SPI::DataSize::SZ_8BIT;
  }    // namespace NOR

  /*-------------------------------------------------------------------------------
  Radio Hardware - SPI1
  -------------------------------------------------------------------------------*/
  namespace Radio
  {
    /*-------------------------------------------------
    GPIO: IRQ Input
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinIRQ_pin             = 1;
    static constexpr Chimera::GPIO::Port pinIRQ_port           = Chimera::GPIO::Port::PORTB;
    static constexpr Chimera::EXTI::EdgeTrigger pinIRQ_Trigger = Chimera::EXTI::EdgeTrigger::FALLING_EDGE;

    /*-------------------------------------------------
    GPIO: Chip Enable
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCE_pin   = 4;
    static constexpr Chimera::GPIO::Port pinCE_port = Chimera::GPIO::Port::PORTA;

    /*-------------------------------------------------
    GPIO: Chip Select
    -------------------------------------------------*/
    static constexpr Chimera::GPIO::Pin pinCS_pin   = 4;
    static constexpr Chimera::GPIO::Port pinCS_port = Chimera::GPIO::Port::PORTC;

    /*-------------------------------------------------
    SPI
    -------------------------------------------------*/
    static constexpr bool pinThreadMode = false;

    static constexpr Chimera::GPIO::Pin pinSCK       = 5;
    static constexpr Chimera::GPIO::Alternate altSCK = Chimera::GPIO::Alternate::SPI1_SCK;

    static constexpr Chimera::GPIO::Pin pinMOSI       = 7;
    static constexpr Chimera::GPIO::Alternate altMOSI = Chimera::GPIO::Alternate::SPI1_MOSI;

    static constexpr Chimera::GPIO::Pin pinMISO       = 6;
    static constexpr Chimera::GPIO::Alternate altMISO = Chimera::GPIO::Alternate::SPI1_MISO;

    static constexpr Chimera::GPIO::Port spiPort = Chimera::GPIO::Port::PORTA;

    static constexpr Chimera::SPI::Channel spiChannel       = Chimera::SPI::Channel::SPI1;
    static constexpr Chimera::SPI::TransferMode spiTxfrMode = Chimera::SPI::TransferMode::BLOCKING;
    static constexpr Chimera::SPI::BitOrder spiBitOrder     = Chimera::SPI::BitOrder::MSB_FIRST;
    static constexpr Chimera::SPI::ClockFreq spiClockFreq   = 8 * 1000000;
    static constexpr Chimera::SPI::ClockMode spiClockMode   = Chimera::SPI::ClockMode::MODE0;
    static constexpr Chimera::SPI::CSMode spiChipSelectMode = Chimera::SPI::CSMode::MANUAL;
    static constexpr Chimera::SPI::DataSize spiDataSize     = Chimera::SPI::DataSize::SZ_8BIT;
  }    // namespace Radio

  /*-------------------------------------------------------------------------------
  Bluetooth - USART6
  -------------------------------------------------------------------------------*/
  namespace Bluetooth
  {
    static constexpr Chimera::Serial::Channel serialChannel = Chimera::Serial::Channel::SERIAL6;

    extern const Chimera::Serial::Config comConfig;
    extern const Chimera::GPIO::PinInit txPinInit;
    extern const Chimera::GPIO::PinInit rxPinInit;

    static constexpr Chimera::GPIO::Pin rxPin   = 7;
    static constexpr Chimera::GPIO::Port rxPort = Chimera::GPIO::Port::PORTC;
    static constexpr Chimera::GPIO::Pin txPin   = 6;
    static constexpr Chimera::GPIO::Port txPort = Chimera::GPIO::Port::PORTC;
  }    // namespace Bluetooth

  /*-------------------------------------------------------------------------------
  Debug Port
  -------------------------------------------------------------------------------*/
  namespace DBG
  {
    static constexpr Chimera::Serial::Channel serialChannel = Chimera::Serial::Channel::SERIAL3;

    extern const Chimera::Serial::Config comConfig;
    extern const Chimera::GPIO::PinInit txPinInit;
    extern const Chimera::GPIO::PinInit rxPinInit;

    static constexpr Chimera::GPIO::Pin rxPin   = 5;
    static constexpr Chimera::GPIO::Port rxPort = Chimera::GPIO::Port::PORTC;
    static constexpr Chimera::GPIO::Pin txPin   = 10;
    static constexpr Chimera::GPIO::Port txPort = Chimera::GPIO::Port::PORTB;
  }    // namespace DBG
}    // namespace DC::IO

#endif /* !DC_BOARD_MAP_HPP */
