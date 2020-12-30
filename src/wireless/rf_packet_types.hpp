/********************************************************************************
 *  File Name:
 *    rf_packet_types.hpp
 *
 *  Description:
 *    RF driver system packet declarations. These define the kinds of data that
 *    are allowed to be transmitted over the network.
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_WIRELESS_PACKET_TYPES_HPP
#define DC_WIRELESS_PACKET_TYPES_HPP

/* STL Includes */
#include <cstdint>


namespace DC::RF
{
  /*-------------------------------------------------------------------------------
  Forward Declarations
  -------------------------------------------------------------------------------*/
  enum PacketId;

  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using PacketCB = void(*)( const PacketId id );

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum class PacketEvent : uint8_t
  {
    RX,
    TX,
    TIMEOUT
  };

  /**
   *  Identifiers for each packet type that may be transmitted on
   *  the radio link.
   */
  enum PacketId : uint8_t
  {
    /*-------------------------------------------------------------------------------
    System Control
    -------------------------------------------------------------------------------*/
    SYS_CTRL_RESET,
    SYS_CTRL_POWER_UP,
    SYS_CTRL_POWER_DOWN,

    /*-------------------------------------------------------------------------------
    Attitude Control
    -------------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------
    Attitude Data
    -------------------------------------------------------------------------------*/
  };

}  // namespace DC::RF

#endif  /* !DC_WIRELESS_PACKET_TYPES_HPP */
