/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMD_INT32X8_INL
#define LIBSIMDPP_SIMD_INT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline basic_int32x8::basic_int32x8(const float32x8& d)
{
#if SIMDPP_USE_AVX2
    operator=(_mm256_castps_si256(d));
#elif SIMDPP_USE_AVX
    __m256i d1 = _mm256_castps_si256(d);
    u32(0) = _mm256_castsi256_si128(d1);
    u32(1) = _mm256_extractf128_si256(d1, 1);
#else
    u32(0) = d[0];
    u32(1) = d[1];
#endif
}

inline int32x8 int32x8::zero()
{
    return int256::zero();
}

inline int32x8 int32x8::load_broadcast(const int32_t* v0)
{
    return uint32x8::load_broadcast(reinterpret_cast<const uint32_t*>(v0));
}

inline int32x8 int32x8::set_broadcast(int32_t v0)
{
    return uint32x8::set_broadcast(v0);
}

inline int32x8 int32x8::make_const(int32_t v0)
{
    return uint32x8::make_const(v0);
}

inline int32x8 int32x8::make_const(int32_t v0, int32_t v1)
{
    return uint32x8::make_const(v0, v1);
}

inline int32x8 int32x8::make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
{
    return uint32x8::make_const(v0, v1, v2, v3);
}

inline int32x8 int32x8::make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3,
                                   int32_t v4, int32_t v5, int32_t v6, int32_t v7)
{
    return uint32x8::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline uint32x8 uint32x8::zero()
{
    return int256::zero();
}

inline uint32x8 uint32x8::load_broadcast(const uint32_t* v0)
{
#if SIMDPP_USE_AVX2
    return uint32x8::set_broadcast(*v0);
#else
    uint32x4 a = uint32x4::load_broadcast(v0);
    return {a, a};
#endif
}

inline uint32x8 uint32x8::set_broadcast(uint32_t v0)
{
#if SIMDPP_USE_AVX2
    int128 a = _mm_cvtsi32_si128(v0);
    return _mm256_broadcastd_epi32(a);
#else
    uint32x4 a = uint32x4::set_broadcast(v0);
    return {a, a};
#endif
}

inline uint32x8 uint32x8::make_const(uint32_t v0)
{
    return uint32x8::make_const(v0, v0, v0, v0, v0, v0, v0, v0);
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1)
{
    return uint32x8::make_const(v0, v1, v0, v1, v0, v1, v0, v1);
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
    return uint32x8::make_const(v0, v1, v2, v3, v0, v1, v2, v3);
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3,
                                     uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi32(v7, v6, v5, v4, v3, v2, v1, v0);
#else
    return {uint32x4::make_const(v0, v1, v2, v3),
            uint32x4::make_const(v4, v5, v6, v7)};
#endif
}

inline mask_int32x8::operator basic_int32x8() const
{
#if SIMDPP_USE_AVX2
    return d_;
#else
    return basic_int32x8(m_[0], m_[1]);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
