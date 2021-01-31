/********************************************************************************
 *  File Name:
 *    reg_data_ahrs_x_accel.cpp
 *
 *  Description:
 *    Parameter data implementation
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
#include <src/registry/reg_data.hpp>

namespace DC::REG
{
  /*-------------------------------------------------------------------------------
  Parameter Implementation
  -------------------------------------------------------------------------------*/
  Observable_ButtonUp Param_ButtonUp;

  void Observable_ButtonUp::initialize()
  {
    basicInit();
  }

  void Observable_ButtonUp::update()
  {
    uint32_t data = 0;
    getDatabase()->write( this->key(), &data );

    notify_observers( data );
  }

  void Observable_ButtonUp::onTimeout()
  {
  }

  bool Observable_ButtonUp::validate( const void *const data, const size_t size ) const
  {
    return false;
  }


  /*-------------------------------------------------------------------------------
  Parameter Implementation
  -------------------------------------------------------------------------------*/
  Observable_ButtonDown Param_ButtonDown;
  void Observable_ButtonDown::initialize()
  {
    basicInit();
  }

  void Observable_ButtonDown::update()
  {
    uint32_t data = 0;
    getDatabase()->write( this->key(), &data );

    notify_observers( data );
  }

  void Observable_ButtonDown::onTimeout()
  {
  }

  bool Observable_ButtonDown::validate( const void *const data, const size_t size ) const
  {
    return false;
  }

}    // namespace DC::REG
