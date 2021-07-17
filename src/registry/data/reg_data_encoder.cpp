/********************************************************************************
 *  File Name:
 *    reg_data_encoder.cpp
 *
 *  Description:
 *    Parameter data for the encoders
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
#include <src/registry/reg_data.hpp>
#include <src/hmi/hmi_discrete_msg_pump.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Rotary Encoder 0
  -------------------------------------------------------------------------------*/
  Observable_Encoder0Btn Param_Encoder0Btn;

  void Observable_Encoder0Btn::initialize()
  {
    basicInit();
  }

  void Observable_Encoder0Btn::update()
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
    bool new_state = ( io_state.Encoder0Center == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_Encoder0Btn::onTimeout()
  {
  }

  bool Observable_Encoder0Btn::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Rotary Encoder 1
  -------------------------------------------------------------------------------*/
  Observable_Encoder1Btn Param_Encoder1Btn;

  void Observable_Encoder1Btn::initialize()
  {
    basicInit();
  }

  void Observable_Encoder1Btn::update()
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
    bool new_state = ( io_state.Encoder1Center == Chimera::GPIO::State::LOW );
    if ( new_state != last_state )
    {
      last_state = new_state;
      getDatabase()->write( this->key(), &new_state );
      notify_observers( new_state );
    }
  }

  void Observable_Encoder1Btn::onTimeout()
  {
  }

  bool Observable_Encoder1Btn::validate( const void *const data, const size_t size ) const
  {
    return false;
  }

}  // namespace DC::REG
