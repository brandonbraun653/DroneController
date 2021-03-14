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
add_subdirectory("lib/ugfx")
add_subdirectory("lib/yaffs2")

# ====================================================
# Project Exports
# ====================================================
# Public include location
add_library(project_inc INTERFACE)
target_include_directories(project_inc INTERFACE "${PROJECT_ROOT}" "${PROJECT_ROOT}/src/config")
export(TARGETS project_inc FILE "${PROJECT_BINARY_DIR}/Project/project_inc.cmake")


add_library(freertos_cfg INTERFACE)
target_include_directories(freertos_cfg INTERFACE "${PROJECT_ROOT}/src/config/freertos")
export(TARGETS freertos_cfg FILE "${PROJECT_BINARY_DIR}/ProjectConfig/freertos-cfg.cmake")

# Adjust Thor build configuration to use this project's config
target_compile_definitions(thor_project_config INTERFACE "THOR_USER_CONFIG")
target_include_directories(thor_project_config INTERFACE "${PROJECT_ROOT}/src/config")

# uGFX Configuration file
add_library(project_ugfx_inc INTERFACE)
target_include_directories(project_ugfx_inc INTERFACE "${PROJECT_ROOT}/src/config/ugfx")
target_link_libraries(project_ugfx_inc INTERFACE ugfx_st7735_inc)
if(Toolchain::REQUIRES_FREERTOS_THREADS)
  target_link_libraries(project_ugfx_inc INTERFACE
    freertos_inc
    freertos_inc_legacy
    freertos_cfg
    freertos_port
  )
endif()

export(TARGETS project_ugfx_inc FILE "${PROJECT_BINARY_DIR}/project/project_ugfx_inc.cmake")



# ====================================================
# Project Imports
# ====================================================
add_subdirectory("src")
