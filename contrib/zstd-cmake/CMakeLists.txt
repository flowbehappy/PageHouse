# ################################################################
# zstd - Makefile
# Copyright (C) Yann Collet 2014-2016
# All rights reserved.
#
# BSD license
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice, this
#   list of conditions and the following disclaimer in the documentation and/or
#   other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# You can contact the author at :
#  - zstd homepage : http://www.zstd.net/
# ################################################################

# Get library version based on information from input content (use regular exp)
function(GetLibraryVersion _content _outputVar1 _outputVar2 _outputVar3)
    string(REGEX MATCHALL ".*define ZSTD_VERSION_MAJOR+.* ([0-9]+).*define ZSTD_VERSION_MINOR+.* ([0-9]+).*define ZSTD_VERSION_RELEASE+.* ([0-9]+)" VERSION_REGEX "${_content}")
    SET(${_outputVar1} ${CMAKE_MATCH_1} PARENT_SCOPE)
    SET(${_outputVar2} ${CMAKE_MATCH_2} PARENT_SCOPE)
    SET(${_outputVar3} ${CMAKE_MATCH_3} PARENT_SCOPE)
endfunction()

# Define library directory, where sources and header files are located
SET(LIBRARY_DIR ${PageHouse_SOURCE_DIR}/contrib/zstd/lib)
INCLUDE_DIRECTORIES(BEFORE ${LIBRARY_DIR} ${LIBRARY_DIR}/common)

# Read file content
FILE(READ ${LIBRARY_DIR}/zstd.h HEADER_CONTENT)

# Parse version
GetLibraryVersion("${HEADER_CONTENT}" LIBVER_MAJOR LIBVER_MINOR LIBVER_RELEASE)
MESSAGE(STATUS "ZSTD VERSION ${LIBVER_MAJOR}.${LIBVER_MINOR}.${LIBVER_RELEASE}")

SET(Sources
        ${LIBRARY_DIR}/dictBuilder/cover.c
        ${LIBRARY_DIR}/dictBuilder/zdict.c
        ${LIBRARY_DIR}/dictBuilder/divsufsort.c
        ${LIBRARY_DIR}/dictBuilder/fastcover.c
        ${LIBRARY_DIR}/compress/zstd_fast.c
        ${LIBRARY_DIR}/compress/fse_compress.c
        ${LIBRARY_DIR}/compress/hist.c
        ${LIBRARY_DIR}/compress/zstd_lazy.c
        ${LIBRARY_DIR}/compress/zstd_compress_superblock.c
        ${LIBRARY_DIR}/compress/zstdmt_compress.c
        ${LIBRARY_DIR}/compress/zstd_ldm.c
        ${LIBRARY_DIR}/compress/zstd_compress_literals.c
        ${LIBRARY_DIR}/compress/zstd_compress.c
        ${LIBRARY_DIR}/compress/zstd_opt.c
        ${LIBRARY_DIR}/compress/zstd_compress_sequences.c
        ${LIBRARY_DIR}/compress/huf_compress.c
        ${LIBRARY_DIR}/compress/zstd_double_fast.c
        ${LIBRARY_DIR}/common/entropy_common.c
        ${LIBRARY_DIR}/common/debug.c
        ${LIBRARY_DIR}/common/fse_decompress.c
        ${LIBRARY_DIR}/common/pool.c
        ${LIBRARY_DIR}/common/error_private.c
        ${LIBRARY_DIR}/common/threading.c
        ${LIBRARY_DIR}/common/zstd_common.c
        ${LIBRARY_DIR}/common/xxhash.c
        ${LIBRARY_DIR}/deprecated/zbuff_decompress.c
        ${LIBRARY_DIR}/deprecated/zbuff_compress.c
        ${LIBRARY_DIR}/deprecated/zbuff_common.c
        ${LIBRARY_DIR}/decompress/zstd_decompress_block.c
        ${LIBRARY_DIR}/decompress/huf_decompress.c
        ${LIBRARY_DIR}/decompress/zstd_decompress.c
        ${LIBRARY_DIR}/decompress/zstd_ddict.c
        ${LIBRARY_DIR}/decompress/huf_decompress_amd64.S)

SET(Headers
        ${LIBRARY_DIR}/dictBuilder/cover.h
        ${LIBRARY_DIR}/dictBuilder/divsufsort.h
        ${LIBRARY_DIR}/compress/zstd_ldm_geartab.h
        ${LIBRARY_DIR}/compress/zstd_compress_internal.h
        ${LIBRARY_DIR}/compress/zstd_ldm.h
        ${LIBRARY_DIR}/compress/zstd_double_fast.h
        ${LIBRARY_DIR}/compress/clevels.h
        ${LIBRARY_DIR}/compress/zstd_lazy.h
        ${LIBRARY_DIR}/compress/zstdmt_compress.h
        ${LIBRARY_DIR}/compress/zstd_fast.h
        ${LIBRARY_DIR}/compress/zstd_opt.h
        ${LIBRARY_DIR}/compress/hist.h
        ${LIBRARY_DIR}/compress/zstd_cwksp.h
        ${LIBRARY_DIR}/compress/zstd_compress_superblock.h
        ${LIBRARY_DIR}/compress/zstd_compress_sequences.h
        ${LIBRARY_DIR}/compress/zstd_compress_literals.h
        ${LIBRARY_DIR}/common/portability_macros.h
        ${LIBRARY_DIR}/common/error_private.h
        ${LIBRARY_DIR}/common/huf.h
        ${LIBRARY_DIR}/common/mem.h
        ${LIBRARY_DIR}/common/compiler.h
        ${LIBRARY_DIR}/common/bitstream.h
        ${LIBRARY_DIR}/common/debug.h
        ${LIBRARY_DIR}/common/pool.h
        ${LIBRARY_DIR}/common/fse.h
        ${LIBRARY_DIR}/common/xxhash.h
        ${LIBRARY_DIR}/common/threading.h
        ${LIBRARY_DIR}/common/zstd_trace.h
        ${LIBRARY_DIR}/common/cpu.h
        ${LIBRARY_DIR}/common/zstd_internal.h
        ${LIBRARY_DIR}/common/zstd_deps.h
        ${LIBRARY_DIR}/deprecated/zbuff.h
        ${LIBRARY_DIR}/zstd.h
        ${LIBRARY_DIR}/legacy/zstd_legacy.h
        ${LIBRARY_DIR}/zdict.h
        ${LIBRARY_DIR}/zstd_errors.h
        ${LIBRARY_DIR}/decompress/zstd_decompress_block.h
        ${LIBRARY_DIR}/decompress/zstd_ddict.h
        ${LIBRARY_DIR}/decompress/zstd_decompress_internal.h)

SET(ZSTD_LEGACY_SUPPORT true)

IF (ZSTD_LEGACY_SUPPORT)
    SET(LIBRARY_LEGACY_DIR ${LIBRARY_DIR}/legacy)
    INCLUDE_DIRECTORIES(BEFORE ${LIBRARY_LEGACY_DIR})
    ADD_DEFINITIONS(-D ZSTD_LEGACY_SUPPORT=1)

    SET(Sources ${Sources}
            ${LIBRARY_LEGACY_DIR}/zstd_v01.c
            ${LIBRARY_LEGACY_DIR}/zstd_v02.c
            ${LIBRARY_LEGACY_DIR}/zstd_v03.c
            ${LIBRARY_LEGACY_DIR}/zstd_v04.c
            ${LIBRARY_LEGACY_DIR}/zstd_v05.c
            ${LIBRARY_LEGACY_DIR}/zstd_v06.c
            ${LIBRARY_LEGACY_DIR}/zstd_v07.c)

    SET(Headers ${Headers}
            ${LIBRARY_LEGACY_DIR}/zstd_legacy.h
            ${LIBRARY_LEGACY_DIR}/zstd_v01.h
            ${LIBRARY_LEGACY_DIR}/zstd_v02.h
            ${LIBRARY_LEGACY_DIR}/zstd_v03.h
            ${LIBRARY_LEGACY_DIR}/zstd_v04.h
            ${LIBRARY_LEGACY_DIR}/zstd_v05.h
            ${LIBRARY_LEGACY_DIR}/zstd_v06.h
            ${LIBRARY_LEGACY_DIR}/zstd_v07.h)
ENDIF (ZSTD_LEGACY_SUPPORT)
ENABLE_LANGUAGE(ASM)
ADD_LIBRARY(zstd ${Sources} ${Headers})

target_include_directories (zstd PUBLIC ${LIBRARY_DIR})

if (PageHouse_ENABLE_ARCH_HASWELL_SUPPORT)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PageHouse_COMPILER_ARCH_HASWELL_FLAG}")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PageHouse_COMPILER_ARCH_HASWELL_FLAG}")
endif ()
