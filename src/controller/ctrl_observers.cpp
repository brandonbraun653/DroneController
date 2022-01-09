/******************************************************************************
 *  File Name:
 *    ctrl_observers.cpp
 *
 *  Description:
 *    Implementation of the controller observers for all
 *
 *  2022 | Brandon Braun | brandonbraun653@gmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include "controller.pb.h"
#include <Aurora/logging>
#include <Chimera/common>
#include <Ripple/user>
#include <src/config/ripple/ripple_packet_contract_prj.hpp>
#include <src/controller/ctrl_observers.hpp>
#include <src/registry/reg_data.hpp>
#include <src/tasks/tsk_radio.hpp>

namespace DC::CTRL
{
  /*---------------------------------------------------------------------------
  Static Functions
  ---------------------------------------------------------------------------*/
  void publishEvent( DiscreteEvent &event )
  {
    using namespace DC::Tasks::RADIO;

    if ( !txSocket )
    {
      return;
    }

    auto success = Ripple::transmit( PKT_EVENT_DISCRETE_INPUT, *txSocket, &event, sizeof( event ) );
    LOG_WARN_IF( !success, "Failed to transmit PKT_EVENT_DISCRETE_INPUT packet\r\n" );
  }


  void handleButtonEvent( const DiscreteEvent_SignalType signal, const bool data )
  {
    /*-------------------------------------------------------------------------
    Pack the event data
    -------------------------------------------------------------------------*/
    DiscreteEvent event;
    event.signal    = signal;
    event.state     = data ? DiscreteEvent_StateType_Active : DiscreteEvent_StateType_Inactive;
    event.timestamp = Chimera::millis();

    /*-------------------------------------------------------------------------
    Push the data onto the network
    -------------------------------------------------------------------------*/
    publishEvent( event );
  }


  void handleToggleEvent( const DiscreteEvent_SignalType signal, const Chimera::GPIO::State data )
  {
    /*-------------------------------------------------------------------------
    Pack the event data
    -------------------------------------------------------------------------*/
    DiscreteEvent event;
    event.signal    = signal;
    event.timestamp = Chimera::millis();

    switch( data )
    {
      case Chimera::GPIO::State::HIGH:
        event.state = DiscreteEvent_StateType_Active;
        break;

      case Chimera::GPIO::State::LOW:
        event.state = DiscreteEvent_StateType_Inactive;
        break;

      default:
        event.state = DiscreteEvent_StateType_HiZ;
        break;
    };

    /*-------------------------------------------------------------------------
    Push the data onto the network
    -------------------------------------------------------------------------*/
    publishEvent( event );
  }


  /*---------------------------------------------------------------------------
  Class Implementations
  ---------------------------------------------------------------------------*/
  void PitchTrimUpObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_PitchTrimUp, data );
  }

  void PitchTrimDnObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_PitchTrimDn, data );
  }


  void RollTrimUpObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_RollTrimUp, data );
  }


  void RollTrimDnObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_RollTrimDn, data );
  }


  void YawTrimUpObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_YawTrimUp, data );
  }


  void YawTrimDnObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_YawTrimDn, data );
  }


  void ThrottleTrimUpObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_ThrottleTrimUp, data );
  }


  void ThrottleTrimDnObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_ThrottleTrimDn, data );
  }


  void Encoder0CenterButtonObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_Encoder0Center, data );
  }


  void Encoder1CenterButtonObserver::notification( bool data )
  {
    handleButtonEvent( DiscreteEvent_SignalType_Encoder1Center, data );
  }


  void SwitchAObserver::notification( Chimera::GPIO::State data )
  {
    handleToggleEvent( DiscreteEvent_SignalType_SwitchAToggle, data );
  }


  void SwitchBObserver::notification( Chimera::GPIO::State data )
  {
    handleToggleEvent( DiscreteEvent_SignalType_SwitchBToggle, data );
  }


  void SwitchCObserver::notification( Chimera::GPIO::State data )
  {
    handleToggleEvent( DiscreteEvent_SignalType_SwitchCToggle, data );
  }


  void SwitchDObserver::notification( Chimera::GPIO::State data )
  {
    handleToggleEvent( DiscreteEvent_SignalType_SwitchDToggle, data );
  }

}    // namespace DC::CTRL
