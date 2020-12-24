cmake_minimum_required(VERSION 3.18.0)
project(DroneController VERSION 0.1.0)
enable_testing()

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
if(Toolchain::HAS_GCC_ARM_NONE_EABI)
  include("lib/CommonTools/cmake/toolchains/linker_whole_archive.cmake")
endif()

# ====================================================
# Import common packages and projects
# ====================================================
find_package(Boost REQUIRED)
add_subdirectory("lib/Aurora")
add_subdirectory("lib/Chimera")
add_subdirectory("lib/CommonTools/cpputest")
add_subdirectory("lib/CommonTools/googletest")
add_subdirectory("lib/FreeRTOS")
add_subdirectory("lib/Thor")
add_subdirectory("lib/ugfx")

# ====================================================
# Project Exports
# ====================================================
# Public include location
add_library(project_inc INTERFACE)
target_include_directories(project_inc INTERFACE "${PROJECT_ROOT}")
export(TARGETS project_inc FILE "${PROJECT_BINARY_DIR}/Project/project_inc.cmake")

# Adjust Thor build configuration to use this project's config
target_compile_definitions(thor_project_config INTERFACE "THOR_USER_CONFIG")
target_include_directories(thor_project_config INTERFACE "${PROJECT_ROOT}/src/config")

# uGFX Configuration file
add_library(project_ugfx_inc INTERFACE)
target_include_directories(project_ugfx_inc INTERFACE "${PROJECT_ROOT}/src/config/ugfx")
target_link_libraries(project_ugfx_inc INTERFACE
  freertos_inc
  freertos_inc_legacy
  freertos_cfg
  freertos_port
  ugfx_st7735_inc
)
export(TARGETS project_ugfx_inc FILE "${PROJECT_BINARY_DIR}/project/project_ugfx_inc.cmake")

# ====================================================
# Project Imports
# ====================================================
add_subdirectory("src")
