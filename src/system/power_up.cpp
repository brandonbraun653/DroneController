/********************************************************************************
 *  File Name:
 *    power_up.cpp
 *
 *  Description:
 *    Powers up the board modules and peripherals
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Project Includes */
#include <src/io/gpio_driver.hpp>
#include <src/io/sr_driver.hpp>
#include <src/registry/reg_intf.hpp>
#include <src/system/power_up.hpp>
#include <src/utility/serial_output.hpp>
#include <src/utility/logger.hpp>

namespace DC::SYS
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void powerUpModules()
  {
    /*-------------------------------------------------
    Power up serial resources first for debug functions
    -------------------------------------------------*/
    powerUpSerial();

    /*-------------------------------------------------
    Attempt to mount the file system, which allows the
    registry to initialize properly.
    -------------------------------------------------*/
    powerUpFileSystem();

    /*-------------------------------------------------
    Power up the shift register processing
    -------------------------------------------------*/
    DC::GPIO::SR::init();
  }


  void powerUpSerial()
  {
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Initialize the serial hardware channel
    -------------------------------------------------*/
    UTL::initializeSerial();

    /*-------------------------------------------------
    Turn on logger functionality (depends on serial)
    -------------------------------------------------*/
    UTL::initializeLogger( Level::LVL_DEBUG );
    getRootSink()->flog( Level::LVL_DEBUG, "Power on device\r\n" );
  }


  void powerUpFileSystem()
  {
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Mount the file system
    -------------------------------------------------*/
    if( !REG::initialize() )
    {
      getRootSink()->flog( Level::LVL_ERROR, "Failed to mount registry\r\n" );
    }
  }
}    // namespace DC::SYS
