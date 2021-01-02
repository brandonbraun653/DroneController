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
set(LIB lib_utility)
add_library(${LIB} STATIC
  logger.cpp
  serial_output.cpp
)
target_link_libraries(${LIB} PRIVATE ${LINK_LIBS})
export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/${LIB}.cmake")
