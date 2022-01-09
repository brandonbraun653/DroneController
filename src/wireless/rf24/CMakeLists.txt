include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_rf24
  SOURCES
    rf_driver.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    ripple_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
