include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_bluetooth
  SOURCES
    bt_driver.cpp
    rn4871/rn_action_cmds.cpp
    rn4871/rn_device.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
