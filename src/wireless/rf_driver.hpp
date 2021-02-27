/********************************************************************************
 *  File Name:
 *    rf_driver.hpp
 *
 *  Description:
 *    Core RF driver interface that is responsible for abstracting away the
 *    complexities of a radio link and focuses on allowing the main application
 *    to easily pass data through the system.
 *
 *    The driver is written with thread safety in mind so that any thread can
 *    transmit or recieve data without fear.
 *
 *  2020-2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef DC_WIRELESS_DRIVER_HPP
#define DC_WIRELESS_DRIVER_HPP

/* Ripple Includes */
#include <Ripple/netif/nrf24l01>

/* Project Includes */
#include <src/wireless/rf_system_types.hpp>
#include <src/wireless/rf_packet_types.hpp>


namespace DC::RF
{
  /*-------------------------------------------------------------------------------
  Public Functions
  -------------------------------------------------------------------------------*/
  /**
   *  Generates the project's radio configuration structure
   *
   *  @param[in]  config    Object to be configured
   *  @return void
   */
  void genRadioCfg( Ripple::NetIf::NRF24::Physical::Handle &config );

  /**
   *  Attempts to make a connection to a device with the given address.
   *
   *  @note The other device must be on the same RF channel.
   *
   *  @param[in]  device    Address of the device to connect to
   *  @return bool
   */
  bool connect( const Ripple::IPAddress device );

  /**
   *  Severs the connection with the remote device
   *  @return void
   */
  void disconnect();

  /**
   *  Enqueues a packet for transmission over the network
   *
   *  @param[in]  id        Which packet to transmit
   *  @param[in]  data      Data to transmit
   *  @param[in]  length    Size of the data
   *  @return bool          Whether or not the packet was successfully enqueued
   */
  bool tx_packet( const PacketId id, const void *const data, const size_t length );

  /**
   *  Gets the last received data for a packet type
   *
   *  @param[in]  id        Which packet to read data for
   *  @param[in]  data      Output container for the data
   *  @param[in]  length    Size of the data to copy
   *  @return bool          Validity of the returned data
   */
  bool rx_packet( const PacketId id, void *const data, const size_t length );

  /**
   *  Registers a handler for an event on a packet
   *
   *  @param[in]  id        Which packet to register the handler against
   *  @param[in]  event     The event the handler should respond to
   *  @param[in]  handler   The handler function
   *  @return void
   */
  void register_handler( const PacketId id, const PacketEvent event, PacketHandler handler );

}  // namespace DC::RF

#endif  /* !DC_WIRELESS_DRIVER_HPP */
