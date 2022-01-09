/********************************************************************************
 *  File Name:
 *    ripple_packet_defs.cpp
 *
 *  Description:
 *    Packet definitions for use with Rippl
 *
 *  2021-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include "ahrs.pb.h"
#include "controller.pb.h"
#include <Ripple/packets>
#include <etl/map.h>
#include <src/config/ripple/ripple_packet_contract_prj.hpp>

namespace Ripple
{
  /*-------------------------------------------------------------------------------
  Project Packet Definitions

  Lists out all packets that may be used in the project. Declaration order does not
  matter as this will be sorted on power up for efficient lookup.
  -------------------------------------------------------------------------------*/
  etl::map<PacketId, PacketDef, RIPPLE_MAX_NUM_PKTS> PacketDefinitions{
    /* clang-format off */

    { PKT_AHRS_ACCEL_DATA,        PacketDef{ PKT_AHRS_ACCEL_DATA,         AccelSample_size,       AccelSample_fields   } },
    { PKT_AHRS_GYRO_DATA,         PacketDef{ PKT_AHRS_GYRO_DATA,          GyroSample_size,        GyroSample_fields    } },
    { PKT_AHRS_MAG_DATA,          PacketDef{ PKT_AHRS_MAG_DATA,           MagSample_size,         MagSample_fields     } },
    { PKT_CMD_STICK_INPUTS,       PacketDef{ PKT_CMD_STICK_INPUTS,        StickInputs_size,       StickInputs_fields   } },
    { PKT_EVENT_DISCRETE_INPUT,   PacketDef{ PKT_EVENT_DISCRETE_INPUT,    DiscreteEvent_size,     DiscreteEvent_fields } },

  }; /* clang-format on */

}    // namespace Ripple
