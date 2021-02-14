/********************************************************************************
 *  File Name:
 *    reg_disk.hpp
 *
 *  Description:
 *    Interface for reading/writing system parameter data that lives on disk
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_REG_DISK_IO_HPP
#define DC_REG_DISK_IO_HPP

/* STL Includes */
#include <string_view>

/* Aurora Includes */
#include <Aurora/filesystem>

/* Project Includes */
#include <src/registry/reg_files.hpp>

namespace DC::REG::Disk
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Unified way for the project to open files
   *
   *  @param[in]  direction     Which direction to open the file as
   *  @param[in]  filename      Name of the file to open
   *  @return FileHandle        Will be nullptr if not found
   */
  Aurora::FileSystem::FileHandle openFile( const Aurora::FileSystem::IODirection direction, const std::string_view &filename );

  /**
   *  Tries to open a file. If non-existant, creates and fills it with default information, then
   *  returns the opened file handle.
   *
   *  @param[in]  direction     Which direction to open the file as
   *  @param[in]  filename      Name of the file to open
   *  @param[in]  data          Data to use as defaults
   *  @param[in]  size          Number of bytes expected to write
   *  @return FileHandle        Will be nullptr if all fails
   */
  Aurora::FileSystem::FileHandle openFileWithDefaults( const Aurora::FileSystem::IODirection direction,
                                                       const std::string_view &filename, const void *const data,
                                                       const size_t size );

  /**
   *  Creates a file with the given data.
   *
   *  @param[in]  filename      The file to create
   *  @param[in]  data          The data to be written
   *  @param[in]  size          Number of bytes to write
   *  @return bool
   */
  bool createFile( const std::string_view &filename, const void *const data, const size_t size );

  /**
   *  Unified way to write to a file that verifies all data was written
   *
   *  @param[in]  direction     Which direction the transaction is going
   *  @param[in]  handle        The file to use for IO operations
   *  @param[in]  data          Data to read/write into
   *  @param[in]  size          Number of bytes expected to read/write
   *  @return bool
   */
  bool fileTransaction( const Aurora::FileSystem::IODirection direction, Aurora::FileSystem::FileHandle handle, void *const data, const size_t size );

  /**
   *  IO operations for interacting with the SysCfg file data. If the file doesn't
   *  exist, it will be created with default values.
   *
   *  @param[in]  direction     Which direction the data flow is going
   *  @param[in]  data          Input/output buffer for the file data
   *  @return bool
   */
  bool io_sys_cfg( const Aurora::FileSystem::IODirection direction, Files::SysCfg::DataType &data );
}  // namespace DC::REG::Disk

#endif  /* !DC_REG_DISK_IO_HPP */
