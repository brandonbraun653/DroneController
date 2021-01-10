include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# ====================================================
# Common
# ====================================================
set(LINK_LIBS
  Boost::boost
  chimera_inc       # Chimera public headers
  aurora_inc        # Aurora public headers
  lfs_inc
  ripple_inc
  ugfx_inc
  ulog_inc
  project_inc
  prj_device_target
)

# ====================================================
# Driver Library
# ====================================================
function(build_library_tasks variant)
  set(LIB lib_tasks${variant})
  add_library(${LIB} STATIC
    tsk_common.cpp
    tsk_graphics.cpp
    tsk_heartbeat.cpp
    tsk_monitor.cpp
    tsk_radio.cpp
    tsk_file_system.cpp
  )
  target_link_libraries(${LIB} PRIVATE ${LINK_LIBS} prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/${LIB}.cmake")
endfunction()

add_target_variants(build_library_tasks)
