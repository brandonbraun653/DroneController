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
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::HMI
{
  void keyPress( DC::HMI::Button::Key key )
  {
    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "Key pressed! \r\n" );
  }

  void keyRelease( DC::HMI::Button::Key key )
  {
    uLog::getRootSink()->flog( uLog::Level::LVL_DEBUG, "Key release! \r\n" );
  }

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void HumanInterfaceThread( void *arg )
  {
    using namespace Chimera::Threading;
    using namespace DC::HMI;

    /*-------------------------------------------------
    Wait for initialization command
    -------------------------------------------------*/
    waitInit();
    Chimera::delayMilliseconds( 100 );

    /*-------------------------------------------------
    Initialize the HMI drivers
    -------------------------------------------------*/
    auto pressCB    = Button::EventCallback::create<keyPress>();
    auto releaseCB  = Button::EventCallback::create<keyRelease>();
    bool initResult = DC::HMI::Button::initialize();
    RT_HARD_ASSERT( initResult );

    Button::onPress( Button::Key::TOUCH_KEY_1, pressCB );
    Button::onRelease( Button::Key::TOUCH_KEY_1, releaseCB );
    Button::enable( Button::Key::TOUCH_KEY_1 );

    size_t lastWoken;
    while ( true )
    {
      lastWoken = Chimera::millis();

      Chimera::delayMilliseconds( lastWoken, 100 );
    }
  }
}    // namespace DC::Tasks::HMI
