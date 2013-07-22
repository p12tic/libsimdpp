/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT64X2_INL
#define LIBSIMDPP_SIMD_INT64X2_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline basic_int64x2::basic_int64x2(const float64x2& d)
{
#if SIMDPP_USE_NULL
    u64(0) = bit_cast<uint64_t>(d[0]);
    u64(1) = bit_cast<uint64_t>(d[1]);
#elif SIMDPP_USE_NEON
    operator=(bit_cast<basic_int64x2>(d));
#elif SIMDPP_USE_SSE2
    operator=(_mm_castpd_si128(d));
#endif
}

inline int64x2 int64x2::zero()
{
    return int128::zero();
}

inline int64x2 int64x2::load_broadcast(const int64_t* v0)
{
    return uint64x2::load_broadcast(reinterpret_cast<const uint64_t*>(v0));
}

inline int64x2 int64x2::set_broadcast(int64_t v0)
{
    return uint64x2::set_broadcast(v0);
}

inline int64x2 int64x2::make_const(int64_t v0)
{
    return uint64x2::make_const(v0);
}

inline int64x2 int64x2::make_const(int64_t v0, int64_t v1)
{
    return uint64x2::make_const(v0, v1);
}

inline uint64x2 uint64x2::zero()
{
    return int128::zero();
}

inline uint64x2 uint64x2::load_broadcast(const uint64_t* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint64x2>(*v0);
#elif SIMDPP_USE_SSE2
    uint64x2 r;
    r = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(v0));
    r = permute<0,0>(r);
    return r;
#elif SIMDPP_USE_NEON
    uint64x1_t r0 = vld1_dup_u64(v0);
    return vcombine_u64(r0, r0);
#endif
}

inline uint64x2 uint64x2::set_broadcast(uint64_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint64x2>(v0);
#elif SIMDPP_USE_SSE2
    uint64x2 r0;
    r0 = _mm_cvtsi64_si128(v0);
    r0 = permute<0,0>(r0);
    return uint64x2(r0);
#elif SIMDPP_USE_NEON
    uint64x1_t r0 = vcreate_u64(v0);
    return vcombine_u64(r0, r0);
#endif
}

inline uint64x2 uint64x2::make_const(uint64_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint64x2>(v0);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi64x(v0, v0);
#elif SIMDPP_USE_NEON
    uint64x1_t r0 = vcreate_u64(v0);
    return vcombine_u64(r0, r0);
#endif
}

inline uint64x2 uint64x2::make_const(uint64_t v0, uint64_t v1)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint64x2>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi64x(v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        uint64_t v[2];
    };
    v[0] = v0;
    v[1] = v1;
    return vld1q_u64(v);
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
