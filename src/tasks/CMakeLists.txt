# ====================================================
# Common
# ====================================================
set(LINK_LIBS
  Boost::boost
  chimera_inc       # Chimera public headers
  aurora_inc        # Aurora public headers
  ripple_inc
  ugfx_inc
  ulog_inc
  yaffs_inc
  project_inc
  prj_device_target
)

# ====================================================
# Driver Library
# ====================================================
set(LIB lib_tasks)
add_library(${LIB} STATIC
  tsk_common.cpp
  tsk_graphics.cpp
  tsk_heartbeat.cpp
  tsk_monitor.cpp
  tsk_radio.cpp
  tsk_file_system.cpp
)

target_link_libraries(${LIB} PRIVATE ${LINK_LIBS})
export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/${LIB}.cmake")
