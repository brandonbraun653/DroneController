include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

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
function(build_library_wireless variant)
  set(LIB lib_wireless${variant})
  add_library(${LIB} STATIC
    rf_driver_internal.cpp
    rf_driver.cpp
    rf_packet_types.cpp
  )
  target_link_libraries(${LIB} PRIVATE ${LINK_LIBS} prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/${LIB}.cmake")
endfunction()

add_target_variants(build_library_wireless)
