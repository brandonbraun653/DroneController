/********************************************************************************
 *  File Name:
 *    usb_cdc_cb.cpp
 *
 *  Description:
 *    TinyUSB CDC application callback implementations
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>

/* TinyUSB Includes */
#include <class/cdc/cdc_device.h>


/**
 * @brief Invoked when received new data
 *
 */
extern "C" void tud_cdc_rx_cb( uint8_t itf )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when received `wanted_char`
 *
 */
extern "C" void tud_cdc_rx_wanted_cb( uint8_t itf, char wanted_char )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when space becomes available in TX buffer
 *
 */
extern "C" void tud_cdc_tx_complete_cb( uint8_t itf )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when line state DTR & RTS are changed via SET_CONTROL_LINE_STATE
 *
 */
extern "C" void tud_cdc_line_state_cb( uint8_t itf, bool dtr, bool rts )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when line coding is change via SET_LINE_CODING
 *
 */
extern "C" void tud_cdc_line_coding_cb( uint8_t itf, cdc_line_coding_t const *p_line_coding )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when received send break
 *
 */
extern "C" void tud_cdc_send_break_cb( uint8_t itf, uint16_t duration_ms )
{
  Chimera::insert_debug_breakpoint();
}
