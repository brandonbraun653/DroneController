/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the file system thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* STL Includes */
#include <filesystem>
#include <string>

/* Aurora Includes */
#include <Aurora/filesystem>
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/registry/reg_files.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/system/sys_config.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_file_system.hpp>

#include <Chimera/i2c>

struct TestStruct
{
  float mySensor;
  uint32_t timestamp;
  uint32_t logThing;
};

namespace DC::Tasks::FIL
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void FileSystemThread( void *arg )
  {
    using namespace Chimera::Thread;
    using namespace Chimera::Interrupt;
    using namespace Chimera::Peripheral;
    using namespace Aurora::Logging;

    /*-------------------------------------------------------------------------
    Wait for the initialization command
    -------------------------------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------------------------------
    Mount the filesystem
    -------------------------------------------------------------------------*/
    //Aurora::FileSystem::massErase();
    Aurora::FileSystem::mount();
    DC::REG::loadRegistryFromFile();
    SYS::updateBootCount();

    /*-------------------------------------------------------------------------
    Program the device configuration
    -------------------------------------------------------------------------*/
    //DC::SYS::configureDevice( DC::SYS::DEV_1 );

    uint16_t address        = 0x32;
    char     test_data[ 5 ] = { '0', '1', '2', '3', '4' };

    auto i2c = Chimera::I2C::getDriver( Chimera::I2C::Channel::I2C2 );
    auto cfg = Chimera::I2C::DriverConfig();
    cfg.clear();
    cfg.validity = true;

    cfg.HWInit.channel = Chimera::I2C::Channel::I2C2;
    cfg.HWInit.frequency = Chimera::I2C::Frequency::F400KHZ;

    cfg.SCLInit.alternate = Chimera::GPIO::Alternate::I2C3_SCL;
    cfg.SCLInit.drive     = Chimera::GPIO::Drive::ALTERNATE_OPEN_DRAIN;
    cfg.SCLInit.pin       = 8;
    cfg.SCLInit.port      = Chimera::GPIO::Port::PORTA;
    cfg.SCLInit.threaded  = true;
    cfg.SCLInit.validity  = true;

    cfg.SDAInit.alternate = Chimera::GPIO::Alternate::I2C3_SDA;
    cfg.SDAInit.drive     = Chimera::GPIO::Drive::ALTERNATE_OPEN_DRAIN;
    cfg.SDAInit.pin       = 9;
    cfg.SDAInit.port      = Chimera::GPIO::Port::PORTC;
    cfg.SDAInit.threaded  = true;
    cfg.SDAInit.validity  = true;

    i2c->open( cfg );
    i2c->write( address, test_data, sizeof( test_data ) );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();
      BKGD::kickDog( PrjTaskId::FILE_SYSTEM );
      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::FIL
