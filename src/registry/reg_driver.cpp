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
#include <Aurora/hmi>
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
#include <src/registry/reg_files.hpp>

namespace DC::REG
{
  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/
  static bool initializeSPI();
  static void registerDatabaseKeys();
  static void registerObservables();
  static void datastoreRegisterFail( const size_t id );
  static bool initializeFiles();
  static void populateStructuredData();

  /*---------------------------------------------------------------------------
  Static Data
  ---------------------------------------------------------------------------*/
  /* Database Memory Allocation */
  Aurora::Database::RAM Database;
  static Aurora::Database::EntryStore<NUM_DATABASE_KEYS> dbEntryStore;
  static std::array<uint8_t, 1024> dbRAM;

  /* Datastore Memory Allocation */
  static constexpr size_t ObservableRange = KEY_OBSERVABLE_END - KEY_OBSERVABLE_START;
  Aurora::Datastore::Manager Datastore;
  static Aurora::Datastore::ObservableMapStorage<ObservableRange> dsMemory;

  /*---------------------------------------------------------------------------
  Public Interface Functions
  ---------------------------------------------------------------------------*/
  bool initialize()
  {
    using namespace Aurora::Flash::NOR;
    using namespace Aurora::Datastore;
    using namespace Aurora::FileSystem;
    using namespace Aurora::Logging;

    bool result = true;

    /*-------------------------------------------------------------------------
    Prepare the FileSystem Driver
    -------------------------------------------------------------------------*/
    if constexpr ( DEFAULT_FILESYSTEM == BackendType::DRIVER_SPIFFS )
    {
      result |= initializeSPI();
      result |= Aurora::FileSystem::SPIFFS::attachDevice( Chip::AT25SF081, DC::IO::NOR::spiChannel );
      RT_HARD_ASSERT( result );
    }

    result = Aurora::FileSystem::configureDriver( DEFAULT_FILESYSTEM );
    RT_HARD_ASSERT( result );

    /*-------------------------------------------------------------------------
    Initialize the database, which forms the back-end of the datastore.
    -------------------------------------------------------------------------*/
    Database.assignCoreMemory( dbEntryStore, dbRAM.data(), dbRAM.size() );
    Database.reset();
    registerDatabaseKeys();

    /*-------------------------------------------------------------------------
    Initialize the datastore
    -------------------------------------------------------------------------*/
    auto registerCallback = etl::delegate<void( size_t )>::create<datastoreRegisterFail>();

    Datastore.assignCoreMemory( &dsMemory );
    Datastore.resetRegistry();
    Datastore.registerCallback( CB_REGISTER_FAIL, registerCallback );
    registerObservables();

    return true;
  }


  void format()
  {
    LOG_INFO( "Performing full chip erase. Please be patient...\r\n" );
    Aurora::FileSystem::massErase();
    LOG_INFO( "Chip erased\r\n" );
  }


  void doPeriodicProcessing()
  {
    /* Process observables */
    Datastore.process();
  }


  bool readSafe( const DatabaseKeys key, void *const data, const size_t size )
  {
    /*-------------------------------------------------------------------------
    Input Protections
    -------------------------------------------------------------------------*/
    if ( !data || !size || !( key < NUM_DATABASE_KEYS ) )
    {
      return false;
    }

    /*-------------------------------------------------------------------------
    Select the proper interface to read from
    -------------------------------------------------------------------------*/
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
    /*-------------------------------------------------------------------------
    Input Protection
    -------------------------------------------------------------------------*/
    if ( !data || !size || !( key < NUM_DATABASE_KEYS ) )
    {
      return false;
    }

    /*-------------------------------------------------------------------------
    Select the proper interface to write. Observable registry key types cannot
    be directly written to.
    -------------------------------------------------------------------------*/
    if ( ( KEY_SIMPLE_START <= key ) && ( key < KEY_SIMPLE_END ) && ( size == Database.size( key ) ) )
    {
      return Database.write( key, data );
    }
    else
    {
      return false;
    }
  }


  void loadRegistryFromFile()
  {
    initializeFiles();
    populateStructuredData();
  }


  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/
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
        case KEY_BATT_VOLTAGE_SENSE:
          result = Database.insert( x, sizeof( float ) );
          break;

        case KEY_BATT_POWER_GOOD:
        case KEY_BATT_CHARGE_GOOD:
          result = Database.insert( x, sizeof( bool ) );
          break;

        case KEY_ENCODER_0_STATE:
        case KEY_ENCODER_1_STATE:
          result = Database.insert( x, sizeof( Aurora::HMI::Encoder::State ) );
          break;

        case KEY_RF24_CONFIG:
          result = Database.insert( x, sizeof( DC::Files::RF24Config::DataType ) );
          break;

        case KEY_UNIT_INFO:
          result = Database.insert( x, sizeof( DC::Files::UnitInfo::DataType ) );
          break;

        default:
          // A parameter was forgotten to be registered
          result = Chimera::Status::FAIL;
          LOG_ERROR( "Failed to register parameter: %d\r\n", x );
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


  /**
   * @brief Creates all files on the system to ensure they exist at runtime
   *
   * @return true
   * @return false
   */
  static bool initializeFiles()
  {
    /*-------------------------------------------------------------------------
    Files that should exist at boot
    -------------------------------------------------------------------------*/
    const std::array<std::string_view, 3> files = {
      DC::Files::BootCount::Filename,
      DC::Files::UnitInfo::Filename,
      DC::Files::RF24Config::Filename
    };

    /*-------------------------------------------------------------------------
    Ensure each file exists on disk
    -------------------------------------------------------------------------*/
    Aurora::FileSystem::BinaryFile f;
    uint32_t creation_errors = 0;
    for( auto file : files )
    {
      if ( !f.open( file, "rb" ) )
      {
        f.clearErrors();
        f.create( file );
        if( !f.open( file, "wb" ) )
        {
          creation_errors++;
          LOG_ERROR( "Creation of %s failed: %d\r\n", file.data(), f.getError() );
        }
      }

      f.close();
    }

    return creation_errors == 0;
  }


  /**
   * @brief Pull data out from files and push them to the registry
   */
  static void populateStructuredData()
  {
    Aurora::FileSystem::BinaryFile file;

    /*-------------------------------------------------------------------------
    Unit Information
    -------------------------------------------------------------------------*/
    if( file.open( DC::Files::UnitInfo::Filename, "rb" ) )
    {
      DC::Files::UnitInfo::DataType data;
      if( file.read( &data, sizeof( data ) ) )
      {
        writeSafe( DC::Files::UnitInfo::DBKey, &data, sizeof( data ) );
      }
      file.close();
    }

    /*-------------------------------------------------------------------------
    RF24 Configuration
    -------------------------------------------------------------------------*/
    if( file.open( DC::Files::RF24Config::Filename, "rb" ) )
    {
      DC::Files::RF24Config::DataType data;
      if( file.read( &data, sizeof( data ) ) )
      {
        writeSafe( DC::Files::RF24Config::DBKey, &data, sizeof( data ) );
      }
      file.close();
    }
  }
}    // namespace DC::REG
