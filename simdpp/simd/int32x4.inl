/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT32X4_INL
#define LIBSIMDPP_SIMD_INT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline basic_int32x4::basic_int32x4(const float32x4& d)
{
#if SIMDPP_USE_NULL
    u32(0) = bit_cast<uint32_t>(d[0]);
    u32(1) = bit_cast<uint32_t>(d[1]);
    u32(2) = bit_cast<uint32_t>(d[2]);
    u32(3) = bit_cast<uint32_t>(d[3]);
#elif SIMDPP_USE_NEON
    operator=(bit_cast<basic_int32x4>(d));
#elif SIMDPP_USE_SSE2
    operator=(_mm_castps_si128(d));
#endif
}

inline int32x4 int32x4::zero()
{
    return int128::zero();
}

inline int32x4 int32x4::load_broadcast(const int32_t* v0)
{
    return uint32x4::load_broadcast(reinterpret_cast<const uint32_t*>(v0));
}

inline int32x4 int32x4::set_broadcast(int32_t v0)
{
    return uint32x4::set_broadcast(v0);
}

inline int32x4 int32x4::make_const(int32_t v0)
{
    return uint32x4::make_const(v0);
}

inline int32x4 int32x4::make_const(int32_t v0, int32_t v1)
{
    return uint32x4::make_const(v0, v1);
}

inline int32x4 int32x4::make_const(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
{
    return uint32x4::make_const(v0, v1, v2, v3);
}

inline uint32x4 uint32x4::zero()
{
    return int128::zero();
}

inline uint32x4 uint32x4::load_broadcast(const uint32_t* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint32x4>(*v0);
#elif SIMDPP_USE_SSE2
    uint32x4 r;
    r = _mm_cvtsi32_si128(*v0);
    r = permute<0,0,0,0>(r);
    return r;
#elif SIMDPP_USE_NEON
    return vld1q_dup_u32(v0);
#endif
}

inline uint32x4 uint32x4::set_broadcast(uint32_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint32x4>(v0);
#elif SIMDPP_USE_SSE2
    uint32x4 r0;
    r0 = _mm_cvtsi32_si128(v0);
    r0 = permute<0,0,0,0>(r0);
    return uint32x4(r0);
#elif SIMDPP_USE_NEON
    uint32x4 r0;
    r0 = vsetq_lane_u32(v0, r0, 0);
    r0 = broadcast<0>(r0);
    return r0;
#endif
}

inline uint32x4 uint32x4::make_const(uint32_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint32x4>(v0);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi32(v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u32(&v0);
#endif
}

inline uint32x4 uint32x4::make_const(uint32_t v0, uint32_t v1)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint32x4>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi32(v1, v0, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        uint32_t v[2];
    };
    v[0] = v0;
    v[1] = v1;
    uint32x2_t r0 = vld1_u32(v);
    return vcombine_u32(r0, r0);
#endif
}

inline uint32x4 uint32x4::make_const(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint32x4>(v0, v1, v2, v3);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi32(v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        uint32_t v[4];
    };
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
    return vld1q_u32(v);
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
