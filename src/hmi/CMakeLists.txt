include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_human_interface
  SOURCES
    hmi_discrete.cpp
    hmi_discrete_msg_pump.cpp
    hmi_encoder.cpp
    hmi_encoder_msg_pump.cpp
    hmi_sticks.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController/hmi"
)
