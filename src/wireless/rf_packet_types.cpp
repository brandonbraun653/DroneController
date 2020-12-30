/********************************************************************************
 *  File Name:
 *    rf_packet_types.cpp
 *
 *  Description:
 *    Packet type memory storage and retrieval
 *
 *  2020 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/


namespace DC::RF
{
  // Use macros to generate register packets. This is how you'll be able to automate
  // all the struct member types.

  /*
  struct <pkt_name>_type
  {
    uint8_t flags;
    uint8_t endpoint;
    uint8_t reserved[2];
    uint16_t rx_timeout;
    uint16_t tx_timeout;
    void * cb_tx;
    void * cb_rx;
    void * cb_timeout;
    <pkt_data_struct> data[2];
  } <pkt_name>_data;
  */

  /*-------------------------------------------------------------------------------
  Useful Packet Properties

  - RX timeouts: If the data hasn't been received in X time, it's considered an error
  - TX timeouts: If the data hasn't been transmitted in X time, it's considered an error
  - Callbacks:
    - On timeout
    - On transmit
    - On receive
  - Flags: (Bit field)
    - Ready for transmission
    - Data is valid
    - Packet is periodic or asynchronous
    - Override old data for TX/RX if not handled, or throw out new data?
  - Cache for RX data as well as TX data
  -------------------------------------------------------------------------------*/


}  // namespace DC::RF
