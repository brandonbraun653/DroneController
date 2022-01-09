/******************************************************************************
 *  File Name:
 *    ctrl_intf.hpp
 *
 *  Description:
 *    Main interface to the controller module. This represents the user facing
 *    software for hardware components used to control the remote drone. It
 *    includes the buttons, joysticks, and switches on the controller. While
 *    the HMI module handles the hardware level interactions, this represents
 *    higher level concerns to serve business logic.
 *
 *  2022 | Brandon Braun | brandonbraun653@gmail.com
 *****************************************************************************/

#pragma once
#ifndef DC_CONTROLLER_INTERFACE_HPP
#define DC_CONTROLLER_INTERFACE_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/thread>
#include <src/controller/ctrl_types.hpp>
#include <src/hmi/hmi_sticks.hpp>

namespace DC::CTRL
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  class JoyStick;

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  /**
   * @brief Initializes the controller module
   */
  void initController();

  /**
   * @brief Retrieves the JoyStick object associated with the given axis.
   *
   * @param type  Which joystick to retrieve
   * @return JoyStick*
   */
  JoyStick* getJoyStick( const DC::HMI::JoyStick::Axis type );


  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  class JoyStick : public Chimera::Thread::Lockable<JoyStick>
  {
  public:
    JoyStick( const DC::HMI::JoyStick::Axis type );
    ~JoyStick();

    /**
     * @brief Returns the axis associated with the object
     *
     * @return DC::HMI::JoyStick::Axis
     */
    DC::HMI::JoyStick::Axis axis() const;

    /**
     * @brief Retrieves the current value of the joystick on the range (0-100)
     *
     * @return float
     */
    float value();

    /**
     * @brief Sets the upper limit for a joystick ranged to 100%
     *
     * @param limit   Value that indicates joystick is at max travel
     */
    void setUpperLimit( const float limit );

    /**
     * @brief Set the lower limit for a joystick ranged to 0%
     *
     * @param limit   Value that indicates joystick is at min travel
     */
    void setLowerLimit( const float limit );

  private:
    friend Chimera::Thread::Lockable<JoyStick>;

    float mUpperLimit;
    float mLowerLimit;
    DC::HMI::JoyStick::Axis mAxis;

    /**
     * @brief Maps value in one range into another
     *
     * @param val       Value to transform
     * @param in_min    Input range minimum value
     * @param in_max    Input range maximum value
     * @param out_min   Output range minimum value
     * @param out_max   Output range maximum value
     * @return float    Mapped value
     */
    float map( const float val, const float in_min, const float in_max, const float out_min, const float out_max ) const;
  };

}  // namespace DC::CTRL

#endif  /* !DC_CONTROLLER_INTERFACE_HPP */
