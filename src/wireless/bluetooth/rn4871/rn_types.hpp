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
  using VersionString = etl::string<16>;
  using PacketString = etl::string<128>;

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

    NUM_OPTIONS,
    INVALID
  };

}  // namespace RN4871

#endif  /* !RN4871_TYPES_HPP */
