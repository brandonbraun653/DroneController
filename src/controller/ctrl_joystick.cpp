/******************************************************************************
 *  File Name:
 *    ctrl_joystick.cpp
 *
 *  Description:
 *    Joystick controller implementation
 *
 *  2022 | Brandon Braun | brandonbraun653@gmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/logging>
#include <Chimera/thread>
#include <src/controller/ctrl_intf.hpp>
#include <src/registry/reg_intf.hpp>

namespace DC::CTRL
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  JoyStick::JoyStick( const DC::HMI::JoyStick::Axis type ) : mUpperLimit( -1.0f ), mLowerLimit( -1.0f ), mAxis( type )
  {
  }


  JoyStick::~JoyStick()
  {
  }


  DC::HMI::JoyStick::Axis JoyStick::axis() const
  {
    return mAxis;
  }


  float JoyStick::value()
  {
    Chimera::Thread::LockGuard _lock( *this );
    /*-------------------------------------------------------------------------
    Input Protection
    -------------------------------------------------------------------------*/
    if ( ( mUpperLimit == -1.0f ) || ( mLowerLimit == -1.0f ) )
    {
      return -1.0f;
    }

    /*-------------------------------------------------------------------------
    Grab the latest data from the registry
    -------------------------------------------------------------------------*/
    float stickValue = 0.0f;
    switch( mAxis )
    {
      case DC::HMI::JoyStick::Axis::PITCH:
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_PITCH, &stickValue, sizeof( stickValue ) );
        break;

      case DC::HMI::JoyStick::Axis::ROLL:
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_ROLL, &stickValue, sizeof( stickValue ) );
        break;

      case DC::HMI::JoyStick::Axis::YAW:
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_YAW, &stickValue, sizeof( stickValue ) );
        break;

      case DC::HMI::JoyStick::Axis::THROTTLE:
        DC::REG::readSafe( DC::REG::KEY_ANALOG_IN_THROTTLE, &stickValue, sizeof( stickValue ) );
        break;

      default:
        LOG_ERROR( "Improperly configured JoyStick object!\r\n" );
        return -1.0f;
        break;
    };

    return this->map( stickValue, mLowerLimit, mUpperLimit, 0.0f, 100.0f );
  }


  void JoyStick::setUpperLimit( const float limit )
  {
    Chimera::Thread::LockGuard _lock( *this );
    mUpperLimit = limit;
  }


  void JoyStick::setLowerLimit( const float limit )
  {
    Chimera::Thread::LockGuard _lock( *this );
    mLowerLimit = limit;
  }


  float JoyStick::map(const float val, const float in_min, const float in_max, const float out_min, const float out_max ) const
  {
    const float slope = (out_max - out_min) / (in_max - in_min);
    const float output = out_min + slope * (val - in_min);

    return output;
  }

}    // namespace DC::CTRL
