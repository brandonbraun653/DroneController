/******************************************************************************
 *  File Name:
 *    net_data_package.cpp
 *
 *  Description:
 *    NET layer data propagation methods
 *
 *  2022 | Brandon Braun | brandonbraun653@gmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include "controller.pb.h"
#include <Aurora/logging>
#include <Aurora/utility>
#include <Ripple/user>
#include <src/config/ripple/ripple_packet_contract_prj.hpp>
#include <src/controller/ctrl_intf.hpp>
#include <src/network/net_data_package.hpp>
#include <src/tasks/tsk_radio.hpp>

namespace DC::NET
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void initDataPackage()
  {

  }


  void procStickInputs()
  {
    using namespace DC::HMI::JoyStick;
    using namespace DC::Tasks::RADIO;

    /*-------------------------------------------------------------------------
    Local Constants
    -------------------------------------------------------------------------*/
    /**
     * When all data fields have been filled properly for the stick inputs, the
     * tracker variable below will equal the mask value exactly. This is to help
     * ensure that partial data isn't sent to the drone.
     */
    static constexpr uint8_t fillMask = 0xF;

    /*-------------------------------------------------------------------------
    Fill up the packet data being sent
    -------------------------------------------------------------------------*/
    StickInputs inputs;
    uint8_t dataFilled = 0;

    for( size_t idx = 0; idx < EnumValue( Axis::NUM_OPTIONS ); idx++ )
    {
      auto axis     = static_cast<Axis>( idx );
      auto joystick = DC::CTRL::getJoyStick( axis );
      if( !joystick )
      {
        continue;
      }

      switch( axis )
      {
        case Axis::PITCH:
          inputs.pitch = joystick->value();
          dataFilled |= ( 1u << EnumValue( axis ) );
          break;

        case Axis::ROLL:
          inputs.roll = joystick->value();
          dataFilled |= ( 1u << EnumValue( axis ) );
          break;

        case Axis::YAW:
          inputs.yaw = joystick->value();
          dataFilled |= ( 1u << EnumValue( axis ) );
          break;

        case Axis::THROTTLE:
          inputs.throttle = joystick->value();
          dataFilled |= ( 1u << EnumValue( axis ) );
          break;

        default:
          break;
      };
    }

    /*-------------------------------------------------------------------------
    Send the data off
    -------------------------------------------------------------------------*/
    if( txSocket && ( dataFilled == fillMask ) )
    {
      auto success = Ripple::transmit( PKT_CMD_STICK_INPUTS, *txSocket, &inputs, sizeof( inputs ) );
      LOG_WARN_IF( !success, "Failed to transmit PKT_CMD_STICK_INPUTS packet\r\n" );
    }
  }


  void procStateData()
  {
    // Add generic system info here. Systick, etc.
  }

}  // namespace DC::NET
