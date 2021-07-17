/********************************************************************************
 *  File Name:
 *    reg_data_button_trim.cpp
 *
 *  Description:
 *    Parameter data implementation for all trim up/down inputs.
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
#include <src/registry/reg_data.hpp>
#include <src/hmi/hmi_discrete_msg_pump.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Pitch Trim Up
  -------------------------------------------------------------------------------*/
  Observable_PitchTrimUp Param_PitchTrimUp;

  void Observable_PitchTrimUp::initialize()
  {
    basicInit();
  }

  void Observable_PitchTrimUp::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.PitchTrimUp == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_PitchTrimUp::onTimeout()
  {
  }

  bool Observable_PitchTrimUp::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Pitch Trim Dn
  -------------------------------------------------------------------------------*/
  Observable_PitchTrimDn Param_PitchTrimDn;

  void Observable_PitchTrimDn::initialize()
  {
    basicInit();
  }

  void Observable_PitchTrimDn::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.PitchTrimDn == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_PitchTrimDn::onTimeout()
  {
  }

  bool Observable_PitchTrimDn::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Roll Trim Up
  -------------------------------------------------------------------------------*/
  Observable_RollTrimUp Param_RollTrimUp;

  void Observable_RollTrimUp::initialize()
  {
    basicInit();
  }

  void Observable_RollTrimUp::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.RollTrimUp == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_RollTrimUp::onTimeout()
  {
  }

  bool Observable_RollTrimUp::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Roll Trim Dn
  -------------------------------------------------------------------------------*/
  Observable_RollTrimDn Param_RollTrimDn;

  void Observable_RollTrimDn::initialize()
  {
    basicInit();
  }

  void Observable_RollTrimDn::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.RollTrimDn == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_RollTrimDn::onTimeout()
  {
  }

  bool Observable_RollTrimDn::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Yaw Trim Up
  -------------------------------------------------------------------------------*/
  Observable_YawTrimUp Param_YawTrimUp;

  void Observable_YawTrimUp::initialize()
  {
    basicInit();
  }

  void Observable_YawTrimUp::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.YawTrimUp == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_YawTrimUp::onTimeout()
  {
  }

  bool Observable_YawTrimUp::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Yaw Trim Dn
  -------------------------------------------------------------------------------*/
  Observable_YawTrimDn Param_YawTrimDn;

  void Observable_YawTrimDn::initialize()
  {
    basicInit();
  }

  void Observable_YawTrimDn::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.YawTrimDn == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_YawTrimDn::onTimeout()
  {
  }

  bool Observable_YawTrimDn::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Throttle Trim Up
  -------------------------------------------------------------------------------*/
  Observable_ThrottleTrimUp Param_ThrottleTrimUp;

  void Observable_ThrottleTrimUp::initialize()
  {
    basicInit();
  }

  void Observable_ThrottleTrimUp::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.ThrottleTrimUp == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_ThrottleTrimUp::onTimeout()
  {
  }

  bool Observable_ThrottleTrimUp::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Throttle Trim Dn
  -------------------------------------------------------------------------------*/
  Observable_ThrottleTrimDn Param_ThrottleTrimDn;

  void Observable_ThrottleTrimDn::initialize()
  {
    basicInit();
  }

  void Observable_ThrottleTrimDn::update()
  {
    static bool last_state = false;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    If new state different than last, update and notify
    -------------------------------------------------*/
    bool new_state = ( io_state.ThrottleTrimDn == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_ThrottleTrimDn::onTimeout()
  {
  }

  bool Observable_ThrottleTrimDn::validate( const void *const data, const size_t size ) const
  {
    return false;
  }
}    // namespace DC::REG
