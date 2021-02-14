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

/* STL Includes */
#include <cstddef>

namespace DC::SYS
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
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
}  // namespace DC::SYS

#endif  /* !DC_SYSTEM_CONFIG_HPP */
