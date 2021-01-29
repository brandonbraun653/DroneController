/********************************************************************************
 *  File Name:
 *    reg_types.hpp
 *
 *  Description:
 *    Registry types
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_REGISTRY_TYPES_HPP
#define DC_REGISTRY_TYPES_HPP

/* STL Includes */
#include <cstdint>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Aliases
  -------------------------------------------------------------------------------*/
  using RegTag = uint16_t;

  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  enum class MemProp : uint8_t
  {
    READ_ONLY  = ( 1u << 0 ), /**< Data should be read only */
    CACHEABLE  = ( 1u << 1 ), /**< A copy of the data should be stored in RAM */
    WRITE_BACK = ( 1u << 2 ), /**< Data is written back to NonVol on updates */
  };

  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/
  struct EntryDesc
  {
    RegTag tagId;          /**< Unique id for the data being stored */
    MemProp memProperties; /**< How the memory should behave */
  };
}  // namespace DC::REG

#endif  /* !DC_REGISTRY_TYPES_HPP */
