# -----------------------------------------------------------------------------
# Project Libraries
# -----------------------------------------------------------------------------
add_subdirectory(config/bsp)
add_subdirectory(config/ugfx)
add_subdirectory(registry)
add_subdirectory(system)
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
  lib_config
  lib_registry
  lib_system
  lib_tasks
  lib_utility
  # lib_wireless

  # Board Support Libraries
  bsp_nucleo_f446re

  # Graphics Libraries
  ugfx_lib_dbg
  ugfx_st7735_lib_dbg
  ugfx_prj_config

  # Networking Libraries
  # ripple_core_rel

  # File System
  lfs_core_dbg
  memory_flash_littlefs_dbg

  # Utility Libraries
  aurora_core_dbg
  aurora_hmi_dbg
  aurora_logging_dbg
  aurora_memory_dbg
  aurora_database_dbg
  aurora_datastore_dbg

  # Hardware Libraries
  chimera_core_dbg
  freertos_cfg
  freertos_core_dbg
  freertos_heap
  freertos_port
  thor_cfg_freertos_dbg
  thor_cmn_cm4_dbg
  thor_hld_core_dbg
  thor_lld_intf_dbg

  # Target Properties
  prj_device_target
  prj_build_target
)

if(${DEVICE_TARGET} MATCHES "^stm32l4")
  target_link_libraries(DroneController PRIVATE thor_lld_stm32l4_dbg )
elseif(${DEVICE_TARGET} MATCHES "^stm32f4")
  target_link_libraries(DroneController PRIVATE thor_lld_stm32f4_dbg)
else()
  message(FATAL_ERROR "Unsupported device target")
endif()

target_include_directories(DroneController PRIVATE ${PROJECT_ROOT})
add_custom_command(TARGET DroneController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DroneController> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sys_image
)
