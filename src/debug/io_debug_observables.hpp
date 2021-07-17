/********************************************************************************
 *  File Name:
 *    io_debug_observables.hpp
 *
 *  Description:
 *    Observable declarations for debugging
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_DEBUG_OBSERVABLES_HPP
#define DC_DEBUG_OBSERVABLES_HPP

/* Aurora Includes */
#include <Aurora/logging>

/* Chimera Includes */
#include <Chimera/gpio>

/* ETL Includes */
#include <etl/observer.h>


namespace DC::DBG
{
  /*-----------------------------------------------------------------
  Classes
  -----------------------------------------------------------------*/
  class PitchTrimUpObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Pitch trim up %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class PitchTrimDnObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Pitch trim down %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class RollTrimUpObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Roll trim up %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class RollTrimDnObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Roll trim down %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class YawTrimUpObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Yaw trim up %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class YawTrimDnObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Yaw trim down %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class ThrottleTrimUpObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Throttle trim up %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class ThrottleTrimDnObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Throttle trim down %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class SwitchAObserver : public etl::observer<Chimera::GPIO::State>
  {
  public:
    void notification( Chimera::GPIO::State data )
    {
      LOG_INFO( "Switch A %s\r\n", ( data == Chimera::GPIO::State::HIGH ? "PRESSED" : "RELEASED" ) );
    }
  };

  class SwitchBObserver : public etl::observer<Chimera::GPIO::State>
  {
  public:
    void notification( Chimera::GPIO::State data )
    {
      LOG_INFO( "Switch B %s\r\n", ( data == Chimera::GPIO::State::HIGH ? "PRESSED" : "RELEASED" ) );
    }
  };

  class SwitchCObserver : public etl::observer<Chimera::GPIO::State>
  {
  public:
    void notification( Chimera::GPIO::State data )
    {
      LOG_INFO( "Switch C %s\r\n", ( data == Chimera::GPIO::State::HIGH ? "PRESSED" : "RELEASED" ) );
    }
  };

  class SwitchDObserver : public etl::observer<Chimera::GPIO::State>
  {
  public:
    void notification( Chimera::GPIO::State data )
    {
      LOG_INFO( "Switch D %s\r\n", ( data == Chimera::GPIO::State::HIGH ? "PRESSED" : "RELEASED" ) );
    }
  };

  class Encoder0CenterButtonObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Encoder 0 %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };

  class Encoder1CenterButtonObserver : public etl::observer<bool>
  {
  public:
    void notification( bool data )
    {
      LOG_INFO( "Encoder 1 %s\r\n", ( data ? "PRESSED" : "RELEASED" ) );
    }
  };
}  // namespace DC::DBG

#endif  /* !DC_DEBUG_OBSERVABLES_HPP */
