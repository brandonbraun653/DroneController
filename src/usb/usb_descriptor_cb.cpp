/********************************************************************************
 *  File Name:
 *    usb_descriptor_cb.cpp
 *
 *  Description:
 *    Callback implementations for TinyUSB device descriptors
 *
 *  2021 | Brandon Braun | brandonbraun653@gmail.com
 *******************************************************************************/

/* Chimera Includes */
#include <Chimera/common>

/* TinyUSB Includes */
#include <device/usbd.h>

/**
 * @brief Invoked when received GET DEVICE DESCRIPTOR request
 *
 * @return uint8_t const*
 */
extern "C" uint8_t const *tud_descriptor_device_cb( void )
{
  Chimera::insert_debug_breakpoint();
  return nullptr;
}


/**
 * @brief Invoked when received GET BOS DESCRIPTOR request
 *
 * @return  const*
 */
extern "C" uint8_t const *tud_descriptor_bos_cb( void )
{
  Chimera::insert_debug_breakpoint();
  return nullptr;
}


/**
 * @brief Invoked when received GET CONFIGURATION DESCRIPTOR request
 * Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
 *
 * @param index
 * @return uint8_t const*
 */
extern "C" uint8_t const *tud_descriptor_configuration_cb( uint8_t index )
{
  Chimera::insert_debug_breakpoint();
  return nullptr;
}


/**
 * @brief Invoked when received GET STRING DESCRIPTOR request
 * Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
 *
 * @param index
 * @param langid
 * @return uint16_t const*
 */
extern "C" uint16_t const *tud_descriptor_string_cb( uint8_t index, uint16_t langid )
{
  Chimera::insert_debug_breakpoint();
  return nullptr;
}


/**
 * @brief Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
 * Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
 *
 * @return uint8_t const*
 */
extern "C" uint8_t const *tud_descriptor_device_qualifier_cb( void )
{
  Chimera::insert_debug_breakpoint();
  return nullptr;
}


/**
 * @brief Invoked when device is mounted (configured)
 */
extern "C" void tud_mount_cb( void )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when device is unmounted
 */
extern "C" void tud_umount_cb( void )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when usb bus is suspended
 * Within 7ms, device must draw an average of current less than 2.5 mA from bus
 *
 * @param remote_wakeup_en
 */
extern "C" void tud_suspend_cb( bool remote_wakeup_en )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when usb bus is resumed
 */
extern "C" void tud_resume_cb( void )
{
  Chimera::insert_debug_breakpoint();
}


/**
 * @brief Invoked when received control request with VENDOR TYPE
 *
 * @param rhport
 * @param stage
 * @param request
 * @return bool
 */
extern "C" bool tud_vendor_control_xfer_cb( uint8_t rhport, uint8_t stage, tusb_control_request_t const *request )
{
  Chimera::insert_debug_breakpoint();
  return false;
}
