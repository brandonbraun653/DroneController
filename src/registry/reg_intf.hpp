/********************************************************************************
 *  File Name:
 *    reg_intf.hpp
 *
 *  Description:
 *    Registry system to store and retrieve data in non-volatile memory
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_REGISTRY_INTF_HPP
#define DC_REGISTRY_INTF_HPP

/* STL Includes */
#include <cstdint>

/* Project Includes */
#include <src/registry/reg_data.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/

  bool initialize();

  void format();

  bool readSafe( const DatabaseKeys key, void *const data, const size_t size );

  bool writeSafe( const DatabaseKeys key, const void *const data, const size_t size );

}  // namespace DC::REG

#endif  /* !DC_REGISTRY_INTF_HPP */
