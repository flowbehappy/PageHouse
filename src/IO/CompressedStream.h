// Copyright 2022 PingCAP, Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>

/** Common Defines */

#define DBMS_MAX_COMPRESSED_SIZE 0x40000000ULL /// 1GB

#define COMPRESSED_BLOCK_HEADER_SIZE 9


namespace DB
{
/** Compression method */
enum class CompressionMethod
{
    kLZ4 = 1,
    kLZ4HC = 2, /// The format is the same as for kLZ4. The difference is only in compression.
    kZSTD = 3, /// Experimental algorithm: https://github.com/Cyan4973/zstd
    kNONE = 4, /// No compression
};

/** The compressed block format is as follows:
  *
  * The first 16 bytes are the checksum from all other bytes of the block. Now only CityHash128 is used.
  * In the future, you can provide other checksums, although it will not be possible to make them different in size.
  *
  * The next byte specifies the compression algorithm. Then everything depends on the algorithm.
  *
  * 0x82 - kLZ4 or kLZ4HC (they have the same format).
  *        Next 4 bytes - the size of the compressed data, taking into account the header; 4 bytes is the size of the uncompressed data.
  *
  * NOTE: Why is 0x82?
  * Originally only QuickLZ was used. Then kLZ4 was added.
  * The high bit is set to distinguish from QuickLZ, and the second bit is set for compatibility,
  *  for the functions qlz_size_compressed, qlz_size_decompressed to work.
  * Although now such compatibility is no longer relevant.
  *
  * 0x90 - kZSTD
  *
  * All sizes are little endian.
  */

enum class CompressionMethodByte : uint8_t
{
    kNONE = 0x02,
    kLZ4 = 0x82,
    kZSTD = 0x90,
    // COL_END is not a compreesion method, but a flag of column end used in compact file.
    COL_END = 0x66,
};

} // namespace DB
