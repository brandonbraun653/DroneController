/********************************************************************************
 *  File Name:
 *    rn_action_cmds.cpp
 *
 *  Description:
 *    Utilities for building Action commands. This module references the
 *    RN4870/71 Bluetooth® Low Energy Module User’s Guide (DS50002466B).
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/utility>

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_action_cmds.hpp>
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>

namespace RN4871::CMD::Action
{
  /**
   * @brief Builds the Version command (2.6.31)
   *
   * @param cmd     Output buffer
   * @return bool   Pass/fail
   */
  StatusCode version( PacketString &cmd )
  {
    cmd.clear();
    cmd = "V\n";

    return StatusCode::OK;
  }
}  // namespace RN4871::CMD::Action
