/********************************************************************************
 *  File Name:
 *    power_up.cpp
 *
 *  Description:
 *    Powers up the board modules and peripherals
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
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
    //powerUpFileSystem();
  }


  void powerUpSerial()
  {
    /*-------------------------------------------------
    Initialize the serial hardware channel
    -------------------------------------------------*/
    UTL::initializeSerial();

    /*-------------------------------------------------
    Turn on logger functionality (depends on serial)
    -------------------------------------------------*/
    UTL::initializeLogger( uLog::Level::LVL_DEBUG );
    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "Power on device\r\n" );
  }


  void powerUpFileSystem()
  {
    /*-------------------------------------------------
    Mount the file system
    -------------------------------------------------*/
    if( !REG::initialize() || !REG::mount() )
    {
      uLog::getRootSink()->flog( uLog::Level::LVL_ERROR, "Failed to mount registry\r\n" );
    }
  }
}    // namespace DC::SYS
