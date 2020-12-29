add_subdirectory(config/ugfx)
add_subdirectory(tasks)

# -----------------------------------------------------------------------------
# Test Suite: HLD ADC
#
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DDEVICE_TARGET=stm32l432kb -DCMAKE_BUILD_TYPE=Debug --configure ../
# -----------------------------------------------------------------------------
add_executable(DroneController
  startup.cpp
)

target_include_directories(DroneController PRIVATE "." )

target_link_libraries(DroneController PRIVATE
  # Public Includes
  aurora_inc
  Boost::boost
  chimera_inc
  freertos_inc
  thor_inc
  type_safe_inc

  # Project Libraries
  lib_tasks

  # Graphics Libraries
  ugfx_inc
  ugfx_lib
  ugfx_st7735_lib
  ugfx_prj_config

  # Networking Libraries
  ripple_inc
  ripple_core

  # Hardware Libraries
  aurora_core_rel
  aurora_logging_rel
  chimera_core_dbg
  freertos_cfg
  freertos_core_rel
  freertos_heap
  freertos_port
  thor_cfg_freertos_rel
  thor_cmn_cm4_dbg
  thor_hld_core_dbg
  thor_lld_intf_dbg
  thor_lld_stm32l4_dbg

  # Target Properties
  prj_device_target
  prj_build_target
)

target_include_directories(DroneController PRIVATE ${PROJECT_ROOT})
add_custom_command(TARGET DroneController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DroneController> ${LAST_BUILT_VERSION_DIRECTORY}/sys_image
)
