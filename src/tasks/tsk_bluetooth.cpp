/********************************************************************************
 *  File Name:
 *    tsk_bluetooth.cpp
 *
 *  Description:
 *    Implements the bluetooth threading functions
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/common>
#include <Chimera/thread>

/* Project Includes */
#include <src/tasks/tsk_common.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_bluetooth.hpp>
#include <src/wireless/bluetooth/bt_driver.hpp>


// Driver testing
#include <algorithm>
#include <array>
#include <Chimera/dma>
#include <etl/random.h>
static constexpr size_t dma_period = 500;
static size_t last_dma = 0;
static std::array<uint8_t, 1024> s_dma_buf0, s_dma_buf1;
static etl::random_xorshift s_rng;
static bool txfr_success = false;

static void dma_cb( const Chimera::DMA::TransferStats &stats )
{
  txfr_success = ( s_dma_buf0 == s_dma_buf1 );
}


namespace DC::Tasks::BT
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void BluetoothThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;

    /*-------------------------------------------------
    Wait to be told to initialize by monitor thread
    -------------------------------------------------*/
    waitInit();

    /*-------------------------------------------------
    Power up the bluetooth driver
    -------------------------------------------------*/
    LOG_INFO( "Enabling bluetooth module\r\n" );
    RF::BT::setPower( RF::BT::PowerState::ENABLED );

    s_rng.initialise( Chimera::millis() );
    last_dma = Chimera::millis();
    txfr_success = false;


    while ( 1 )
    {
      if( ( Chimera::millis() - last_dma ) >= dma_period )
      {
        using namespace Chimera::DMA;

        last_dma = Chimera::millis();

        /* Reset the buffers */
        //std::generate( s_dma_buf0.begin(), s_dma_buf0.end(), s_rng );
        s_dma_buf0.fill( 0xCC );
        s_dma_buf1.fill( 0 );

        MemTransfer cfg;
        cfg.alignment = Alignment::BYTE;
        cfg.src       = reinterpret_cast<std::uintptr_t>( s_dma_buf0.data() );
        cfg.dst       = reinterpret_cast<std::uintptr_t>( s_dma_buf1.data() );
        cfg.size      = s_dma_buf0.size();
        cfg.priority  = Chimera::DMA::Priority::MEDIUM;
        cfg.callback  = TransferCallback::create<dma_cb>();

        transfer( cfg );
      }

      if( txfr_success )
      {
        txfr_success = false;
        LOG_INFO( "DMA transfer succeeded\r\n" );
      }


      BKGD::kickDog( PrjTaskId::BLUETOOTH );
      Chimera::delayMilliseconds( 10 );
    }
  }

}    // namespace DC::Tasks::RADIO
