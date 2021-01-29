include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
    lib_config
  SOURCES
    board_map.cpp
  PRV_LIBRARIES
    Boost::boost
    chimera_intf_inc
    aurora_intf_inc
    ulog_inc
    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)
