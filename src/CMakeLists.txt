include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# -----------------------------------------------------------------------------
# Project Libraries
# -----------------------------------------------------------------------------
add_subdirectory(config/bsp)
add_subdirectory(config/ripple)
add_subdirectory(controller)
add_subdirectory(debug)
add_subdirectory(hmi)
add_subdirectory(io)
add_subdirectory(network)
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

gen_intf_lib_variants(
  TARGET
    ripple_libs
  LIBRARIES
    ripple_shared
    ripple_user_intf
    ripple_network_stack
    ripple_packets
  EXPORT_DIR
    ${PROJECT_BINARY_DIR}/DroneController
)

gen_intf_lib_variants(
  TARGET
    aurora_libs
  LIBRARIES
    aurora_core
    aurora_database
    aurora_datastore
    aurora_filesystem_core
    aurora_hmi
    aurora_logging
    aurora_memory
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
  vdrone_nanopb_proto_intf_inc

  # Project Libraries
  lib_bluetooth
  lib_rn4871
  lib_config_bsp
  lib_config_ripple
  lib_controller
  lib_debug
  lib_human_interface
  lib_io
  lib_network
  lib_registry
  lib_rf24
  lib_system
  lib_tasks
  lib_usb
  lib_utility

  # Submodule Libraries
  chimera_core_rel
  aurora_libs_rel
  ripple_libs_rel
  vdrone_nanopb_proto_rel

  # Target Properties
  prj_device_target
  prj_build_target
)

# Hardware Driver Model
if(${DEVICE_TARGET} MATCHES "^stm32f4")
  target_link_libraries(DroneController PRIVATE embedded_core_libs_rel)
elseif(${DEVICE_TARGET} MATCHES "^sim")
  target_link_libraries(DroneController PRIVATE chimera_sim_core)
else()
  message(FATAL_ERROR "Unsupported device target")
endif()


if(Toolchain::HAS_GCC)
  add_dependencies(DroneController vdrone_nanopb_proto)

  target_link_libraries(DroneController PRIVATE
    # Aurora
    aurora_filesystem_generic_driver_dbg

    # Ripple NetIf
    ripple_netif_loopback

    # Testing & Mock Libraries
    gmock_src
    gtest_src

    # Simulator networking
    zmq
  )
endif()

if(Toolchain::HAS_GCC_ARM_NONE_EABI)
  target_link_libraries(DroneController PRIVATE
    # Aurora
    aurora_filesystem_spiffs_rel

    # Threading Library
    freertos_intf_inc_all
    freertos_core_rel
    freertos_port
    freertos_heap
    freertos_heap_4_rel
    freertos_cm4f_port_rel

    # Ripple NetIf
    ripple_netif_nrf24_datalink_rel
    ripple_netif_nrf24_physical_rel

    # Segger System View
    segger_sys_view_rel
    segger_sys_view_intf
    segger_sys_view_cortex_m4_freertos_rel

    # Tiny USB
    tiny_usb_intf_inc
    tiny_usb_core_rel
    tiny_usb_port_st_rel
  )
endif()

target_include_directories(DroneController PRIVATE ${PROJECT_ROOT})
add_custom_command(TARGET DroneController POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DroneController> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sys_image
)
