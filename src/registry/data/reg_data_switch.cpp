/********************************************************************************
 *  File Name:
 *    reg_data_switch.cpp
 *
 *  Description:
 *    Observable data for user switches
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/gpio>

/* Project Includes */
#include <src/registry/reg_data.hpp>
#include <src/hmi/hmi_discrete.hpp>
#include <src/hmi/hmi_discrete_msg_pump.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_switch_a_validity;
  static bool s_switch_b_validity;
  static bool s_switch_c_validity;
  static bool s_switch_d_validity;

  /*-------------------------------------------------------------------------------
  Switch A Toggle
  -------------------------------------------------------------------------------*/
  Observable_SwitchAToggle Param_SwitchAToggle;

  void Observable_SwitchAToggle::initialize()
  {
    basicInit();
    s_switch_a_validity = false;
  }

  void Observable_SwitchAToggle::update()
  {
    static Chimera::GPIO::State last_state = Chimera::GPIO::State::LOW;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    Cache the state and notify listeners
    -------------------------------------------------*/
    s_switch_a_validity = true;
    Chimera::GPIO::State state = io_state.SwitchAToggle;

    if ( state != last_state )
    {
      last_state = state;
      getDatabase()->write( this->key(), &state );
      notify_observers( state );
    }
  }

  void Observable_SwitchAToggle::onTimeout()
  {
    s_switch_a_validity = false;
  }

  bool Observable_SwitchAToggle::validate( const void *const data, const size_t size ) const
  {
    return s_switch_a_validity;
  }

  /*-------------------------------------------------------------------------------
  Switch B Toggle
  -------------------------------------------------------------------------------*/
  Observable_SwitchBToggle Param_SwitchBToggle;

  void Observable_SwitchBToggle::initialize()
  {
    basicInit();
    s_switch_b_validity = false;
  }

  void Observable_SwitchBToggle::update()
  {
    static Chimera::GPIO::State last_state = Chimera::GPIO::State::LOW;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    Cache the state and notify listeners
    -------------------------------------------------*/
    s_switch_a_validity = true;
    Chimera::GPIO::State state = io_state.SwitchBToggle;

    if ( state != last_state )
    {
      last_state = state;
      getDatabase()->write( this->key(), &state );
      notify_observers( state );
    }
  }

  void Observable_SwitchBToggle::onTimeout()
  {
    s_switch_b_validity = false;
  }

  bool Observable_SwitchBToggle::validate( const void *const data, const size_t size ) const
  {
    return s_switch_b_validity;
  }

  /*-------------------------------------------------------------------------------
  Switch C Toggle
  -------------------------------------------------------------------------------*/
  Observable_SwitchCToggle Param_SwitchCToggle;

  void Observable_SwitchCToggle::initialize()
  {
    basicInit();
    s_switch_c_validity = false;
  }

  void Observable_SwitchCToggle::update()
  {
    static Chimera::GPIO::State last_state = Chimera::GPIO::State::LOW;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    Cache the state and notify listeners
    -------------------------------------------------*/
    s_switch_a_validity = true;
    Chimera::GPIO::State state = io_state.SwitchCToggle;

    if ( state != last_state )
    {
      last_state = state;
      getDatabase()->write( this->key(), &state );
      notify_observers( state );
    }
  }

  void Observable_SwitchCToggle::onTimeout()
  {
    s_switch_c_validity = false;
  }

  bool Observable_SwitchCToggle::validate( const void *const data, const size_t size ) const
  {
    return s_switch_c_validity;
  }

  /*-------------------------------------------------------------------------------
  Switch D Toggle
  -------------------------------------------------------------------------------*/
  Observable_SwitchDToggle Param_SwitchDToggle;

  void Observable_SwitchDToggle::initialize()
  {
    basicInit();
    s_switch_d_validity = false;
  }

  void Observable_SwitchDToggle::update()
  {
    static Chimera::GPIO::State last_state = Chimera::GPIO::State::LOW;

    /*-------------------------------------------------
    Read the latest state information
    -------------------------------------------------*/
    HMI::Discrete::ReportedState io_state;
    HMI::Discrete::getCurrentState( io_state );

    /*-------------------------------------------------
    Cache the state and notify listeners
    -------------------------------------------------*/
    s_switch_a_validity = true;
    Chimera::GPIO::State state = io_state.SwitchDToggle;

    if ( state != last_state )
    {
      last_state = state;
      getDatabase()->write( this->key(), &state );
      notify_observers( state );
    }
  }

  void Observable_SwitchDToggle::onTimeout()
  {
    s_switch_d_validity = false;
  }

  bool Observable_SwitchDToggle::validate( const void *const data, const size_t size ) const
  {
    return s_switch_d_validity;
  }

}  // namespace DC::REG
