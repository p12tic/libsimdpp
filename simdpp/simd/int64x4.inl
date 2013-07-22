/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT64X4_INL
#define LIBSIMDPP_SIMD_INT64X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN


inline basic_int64x4::basic_int64x4(const float64x4& d)
{
#if SIMDPP_USE_AVX2
    operator=(_mm256_castpd_si256(d));
#elif SIMDPP_USE_AVX
    __m256i d1 = _mm256_castpd_si256(d);
    u64(0) = _mm256_castsi256_si128(d1);
    u64(1) = _mm256_extracti128_si256(d1, 1);
#else
    u64(0) = d[0];
    u64(1) = d[1];
#endif
}

inline int64x4 int64x4::zero()
{
    return int256::zero();
}

inline int64x4 int64x4::load_broadcast(const int64_t* v0)
{
    return uint64x4::load_broadcast(reinterpret_cast<const uint64_t*>(v0));
}

inline int64x4 int64x4::set_broadcast(int64_t v0)
{
    return uint64x4::set_broadcast(v0);
}

inline int64x4 int64x4::make_const(int64_t v0)
{
    return uint64x4::make_const(v0);
}

inline int64x4 int64x4::make_const(int64_t v0, int64_t v1)
{
    return uint64x4::make_const(v0, v1);
}

inline int64x4 int64x4::make_const(int64_t v0, int64_t v1, int64_t v2, int64_t v3)
{
    return uint64x4::make_const(v0, v1, v2, v3);
}

inline uint64x4 uint64x4::zero()
{
    return int256::zero();
}

inline uint64x4 uint64x4::load_broadcast(const uint64_t* v0)
{
#if SIMDPP_USE_AVX2
    return uint64x4::set_broadcast(*v0);
#else
    uint64x2 a = uint64x2::load_broadcast(v0);
    return {a, a};
#endif
}

inline uint64x4 uint64x4::set_broadcast(uint64_t v0)
{
#if SIMDPP_USE_AVX2
    int128 a = _mm_cvtsi64_si128(v0);
    return _mm256_broadcastq_epi64(a);
#else
    uint64x2 a = uint64x2::set_broadcast(v0);
    return {a, a};
#endif
}

inline uint64x4 uint64x4::make_const(uint64_t v0)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi64x(v0, v0, v0, v0);
#else
    uint64x2 a = uint64x2::make_const(v0);
    return {a, a};
#endif
}

inline uint64x4 uint64x4::make_const(uint64_t v0, uint64_t v1)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi64x(v1, v0, v1, v0);
#else
    uint64x2 a = uint64x2::make_const(v0, v1);
    return {a, a};
#endif
}

inline uint64x4 uint64x4::make_const(uint64_t v0, uint64_t v1, uint64_t v2, uint64_t v3)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi64x(v3, v2, v1, v0);
#else
    return {uint64x2::make_const(v0, v1),
            uint64x2::make_const(v2, v3)};
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
