include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_controller
  SOURCES
    ctrl_intf.cpp
    ctrl_joystick.cpp
    ctrl_observers.cpp
  PRV_LIBRARIES
    chimera_intf_inc
    aurora_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
