/********************************************************************************
 *  File Name:
 *    rf_system_types.hpp
 *
 *  Description:
 *    Data resources associated with the RF driver
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_WIRELESS_SYSTEM_TYPES_HPP
#define DC_WIRELESS_SYSTEM_TYPES_HPP

/* STL Includes */
#include <cstdint>
#include <cstddef>

/* Ripple Includes */
#include <Ripple/session>
#include <Ripple/physical>

namespace DC::RF
{
  /*-------------------------------------------------------------------------------
  Enumerations
  -------------------------------------------------------------------------------*/
  /**
   *  Possible events that can occur in the radio link
   */
  enum class RadioEvent : uint8_t
  {
    UNHANDLED_EVENT,        /**< An event occurred that wasn't handled in some way */
    CONNECTION_ESTABLISHED, /**< A radio link was established */
    CONNECTION_DROPPED,     /**< The radio link failed */
    PACKET_RECEIVED,        /**< A new packet arrived */
    PACKET_TRANSMITTED,     /**< A packet was transmitted successfully */

    NUM_OPTIONS,
    UNKNOWN
  };

  /**
   *  Describes the available network services and the
   *  endpoint identifiers assigned to each one.
   */
  enum class ServiceEndpoint : uint8_t
  {
    /*-------------------------------------------------
    System Level
    -------------------------------------------------*/
    SYS_CTRL,   /**< Root endpoint to transfer high level control messages */
    SYS_HEALTH, /**< System health monitoring data */

    /*-------------------------------------------------
    Control Systems
    -------------------------------------------------*/
    ATT_CTRL, /**< Endpoint for user attitude command inputs */
    ATT_DATA, /**< Endpoint for receiving realtime attitude data */

    /*-------------------------------------------------
    Configuration
    -------------------------------------------------*/
    CFG_ALGO_PARAM,  /**< Endpoint for algorithm tuning and parameters */
    CFG_PILOT_PARAM, /**< Endpoint for pilot settings */
    CFG_SYS_PARAM,   /**< Endpoint for system configuration settings */
  };

  /*-------------------------------------------------------------------------------
  Structures
  -------------------------------------------------------------------------------*/

}    // namespace DC::RF

#endif /* !DC_WIRELESS_SYSTEM_TYPES_HPP */
