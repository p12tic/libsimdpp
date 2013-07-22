/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT32X8_INL
#define LIBSIMDPP_SIMD_INT32X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline basic_int32x8::basic_int32x8(const float32x8& d)
{
#if SIMDPP_USE_AVX2
    operator=(_mm256_castps_si256(d));
#elif SIMDPP_USE_AVX
    __m256i d1 = _mm256_castps_si256(d);
    u32(0) = _mm256_castsi256_si128(d1);
    u32(1) = _mm256_extracti128_si256(d1, 1);
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
#if SIMDPP_USE_AVX2
    return _mm256_set_epi32(v0, v0, v0, v0, v0, v0, v0, v0);
#else
    uint32x4 a = uint32x4::make_const(v0);
    return {a, a};
#endif
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi32(v1, v0, v1, v0, v1, v0, v1, v0);
#else
    uint32x4 a = uint32x4::make_const(v0, v1);
    return {a, a};
#endif
}

inline uint32x8 uint32x8::make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi32(v3, v2, v1, v0, v3, v2, v1, v0);
#else
    uint32x4 a = uint32x4::make_const(v0, v1, v2, v3);
    return {a, a};
#endif
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


SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
