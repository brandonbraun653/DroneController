/********************************************************************************
 *  File Name:
 *    reg_files.hpp
 *
 *  Description:
 *    File listing for the project. All files are assumed to use a flat directory
 *    structure due to limitations with the embedded file system driver.
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_FILE_LISTING_HPP
#define DC_FILE_LISTING_HPP

/* STL Includes */
#include <string_view>

namespace DC::Files
{
  /*-------------------------------------------------------------------------------
  System Configuration Data
  -------------------------------------------------------------------------------*/
  namespace SysCfg
  {
    static const std::string_view filename = "root/sys_config.bin";

    struct DataType
    {
      uint32_t bootCount;
    };
  }
}  // namespace DC::Files

#endif  /* !DC_FILE_LISTING_HPP */
