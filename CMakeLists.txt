cmake_minimum_required (VERSION 3.21)

project (PageHouse LANGUAGES C CXX ASM)

cmake_policy(SET CMP0048 NEW)
include(CheckCXXCompilerFlag)

include (cmake/arch.cmake)
include (cmake/utils.cmake)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UC)
message (STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TiFlash_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_MACOSX_RPATH 1)

if(CMAKE_PREFIX_PATH)
    # append paths for cmake to check libs
    set(ENV{LD_LIBRARY_PATH}
            "${CMAKE_PREFIX_PATH}/lib:${CMAKE_PREFIX_PATH}/lib/x86_64-unknown-linux-gnu/:${CMAKE_PREFIX_PATH}/lib/aarch64-unknown-linux-gnu/")
endif()

include (cmake/cpu_features.cmake)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS 1) # https://cmake.org/cmake/help/latest/prop_tgt/CXX_EXTENSIONS.html#prop_tgt:CXX_EXTENSIONS
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS_RELWITHDEBINFO      "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3")
set (CMAKE_C_FLAGS_RELWITHDEBINFO        "${CMAKE_C_FLAGS_RELWITHDEBINFO} -O3")

option (DEBUG_WITHOUT_DEBUG_INFO "Set to ON to build dev target without debug info (remove flag `-g` in order to accelerate compiling speed and reduce target binary size)" OFF)
if (DEBUG_WITHOUT_DEBUG_INFO)
    string(REPLACE "-g" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    string(REPLACE "-g" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    message (STATUS "Build debug target without debug info")
else ()
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -ggdb3")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb3")
endif ()

message(STATUS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}")

set (CMAKE_BUILD_COLOR_MAKEFILE          ON)
set (CMAKE_CXX_FLAGS                     "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS} ${PLATFORM_EXTRA_CXX_FLAG} -fno-omit-frame-pointer ${COMMON_WARNING_FLAGS} ${CXX_WARNING_FLAGS} ${GLIBC_COMPATIBILITY_COMPILE_FLAGS}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO      "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CMAKE_CXX_FLAGS_ADD}")
set (CMAKE_CXX_FLAGS_DEBUG               "${CMAKE_CXX_FLAGS_DEBUG} ${MOST_DEBUGGABLE_LEVEL} -fverbose-asm -fno-inline ${CMAKE_CXX_FLAGS_ADD}")

set (CMAKE_C_FLAGS                       "${CMAKE_C_FLAGS} ${COMPILER_FLAGS} -fno-omit-frame-pointer ${COMMON_WARNING_FLAGS} ${GLIBC_COMPATIBILITY_COMPILE_FLAGS} ${CMAKE_C_FLAGS_ADD}")
set (CMAKE_C_FLAGS_RELWITHDEBINFO        "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${CMAKE_C_FLAGS_ADD}")
set (CMAKE_C_FLAGS_DEBUG                 "${CMAKE_C_FLAGS_DEBUG} ${MOST_DEBUGGABLE_LEVEL} -fverbose-asm -fno-inline ${CMAKE_C_FLAGS_ADD}")

message(STATUS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}, CMAKE_CXX_FLAGS_RELWITHDEBINFO:${CMAKE_CXX_FLAGS_RELWITHDEBINFO}, CMAKE_CXX_FLAGS_DEBUG:${CMAKE_CXX_FLAGS_DEBUG}")

include (cmake/test_compiler.cmake)

if (ARCH_AMD64)
    check_cxx_compiler_flag("-mvpclmulqdq -Werror -Wall -Wextra" PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT)
    if(PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT)
        add_definitions(-DPAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT=1)
    else()
        add_definitions(-DPAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT=0)
    endif()
else()
    add_definitions(-DPAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT=0)
endif()

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

# Enable tests by default when build type is debug
if (CMAKE_BUILD_TYPE_UC STREQUAL "DEBUG")
    set (ENABLE_TESTS_DEFAULT ON)
else ()
    set (ENABLE_TESTS_DEFAULT OFF)
endif ()

message (STATUS "CMAKE_BUILD_TYPE_UC:${CMAKE_BUILD_TYPE_UC}, ENABLE_TESTS_DEFAULT:${ENABLE_TESTS_DEFAULT}")

option (DISABLE_PAGEHOUSE_TESTS "Disable PageHouses tests. It is for the lib users to disable tests in this libpagehouse" OFF)
option (ENABLE_TESTS "Enables unit tests" ${ENABLE_TESTS_DEFAULT})

if (DISABLE_PAGEHOUSE_TESTS)
    set (ENABLE_TESTS OFF)
endif()

message (STATUS "ENABLE_TESTS:${ENABLE_TESTS}")

add_subdirectory (contrib) # Should be done after option ENABLE_TESTS, cause we will disable tests under contrib/
add_subdirectory(libs)

# Enable failpoints injection by default when ENABLE_TESTS is turn ON.
if (ENABLE_TESTS)
    enable_testing()
    set (ENABLE_FAILPOINTS_DEFAULT ON)
    message (STATUS "Tests are enabled")
else ()
    set (ENABLE_FAILPOINTS_DEFAULT OFF)
    message (STATUS "Tests are disabled")
endif()
option (ENABLE_FAILPOINTS "Enables failpoints injection" ${ENABLE_FAILPOINTS_DEFAULT})
if (ENABLE_FAILPOINTS)
    message (STATUS "Failpoints are enabled")
else ()
    message (STATUS "Failpoints are disabled")
endif ()

include_directories (src)
add_subdirectory(src)


print_flags ()
