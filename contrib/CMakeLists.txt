set_property(DIRECTORY PROPERTY EXCLUDE_FROM_ALL 1)

if (NOT MSVC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast")
endif ()

SET (POCO_STATIC ON CACHE BOOL "Build using shared libraries of poco" FORCE)

add_subdirectory(libfiu)
add_subdirectory(boost-cmake)
add_subdirectory(lz4-cmake)

set (CMAKE_POLICY_DEFAULT_CMP0077 NEW)
add_subdirectory(zlib-ng)
unset (CMAKE_POLICY_DEFAULT_CMP0077)

add_subdirectory(magic_enum)
add_subdirectory(libcityhash)
add_subdirectory(fmtlib-cmake)

set (BUILD_TESTING OFF CACHE BOOL "Disable cpu-features testing" FORCE)
if (NOT (OS_DARWIN AND ARCH_AARCH64))
    add_subdirectory(cpu_features)
endif()

if (ARCH_AARCH64 AND OS_LINUX)
    add_subdirectory(arm-optimized-routines-cmake)
endif ()

if (USE_INTERNAL_POCO_LIBRARY)
    set (save_CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    set (save_CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
    set (_save ${ENABLE_TESTS})
    set (ENABLE_TESTS 0)
    set (CMAKE_DISABLE_FIND_PACKAGE_ZLIB 1)
    if (USE_INTERNAL_SSL_LIBRARY)
        set (DISABLE_INTERNAL_OPENSSL 1 CACHE INTERNAL "")
    endif ()
    if (MSVC)
        set (ENABLE_DATA_ODBC 0 CACHE INTERNAL "") # TODO (build fail)
    endif ()
    add_subdirectory (poco)
    unset (CMAKE_DISABLE_FIND_PACKAGE_ZLIB)
    set (ENABLE_TESTS ${_save})
    set (CMAKE_CXX_FLAGS ${save_CMAKE_CXX_FLAGS})
    set (CMAKE_C_FLAGS ${save_CMAKE_C_FLAGS})
    if (OPENSSL_FOUND AND TARGET Crypto)
        # Bug in poco https://github.com/pocoproject/poco/pull/2100 found on macos
        target_include_directories(Crypto PUBLIC ${OPENSSL_INCLUDE_DIR})
    endif ()
endif ()

add_subdirectory (protobuf-cmake)

SET (BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable google-benchmark testing" FORCE)
SET (BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable google-benchmark testing" FORCE)
add_subdirectory(benchmark)
if (ENABLE_TESTS)
    add_subdirectory(googletest)
endif()
add_subdirectory(zstd-cmake)
add_subdirectory(double-conversion)

if (ENABLE_JEMALLOC AND USE_INTERNAL_JEMALLOC_LIBRARY)
    add_subdirectory (jemalloc-cmake)
endif ()

