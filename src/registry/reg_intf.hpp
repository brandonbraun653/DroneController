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

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstdint>
#include <src/registry/reg_data.hpp>

namespace DC::REG
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  /**
   * @brief Initialize the registry
   *
   * @return true
   * @return false
   */
  bool initialize();

  /**
   * @brief Format the underlying memory containing the registry
   */
  void format();

  /**
   * @brief Process observable registry entries
   */
  void doPeriodicProcessing();

  /**
   * @brief Read data out from the registry
   *
   * @param key     Which key to look up
   * @param data    Output buffer for the raw data type
   * @param size    Size of output buffer. Must match registered size.
   * @return true
   * @return false
   */
  bool readSafe( const DatabaseKeys key, void *const data, const size_t size );

  /**
   * @brief Write new data into the registry
   *
   * @param key     Which key to write to
   * @param data    Input buffer
   * @param size    Size of input buffer. Must match registered size.
   * @return true
   * @return false
   */
  bool writeSafe( const DatabaseKeys key, const void *const data, const size_t size );

}  // namespace DC::REG

#endif  /* !DC_REGISTRY_INTF_HPP */
