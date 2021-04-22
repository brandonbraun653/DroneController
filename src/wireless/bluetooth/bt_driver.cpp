/********************************************************************************
 *  File Name:
 *    bt_driver.cpp
 *
 *  Description:
 *    Bluetooth module driver
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Project Includes */
#include <src/io/gpio_driver.hpp>
#include <src/wireless/bluetooth/bt_driver.hpp>

namespace DC::RF::BT
{
  /*-------------------------------------------------------------------------------
  Static Data
  -------------------------------------------------------------------------------*/
  static bool s_is_enabled = false;

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void initDriver()
  {
    /*-------------------------------------------------
    Initialize local data
    -------------------------------------------------*/
    s_is_enabled = false;
  }


  void setPower( const PowerState state )
  {
    if( state == PowerState::ENABLED )
    {
      GPIO::setShiftRegister( GPIO::SR::OutputPin::BT_PWR_EN );
      s_is_enabled = true;
    }
    else
    {
      GPIO::clearShiftRegister( GPIO::SR::OutputPin::BT_PWR_EN );
      s_is_enabled = false;
    }
  }

}    // namespace DC::RF::BT
