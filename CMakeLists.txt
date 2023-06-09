cmake_minimum_required (VERSION 3.21)

project (PageHouse LANGUAGES C CXX ASM)

cmake_policy(SET CMP0048 NEW)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS 1) # https://cmake.org/cmake/help/latest/prop_tgt/CXX_EXTENSIONS.html#prop_tgt:CXX_EXTENSIONS
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PageHouse_SOURCE_DIR}/cmake/Modules/")

option (UNBUNDLED "Try find all libraries in system (if fail - use bundled from contrib/)" OFF)
if (UNBUNDLED)
    set(NOT_UNBUNDLED 0)
else ()
    set(NOT_UNBUNDLED 1)
endif ()
# Using system libs can cause lot of warnings in includes.
if (UNBUNDLED OR NOT (OS_LINUX OR OS_DARWIN) OR ARCH_32)
    option (NO_WERROR "Disable -Werror compiler option" ON)
endif ()

message(STATUS "UNBUNDLED=${UNBUNDLED}, NOT_UNBUNDLED=${NOT_UNBUNDLED}")

include (cmake/add_warning.cmake)
include (cmake/sources.cmake)
include (cmake/find_jemalloc.cmake)
include (cmake/find_boost.cmake)
include (cmake/find_zlib.cmake)
include (cmake/find_poco.cmake)
include (cmake/find_protobuf.cmake)
include (cmake/find_lz4.cmake)
include (cmake/find_gtest.cmake)

include_directories (src)

add_subdirectory (contrib)
add_subdirectory (libs)
add_subdirectory (src)