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
#include <Aurora/database>
#include <Aurora/datastore>
#include <Aurora/filesystem_spiffs>
#include <Aurora/logging>
#include <Aurora/memory>

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/spi>
#include <Chimera/system>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/registry/reg_data.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Static Functions
  -------------------------------------------------------------------------------*/
  static bool initializeSPI();
  static void registerDatabaseKeys();
  static void registerObservables();
  static void datastoreRegisterFail( const size_t id );

  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
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
    using namespace Aurora::FileSystem;
    using namespace Aurora::Logging;

    bool result = true;

    /*-------------------------------------------------
    Prepare the FileSystem driver
    -------------------------------------------------*/
    if constexpr ( DEFAULT_FILESYSTEM == BackendType::DRIVER_SPIFFS )
    {
      result |= initializeSPI();
      result |= Aurora::FileSystem::SPIFFS::attachDevice( Chip::AT25SF081, DC::IO::NOR::spiChannel );
      RT_HARD_ASSERT( result );
    }

    /*-------------------------------------------------
    Now actually initialize the FileSystem
    -------------------------------------------------*/
    result = Aurora::FileSystem::configureDriver( DEFAULT_FILESYSTEM );
    RT_HARD_ASSERT( result );

    /*-------------------------------------------------
    Initialize the database, which forms the back-end
    of the datastore.
    -------------------------------------------------*/
    Database.assignCoreMemory( dbEntryStore, dbRAM.data(), dbRAM.size() );
    Database.reset();
    registerDatabaseKeys();

    /*-------------------------------------------------
    Initialize the datastore
    -------------------------------------------------*/
    auto registerCallback = etl::delegate<void( size_t )>::create<datastoreRegisterFail>();

    Datastore.assignCoreMemory( &dsMemory );
    Datastore.resetRegistry();
    Datastore.registerCallback( CB_REGISTER_FAIL, registerCallback );
    registerObservables();

    LOG_DEBUG( "Registry initialized\r\n" );
    return true;
  }


  void format()
  {
    // uint32_t eraseTimeout = 10000;
    // LOG_ERROR( "Performing full chip erase. Timeout of %d ms.\r\n", eraseTimeout );
    // Aurora::Memory::LFS::fullChipErase( eraseTimeout );
    // LOG_ERROR( "Chip erased\r\n" );
  }


  bool readSafe( const DatabaseKeys key, void *const data, const size_t size )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    if ( !data || !size || !( key < NUM_DATABASE_KEYS ) )
    {
      return false;
    }

    /*-------------------------------------------------
    Select the proper interface to read from
    -------------------------------------------------*/
    if ( ( KEY_SIMPLE_START <= key ) && ( key < KEY_SIMPLE_END ) && ( size == Database.size( key ) ) )
    {
      return Database.read( key, data );
    }
    else if ( ( KEY_OBSERVABLE_START <= key ) && ( key < KEY_OBSERVABLE_END ) )
    {
      return Datastore.readDataSafe( key, data, size );
    }
    else
    {
      return false;
    }
  }


  bool writeSafe( const DatabaseKeys key, const void *const data, const size_t size )
  {
    /*-------------------------------------------------
    Input protection
    -------------------------------------------------*/
    if ( !data || !size || !( key < NUM_DATABASE_KEYS ) )
    {
      return false;
    }

    /*-------------------------------------------------
    Select the proper interface to write. Observable
    registry key types cannot be directly written to.
    -------------------------------------------------*/
    if ( ( KEY_SIMPLE_START <= key ) && ( key < KEY_SIMPLE_END ) && ( size == Database.size( key ) ) )
    {
      return Database.write( key, data );
    }
    else
    {
      return false;
    }
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
   *  Allocates memory in the database for all system parameters
   *  @return void
   */
  static void registerDatabaseKeys()
  {
    using namespace Aurora::Database;

    /*-------------------------------------------------
    Parameter sizing information
    -------------------------------------------------*/
    union ParamData
    {
      uint32_t boot_count;
    } pData;

    /*-------------------------------------------------
    Register all known parameters
    -------------------------------------------------*/
    for ( size_t x = KEY_SIMPLE_START; x < KEY_SIMPLE_END; x++ )
    {
      Chimera::Status_t result = Chimera::Status::OK;
      switch ( x )
      {
        case KEY_BOOT_COUNT:
          pData.boot_count = 0;
          result           = Database.insert( x, &pData.boot_count, sizeof( ParamData::boot_count ), MemAccess::MEM_RW );
          break;


        case KEY_ANALOG_IN_PITCH:
        case KEY_ANALOG_IN_ROLL:
        case KEY_ANALOG_IN_YAW:
        case KEY_ANALOG_IN_THROTTLE:
          result = Database.insert( x, sizeof( float ) );
          break;

        default:
          // A parameter was forgotten to be registered
          RT_HARD_ASSERT( false );
          break;
      }

      RT_HARD_ASSERT( result == Chimera::Status::OK );
    }
  }


  /**
   *  Allocates memory in the datastore for all system observables
   *  @return void
   */
  static void registerObservables()
  {
    for ( size_t x = 0; x < ARRAY_COUNT( ObservableList ); x++ )
    {
      RT_HARD_ASSERT( Datastore.registerObservable( ObservableList[ x ], &Database ) );
    }
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
    using namespace Aurora::Logging;
    LOG_ERROR( "Failed to register observable" );
  }
}    // namespace DC::REG
