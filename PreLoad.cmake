cmake_minimum_required(VERSION 3.18.0)

# ====================================================
# Override the toolchain used. This must be done here
# else CMake won't allow the override.
# ====================================================
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE STRING "")
set(COMMON_TOOL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/CommonTools" CACHE STRING "")
set(BOOST_ROOT "$ENV{HOME}/Programs/boost/boost_1_76_0" CACHE STRING "")
set(ARM_NONE_EABI_ROOT "$ENV{HOME}/Programs/compilers/gcc-arm-none-eabi-10-2020-q4-major/bin" CACHE STRING "")

include("${COMMON_TOOL_ROOT}/cmake/options/toolchain.cmake")