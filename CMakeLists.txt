cmake_minimum_required(VERSION 3.18.0)
project(DroneController NONE)
enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CPP_PLATFORM "freertos")

# ====================================================
# Perform very high level configuration
# ====================================================
# Set some vars common to both development environments
include("lib/CommonTools/cmake/options/common.cmake")

# Override the linker command
if(Toolchain::HAS_GCC_ARM_NONE_EABI OR Toolchain::HAS_GCC)
  include("lib/CommonTools/cmake/toolchains/linker_whole_archive.cmake")
endif()

# Select a global target flag
if(Toolchain::HAS_GCC_ARM_NONE_EABI)
  add_compile_definitions(EMBEDDED)
elseif(Toolchain::HAS_GCC)
  add_compile_definitions(SIMULATOR)
endif()


# ====================================================
# NanoPB exports
# ====================================================
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/nanopb/extra)
find_package(Nanopb REQUIRED)
set(NANO_PB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/nanopb" CACHE STRING "")

# ====================================================
# Import common packages and projects
# ====================================================
find_package(Boost REQUIRED)
add_subdirectory("lib/Aurora")
add_subdirectory("lib/Chimera")
add_subdirectory("lib/ChimeraSim")
add_subdirectory("lib/CommonTools/cpputest")
add_subdirectory("lib/CommonTools/googletest")
add_subdirectory("lib/DroneNet")
add_subdirectory("lib/FreeRTOS")
add_subdirectory("lib/Ripple")
add_subdirectory("lib/Thor")
add_subdirectory("lib/nanopb")
add_subdirectory("lib/yaffs2")

# ====================================================
# Project Exports
# ====================================================
# Project Headers
gen_intf_lib(
  TARGET
    project_inc
  INTF_DEFINES
    THOR_USER_CONFIG
  INTF_INCLUDES
    "${PROJECT_ROOT}"
    "${PROJECT_ROOT}/src/config"
  INTF_LIBRARIES
    ripple_inc
    freertos_intf_inc_all
    #vdrone_nanopb_proto_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Project"
)

# FreeRTOS Configuration
gen_intf_lib(
  TARGET
    freertos_cfg
  INTF_INCLUDES
    "${PROJECT_ROOT}/src/config/freertos"
    "${PROJECT_ROOT}/lib/Aurora/lib/segger/contrib/cortex_m4_freertos"
  INTF_LIBRARIES
    # segger_sys_view_intf
    # segger_sys_view_cortex_m4_freertos_intf
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Project"
)

gen_intf_lib(
  TARGET
    freertos_port
  INTF_INCLUDES
    "${PROJECT_ROOT}/lib/FreeRTOS/portable/GCC/ARM_CM4F"
  INTF_DEFINES
    FREERTOS_CFG_PORT_ARM_CM4F=1
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Project"
)

gen_intf_lib(
  TARGET
    freertos_heap
  INTF_DEFINES
    FREERTOS_CFG_MEM_MANG_HEAP4=1
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/Project"
)

# ====================================================
# Project Imports
# ====================================================
add_subdirectory("src")
