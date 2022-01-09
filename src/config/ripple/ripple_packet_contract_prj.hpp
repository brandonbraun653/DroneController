/********************************************************************************
 *  File Name:
 *    ripple_packet_contract_prj.hpp
 *
 *  Description:
 *    Packet definitions for the project
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_PACKET_DEFINTIONS_HPP
#define DC_PACKET_DEFINTIONS_HPP

/* STL Includes */
#include <cstddef>

/*-------------------------------------------------------------------------------
Enumerations
-------------------------------------------------------------------------------*/
/**
 * @brief Gives a unique name to all packets used on this project
 * @note Type is aliased to uint32_t, but is actually Ripple::PacketId
 *
 * In addition to unique naming, these IDs are what will be used to reference
 * a particular packet throughout the network stack.
 */
enum DCPacketList : uint32_t
{
  PKT_AHRS_ACCEL_DATA,
  PKT_AHRS_GYRO_DATA,
  PKT_AHRS_MAG_DATA,
  PKT_CMD_STICK_INPUTS,
  PKT_EVENT_DISCRETE_INPUT,

  PKT_NUM_PKTS,
  PKT_INVALID
};

/*-------------------------------------------------------------------------------
Constants
-------------------------------------------------------------------------------*/
static constexpr size_t RIPPLE_MAX_NUM_PKTS = DCPacketList::PKT_NUM_PKTS;

#endif  /* !DC_PACKET_DEFINTIONS_HPP */
