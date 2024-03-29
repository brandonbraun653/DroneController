/********************************************************************************
 *  File Name:
 *    version.hpp
 *
 *  Description:
 *    Drone Controller Version
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_VERSION_HPP
#define DC_VERSION_HPP

/* STL Includes */
#include <string_view>

namespace DC
{
  /**
   *  CHANGELOG;
   *
   *  v0.1.0: Initial version
   *  v0.2.0: Core hardware working, including basic networking.
   */
  static constexpr std::string_view version = "0.2.0";

}  // namespace DC

#endif  /* !DC_VERSION_HPP */
