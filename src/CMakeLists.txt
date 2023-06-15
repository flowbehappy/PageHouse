# Copyright 2022 PingCAP, Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if (APPLE)
    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" AND NOT "${CMAKE_SYSTEM_VERSION}" VERSION_LESS "16.0.0")
        set (APPLE_SIERRA_OR_NEWER 1)
    else ()
        set (APPLE_SIERRA_OR_NEWER 0)
    endif ()
endif ()

set (CONFIG_COMMON ${CMAKE_CURRENT_BINARY_DIR}/Common/config_common.h)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Common/config_common.h.in ${CONFIG_COMMON})
message(STATUS "config common path: ${CONFIG_COMMON}")

add_subdirectory(Common)

add_headers_and_sources(page .)
add_headers_and_sources(page ./Common)
add_headers_and_sources(page ./Common/crc64_arch)
add_headers_and_sources(page ./Common/StringUtils)
add_headers_and_sources(page ./Common/SyncPoint)
add_headers_and_sources(page ./Core)
add_headers_and_sources(page ./Encryption)
add_headers_and_sources(page ./IO)
add_headers_and_sources(page ./V3)
add_headers_and_sources(page ./V3/Blob)
add_headers_and_sources(page ./V3/LogFile)
add_headers_and_sources(page ./V3/PageDirectory)
add_headers_and_sources(page ./V3/spacemap)
add_headers_and_sources(page ./V3/Universal)
add_headers_and_sources(page ./V3/CheckpointFile)
add_headers_and_sources(page ./V3/CheckpointFile/Proto)
add_headers_and_sources(page ./V3/WAL)

add_library(page_house ${CONFIG_COMMON} ${page_headers} ${page_sources})
target_include_directories(page_house PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/)
target_include_directories (page_house PUBLIC ${PageHouse_SOURCE_DIR}/contrib/libpcg-random/include)

target_link_libraries (page_house
    PUBLIC
    fiu
    fmt
    zstd
    cityhash
    magic_enum
    cpu_features
    double-conversion
    ${LZ4_LIBRARY}
    ${Poco_Util_LIBRARY}
    ${Poco_Data_LIBRARY}
    ${Poco_Foundation_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

if (ARCH_AARCH64 AND OS_LINUX)
    target_link_libraries (page_house PUBLIC pagehouse-aarch64-string pagehouse-aarch64-math)
endif()

add_subdirectory(TestUtils EXCLUDE_FROM_ALL)
add_subdirectory(V3/tests EXCLUDE_FROM_ALL)

