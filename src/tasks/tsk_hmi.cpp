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

/* Chimera Includes */
#include <Chimera/assert>
#include <Chimera/common>
#include <Chimera/interrupt>
#include <Chimera/serial>
#include <Chimera/thread>

/* Project Includes */
#include <src/hmi/hmi_button.hpp>
#include <src/hmi/hmi_encoder.hpp>
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::HMI
{
  volatile int currentPosition = 0;
  volatile bool updated        = false;

  void keyPress( Aurora::HMI::Button::ActiveEdge key )
  {
    using namespace Aurora::Logging;
    getRootSink()->flog( Level::LVL_DEBUG, "Key pressed! \r\n" );
  }

  void keyRelease( Aurora::HMI::Button::ActiveEdge key )
  {
    using namespace Aurora::Logging;
    getRootSink()->flog( Level::LVL_DEBUG, "Key release! \r\n" );
  }

  void rotate( Aurora::HMI::Encoder::State &state )
  {
    currentPosition = state.absolutePosition;
    updated = true;
  }

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
    auto pressCB    = Aurora::HMI::Button::EdgeCallback::create<keyPress>();
    auto releaseCB  = Aurora::HMI::Button::EdgeCallback::create<keyRelease>();
    auto rotateCB   = Aurora::HMI::Encoder::RotationCallback::create<rotate>();
    // bool initResult = DC::HMI::Encoder::initialize();
    // RT_HARD_ASSERT( initResult );

    // Encoder::onCenterPress( Encoder::Key::ENCODER_1, pressCB );
    // Encoder::onCenterRelease( Encoder::Key::ENCODER_1, releaseCB );
    // Encoder::onRotate( Encoder::Key::ENCODER_1, rotateCB );

    // Encoder::enable( Encoder::Key::ENCODER_1 );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      if ( updated )
      {
        int pos = currentPosition;
        updated = false;
        getRootSink()->flog( Level::LVL_DEBUG, "Position %d\r\n", pos );
      }

      Chimera::delayMilliseconds( lastWoken, 10 );
    }
  }
}    // namespace DC::Tasks::HMI
