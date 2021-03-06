/********************************************************************************
 *  File Name:
 *    serial_output.cpp
 *
 *  Description:
 *    Insert Description
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/gpio>
#include <Chimera/serial>
#include <Chimera/thread>

/* ETL Includes */
#include <etl/circular_buffer.h>

/* Testing Includes */
#include <src/utility/serial_output.hpp>
#include <src/config/bsp/board_map.hpp>

/*-------------------------------------------------
Serial Driver Configuration
-------------------------------------------------*/
// Length of the hardware buffer for transceiving a Serial message
static constexpr size_t HWBufferSize = 128;
static constexpr size_t CircleBufSize = 2 * HWBufferSize;

// Serial Transmit Buffers
static std::array<uint8_t, HWBufferSize> sTXHWBuffer;
static etl::circular_buffer<uint8_t, CircleBufSize> sTXCircularBuffer;

// Serial Receive Buffers
static std::array<uint8_t, HWBufferSize> sRXHWBuffer;
static etl::circular_buffer<uint8_t, CircleBufSize> sRXCircularBuffer;


namespace DC::UTL
{
  void initializeSerial()
  {
    using namespace Chimera::Serial;
    using namespace Chimera::Hardware;

    /*------------------------------------------------
    Configuration info for the serial object
    ------------------------------------------------*/
    IOPins pins;
    pins.tx = DC::IO::DBG::txPinInit;
    pins.rx = DC::IO::DBG::rxPinInit;

    Config cfg = DC::IO::DBG::comConfig;

    /*------------------------------------------------
    Create the serial object and initialize it
    ------------------------------------------------*/
    auto result = Chimera::Status::OK;
    auto Serial = Chimera::Serial::getDriver( DC::IO::DBG::serialChannel );

    if ( !Serial )
    {
      Chimera::insert_debug_breakpoint();
    }

    result |= Serial->assignHW( DC::IO::DBG::serialChannel, pins );
    result |= Serial->configure( cfg );
    result |= Serial->enableBuffering( SubPeripheral::TX, sTXCircularBuffer, sTXHWBuffer.data(), sTXHWBuffer.size() );
    result |= Serial->enableBuffering( SubPeripheral::RX, sRXCircularBuffer, sRXHWBuffer.data(), sRXHWBuffer.size() );
    RT_HARD_ASSERT( result == Chimera::Status::OK );

    Serial->begin( PeripheralMode::INTERRUPT, PeripheralMode::INTERRUPT );
  }
}    // namespace DC::UTL
