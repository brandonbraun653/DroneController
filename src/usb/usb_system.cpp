/********************************************************************************
 *  File Name:
 *    usb_system.cpp
 *
 *  Description:
 *    USB system implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* DC Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/config/tinyusb/tusb_config.h>
#include <src/usb/usb_system.hpp>


extern "C" int CFG_TUSB_DEBUG_PRINTF( const char *format, ... )
{
  /*-------------------------------------------------
  Format the log string into the message buffer
  -------------------------------------------------*/
  char msg_buffer[ 256 ];
  va_list argptr;
  va_start( argptr, format );
  memset( msg_buffer, 0, sizeof( msg_buffer ) );
  vsnprintf( msg_buffer, ARRAY_COUNT( msg_buffer ), format, argptr );
  va_end( argptr );

  LOG_INFO( msg_buffer );
  return 0;
}

namespace DC::USB
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initialize()
  {
    Chimera::Status_t initResult = Chimera::Status::OK;

    auto dm    = Chimera::GPIO::getDriver( DC::IO::USB::dMPinInit.port, DC::IO::USB::dMPinInit.pin );
    initResult = dm->init( DC::IO::USB::dMPinInit );
    LOG_ERROR_IF( initResult != Chimera::Status::OK, "USB DM pin init fail\r\n" );

    auto dp    = Chimera::GPIO::getDriver( DC::IO::USB::dPPinInit.port, DC::IO::USB::dPPinInit.pin );
    initResult = dp->init( DC::IO::USB::dPPinInit );
    LOG_ERROR_IF( initResult != Chimera::Status::OK, "USB DP pin init fail\r\n" );
  }

}    // namespace DC::USB
