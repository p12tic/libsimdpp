/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT16X8_INL
#define LIBSIMDPP_SIMD_INT16X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <cstdint>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline int128 int16x8::zero()
{
    return int128::zero();
}

inline int128 int16x8::load_broadcast(const int16_t* v0)
{
    return uint16x8::load_broadcast(reinterpret_cast<const uint16_t*>(v0));
}

inline int128 int16x8::set_broadcast(int16_t v0)
{
    return uint16x8::set_broadcast(v0);
}

inline int128 int16x8::make_const(int16_t v0)
{
    return uint16x8::make_const(v0);
}

inline int128 int16x8::make_const(int16_t v0, int16_t v1)
{
    return uint16x8::make_const(v0, v1);
}

inline int128 int16x8::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3)
{
    return uint16x8::make_const(v0, v1, v2, v3);
}

inline int128 int16x8::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                                  int16_t v4, int16_t v5, int16_t v6, int16_t v7)
{
    return uint16x8::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline int128 uint16x8::zero()
{
    return int128::zero();
}

inline int128 uint16x8::load_broadcast(const uint16_t* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(*v0);
#elif SIMDPP_USE_SSE2
    return uint16x8::set_broadcast(*v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u16(v0);
#endif
}

inline int128 uint16x8::set_broadcast(uint16_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(v0);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    uint32_t u0;
    u0 = v0 | v0 << 16;
    return uint32x4::set_broadcast(u0);
#endif
}

inline int128 uint16x8::make_const(uint16_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(v0);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi16(v0, v0, v0, v0, v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u16(&v0);
#endif
}

inline int128 uint16x8::make_const(uint16_t v0, uint16_t v1)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi16(v1, v0, v1, v0, v1, v0, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint16_t v[2];
        uint32_t vi[1];
    };
    v[0] = v0;
    v[1] = v1;
    return uint16x8(vld1q_dup_u32(vi));
#endif
}

inline int128 uint16x8::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(v0, v1, v2, v3);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi16(v3, v2, v1, v0, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint64_t align;
        uint16_t v[4];
    };
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
    uint16x4_t r0 = vld1_u16(v);
    return vcombine_u16(r0, r0);
#endif
}

inline int128 uint16x8::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                   uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(v0, v1, v2, v3, v4, v5, v6, v7);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi16(v7, v6, v5, v4, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        uint16_t v[8];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    v[4] = v4;  v[5] = v5;  v[6] = v6;  v[7] = v7;
    return vld1q_u16(v);
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
