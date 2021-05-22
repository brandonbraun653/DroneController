/********************************************************************************
 *  File Name:
 *    rn_types.hpp
 *
 *  Description:
 *    Common types used across the RN4871 driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef RN4871_TYPES_HPP
#define RN4871_TYPES_HPP

/* ETL Includes */
#include <etl/string.h>

namespace RN4871
{
  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using VersionString = etl::string<64>;
  using PacketString  = etl::string<128>;
  using PacketBuffer  = char[ PacketString::MAX_SIZE ];

  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr char CMD_TERM = '\n';

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum class StatusCode : uint8_t
  {
    OK,
    FAIL,
    NO_RESPONSE,
    TIMEOUT,
    OVERFLOW,

    NUM_OPTIONS,
    INVALID
  };


  enum class OpMode : uint8_t
  {
    COMMAND,
    DATA,

    NUM_OPTIONS,
    INVALID
  };

}    // namespace RN4871

#endif /* !RN4871_TYPES_HPP */
