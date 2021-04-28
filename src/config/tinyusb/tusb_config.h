/********************************************************************************
 *  File Name:
 *    tusb_config.h
 *
 *  Description:
 *    Tiny USB configuration
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

#pragma once
#ifndef TINY_USB_USER_CONFIG_HPP
#define TINY_USB_USER_CONFIG_HPP

#ifdef __cplusplus
extern "C"
{
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUSB_MCU ( OPT_MCU_STM32F4 )

#define BOARD_DEVICE_RHPORT_NUM   ( 0 )
#define BOARD_DEVICE_RHPORT_SPEED ( OPT_MODE_HIGH_SPEED )
#define CFG_TUSB_RHPORT0_MODE     ( OPT_MODE_DEVICE | BOARD_DEVICE_RHPORT_SPEED )
#define CFG_TUSB_OS               ( OPT_OS_NONE )
#define CFG_TUSB_DEBUG            ( 0 )

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN __attribute__( ( aligned( 4 ) ) )

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUD_ENDPOINT0_SIZE 64

//------------- CLASS -------------//
#define CFG_TUD_CDC 1
#define CFG_TUD_MSC 0
#define CFG_TUD_HID 0
#define CFG_TUD_MIDI 0
#define CFG_TUD_VENDOR 0

// CDC FIFO size of TX and RX
#define CFG_TUD_CDC_RX_BUFSIZE ( TUD_OPT_HIGH_SPEED ? 512 : 64 )
#define CFG_TUD_CDC_TX_BUFSIZE ( TUD_OPT_HIGH_SPEED ? 512 : 64 )

// CDC Endpoint transfer buffer size, more is faster
#define CFG_TUD_CDC_EP_BUFSIZE ( TUD_OPT_HIGH_SPEED ? 512 : 64 )

// MSC Buffer size of Device Mass storage
#define CFG_TUD_MSC_EP_BUFSIZE 512

#ifdef __cplusplus
}
#endif

#endif /* !TINY_USB_USER_CONFIG_HPP */
