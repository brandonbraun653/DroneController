include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_usb
  SOURCES
    usb_cdc_cb.cpp
    usb_descriptor_cb.cpp
    usb_isr_handler.cpp
    usb_system.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    tiny_usb_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)

