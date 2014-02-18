/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_LAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_LAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/load.h>
#include <simdpp/core/load_u.h>
#include <simdpp/core/store.h>
#include <simdpp/neon/memory_store.h>
#include <simdpp/null/memory.h>
#include <simdpp/sse/extract_half.h>
#include <simdpp/sse/memory_store.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// Multi-vector i_store_last is mostly boilerplate
template<class P, class V>
void v_store_last(P* p, V a, unsigned n);

// -----------------------------------------------------------------------------

inline void i_store_last(void* p, gint8x16 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    static const uint8_t mask_d[32] = {0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

    gint8x16 mask = load_u(mask, mask_d + n);
    gint8x16 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_last(void* p, gint8x32 a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
    static const uint8_t mask_d[64] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    gint8x32 mask = load_u(mask, mask_d + n);
    gint8x32 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void i_store_last(void* p, gint8<N> a, unsigned n)
{
    v_store_last(reinterpret_cast<char*>(p), a, n);
}

// -----------------------------------------------------------------------------
// 16 bits

inline void i_store_last(void* p, gint16x8 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_last(p, (gint8x16)a, n*2);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_last(void* p, gint16x16 a, unsigned n)
{
    i_store_last(p, gint8x32(a), n*2);
}
#endif

template<unsigned N>
void i_store_last(void* p, gint16<N> a, unsigned n)
{
    v_store_last(reinterpret_cast<char*>(p), a, n);
}

// -----------------------------------------------------------------------------
// 32 bits

inline void i_store_last(void* p, gint32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_last(p, (gint8x16)a, n*4);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_last(void* p, gint32x8 a, unsigned n)
{
    i_store_last(p, gint8x32(a), n*4);
}
#endif

template<unsigned N>
void i_store_last(void* p, gint32<N> a, unsigned n)
{
    v_store_last(reinterpret_cast<char*>(p), a, n);
}

// -----------------------------------------------------------------------------
// 64 bits

inline void i_store_last(void* p, gint64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        sse::store_lane<1,1>(q+8, a);
    }
#elif SIMDPP_USE_NEON
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        neon::store_lane<1,1>(q+8, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        vec_ste((__vector uint32_t)a, 8, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 12, reinterpret_cast<uint32_t*>(q));
    }
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_last(void* p, gint64x4 a, unsigned n)
{
    i_store_last(p, gint8x32(a), n*2);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned N>
void i_store_last(void* p, gint64<N> a, unsigned n)
{
    v_store_last(reinterpret_cast<char*>(p), a, n);
}

inline void i_store_last(float* p, float32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON_FLT_SP
    i_store_last(p, int32x4{a}, n);
#elif SIMDPP_USE_SSE2
    static const uint32_t mask_d[8] = {0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                       0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

    const float* mask_dp = reinterpret_cast<const float*>(mask_d);
    float32x4 mask = load_u(mask, mask_dp + n);
    float32x4 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
#elif SIMDPP_USE_NEON
    // + VFP
    if (n < 1) return;
    neon::store_lane<3,1>(p+3, a);
    if (n < 2) return;
    neon::store_lane<2,1>(p+2, a);
    if (n < 3) return;
    neon::store_lane<1,1>(p+1, a);
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_last(float* p, float32x8 a, unsigned n)
{
    static const uint32_t mask_d[16] = {0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                        0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                        0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                        0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

    const float* mask_dp = reinterpret_cast<const float*>(mask_d);
    float32x8 mask = load_u(mask, mask_dp + n);
    float32x8 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void i_store_last(float* p, float32<N> a, unsigned n)
{
    v_store_last(p, a, n);
}

// -----------------------------------------------------------------------------

inline void i_store_last(double* p, float64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<1,1>(p+1, a);
    }
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_last(double* p, float64x4 a, unsigned n)
{
    static const uint64_t mask_d[16] = {0x0000000000000000, 0x0000000000000000,
                                        0x0000000000000000, 0x0000000000000000,
                                        0xffffffffffffffff, 0xffffffffffffffff,
                                        0xffffffffffffffff, 0xffffffffffffffff};

    const double* mask_dp = reinterpret_cast<const double*>(mask_d);
    float64x4 mask = load_u(mask, mask_dp + n);
    float64x4 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void i_store_last(double* p, float64<N> a, unsigned n)
{
    v_store_last(p, a, n);
}

// -----------------------------------------------------------------------------

template<class P, class V>
void v_store_last(P* p, V a, unsigned n)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    unsigned el_to_skip = V::length - n;

    unsigned n_empty_vec = el_to_skip / V::base_vector_type::length;
    unsigned mid_vec_skip_count = n % V::base_vector_type::length;
    unsigned curr_vec = 0;

    p += n_empty_vec * veclen / sizeof(P);
    curr_vec += n_empty_vec;
    if (mid_vec_skip_count > 0) {
        i_store_last(p, a[curr_vec], mid_vec_skip_count);
        p += veclen / sizeof(P);
        curr_vec++;
    }

    for (; curr_vec < V::vec_length; ++curr_vec) {
        i_store(p, a[curr_vec]);
        p += veclen / sizeof(P);
    }
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

