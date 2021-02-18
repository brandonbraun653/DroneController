/********************************************************************************
 *  File Name:
 *    tsk_graphics.cpp
 *
 *  Description:
 *    Implementation of the graphics thread
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_graphics.hpp>



// TESTING ONLY
#include <filesystem>
#include <ChimeraSim/control>
#include <ChimeraSim/transport>
#include <Chimera/spi>

namespace DC::Tasks::GFX
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void GraphicsThread( void *arg )
  {
    using namespace Chimera::Thread;
    using namespace Aurora::Logging;

    /*-------------------------------------------------
    Wait for the background thread to wake us
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 100 );

    Chimera::SIM::setDriverType( Chimera::Peripheral::Type::PERIPH_SPI, Chimera::SIM::Driver_t::NETWORKED_CONTROL );

    std::array<uint8_t, 10> txBuffer= { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::array<uint8_t, 10> rxBuffer;
    rxBuffer.fill( 0 );


    Chimera::SPI::DriverConfig cfg;
    cfg.HWInit.hwChannel = Chimera::SPI::Channel::SPI1;

    auto driver = Chimera::SPI::getDriver( Chimera::SPI::Channel::SPI1 );
    driver->init( cfg );
    driver->readWriteBytes( txBuffer.data(), rxBuffer.data(), rxBuffer.size() );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      Chimera::delayMilliseconds( lastWoken, 500 );
    }
  }
}    // namespace DC::Tasks::GFX

