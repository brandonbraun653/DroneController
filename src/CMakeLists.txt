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
# Without Map:
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DCUSTOM_FREERTOS_CFG=ON -DDEVICE_TARGET=stm32l432kb -DCMAKE_BUILD_TYPE=Debug --configure ../
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DCUSTOM_FREERTOS_CFG=ON -DDEVICE_TARGET=stm32f446re -DCMAKE_BUILD_TYPE=Debug --configure ../
#
# With Map File:
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DCUSTOM_FREERTOS_CFG=ON -DDEVICE_TARGET=stm32l432kb -DCMAKE_BUILD_TYPE=Debug -DGENERATE_MAP_FILE=ON --configure ../
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DCUSTOM_FREERTOS_CFG=ON -DDEVICE_TARGET=stm32f446re -DCMAKE_BUILD_TYPE=Debug -DGENERATE_MAP_FILE=ON --configure ../
# -----------------------------------------------------------------------------
add_executable(DroneController
  startup.cpp
)

target_include_directories(DroneController PRIVATE "." )

target_link_libraries(DroneController PRIVATE
  # Public Includes
  aurora_intf_inc
  Boost::boost
  chimera_intf_inc
  freertos_inc
  thor_intf_inc
  type_safe_inc

  # Project Libraries
  lib_tasks
  lib_utility
  # lib_wireless

  # Graphics Libraries
  # ugfx_lib_rel
  # ugfx_st7735_lib_rel

  # Networking Libraries
  # ripple_core_rel

  # File System
  aurora_memory_dbg
  lfs_core_dbg
  memory_flash_littlefs_dbg

  # Hardware Libraries
  aurora_core_rel
  aurora_hmi_rel
  aurora_logging_rel
  chimera_core_dbg
  freertos_cfg
  freertos_core_rel
  freertos_heap
  freertos_port
  thor_cfg_freertos_rel
  thor_cmn_cm4_rel
  thor_hld_core_rel
  thor_lld_intf_rel
  thor_lld_stm32l4

  # Target Properties
  prj_device_target
  prj_build_target
)

target_include_directories(DroneController PRIVATE ${PROJECT_ROOT})
add_custom_command(TARGET DroneController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DroneController> ${LAST_BUILT_VERSION_DIRECTORY}/sys_image
)
