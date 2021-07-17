/********************************************************************************
 *  File Name:
 *    tsk_hmi.cpp
 *
 *  Description:
 *    Implementation of the human-machine interface
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Aurora Includes */
#include <Aurora/logging>
#include <Aurora/math>

/* Chimera Includes */
#include <Chimera/adc>
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/config/bsp/board_map.hpp>
#include <src/hmi/hmi_discrete.hpp>
#include <src/hmi/hmi_discrete_msg_pump.hpp>
#include <src/hmi/hmi_encoder.hpp>
#include <src/hmi/hmi_encoder_msg_pump.hpp>
#include <src/io/shift_register_driver.hpp>
#include <src/tasks/tsk_background.hpp>
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::HMI
{

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void HumanInterfaceThread( void *arg )
  {
    using namespace Aurora::Logging;
    using namespace Chimera::Thread;
    using namespace DC::HMI;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------
    Initialize the HMI drivers
    -------------------------------------------------*/
    Discrete::initMessagePump();
    Encoder::initMessagePump();

    auto adc = Chimera::ADC::getDriver( Chimera::ADC::Peripheral::ADC_0 );

    while ( true )
    {
      BKGD::kickDog( PrjTaskId::HMI );
      Chimera::delayMilliseconds( 10 );

      /*-------------------------------------------------
      Update the GPIO states
      -------------------------------------------------*/
      DC::HMI::Discrete::doPeriodicProcessing();
      DC::HMI::Encoder::doPeriodicProcessing();

      /*-------------------------------------------------
      Sample the ADC inputs
      -------------------------------------------------*/
      adc->startSequence();
    }
  }
}    // namespace DC::Tasks::HMI
