/******************************************************************************
 *  File Name:
 *    ctrl_observers.hpp
 *
 *  Description:
 *    Observable declarations for control input events
 *
 *  2022 | Brandon Braun | brandonbraun653@gmail.com
 *****************************************************************************/

#pragma once
#ifndef DC_CONTROLLER_OBSERVABLES_HPP
#define DC_CONTROLLER_OBSERVABLES_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Aurora/datastore>
#include <Aurora/hmi>
#include <Chimera/gpio>
#include <src/registry/reg_data.hpp>

namespace DC::CTRL
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  ObserverDeclare( PitchTrimUpObserver, bool );
  ObserverDeclare( PitchTrimDnObserver, bool );
  ObserverDeclare( RollTrimUpObserver, bool );
  ObserverDeclare( RollTrimDnObserver, bool );
  ObserverDeclare( YawTrimUpObserver, bool );
  ObserverDeclare( YawTrimDnObserver, bool );
  ObserverDeclare( ThrottleTrimUpObserver, bool );
  ObserverDeclare( ThrottleTrimDnObserver, bool );
  ObserverDeclare( SwitchAObserver, Chimera::GPIO::State );
  ObserverDeclare( SwitchBObserver, Chimera::GPIO::State );
  ObserverDeclare( SwitchCObserver, Chimera::GPIO::State );
  ObserverDeclare( SwitchDObserver, Chimera::GPIO::State );
  ObserverDeclare( Encoder0CenterButtonObserver, bool );
  ObserverDeclare( Encoder1CenterButtonObserver, bool );

}  // namespace DC::CTRL

#endif  /* !DC_CONTROLLER_OBSERVABLES_HPP */
