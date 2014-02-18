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

#ifndef LIBSIMDPP_SIMDPP_CORE_STORE_LAST_H
#define LIBSIMDPP_SIMDPP_CORE_STORE_LAST_H

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
// The 256-bit store_first and store_last are mostly boilerplate.

// hsz - the number of elements in the half-vector
template<unsigned hsz, class P, class V>
void v256_store_last(P* p, V a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_SSE2
    if (n >= hsz) {
        store_last(p, sse::extract_lo(a), n - hsz);
        store(p + 16 / sizeof(P), sse::extract_hi(a));
    } else {
        store_last(p + 16 / sizeof(P), sse::extract_hi(a), n);
    }
#else
    if (n >= hsz) {
        store_last(p, a[0], n - hsz);
        store(p + 16 / sizeof(P), a[1]);
    } else {
        store_last(p + 16 / sizeof(P), a[1], n);
    }
#endif
}

} // namespace detail

/// @{
/** Stores the last @a n elements of an 128-bit or 256-bit integer, 32-bit or
    64-bit floating point vector to memory. @a n must be in range [0..N-1]
    where @a N is the number of elements in the vector. If @a n is zero, no
    store is made.

    The function may write entire block of 128 or 256 bits.

    @code
    *(p+N-n) = a{N-n}
    ...
    *(p+N-2) = a{N-2}
    *(p+N-1) = a{N-1}
    @endcode

    This function results in several instructions. It is best not to use it in
    inner loops.

    @par 128-bit version:
    @a p must be aligned to 16 bytes.
    @par 256-bit version:
    @a p must be aligned to 32 bytes.
*/
inline void store_last(void* p, gint8x16 a, unsigned n)
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

inline void store_last(void* p, gint8x32 a, unsigned n)
{
    detail::v256_store_last<16>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, gint16x8 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    store_last(p, (gint8x16)a, n*2);
#endif
}

inline void store_last(void* p, gint16x16 a, unsigned n)
{
    detail::v256_store_last<8>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, gint32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::store_last(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    store_last(p, (gint8x16)a, n*4);
#endif
}

inline void store_last(void* p, gint32x8 a, unsigned n)
{
    detail::v256_store_last<4>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(void* p, gint64x2 a, unsigned n)
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

inline void store_last(void* p, gint64x4 a, unsigned n)
{
    detail::v256_store_last<2>(reinterpret_cast<char*>(p), a, n);
}

inline void store_last(float* p, float32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON_FLT_SP
    store_last(p, int32x4{a}, n);
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

inline void store_last(float* p, float32x8 a, unsigned n)
{
    detail::v256_store_last<4>(p, a, n);
}

inline void store_last(double* p, float64x2 a, unsigned n)
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

inline void store_last(double* p, float64x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    switch (n) {
    case 3:
        sse::store_lane<1,1>(p+1, sse::extract_lo(a));
        store(p+2, sse::extract_hi(a));
        return;
    case 2:
        store(p+2, sse::extract_hi(a));
        return;
    case 1:
        sse::store_lane<1,1>(p+3, sse::extract_hi(a));
        return;
    }
#else
    detail::v256_store_last<2>(p, a, n);
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

