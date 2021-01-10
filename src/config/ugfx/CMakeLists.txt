# ====================================================
# Common
# ====================================================
set(LINK_LIBS
  chimera_intf_inc
  ugfx_inc
  project_inc
  prj_device_target
)

# ====================================================
# Driver Library
# ====================================================
set(LIB ugfx_prj_config)
add_library(${LIB} STATIC
  board_ST7735.cpp
)

target_link_libraries(${LIB} PRIVATE ${LINK_LIBS})
export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/DroneController/config/${LIB}.cmake")
