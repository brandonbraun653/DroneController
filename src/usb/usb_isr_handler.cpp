/********************************************************************************
 *  File Name:
 *    usb_isr_handler.cpp
 *
 *  Description:
 *    ISR handlers for the STM32F4 series USB stack
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>

/* TinyUSB Includes */
#include <device/usbd.h>


extern "C" void OTG_FS_WKUP_IRQHandler()
{
  tud_int_handler(0);
}


extern "C" void OTG_FS_IRQHandler()
{
  tud_int_handler(0);
}


extern "C" void OTG_HS_EP1_OUT_IRQHandler()
{
  Chimera::insert_debug_breakpoint();
}


extern "C" void OTG_HS_EP1_IN_IRQHandler()
{
  Chimera::insert_debug_breakpoint();
}


extern "C" void OTG_HS_WKUP_IRQHandler()
{
  Chimera::insert_debug_breakpoint();
}


extern "C" void OTG_HS_IRQHandler()
{
  Chimera::insert_debug_breakpoint();
}
