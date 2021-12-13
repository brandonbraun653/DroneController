/********************************************************************************
 *  File Name:
 *    sys_config.hpp
 *
 *  Description:
 *    System configuration information and control
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_SYSTEM_CONFIG_HPP
#define DC_SYSTEM_CONFIG_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstddef>
#include <src/registry/reg_files.hpp>

namespace DC::SYS
{
  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr size_t DEV_0 = 1234;
  static constexpr size_t DEV_1 = 4321;

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  /**
   * @brief Utility function to program a device configuration
   *
   * @param num   Which device to set up
   */
  void configureDevice( const size_t num );

  /**
   *  Updates the current boot count information and then stores it to disk
   *  @return void
   */
  void updateBootCount();

  /**
   *  Looks up the latest boot count information
   *  @return size_t
   */
  size_t getBootCount();

  /**
   * @brief Gets the name of the device
   *
   * @return etl::string
   */
  DC::Files::UnitInfo::Name_t deviceName();

  /**
   * @brief Sets the device name in non-vol
   *
   * @param name  Name to set
   * @param size  Bytes in the name
   */
  void setDeviceName( const char *name, const size_t length );

  /**
   * @brief Gets the serial number assigned to the device
   *
   * @return etl::string
   */
  DC::Files::UnitInfo::Serial_t deviceSerial();

  /**
   * @brief Sets the device serial number in non-vol
   *
   * @param serial  Serial to set
   * @param length  Bytes in the serial string
   */
  void setDeviceSerial( const char *serial, const size_t length );

}  // namespace DC::SYS

#endif  /* !DC_SYSTEM_CONFIG_HPP */
