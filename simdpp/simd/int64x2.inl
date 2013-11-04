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

#ifndef LIBSIMDPP_SIMD_INT64X2_INL
#define LIBSIMDPP_SIMD_INT64X2_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/simd/detail/word_size.h>
#include <simdpp/simd/detail/mem_block.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline basic_int64x2::basic_int64x2(const float64x2& d)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<basic_int64x2> ax;
    ax[0] = bit_cast<uint64_t>(d[0]);
    ax[1] = bit_cast<uint64_t>(d[1]);
    operator=(basic_int64x2(ax));
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
#elif SIMDPP_USE_ALTIVEC
    return uint64x2::set_broadcast(*v0);
#endif
}

inline uint64x2 uint64x2::set_broadcast(uint64_t v0)
{
#if SIMDPP_USE_NULL
    return uint64x2::load_broadcast(&v0);
#elif SIMDPP_USE_SSE2
#if SIMDPP_SSE_32_BITS
    uint32x4 va = _mm_cvtsi32_si128(uint32_t(v0));
    uint32x4 vb = _mm_cvtsi32_si128(uint32_t(v0 >> 32));
    uint64x2 vx = zip_lo(va, vb);
    return permute<0,0>(vx);
#else
    int32x4 ra = _mm_cvtsi32_si128(uint32_t(v0));
    int32x4 rb = _mm_cvtsi32_si128(uint32_t(v0 >> 32));
    int64x2 r0 = zip_lo(ra, rb);
    r0 = permute<0,0>(r0);
    return uint64x2(r0);
#endif
#elif SIMDPP_USE_NEON
    return vdupq_n_u64(v0);
#elif SIMDPP_USE_ALTIVEC
    union {
        uint64_t v[2];
        uint64x2 align;
    };
    v[0] = v0;
    uint64x2 r = load(r, v);
    r = broadcast_w<0>(r);
    return r;
#endif
}

inline uint64x2 uint64x2::make_const(uint64_t v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint64x2::make_const(v0, v0);
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
#elif SIMDPP_USE_ALTIVEC
    return uint32x4::make_const(v0 >> 32, v0, v1 >> 32, v1); // big endian
#endif
}

inline mask_int64x2::operator basic_int64x2() const
{
#if SIMDPP_USE_NULL
    return null::convert_mask<basic_int64x2>(*this);
#else
    return d_;
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
