/********************************************************************************
 *  File Name:
 *    reg_driver.cpp
 *
 *  Description:
 *    Registry driver implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/memory>
#include <Aurora/database>
#include <Aurora/datastore>
#include <Aurora/filesystem_lfs>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/spi>
#include <Chimera/system>

/* Logger Includes */
#include <uLog/ulog.hpp>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/registry/reg_data.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Forward Declarations
  -------------------------------------------------------------------------------*/
  static bool initializeSPI();
  static void datastoreRegisterFail( const size_t id );

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  /*-------------------------------------------------
  File System
  -------------------------------------------------*/
  static lfs_t lfs;
  static const lfs_config lfs_cfg = { .context = nullptr,

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

  /*-------------------------------------------------
  Database Memory Allocation
  -------------------------------------------------*/
  Aurora::Database::RAM Database;
  static Aurora::Database::EntryStore<NUM_DATABASE_KEYS> dbEntryStore;
  static std::array<uint8_t, 1024> dbRAM;

  /*-------------------------------------------------
  Datastore Memory Allocation
  -------------------------------------------------*/
  static constexpr size_t ObservableRange = KEY_OBSERVABLE_END - KEY_OBSERVABLE_START;

  Aurora::Datastore::Manager Datastore;
  static Aurora::Datastore::ObservableMapStorage<ObservableRange> dsMemory;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  bool initialize()
  {
    using namespace Aurora::Flash::NOR;
    using namespace Aurora::Datastore;

    /*-------------------------------------------------
    Prepare the FileSystem driver
    -------------------------------------------------*/
    bool result = true;

    result |= initializeSPI();
    result |= Aurora::FileSystem::Driver::LFS::attachFS( &lfs, &lfs_cfg );
    result |= Aurora::FileSystem::Driver::LFS::attachDevice( Chip::AT25SF081, DC::IO::NOR::spiChannel, lfs_cfg );
    RT_HARD_ASSERT( result );

    /*-------------------------------------------------
    Now actually initialize the FileSystem
    -------------------------------------------------*/
    result = Aurora::FileSystem::configureDriver( Aurora::FileSystem::DRIVER_LITTLE_FS );
    RT_HARD_ASSERT( result );

    /*-------------------------------------------------
    Initialize the database, which forms the back-end
    of the datastore.
    -------------------------------------------------*/
    Database.assignCoreMemory( dbEntryStore, dbRAM.data(), dbRAM.size() );
    Database.reset();

    /*-------------------------------------------------
    Initialize the datastore
    -------------------------------------------------*/
    auto registerCallback = etl::delegate<void(size_t)>::create<datastoreRegisterFail>();

    Datastore.assignCoreMemory( &dsMemory );
    Datastore.resetRegistry();
    Datastore.registerCallback( CB_REGISTER_FAIL, registerCallback );

    for( size_t x=0; x<ARRAY_COUNT( ObservableList ); x++)
    {
      RT_HARD_ASSERT( Datastore.registerObservable( *ObservableList[ x ] ) );
    }

    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "Registry initialized\r\n" );
    return true;
  }

  void format()
  {
    // uint32_t eraseTimeout = 10000;
    // uLog::getRootSink()->flog( uLog::Level::LVL_ERROR, "Performing full chip erase. Timeout of %d ms.\r\n", eraseTimeout );
    // Aurora::Memory::LFS::fullChipErase( eraseTimeout );
    // uLog::getRootSink()->flog( uLog::Level::LVL_ERROR, "Chip erased\r\n" );
  }


  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Configures the SPI controller for the NOR flash chip that
   *  hosts the project's FileSystem.
   *
   *  @return bool
   */
  static bool initializeSPI()
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
    cfg.HWInit.txfrMode    = DC::IO::NOR::spiTxfrMode;
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
    cfg.SCKInit.pull      = Chimera::GPIO::Pull::PULL_DN;
    cfg.SCKInit.threaded  = false;
    cfg.SCKInit.validity  = true;

    // MISO
    cfg.MISOInit.alternate = DC::IO::NOR::misoAlt;
    cfg.MISOInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
    cfg.MISOInit.pin       = DC::IO::NOR::misoPin;
    cfg.MISOInit.port      = DC::IO::NOR::misoPort;
    cfg.MISOInit.pull      = Chimera::GPIO::Pull::PULL_UP;
    cfg.MISOInit.threaded  = false;
    cfg.MISOInit.validity  = true;

    // MOSI
    cfg.MOSIInit.alternate = DC::IO::NOR::mosiAlt;
    cfg.MOSIInit.drive     = Chimera::GPIO::Drive::ALTERNATE_PUSH_PULL;
    cfg.MOSIInit.pin       = DC::IO::NOR::mosiPin;
    cfg.MOSIInit.port      = DC::IO::NOR::mosiPort;
    cfg.MOSIInit.pull      = Chimera::GPIO::Pull::PULL_UP;
    cfg.MOSIInit.threaded  = false;
    cfg.MOSIInit.validity  = true;

    auto spi = Chimera::SPI::getDriver( DC::IO::NOR::spiChannel );
    return spi->init( cfg ) == Chimera::Status::OK;
  }


  /**
   *  Callback for logging when an observable parameter fails
   *  to register with the system
   *
   *  @param[in]  id      Which ID failed
   *  @return void
   */
  static void datastoreRegisterFail( const size_t id )
  {
    uLog::getRootSink()->flog( uLog::Level::LVL_ERROR, "Failed to register observable" );
  }
}    // namespace DC::REG
