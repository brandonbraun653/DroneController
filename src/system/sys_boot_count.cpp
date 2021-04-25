/********************************************************************************
 *  File Name:
 *    sys_boot_count.cpp
 *
 *  Description:
 *    System configuration and control implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <cstdint>
#include <cstddef>

/* Aurora Includes */
#include <Aurora/filesystem>
#include <Aurora/logging>

/* Project Includes */
#include <src/system/sys_config.hpp>
#include <src/registry/reg_files.hpp>
#include <src/registry/reg_intf.hpp>

namespace DC::SYS
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_refreshed_from_disk = false;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void updateBootCount()
  {
    using namespace Aurora::FileSystem;

    /*-------------------------------------------------
    Should only be updated once per power cycle
    -------------------------------------------------*/
    if( s_refreshed_from_disk )
    {
      return;
    }

    BinaryFile bootFile;
    Files::BootCount::DataType boot_count = 0;

    /*-------------------------------------------------
    Create the file if it doesn't exist yet
    -------------------------------------------------*/
    if( !bootFile.open( Files::BootCount::Filename, "rb" ) )
    {
      /* Create the file */
      bootFile.clearErrors();
      bootFile.create( Files::BootCount::Filename );
      bootFile.open( Files::BootCount::Filename, "wb" );

      /* Initialize it with defaults */
      Files::BootCount::DataType initVal = 0;
      bootFile.write( &initVal, sizeof( initVal ) );
      bootFile.close();

      /* Re-open the file for continuing on further */
      bootFile.open( Files::BootCount::Filename, "rb" );
    }

    /*-------------------------------------------------
    Pull the last known info from disk and update it
    -------------------------------------------------*/
    bootFile.read( &boot_count, sizeof( boot_count ) );
    bootFile.close();

    boot_count += 1;
    bootFile.open( Files::BootCount::Filename, "wb" );
    bootFile.write( &boot_count, sizeof( boot_count ) );
    bootFile.close();
    LOG_INFO( "Boot Count: %d\r\n", boot_count );

    /*-------------------------------------------------
    Update the registry cache
    -------------------------------------------------*/
    REG::writeSafe( REG::KEY_BOOT_COUNT, &boot_count, sizeof( boot_count ) );
  }


  size_t getBootCount()
  {
    uint32_t tmp = 123456789;
    REG::readSafe( REG::KEY_BOOT_COUNT, &tmp, sizeof( tmp ) );
    return tmp;
  }
}  // namespace DC::SYS
