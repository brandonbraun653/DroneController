include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

gen_static_lib_variants(
  TARGET
  lib_tasks
  SOURCES
    tsk_background.cpp
    tsk_common.cpp
    tsk_file_system.cpp
    tsk_graphics.cpp
    tsk_heartbeat.cpp
    tsk_hmi.cpp
    tsk_radio.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
    thor_intf_inc
    Boost::boost
    lfs_intf_inc
    ripple_inc

    project_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/DroneController"
)

