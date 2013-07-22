/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_INT8X16_INL
#define LIBSIMDPP_SIMD_INT8X16_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#if SIMDPP_USE_NULL
    #include <simdpp/null/set.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline int8x16 int8x16::zero()
{
    return int128::zero();
}

inline int8x16 int8x16::load_broadcast(const int8_t* v0)
{
    return uint8x16::load_broadcast(reinterpret_cast<const uint8_t*>(v0));
}

inline int8x16 int8x16::set_broadcast(int8_t v0)
{
    return uint8x16::set_broadcast(v0);
}

inline int8x16 int8x16::make_const(int8_t v0)
{
    return uint8x16::make_const(v0);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1)
{
    return uint8x16::make_const(v0, v1);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3)
{
    return uint8x16::make_const(v0, v1, v2, v3);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7)
{
    return uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline int8x16 int8x16::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                                   int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                                   int8_t v12, int8_t v13, int8_t v14, int8_t v15)
{
    return uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v8, v9, v10, v11, v12, v13, v14, v15);
}

inline uint8x16 uint8x16::zero()
{
    return int128::zero();
}

inline uint8x16 uint8x16::load_broadcast(const uint8_t* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(*v0);
#elif SIMDPP_USE_SSE2
    return uint8x16::set_broadcast(*v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u8(v0);
#endif
}

inline uint8x16 uint8x16::set_broadcast(uint8_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
    uint32_t u0;
    u0 = v0 * 0x01010101;
    return uint32x4::set_broadcast(u0);
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi8(v0, v0, v0, v0, v0, v0, v0, v0,
                        v0, v0, v0, v0, v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u8(&v0);
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi8(v1, v0, v1, v0, v1, v0, v1, v0,
                        v1, v0, v1, v0, v1, v0, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint16_t vi[1];
        uint8_t v[2];
    };
    v[0] = v0;
    v[1] = v1;
    return uint8x16(vld1q_dup_u16(vi));
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0, v1, v2, v3);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi8(v3, v2, v1, v0, v3, v2, v1, v0,
                        v3, v2, v1, v0, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint32_t vi[1];
        uint8_t v[4];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    return uint8x16(vld1q_dup_u32(vi));
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0, v1, v2, v3, v4, v5, v6, v7);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi8(v7, v6, v5, v4, v3, v2, v1, v0,
                        v7, v6, v5, v4, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint64_t align;
        uint8_t v[8];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    v[4] = v4;  v[5] = v5;  v[6] = v6;  v[7] = v7;
    uint8x8_t r0 = vld1_u8(v);
    return vcombine_u8(r0, r0);
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                                     uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                                     uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint8x16>(v0, v1, v2, v3, v4, v5, v6, v7,
                                    v8, v9, v10, v11, v12, v13, v14, v15);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi8(v15, v14, v13, v12, v11, v10, v9, v8,
                        v7, v6, v5, v4, v3, v2, v1, v0);
#elif SIMDPP_USE_NEON
    union {
        int128 align;
        uint8_t v[16];
    };
    v[0] = v0;  v[1] = v1;  v[2] = v2;  v[3] = v3;
    v[4] = v4;  v[5] = v5;  v[6] = v6;  v[7] = v7;
    v[8] = v8;  v[9] = v9;  v[10] = v10; v[11] = v11;
    v[12] = v12; v[13] = v13; v[14] = v14; v[15] = v15;
    return vld1q_u8(v);
#endif
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
