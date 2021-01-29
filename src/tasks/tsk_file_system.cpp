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
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Aurora Includes */
#include <Aurora/memory>
#include <Aurora/source/memory/flash/littlefs/lfs_hooks.hpp>

/* Little FS Includes */
#include "lfs.h"

/* Logger Includes */
#include <uLog/ulog.hpp>

/* Project Includes */
#include <src/config/board_map.hpp>
#include <src/tasks/tsk_file_system.hpp>

/*-------------------------------------------------------------------------------
Forward Declarations
-------------------------------------------------------------------------------*/
static void initializeSPI();


bool userCallbackInvoked              = false;
static volatile size_t isrVar         = 0;
static volatile size_t lastInvocation = 0;
static Chimera::Interrupt::SignalCallback callbackRegistry;

static void userCallback( const Chimera::Interrupt::SignalCallback * )
{
  if ( ( Chimera::millis() - lastInvocation ) > 5000 )
  {
    lastInvocation      = Chimera::millis();
    userCallbackInvoked = true;
  }
}

static void fastCallback()
{
  isrVar++;
}


/*-------------------------------------------------
LFS Data
-------------------------------------------------*/
lfs_t lfs;
static lfs_file_t file;

lfs_config cfg = { .context = nullptr,

                   // Block device operations
                   .read  = lfs_safe_read,
                   .prog  = lfs_safe_prog,
                   .erase = lfs_safe_erase,
                   .sync  = lfs_safe_sync,

                   // Block device configuration
                   .read_size      = 16,
                   .prog_size      = 16,
                   .block_size     = 4096,
                   .block_count    = 256,
                   .block_cycles   = 500,
                   .cache_size     = 16,
                   .lookahead_size = 16 };

namespace DC::Tasks::FIL
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Threading;
    using namespace Chimera::Interrupt;
    using namespace Chimera::Peripheral;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    this_thread::pendTaskMsg( ITCMsg::TSK_MSG_WAKEUP, TIMEOUT_BLOCK );
    Chimera::delayMilliseconds( 500 );

    /*-------------------------------------------------
    Testing: Register some ISR handlers
    -------------------------------------------------*/
    // callbackRegistry.isrCallback  = ISRCallback::create<fastCallback>();
    // callbackRegistry.userCallback = UserCallback::create<userCallback>();
    // registerISRHandler( Type::PERIPH_USART, Chimera::Serial::SIG_TX_COMPLETE, callbackRegistry );

    /*-------------------------------------------------
    Setup LFS
    -------------------------------------------------*/
    initializeSPI();
    Aurora::Memory::LFS::attachDevice( Aurora::Flash::NOR::Chip::AT25SF081, DC::IO::NOR::spiChannel, cfg );

    // mount the filesystem
    int err = lfs_mount( &lfs, &cfg );

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if ( err )
    {
      err = lfs_format( &lfs, &cfg );
      err = lfs_mount( &lfs, &cfg );
    }

    // for ( auto x = 0; x < 500; x++ )
    // {
    //   // read current count
    //   uint32_t boot_count = 0;
    //   err                 = lfs_file_open( &lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT );
    //   err                 = lfs_file_read( &lfs, &file, &boot_count, sizeof( boot_count ) );

    //   // update boot count
    //   boot_count += 1;
    //   err = lfs_file_rewind( &lfs, &file );
    //   err = lfs_file_write( &lfs, &file, &boot_count, sizeof( boot_count ) );

    //   // remember the storage is not updated until the file is closed successfully
    //   err = lfs_file_close( &lfs, &file );

    //   // print the boot count
    //   // uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "boot count: %d\r\n", boot_count );
    //   // if( userCallbackInvoked )
    //   // {
    //   //   userCallbackInvoked = false;
    //   //   uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "User callback %d invoked!\n", isrVar );
    //   // }
    // }

    // release any resources we were using
    //err = lfs_unmount( &lfs );

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

  cfg.HWInit.bitOrder    = DC::IO::NOR::spiBitOrder;
  cfg.HWInit.clockFreq   = DC::IO::NOR::spiClockFreq;
  cfg.HWInit.clockMode   = DC::IO::NOR::spiClockMode;
  cfg.HWInit.dataSize    = DC::IO::NOR::spiDataSize;
  cfg.HWInit.hwChannel   = DC::IO::NOR::spiChannel;
  cfg.HWInit.txfrMode    = Chimera::SPI::TransferMode::BLOCKING;
  cfg.HWInit.controlMode = Chimera::SPI::ControlMode::MASTER;
  cfg.HWInit.csMode      = Chimera::SPI::CSMode::MANUAL;
  cfg.HWInit.validity    = true;

  // Chip Select
  cfg.externalCS       = false;
  cfg.CSInit.alternate = Chimera::GPIO::Alternate::NONE;
  cfg.CSInit.drive     = Chimera::GPIO::Drive::OUTPUT_PUSH_PULL;
  cfg.CSInit.pin       = DC::IO::NOR::csPin;
  cfg.CSInit.port      = DC::IO::NOR::csPort;
  cfg.CSInit.pull      = Chimera::GPIO::Pull::PULL_UP;
  cfg.CSInit.state     = Chimera::GPIO::State::HIGH;
  cfg.CSInit.threaded  = false;
  cfg.CSInit.validity  = true;

  // SCK
  cfg.SCKInit.alternate = DC::IO::NOR::sckAlt;
  cfg.SCKInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
  cfg.SCKInit.pin       = DC::IO::NOR::sckPin;
  cfg.SCKInit.port      = DC::IO::NOR::sckPort;
  cfg.SCKInit.threaded  = false;
  cfg.SCKInit.validity  = true;

  // MISO
  cfg.MISOInit.alternate = DC::IO::NOR::misoAlt;
  cfg.MISOInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
  cfg.MISOInit.pin       = DC::IO::NOR::misoPin;
  cfg.MISOInit.port      = DC::IO::NOR::misoPort;
  cfg.MISOInit.threaded  = false;
  cfg.MISOInit.validity  = true;

  // MOSI
  cfg.MOSIInit.alternate = DC::IO::NOR::mosiAlt;
  cfg.MOSIInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
  cfg.MOSIInit.pin       = DC::IO::NOR::mosiPin;
  cfg.MOSIInit.port      = DC::IO::NOR::mosiPort;
  cfg.MOSIInit.threaded  = false;
  cfg.MOSIInit.validity  = true;

  auto spi = Chimera::SPI::getDriver( DC::IO::NOR::spiChannel );
  spi->init( cfg );
}
