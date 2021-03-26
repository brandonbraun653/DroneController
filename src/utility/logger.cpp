/********************************************************************************
 *  File Name:
 *    logger.cpp
 *
 *  Description:
 *    Logger interface for Thor testing
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Logging Includes */
#include <Aurora/logging>

/* Testing Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/utility/logger.hpp>
#include <src/utility/serial_output.hpp>

namespace DC::UTL
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static Aurora::Logging::SerialSink s_serial_sink;
  static Aurora::Logging::SinkHandle s_serial_handle;
  static Aurora::Logging::SinkHandle s_jlink_handle;

#if defined( CHIMERA_SIMULATOR )
  static Aurora::Logging::CoutSink s_console_sink;
  static Aurora::Logging::SinkHandle s_console_handle;
#endif

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initializeLogger( const Aurora::Logging::Level lvl )
  {
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Initialize the framework
    -------------------------------------------------*/
    initialize();
    setGlobalLogLevel( lvl );

    /*-------------------------------------------------
    Initialize the serial sink
    -------------------------------------------------*/
    s_serial_sink.assignChannel( DC::IO::DBG::serialChannel );
    s_serial_sink.setLogLevel( lvl );
    s_serial_sink.enable();
    s_serial_sink.setName( "HWLogger" );

    if ( !s_serial_handle )
    {
      s_serial_handle = SinkHandle( &s_serial_sink );
      registerSink( s_serial_handle );
    }

    /*-------------------------------------------------
    Initialize the JLink sink
    -------------------------------------------------*/
    JLinkSink::getInstance().setLogLevel( lvl );
    JLinkSink::getInstance().enable();
    JLinkSink::getInstance().setName( "JLINK" );

    if( !s_jlink_handle )
    {
      s_jlink_handle = SinkHandle( &JLinkSink::getInstance() );
      registerSink( s_jlink_handle );
    }

    /*-------------------------------------------------
    Initialize the console sink
    -------------------------------------------------*/
#if defined( CHIMERA_SIMULATOR )
    s_console_sink.setLogLevel( lvl );
    s_console_sink.enable();
    s_console_sink.setName( "ConsoleLogger" );

    if ( !s_console_handle )
    {
      s_console_handle = SinkHandle( &s_console_sink );
      registerSink( s_console_handle );
    }
#endif

    /*-------------------------------------------------
    Set the default sink to use
    -------------------------------------------------*/
#if defined( CHIMERA_SIMULATOR )
    setRootSink( s_console_handle );
#else
    setRootSink( s_jlink_handle );
#endif
  }

}    // namespace DC::UTL
