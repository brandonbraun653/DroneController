include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_registry
  SOURCES
    reg_driver.cpp
    data/reg_data_button_up.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    lfs_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
