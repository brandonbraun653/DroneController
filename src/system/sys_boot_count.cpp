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
#include <Aurora/filesystem_spiffs>
#include <Aurora/logging>

/* Project Includes */
#include <src/system/sys_config.hpp>
#include <src/registry/reg_disk.hpp>
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
    namespace fileSys = ::Aurora::FileSystem;

    /*-------------------------------------------------
    Should only be updated once per power cycle
    -------------------------------------------------*/
    if( s_refreshed_from_disk )
    {
      return;
    }

    /*-------------------------------------------------
    Pull the last known info from disk
    -------------------------------------------------*/
    Files::SysCfg::DataType fileData;
    fileData.bootCount = 500;

    auto fd = fileSys::fopen( Files::SysCfg::filename.data(), "rb" );
    fileSys::frewind( fd );
    fileSys::fread( &fileData, 1, sizeof( fileData ), fd );
    fileSys::fclose( fd );

    fileData.bootCount += 1;
    fd = fileSys::fopen( Files::SysCfg::filename.data(), "w+" );
    fileSys::fwrite( &fileData, 1, sizeof( fileData ), fd );
    fileSys::fclose( fd );
    LOG_INFO( "Saved boot count of %d\r\n", fileData.bootCount );

    size_t saved = fileData.bootCount;

    fd = fileSys::fopen( Files::SysCfg::filename.data(), "rb" );
    fileSys::frewind( fd );
    fileSys::fread( &fileData, 1, sizeof( fileData ), fd );
    fileSys::fclose( fd );

    LOG_INFO( "Read boot count of %d\r\n", fileData.bootCount );

    // if( saved != fileData.bootCount )
    // {
    //   auto nor = Aurora::FileSystem::SPIFFS::getDriver();
    //   nor->erase();
    // }

    // fileData.bootCount += 1;
    // fd = fileSys::fopen( Files::SysCfg::filename.data(), "w+" );
    // fileSys::fwrite( &fileData, 1, sizeof( fileData ), fd );
    // fileSys::fclose( fd );

    // Files::SysCfg::DataType fileData;
    // s_refreshed_from_disk = REG::Disk::io_sys_cfg( IO_READ, fileData );

    // fileData.bootCount += 1;
    // REG::Disk::io_sys_cfg( IO_WRITE, fileData );

    /*-------------------------------------------------
    Update the registry cache
    -------------------------------------------------*/
    REG::writeSafe( REG::KEY_BOOT_COUNT, &fileData.bootCount, sizeof( fileData.bootCount ) );
  }


  size_t getBootCount()
  {
    uint32_t tmp = 123456789;
    REG::readSafe( REG::KEY_BOOT_COUNT, &tmp, sizeof( tmp ) );
    return tmp;
  }
}  // namespace DC::SYS
