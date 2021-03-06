include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# -----------------------------------------------------------------------------
# Project Libraries
# -----------------------------------------------------------------------------
add_subdirectory(config/bsp)
add_subdirectory(debug)
add_subdirectory(hmi)
add_subdirectory(io)
add_subdirectory(registry)
add_subdirectory(system)
add_subdirectory(tasks)
add_subdirectory(usb)
add_subdirectory(utility)
add_subdirectory(wireless)

# -----------------------------------------------------------------------------
# Project Libraries
# -----------------------------------------------------------------------------
gen_intf_lib_variants(
  TARGET
    embedded_core_libs
  LIBRARIES
    thor_cmn_cm4
    thor_hld_core
    thor_lld_intf
    thor_lld_stm32f4
    thor_cfg_freertos
  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/DroneController
)

# -----------------------------------------------------------------------------
# Hardware Config:
# cmake -DTOOLCHAIN=arm-none-eabi -DFREERTOS_THREADS=ON -DDEVICE_TARGET=stm32f446re -DCMAKE_BUILD_TYPE=Debug ./../
#
# Simulator Config:
# cmake -DTOOLCHAIN=gcc -DNATIVE_THREADS=ON -DDEVICE_TARGET=sim -DCMAKE_BUILD_TYPE=Debug ./../
# -----------------------------------------------------------------------------
add_executable(DroneController startup.cpp)

target_link_options(DroneController PRIVATE "-Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DroneController.map")

# Include Directories
target_include_directories(DroneController PRIVATE ".")

# Dependent Modules
target_link_libraries(DroneController PRIVATE
  # Public Includes
  aurora_intf_inc
  chimera_intf_inc
  freertos_intf_inc_all
  thor_intf_inc

  # Project Libraries
  lib_bluetooth
  lib_config
  lib_human_interface
  lib_io
  lib_registry
  lib_rf24
  lib_system
  lib_tasks
  lib_usb
  lib_utility

  # Networking Libraries
  ripple_shared
  ripple_user_intf
  ripple_network_stack
  ripple_packets
  # ripple_util

  # Utility Libraries
  aurora_core_dbg
  aurora_database_dbg
  aurora_datastore_dbg
  aurora_filesystem_core_dbg
  aurora_hmi_dbg
  aurora_logging_dbg
  aurora_memory_dbg

  # Hardware Libraries
  chimera_core_dbg

  # Target Properties
  prj_device_target
  prj_build_target
)

# Hardware Driver Model
if(${DEVICE_TARGET} MATCHES "^stm32l4")
  target_link_libraries(DroneController PRIVATE thor_lld_stm32l4_rel embedded_core_libs_rel)
elseif(${DEVICE_TARGET} MATCHES "^stm32f4")
  target_link_libraries(DroneController PRIVATE thor_lld_stm32f4_dbg embedded_core_libs_dbg)
elseif(${DEVICE_TARGET} MATCHES "^sim")
  target_link_libraries(DroneController PRIVATE chimera_sim_core)
else()
  message(FATAL_ERROR "Unsupported device target")
endif()


if(Toolchain::HAS_GCC)
  add_dependencies(DroneController vdrone_nanopb_proto)

  target_link_libraries(DroneController PRIVATE
    # Aurora
    aurora_filesystem_generic_driver

    # Ripple NetIf
    ripple_netif_loopback

    # Testing & Mock Libraries
    gmock_src
    gtest_src

    # Simulator networking
    zmq
    vdrone_nanopb_proto
    vdrone_nanopb_proto_intf_inc
  )
endif()

if(Toolchain::HAS_GCC_ARM_NONE_EABI)
  target_link_libraries(DroneController PRIVATE
    # Aurora
    aurora_filesystem_spiffs_dbg

    # Threading Library
    freertos_intf_inc_all
    freertos_core
    freertos_port
    freertos_heap
    freertos_heap_4
    freertos_cm4f_port

    # Ripple NetIf
    ripple_netif_nrf24_datalink
    ripple_netif_nrf24_physical

    # Segger System View
    segger_sys_view
    segger_sys_view_intf
    segger_sys_view_cortex_m4_freertos

    # Tiny USB
    tiny_usb_intf_inc
    tiny_usb_core_dbg
    tiny_usb_port_st_dbg
  )
endif()

target_include_directories(DroneController PRIVATE ${PROJECT_ROOT})
add_custom_command(TARGET DroneController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DroneController> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sys_image
)
