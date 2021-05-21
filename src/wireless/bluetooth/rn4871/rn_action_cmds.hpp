/********************************************************************************
 *  File Name:
 *    rn_action_cmds.hpp
 *
 *  Description:
 *    Interface for ACTION commands on the RN4871
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef RN4871_ACTION_COMMANDS_HPP
#define RN4871_ACTION_COMMANDS_HPP

/* Driver Includes */
#include <src/wireless/bluetooth/rn4871/rn_types.hpp>

namespace RN4871::CMD::Action
{

  StatusCode version( PacketString &cmd );

}  // namespace RN4871

#endif  /* !RN4871_ACTION_COMMANDS_HPP */
