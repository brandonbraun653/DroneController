/********************************************************************************
 *  File Name:
 *    sys_config.cpp
 *
 *  Description:
 *    System configuration data
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstring>
#include <Aurora/logging>
#include <Aurora/filesystem>
#include <Aurora/utility>
#include <src/registry/reg_intf.hpp>
#include <src/registry/reg_files.hpp>
#include <src/system/sys_config.hpp>

namespace DC::SYS
{
  using namespace DC::Files;

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void configureDevice( const size_t num )
  {
    /*-------------------------------------------------------------------------
    Configure Unit Information
    -------------------------------------------------------------------------*/
    Aurora::FileSystem::BinaryFile uFile;
    UnitInfo::DataType unit_info;
    memset( &unit_info, 0, sizeof( unit_info ) );

    unit_info.version = UnitInfo::Version;
    unit_info.hwRev   = 0;

    /* Perform unique configuration */
    if( num == DEV_0 )
    {
      strcpy( unit_info.name, "Onyx" );
      strcpy( unit_info.serial, "fwqm4acgx87nv7f6kcnohdm8" );
    }
    else
    {
      strcpy( unit_info.name, "Panda" );
      strcpy( unit_info.serial, "skbpc9ri2vqnn9qa245q5wng" );
    }

    /* Write the data to file */
    if( uFile.open( UnitInfo::Filename, "wb" ) )
    {
      uFile.write( &unit_info, sizeof( unit_info ) );
      uFile.close();
    }
    else
    {
      LOG_ERROR( "Failed to open %s\r\n", UnitInfo::Filename.data() );
    }

    /*-------------------------------------------------------------------------
    RF24 Configuration
    -------------------------------------------------------------------------*/
    Aurora::FileSystem::BinaryFile rFile;
    RF24Config::DataType rf_info;
    memset( &rf_info, 0, sizeof( rf_info ) );

    /* Perform unique configuration */
    if( num == DEV_0 )
    {
      rf_info.thisNodeIp  = 23;
      rf_info.thisNodeMAC = 0xB4B5B6B7B5;
      rf_info.destNodeIp  = 35;
      rf_info.destNodeMAC = 0xA4A5A6A7A0;
    }
    else
    {
      rf_info.thisNodeIp  = 35;
      rf_info.thisNodeMAC = 0xA4A5A6A7A0;
      rf_info.destNodeIp  = 23;
      rf_info.destNodeMAC = 0xB4B5B6B7B5;
    }

    /* Write the data to file */
    if( rFile.open( RF24Config::Filename, "wb" ) )
    {
      rFile.write( &rf_info, sizeof( rf_info ) );
      rFile.close();
    }
    else
    {
      LOG_ERROR( "Failed to open %s\r\n", RF24Config::Filename.data() );
    }
  }


  DC::Files::UnitInfo::Name_t deviceName()
  {
    UnitInfo::DataType data;
    if ( !DC::REG::readSafe( UnitInfo::DBKey, &data, sizeof( data ) ) )
    {
      return {};
    }

    return UnitInfo::Name_t( data.name );
  }


  void setDeviceName( const char *name, const size_t length )
  {
    UnitInfo::DataType data;
    Aurora::FileSystem::BinaryFile file;

    /*-------------------------------------------------------------------------
    Input Protection
    -------------------------------------------------------------------------*/
    if( !name || !length || length > UnitInfo::Name_t::MAX_SIZE )
    {
      return;
    }

    /*-------------------------------------------------------------------------
    Copy out the current registry data and insert the new name
    -------------------------------------------------------------------------*/
    DC::REG::readSafe( UnitInfo::DBKey, &data, sizeof( data ) );
    safe_strcpy( data.name, sizeof( data.name ), name );

    /*-------------------------------------------------------------------------
    Write the data back to NVM
    -------------------------------------------------------------------------*/
    if( file.open( UnitInfo::Filename, "wb" ) )
    {
      if( file.write( &data, sizeof( data ) ) )
      {
        DC::REG::writeSafe( UnitInfo::DBKey, &data, sizeof( data ) );
      }
      file.close();
    }
  }


  DC::Files::UnitInfo::Serial_t deviceSerial()
  {
    UnitInfo::DataType data;
    if ( !DC::REG::readSafe( UnitInfo::DBKey, &data, sizeof( data ) ) )
    {
      return {};
    }

    return UnitInfo::Serial_t( data.serial );
  }


  void setDeviceSerial( const char *serial, const size_t length )
  {
    UnitInfo::DataType data;
    Aurora::FileSystem::BinaryFile file;

    /*-------------------------------------------------------------------------
    Input Protection
    -------------------------------------------------------------------------*/
    if( !serial || !length || length > UnitInfo::Serial_t::MAX_SIZE )
    {
      return;
    }

    /*-------------------------------------------------------------------------
    Copy out the current registry data and insert the new serial number
    -------------------------------------------------------------------------*/
    DC::REG::readSafe( UnitInfo::DBKey, &data, sizeof( data ) );
    safe_strcpy( data.serial, sizeof( data.serial ), serial );

    /*-------------------------------------------------------------------------
    Write the data back to NVM
    -------------------------------------------------------------------------*/
    if( file.open( UnitInfo::Filename, "wb" ) )
    {
      if( file.write( &data, sizeof( data ) ) )
      {
        DC::REG::writeSafe( UnitInfo::DBKey, &data, sizeof( data ) );
      }
      file.close();
    }
  }

}  // namespace DC::SYS
