# ====================================================
# Common
# ====================================================
set(LINK_LIBS
  chimera_inc
  project_inc
  prj_device_target
  ripple_inc
)

# ====================================================
# Driver Library
# ====================================================
set(LIB lib_wireless)
add_library(${LIB} STATIC
  rf_driver_internal.cpp
  rf_driver.cpp
  rf_packet_types.cpp
)

target_link_libraries(${LIB} PRIVATE ${LINK_LIBS})
export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/${LIB}.cmake")
