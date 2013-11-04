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

#ifndef LIBSIMDPP_SIMD_INT16X8_INL
#define LIBSIMDPP_SIMD_INT16X8_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline int16x8 int16x8::zero()
{
    return int128::zero();
}

inline int16x8 int16x8::load_broadcast(const int16_t* v0)
{
    return uint16x8::load_broadcast(reinterpret_cast<const uint16_t*>(v0));
}

inline int16x8 int16x8::set_broadcast(int16_t v0)
{
    return uint16x8::set_broadcast(v0);
}

inline int16x8 int16x8::make_const(int16_t v0)
{
    return uint16x8::make_const(v0);
}

inline int16x8 int16x8::make_const(int16_t v0, int16_t v1)
{
    return uint16x8::make_const(v0, v1);
}

inline int16x8 int16x8::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3)
{
    return uint16x8::make_const(v0, v1, v2, v3);
}

inline int16x8 int16x8::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                                   int16_t v4, int16_t v5, int16_t v6, int16_t v7)
{
    return uint16x8::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline uint16x8 uint16x8::zero()
{
    return int128::zero();
}

inline uint16x8 uint16x8::load_broadcast(const uint16_t* v0)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint16x8>(*v0);
#elif SIMDPP_USE_SSE2
    return uint16x8::set_broadcast(*v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u16(v0);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 r = altivec::load1_u(r, v0);
    r = broadcast_w<0>(r);
    return r;
#endif
}

inline uint16x8 uint16x8::set_broadcast(uint16_t v0)
{
#if SIMDPP_USE_NULL
    return uint16x8::load_broadcast(&v0);
#elif SIMDPP_USE_SSE2
    uint32_t u0;
    u0 = v0 | v0 << 16;
    return uint32x4::set_broadcast(u0);
#elif SIMDPP_USE_NEON
    return vdupq_n_u16(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint16_t v[8];
        uint16x8 align;
    };
    v[0] = v0;
    uint16x8 r = altivec::load1(r, v);
    r = broadcast_w<0>(r);
    return r;
#endif
}

inline uint16x8 uint16x8::make_const(uint16_t v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint16x8::make_const(v0, v0, v0, v0, v0, v0, v0, v0);
#elif SIMDPP_USE_NEON
    return vld1q_dup_u16(&v0);
#endif
}

inline uint16x8 uint16x8::make_const(uint16_t v0, uint16_t v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint16x8::make_const(v0, v1, v0, v1, v0, v1, v0, v1);
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

inline uint16x8 uint16x8::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint16x8::make_const(v0, v1, v2, v3, v0, v1, v2, v3);
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

inline uint16x8 uint16x8::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
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
#elif SIMDPP_USE_ALTIVEC
    return (__vector uint16_t){v0, v1, v2, v3, v4, v5, v6, v7};
#endif
}

inline mask_int16x8::operator basic_int16x8() const
{
#if SIMDPP_USE_NULL
    return null::convert_mask<basic_int16x8>(*this);
#else
    return d_;
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
