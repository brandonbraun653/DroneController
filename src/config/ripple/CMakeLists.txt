include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_config_ripple
  SOURCES
    ripple_packet_defs.cpp
  PRV_LIBRARIES
    chimera_intf_inc
    aurora_intf_inc
    nanopb_intf_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
