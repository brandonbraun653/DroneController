include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_human_interface
  SOURCES
    hmi_button.cpp
    hmi_encoder.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc

    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController/hmi"
)
