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

#ifndef LIBSIMDPP_SIMDPP_CORE_STORE_FIRST_H
#define LIBSIMDPP_SIMDPP_CORE_STORE_FIRST_H

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

// Multi-vector store_first is mostly boilerplate
template<class P, class V>
void v_store_first(P* p, V a, unsigned n)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);

    unsigned n_full_vec = n / V::length;
    unsigned mid_vec_fill_count = n % V::length;
    unsigned curr_vec = 0;

    for (; curr_vec < n_full_vec; ++curr_vec) {
        store(p, a[curr_vec]);
        p += veclen / sizeof(P);
    }

    if (mid_vec_fill_count > 0) {
        store_first(p, a[curr_vec], mid_vec_fill_count);
    }
}

} // namespace defail


/// @{
/** Stores the first @a n elements of an 128-bit or 256-bit integer, 32-bit or
    64-bit floating point vector to memory. @a n must be in range [0..N-1]
    where @a N is the number of elements in the vector. If @a n is zero, no
    store is made.

    The function may write entire block of 128 or 256 bits.

    @code
    *(p) = a0
    *(p+1) = a1
    ...
    *(p+n-1) = a{n-1}
    @endcode

    This function results in several instructions. It is best not to use it in
    inner loops.

    @par 128-bit version:
    @a p must be aligned to 16 bytes.
    @par 256-bit version:
    @a p must be aligned to 32 bytes.
*/
inline void store_first(void* p, gint8x16 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    static const uint8_t mask_d[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0};

    gint8x16 mask = load_u(mask, mask_d + 16 - n);
    gint8x16 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
#endif
}

#if SIMDPP_USE_AVX2
inline void store_first(void* p, gint8x32 a, unsigned n)
{
    static const uint8_t mask_d[64] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0};

    gint8x32 mask = load_u(mask, mask_d + 32 - n);
    gint8x32 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void store_first(void* p, gint8<N> a, unsigned n)
{
    detail::v_store_first(reinterpret_cast<char*>(p), a, n);
}

// 16 bits

inline void store_first(void* p, gint16x8 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    store_first(p, (gint8x16)a, n*2);
#endif
}

#if SIMDPP_USE_AVX2
inline void store_first(void* p, gint16x16 a, unsigned n)
{
    store_first(p, gint8x32(a), n*2);
}
#endif

template<unsigned N>
void store_first(void* p, gint16<N> a, unsigned n)
{
    detail::v_store_first(reinterpret_cast<char*>(p), a, n);
}

// 32 bits

inline void store_first(void* p, gint32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    store_first(p, (gint8x16)a, n*4);
#endif
}

#if SIMDPP_USE_AVX2
inline void store_first(void* p, gint32x8 a, unsigned n)
{
    store_first(p, gint8x32(a), n*4);
}
#endif

template<unsigned N>
void store_first(void* p, gint32<N> a, unsigned n)
{
    detail::v_store_first(reinterpret_cast<char*>(p), a, n);
}

// 64 bits

inline void store_first(void* p, gint64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_NEON
    if (n == 1) {
        neon::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_ALTIVEC
    char* q = reinterpret_cast<char*>(p);
    if (n == 1) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(q));
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(q));
    }
#endif
}

#if SIMDPP_USE_AVX2
inline void store_first(void* p, gint64x4 a, unsigned n)
{
    store_first(p, gint8x32(a), n*8);
}
#endif

template<unsigned N>
void store_first(void* p, gint64<N> a, unsigned n)
{
    detail::v_store_first(reinterpret_cast<char*>(p), a, n);
}

// 32 bits float

inline void store_first(float* p, float32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON_FLT_SP
    store_first(p, int32x4{a}, n);
#elif SIMDPP_USE_SSE2
    static const uint32_t mask_d[8] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                       0x00000000, 0x00000000, 0x00000000, 0x00000000};

    const float* mask_dp = reinterpret_cast<const float*>(mask_d);
    float32x4 mask = load_u(mask, mask_dp + 4-n);
    float32x4 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
#elif SIMDPP_USE_NEON
    // + VFP
    if (n < 1) return;
    neon::store_lane<0,1>(p, a);
    if (n < 2) return;
    neon::store_lane<1,1>(p, a);
    if (n < 3) return;
    neon::store_lane<2,1>(p, a);
#endif
}

#if SIMDPP_USE_AVX2
inline void store_first(float* p, float32x8 a, unsigned n)
{
    static const uint32_t mask_d[16] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                        0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                        0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                        0x00000000, 0x00000000, 0x00000000, 0x00000000};

    const float* mask_dp = reinterpret_cast<const float*>(mask_d);
    float32x8 mask = load_u(mask, mask_dp + 8-n);
    float32x8 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void store_first(float* p, float32<N> a, unsigned n)
{
    detail::v_store_first(p, a, n);
}

// 64 bit float

inline void store_first(double* p, float64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#endif
}

#if SIMDPP_USE_AVX2
inline void store_first(double* p, float64x4 a, unsigned n)
{
    static const uint64_t mask_d[16] = {0xffffffffffffffff, 0xffffffffffffffff,
                                        0xffffffffffffffff, 0xffffffffffffffff,
                                        0x0000000000000000, 0x0000000000000000,
                                        0x0000000000000000, 0x0000000000000000};

    const double* mask_dp = reinterpret_cast<const double*>(mask_d);
    float64x4 mask = load_u(mask, mask_dp + 4-n);
    float64x4 old = load(old, p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void store_first(double* p, float64<N> a, unsigned n)
{
    detail::v_store_first(p, a, n);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

