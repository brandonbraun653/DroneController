/********************************************************************************
 *  File Name:
 *    reg_disk.cpp
 *
 *  Description:
 *    IO operations for reading/writing data on system files
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/filesystem>
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/assert>

/* Project Includes */
#include <src/registry/reg_disk.hpp>

namespace DC::REG::Disk
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  Aurora::FileSystem::FileHandle openFile( const Aurora::FileSystem::IODirection direction, const std::string_view &filename )
  {
    using namespace Aurora::FileSystem;
    using namespace Aurora::Logging;
    namespace fs = Aurora::FileSystem;

    FileHandle file = nullptr;

    /*-------------------------------------------------
    Open the file as directed
    -------------------------------------------------*/
    switch ( direction )
    {
      case IO_READ:
        file = fs::fopen( filename.begin(), "rb" );
        break;

      case IO_WRITE:
        file = fs::fopen( filename.begin(), "wb+" );
        break;

      default:
        // Nothing to do
        break;
    };

    /*-------------------------------------------------
    Rewind so subsequent filesystem calls are rooted to
    the start of the file.
    -------------------------------------------------*/
    if ( file )
    {
      fs::frewind( file );
    }
    else
    {
      getRootSink()->flog( Level::LVL_DEBUG, "Failed to open file %s\r\n", filename.begin() );
    }

    return file;
  }


  Aurora::FileSystem::FileHandle openFileWithDefaults( const Aurora::FileSystem::IODirection direction,
                                                       const std::string_view &filename, const void *const data,
                                                       const size_t size )
  {
    using namespace Aurora::FileSystem;

    FileHandle file = openFile( direction, filename );
    if ( !file && createFile( filename, data, size ) )
    {
      file = openFile( direction, filename );
    }

    return file;
  }


  bool createFile( const std::string_view &filename, const void *const data, const size_t size )
  {
    using namespace Aurora::FileSystem;
    using namespace Aurora::Logging;
    namespace fs = Aurora::FileSystem;

    getRootSink()->flog( Level::LVL_DEBUG, "Initializing %s\r\n", filename.begin() );
    FileHandle file = openFile( IO_WRITE, filename );

    if ( !file )
    {
      getRootSink()->flog( Level::LVL_DEBUG, "Could not create %s\r\n", filename.begin() );
      return false;
    }
    else
    {
      fs::frewind( file );
      fs::fwrite( data, sizeof( uint8_t ), size, file );
      fs::fclose( file );
      return true;
    }
  }


  bool fileTransaction( const Aurora::FileSystem::IODirection direction, Aurora::FileSystem::FileHandle handle,
                        void *const data, const size_t size )
  {
    using namespace Aurora::FileSystem;
    namespace fs = Aurora::FileSystem;

    size_t rw_bytes = 0;
    switch ( direction )
    {
      case IO_READ:
        rw_bytes = fs::fread( data, sizeof( uint8_t ), size, handle );
        break;

      default:
        /* This project uses files as binary blob storage. Currently no suppport for growing files. */
        fs::frewind( handle );
        rw_bytes = fs::fwrite( data, sizeof( uint8_t ), size, handle );
        break;
    }

    RT_HARD_ASSERT( rw_bytes == size );
    return true;
  }


  bool io_sys_cfg( const Aurora::FileSystem::IODirection direction, Files::SysCfg::DataType &data )
  {
    using namespace Aurora::FileSystem;
    using namespace Aurora::Logging;
    using namespace DC::Files;
    namespace fs = Aurora::FileSystem;

    /*-------------------------------------------------
    Create the file if it doesn't exist yet
    -------------------------------------------------*/
    DC::Files::SysCfg::DataType tmp;
    memset( &tmp, 0, sizeof( tmp ) );

    FileHandle file = openFileWithDefaults( direction, SysCfg::filename, &tmp, sizeof( tmp ) );

    /*-------------------------------------------------
    Perform the IO transaction
    -------------------------------------------------*/
    fileTransaction( direction, file, &data, sizeof( data ) );
    return fs::fclose( file ) == 0;
  }
}    // namespace DC::REG::Disk
