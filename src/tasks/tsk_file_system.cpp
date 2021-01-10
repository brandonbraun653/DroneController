/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the file system thread
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/thread>

/* Aurora Includes */
#include <Aurora/memory>
#include <Aurora/source/memory/flash/littlefs/lfs_hooks.hpp>

/* Little FS Includes */
#include "lfs.h"

/* Logger Includes */
#include <uLog/ulog.hpp>

/* Project Includes */
#include <src/tasks/tsk_file_system.hpp>

/*-------------------------------------------------------------------------------
Constants
-------------------------------------------------------------------------------*/
static constexpr Chimera::SPI::Channel spiChannel = Chimera::SPI::Channel::SPI1;

/*-------------------------------------------------------------------------------
Forward Declarations
-------------------------------------------------------------------------------*/
static void initializeSPI();


/*-------------------------------------------------
LFS Data
-------------------------------------------------*/
lfs_t lfs;
static lfs_file_t file;

lfs_config cfg = {
  .context = nullptr,

  // Block device operations
  .read = lfs_safe_read,
  .prog = lfs_safe_prog,
  .erase = lfs_safe_erase,
  .sync = lfs_safe_sync,

  // Block device configuration
  .read_size = 16,
  .prog_size = 16,
  .block_size = 4096,
  .block_count = 256,
  .block_cycles = 500,
  .cache_size = 16,
  .lookahead_size = 16
};

namespace DC::Tasks::FIL
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Threading;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    this_thread::pendTaskMsg( ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_BLOCK );

    /*-------------------------------------------------
    Setup LFS
    -------------------------------------------------*/
    Aurora::Memory::LFS::attachDevice( Aurora::Flash::NOR::Chip::AT25SF081, spiChannel, cfg );

    for( auto x = 0; x < 500; x ++)
    {
      // mount the filesystem
      int err = lfs_mount( &lfs, &cfg );

      // reformat if we can't mount the filesystem
      // this should only happen on the first boot
      if ( err )
      {
        err = lfs_format( &lfs, &cfg );
        err = lfs_mount( &lfs, &cfg );
      }

      // read current count
      uint32_t boot_count = 0;
      err = lfs_file_open( &lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT );
      err = lfs_file_read( &lfs, &file, &boot_count, sizeof( boot_count ) );

      // update boot count
      boot_count += 1;
      err = lfs_file_rewind( &lfs, &file );
      err = lfs_file_write( &lfs, &file, &boot_count, sizeof( boot_count ) );

      // remember the storage is not updated until the file is closed successfully
      err = lfs_file_close( &lfs, &file );

      // release any resources we were using
      err = lfs_unmount( &lfs );

      // print the boot count
      uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "boot count: %d\r\n", boot_count );
    }

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      Chimera::delayMilliseconds( lastWoken, 100 );
    }
  }
}    // namespace DC::Tasks::FIL


/*-------------------------------------------------------------------------------
Static Functions
-------------------------------------------------------------------------------*/
static void initializeSPI()
{
  /*-------------------------------------------------
  Initialize the SPI driver
  -------------------------------------------------*/
  Chimera::SPI::DriverConfig cfg;
  cfg.clear();
  cfg.validity = true;

  cfg.HWInit.bitOrder    = Chimera::SPI::BitOrder::MSB_FIRST;
  cfg.HWInit.clockFreq   = 32000000;
  cfg.HWInit.clockMode   = Chimera::SPI::ClockMode::MODE0;
  cfg.HWInit.dataSize    = Chimera::SPI::DataSize::SZ_8BIT;
  cfg.HWInit.hwChannel   = spiChannel;
  cfg.HWInit.txfrMode    = Chimera::SPI::TransferMode::INTERRUPT;
  cfg.HWInit.controlMode = Chimera::SPI::ControlMode::MASTER;
  cfg.HWInit.csMode      = Chimera::SPI::CSMode::MANUAL;
  cfg.HWInit.validity    = true;

  // Chip Select
  cfg.externalCS       = false;
  cfg.CSInit.alternate = Chimera::GPIO::Alternate::NONE;
  cfg.CSInit.drive     = Chimera::GPIO::Drive::OUTPUT_PUSH_PULL;
  cfg.CSInit.pin       = 15;
  cfg.CSInit.port      = Chimera::GPIO::Port::PORTC;
  cfg.CSInit.pull      = Chimera::GPIO::Pull::PULL_UP;
  cfg.CSInit.state     = Chimera::GPIO::State::HIGH;
  cfg.CSInit.threaded  = false;
  cfg.CSInit.validity  = true;

  // SCK
  cfg.SCKInit.alternate = Chimera::GPIO::Alternate::SPI1_SCK;
  cfg.SCKInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
  cfg.SCKInit.pin       = 5;
  cfg.SCKInit.port      = Chimera::GPIO::Port::PORTA;
  cfg.SCKInit.threaded  = false;
  cfg.SCKInit.validity  = true;

  // MISO
  cfg.MISOInit.alternate = Chimera::GPIO::Alternate::SPI1_MISO;
  cfg.MISOInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
  cfg.MISOInit.pin       = 6;
  cfg.MISOInit.port      = Chimera::GPIO::Port::PORTA;
  cfg.MISOInit.threaded  = false;
  cfg.MISOInit.validity  = true;

  // MOSI
  cfg.MOSIInit.alternate = Chimera::GPIO::Alternate::SPI1_MOSI;
  cfg.MOSIInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
  cfg.MOSIInit.pin       = 7;
  cfg.MOSIInit.port      = Chimera::GPIO::Port::PORTA;
  cfg.MOSIInit.threaded  = false;
  cfg.MOSIInit.validity  = true;

  auto spi = Chimera::SPI::getDriver( spiChannel );
  spi->init( cfg );
}
