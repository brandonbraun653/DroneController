include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_io
  SOURCES
    gpio_driver.cpp
    pin_mapping.cpp
    sr_driver.cpp
  PRV_LIBRARIES

    chimera_intf_inc
    aurora_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
