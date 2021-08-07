/********************************************************************************
 *  File Name:
 *    ripple_packet_defs.cpp
 *
 *  Description:
 *    Packet definitions for use with Rippl
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* ETL Includes */
#include <etl/map.h>

/* Ripple Includes */
#include <Ripple/packets>

/* NanoPB Includes */
#include "ahrs.pb.h"
#include "controller.pb.h"

/* Project Includes */
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

    { PKT_AHRS_ACCEL_DATA,        PacketDef{ PKT_AHRS_ACCEL_DATA,         AccelSample_size,       AccelSample_fields      } },
    { PKT_AHRS_GYRO_DATA,         PacketDef{ PKT_AHRS_GYRO_DATA,          GyroSample_size,        GyroSample_fields       } },
    { PKT_AHRS_MAG_DATA,          PacketDef{ PKT_AHRS_MAG_DATA,           MagSample_size,         MagSample_fields        } },
    { PKT_CMD_CONTROLLER_INPUTS,  PacketDef{ PKT_CMD_CONTROLLER_INPUTS,   ControllerInputs_size,  ControllerInputs_fields } },

  }; /* clang-format on */

}    // namespace Ripple
