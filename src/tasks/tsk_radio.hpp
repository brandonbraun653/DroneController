/********************************************************************************
 *  File Name:
 *    tsk_radio.hpp
 *
 *  Description:
 *    Radio communications task interface
 *
 *  2020-2022 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_TASK_RADIO_HPP
#define DC_TASK_RADIO_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Chimera/thread>
#include <Ripple/netstack>
#include <src/tasks/tsk_common.hpp>


namespace DC::Tasks::RADIO
{
  /*-------------------------------------------------------------------------------
  Constants
  -------------------------------------------------------------------------------*/
  static constexpr size_t STACK                           = STACK_BYTES( 4096 );
  static constexpr std::string_view NAME                  = "radio";
  static constexpr Chimera::Thread::TaskPriority PRIORITY = 3;

  /*---------------------------------------------------------------------------
  Public Data
  ---------------------------------------------------------------------------*/
  extern Ripple::Socket_rPtr txSocket;  /**< Transmit socket for NRF24 radio */
  extern Ripple::Socket_rPtr rxSocket;  /**< Receive socket for NRF24 radio */

  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  void RadioThread( void *arg );

}    // namespace DC::Tasks::RADIO

#endif /* !DC_TASK_RADIO_HPP */
