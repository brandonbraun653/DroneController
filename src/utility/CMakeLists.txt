include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# ====================================================
# Common
# ====================================================
set(LINK_LIBS
  Boost::boost
  chimera_inc       # Chimera public headers
  aurora_inc        # Aurora public headers
  ulog_inc
  project_inc
  prj_device_target
)

# ====================================================
# Driver Library
# ====================================================
function(build_library_utility variant)
  set(LIB lib_utility${variant})
  add_library(${LIB} STATIC
    logger.cpp
    serial_output.cpp
  )
  target_link_libraries(${LIB} PRIVATE ${LINK_LIBS} prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/${LIB}.cmake")
endfunction()

add_target_variants(build_library_utility)
