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

#include <Common/crc64.h>
#include <Common/crc64_fast.h>
#include <Common/crc64_table.h>
#include <Common/detect_features.h>
#include <Common/simd.h>
namespace crc64
{
using namespace common;
Digest::Digest(Mode mode)
{
    // clang-format off
#ifdef PAGEHOUSE_CRC64_HAS_SIMD_SUPPORT
    using namespace simd_option;
#if PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT
#ifdef PAGEHOUSE_ENABLE_AVX512_SUPPORT
    if ((mode == Mode::Auto || mode >= Mode::SIMD_512) && ENABLE_AVX512
        && cpu_feature_flags.vpclmulqdq && cpu_feature_flags.avx512dq)
    {
        update_fn = [](uint64_t _state, const void * _src, size_t _length) {
            return crc64::_detail::update_fast<512>(crc64::_detail::update_vpclmulqdq_avx512, _state, _src, _length);
        };
    }
    else
#endif // PAGEHOUSE_ENABLE_AVX512_SUPPORT
#ifdef PAGEHOUSE_ENABLE_AVX_SUPPORT
    if ((mode == Mode::Auto || mode >= Mode::SIMD_256) && ENABLE_AVX
        && cpu_feature_flags.vpclmulqdq && cpu_feature_flags.avx2)
    {
        update_fn = [](uint64_t _state, const void * _src, size_t _length) {
            return crc64::_detail::update_fast<256>(crc64::_detail::update_vpclmulqdq_avx2, _state, _src, _length);
        };
    }
    else
#endif // PAGEHOUSE_ENABLE_AVX_SUPPORT
#endif // PAGEHOUSE_COMPILER_VPCLMULQDQ_SUPPORT
    if (mode == Mode::Auto || mode >= Mode::SIMD_128)
    {
        update_fn = [](uint64_t _state, const void * _src, size_t _length) {
            return crc64::_detail::update_fast(crc64::_detail::update_simd, _state, _src, _length);
        };
#ifdef PAGEHOUSE_ENABLE_ASIMD_SUPPORT
        if (!ENABLE_ASIMD || !cpu_feature_flags.pmull)
        {
            update_fn = _detail::update_table;
        }
#else // must be SSE case then
        if (!cpu_feature_flags.pclmulqdq)
        {
            update_fn = _detail::update_table;
        }
#endif // PAGEHOUSE_ENABLE_ASIMD_SUPPORT
    }
    else
#endif // PAGEHOUSE_CRC64_HAS_SIMD_SUPPORT
    {
        update_fn = _detail::update_table;
    }
    // clang-format on
}
} // namespace crc64
