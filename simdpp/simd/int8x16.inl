/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_INT8X16_INL
#define LIBSIMDPP_SIMD_INT8X16_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

#if SIMDPP_USE_NULL
    #include <simdpp/null/set.h>
#endif
#if SIMDPP_USE_ALTIVEC
    #include <simdpp/altivec/load1.h>
    #include <simdpp/simd/shuffle.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

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
#elif SIMDPP_USE_ALTIVEC
    uint8x16 r = altivec::load1_u(r, v0);
    r = broadcast_w<0>(r);
    return r;
#endif
}

inline uint8x16 uint8x16::set_broadcast(uint8_t v0)
{
#if SIMDPP_USE_NULL
    return uint8x16::load_broadcast(&v0);
#elif SIMDPP_USE_SSE2
    uint32_t u0;
    u0 = v0 * 0x01010101;
    return uint32x4::set_broadcast(u0);
#elif SIMDPP_USE_NEON
    return vdupq_n_u8(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint8_t v[16];
        uint8x16 align;
    };
    v[0] = v0;
    uint8x16 r = altivec::load1(r, v);
    r = broadcast_w<0>(r);
    return r;
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v0, v0, v0, v0, v0, v0, v0,
                                v0, v0, v0, v0, v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u8(&v0);
#endif
}

inline uint8x16 uint8x16::make_const(uint8_t v0, uint8_t v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v1, v0, v1, v0, v1, v0, v1,
                                v0, v1, v0, v1, v0, v1, v0, v1);
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
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v1, v2, v3, v0, v1, v2, v3,
                                v0, v1, v2, v3, v0, v1, v2, v3);
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
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v0, v1, v2, v3, v4, v5, v6, v7);
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
#elif SIMDPP_USE_ALTIVEC
    return (__vector uint8_t){v0, v1, v2, v3, v4, v5, v6, v7,
                              v8, v9, v10, v11, v12, v13, v14, v15};
#endif
}

inline mask_int8x16::operator basic_int8x16() const
{
#if SIMDPP_USE_NULL
    return null::convert_mask<basic_int8x16>(*this);
#else
    return d_;
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
