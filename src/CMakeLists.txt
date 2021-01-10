# -----------------------------------------------------------------------------
# Project Libraries
# -----------------------------------------------------------------------------
add_subdirectory(config/ugfx)
add_subdirectory(tasks)
add_subdirectory(utility)
add_subdirectory(wireless)

# -----------------------------------------------------------------------------
# Test Suite: HLD ADC
#
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DDEVICE_TARGET=stm32l432kb -DCMAKE_BUILD_TYPE=Debug -DGENERATE_MAP_FILE=ON --configure ../
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
  lib_tasks_rel
  lib_utility_rel
  lib_wireless_rel

  # Graphics Libraries
  ugfx_lib_rel
  ugfx_st7735_lib_rel

  # Networking Libraries
  ripple_core_rel

  # File System
  lfs_core_rel
  memory_flash_littlefs_rel

  # Hardware Libraries
  aurora_core_rel
  aurora_hmi_rel
  aurora_logging_rel
  chimera_core_rel
  freertos_cfg
  freertos_core_rel
  freertos_heap
  freertos_port
  thor_cfg_freertos_rel
  thor_cmn_cm4_rel
  thor_hld_core_rel
  thor_lld_intf_rel
  thor_lld_stm32l4_rel

  # Target Properties
  prj_device_target
  prj_build_target
)

target_include_directories(DroneController PRIVATE ${PROJECT_ROOT})
add_custom_command(TARGET DroneController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DroneController> ${LAST_BUILT_VERSION_DIRECTORY}/sys_image
)
