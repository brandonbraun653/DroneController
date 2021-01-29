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

namespace DC::REG
{
  bool initialize();

  bool mount();

  bool unmount();
}  // namespace DC::REG

#endif  /* !DC_REGISTRY_INTF_HPP */
