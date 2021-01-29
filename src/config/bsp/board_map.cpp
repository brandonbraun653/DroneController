/********************************************************************************
 *  File Name:
 *    board_map.cpp
 *
 *  Description:
 *    Board config definitions
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
#include <src/config/bsp/board_map.hpp>

namespace DC::IO
{
  /*-------------------------------------------------------------------------------
  Debug Port
  -------------------------------------------------------------------------------*/
  namespace DBG
  {
    /*-------------------------------------------------
    USART serial output
    -------------------------------------------------*/
    const Chimera::Serial::Config comConfig = BSP::Nucleo::F446RE::USART::ComPort::config;
    const Chimera::GPIO::PinInit txPinInit  = BSP::Nucleo::F446RE::USART::ComPort::txConfig;
    const Chimera::GPIO::PinInit rxPinInit  = BSP::Nucleo::F446RE::USART::ComPort::rxConfig;
  }    // namespace DBG
}  // namespace DC
