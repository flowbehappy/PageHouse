cmake_minimum_required (VERSION 3.21)

project (PageHouse LANGUAGES C CXX ASM)

cmake_policy(SET CMP0048 NEW)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS 1) # https://cmake.org/cmake/help/latest/prop_tgt/CXX_EXTENSIONS.html#prop_tgt:CXX_EXTENSIONS
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PageHouse_SOURCE_DIR}/cmake/Modules/")

include (cmake/add_warning.cmake)
include (cmake/sources.cmake)
include (cmake/find_jemalloc.cmake)
include (cmake/find_boost.cmake)
include (cmake/find_zlib.cmake)
include (cmake/find_poco.cmake)
include (cmake/find_protobuf.cmake)
include (cmake/find_lz4.cmake)

include_directories (src)

add_subdirectory (contrib)
add_subdirectory (libs)
add_subdirectory (src)