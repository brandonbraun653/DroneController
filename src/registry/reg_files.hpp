/********************************************************************************
 *  File Name:
 *    reg_files.hpp
 *
 *  Description:
 *    File listing for the project. All files are assumed to use a flat directory
 *    structure due to limitations with the embedded file system driver. For ease
 *    of use, most files are filled with structures.
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_FILE_LISTING_HPP
#define DC_FILE_LISTING_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <string_view>
#include <etl/string.h>
#include <Chimera/common>
#include <Ripple/shared>
#include <src/registry/reg_data.hpp>

namespace DC::Files
{
  /*---------------------------------------------------------------------------
  Boot Count
  ---------------------------------------------------------------------------*/
  namespace BootCount
  {
    static const std::string_view          Filename = "boot_count.bin";
    static constexpr DC::REG::DatabaseKeys DBKey    = DC::REG::DatabaseKeys::KEY_BOOT_COUNT;
    using DataType                                  = uint32_t;
  }    // namespace BootCount

  /*---------------------------------------------------------------------------
  Unit Information/Configuration
  ---------------------------------------------------------------------------*/
  namespace UnitInfo
  {
    using Name_t   = etl::string<32>;
    using Serial_t = etl::string<32>;

    struct _Info
    {
      uint32_t version;                      /**< Structure version */
      uint8_t  hwRev;                        /**< Hardware revision */
      uint8_t  _pad[ 3 ];                    /**< Pad for alignment */
      char     name[ Name_t::MAX_SIZE ];     /**< Name of the device */
      char     serial[ Serial_t::MAX_SIZE ]; /**< Serial number of the device */
    };

    static const std::string_view          Filename = "unit_info.bin";
    static constexpr DC::REG::DatabaseKeys DBKey    = DC::REG::DatabaseKeys::KEY_UNIT_INFO;
    static constexpr uint32_t              Version  = 0;
    using DataType                                  = _Info;
  }    // namespace UnitInfo

  /*---------------------------------------------------------------------------
  RF24 Radio Configuration
  ---------------------------------------------------------------------------*/
  namespace RF24Config
  {
    struct _Config
    {
      uint32_t          version;     /**< Structure version */
      Ripple::IPAddress thisNodeIp;  /**< Node identifier for this LRU */
      uint64_t          thisNodeMAC; /**< Unique MAC address of this LRU */
      Ripple::IPAddress destNodeIp;  /**< Node identifier for the destination LRU */
      uint64_t          destNodeMAC; /**< Unique MAC address for destination LRU */
    };

    static const std::string_view          Filename = "nrf24_config.bin";
    static constexpr DC::REG::DatabaseKeys DBKey    = DC::REG::DatabaseKeys::KEY_RF24_CONFIG;
    using DataType                                  = _Config;
  }    // namespace RF24Config
}    // namespace DC::Files

#endif /* !DC_FILE_LISTING_HPP */
