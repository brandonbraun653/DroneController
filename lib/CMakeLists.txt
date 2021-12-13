include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# Grab all the source files
set(tusb_src_dir ./tinyusb/src)


gen_intf_lib(
  TARGET
    tiny_usb_intf_inc
  INTF_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src
    ${PROJECT_ROOT}/src/config/tinyusb
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/TinyUsb"
)


gen_static_lib_variants(
  TARGET
    tiny_usb_port_st
  SOURCES
    ${tusb_src_dir}/portable/st/stm32_fsdev/dcd_stm32_fsdev.c
    ${tusb_src_dir}/portable/st/synopsys/dcd_synopsys.c
  PRV_LIBRARIES
    tiny_usb_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/TinyUsb"
)


gen_static_lib_variants(
  TARGET
    tiny_usb_core
  SOURCES
    ${tusb_src_dir}/tusb.c
    ${tusb_src_dir}/class/audio/audio_device.c
    ${tusb_src_dir}/class/bth/bth_device.c
    ${tusb_src_dir}/class/cdc/cdc_device.c
    ${tusb_src_dir}/class/cdc/cdc_host.c
    ${tusb_src_dir}/class/cdc/cdc_rndis_host.c
    ${tusb_src_dir}/class/dfu/dfu_rt_device.c
    ${tusb_src_dir}/class/hid/hid_device.c
    ${tusb_src_dir}/class/hid/hid_host.c
    ${tusb_src_dir}/class/midi/midi_device.c
    ${tusb_src_dir}/class/msc/msc_device.c
    ${tusb_src_dir}/class/msc/msc_host.c
    ${tusb_src_dir}/class/usbtmc/usbtmc_device.c
    ${tusb_src_dir}/class/vendor/vendor_device.c
    ${tusb_src_dir}/class/vendor/vendor_host.c
    ${tusb_src_dir}/common/tusb_fifo.c
    ${tusb_src_dir}/device/usbd_control.c
    ${tusb_src_dir}/device/usbd.c
    ${tusb_src_dir}/host/hub.c
    ${tusb_src_dir}/host/usbh_control.c
    ${tusb_src_dir}/host/usbh.c
  PRV_LIBRARIES
    tiny_usb_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/TinyUsb"
)
