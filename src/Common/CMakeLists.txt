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

if(OS_DARWIN AND ARCH_AARCH64)
    set(CPU_FEATURES_LIBRARY)
else()
    set(CPU_FEATURES_LIBRARY cpu_features)
endif()


# Region for specialized CPU flags tuning

message(STATUS "PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT: ${PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT}")
message(STATUS "PAGEHOUSE_ENABLE_AVX512_SUPPORT:${PAGEHOUSE_ENABLE_AVX512_SUPPORT}")

check_then_add_sources_compile_flag (
        PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT
        "-mvpclmulqdq;-Wno-ignored-attributes"
        crc64_avx2.cpp
        crc64_avx512.cpp
)

check_then_add_sources_compile_flag (
        PAGEHOUSE_ENABLE_ARCH_HASWELL_SUPPORT
        "${PAGEHOUSE_COMPILER_ARCH_HASWELL_FLAG}"
        crc64_avx2.cpp
)

check_then_add_sources_compile_flag (
        PAGEHOUSE_ENABLE_AVX512_SUPPORT
        "-mavx512bw;-mavx512vl;-mavx512f;-mavx512dq"
        crc64_avx512.cpp
        crc64_avx2.cpp
)

check_then_add_sources_compile_flag (
        PAGEHOUSE_ENABLE_ASIMD_SUPPORT
        "-march=armv8-a+simd+crypto"
        crc64_sse2_asimd.cpp
)
