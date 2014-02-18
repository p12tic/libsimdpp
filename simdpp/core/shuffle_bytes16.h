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

#ifndef LIBSIMDPP_SIMDPP_CORE_SHUFFLE_BYTES16_H
#define LIBSIMDPP_SIMDPP_CORE_SHUFFLE_BYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/i_add.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Selects bytes from two vectors according to a mask. Each byte within the
    mask defines which element to select:
     * Bits 7-5 must be zero or the behavior is undefined
     * Bit 4 defines which vector to select. 0 corresponds to @a a, 1 to @a b.
     * Bits 3-0 define the element within the selected vector.

    @par 128-bit version:
    @unimp{SSE2-SSE3}
    @icost{SSSE3, 6}
    @icost{SSE4.1-AVX2, 4}
    @icost{XOP, 1}
    @icost{NEON, 2}

    @par 256-bit version:
    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.

    @unimp{SSE2-SSE3}
    @icost{SSSE3, 12}
    @icost{SSE4.1-AVX, 8}
    @icost{XOP, 2}
    @icost{NEON, 4}
    @icost{ALTIVEC, 2}

*/
inline int128 shuffle_bytes16(int128 a, int128 b, int128 mask)
{
#if SIMDPP_USE_NULL
    uint8x16 ai = a;
    uint8x16 bi = b;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi[i] & 0x0f;
        unsigned which = mi[i] < 0x10;
        r[i] = which ? ai[j] : bi[j];
    }
    return r;
#elif SIMDPP_USE_XOP
    return _mm_perm_epi8(a, b, mask);
#elif SIMDPP_USE_SSE4_1
    int16x8 sel, ai, bi, r;
    sel = mask;
    sel = _mm_slli_epi16(sel, 3);

    ai = _mm_shuffle_epi8(a, mask);
    bi = _mm_shuffle_epi8(b, mask);
    r = _mm_blendv_epi8(ai, bi, sel);
    return r;
#elif SIMDPP_USE_SSSE3
    uint8x16 m, m1, m2, ai, bi;
    m = mask;
    // sets the 7-th bit if we want an element from the other vector
    m1 = add(m, uint8x16::make_const(0x70));
    m2 = add(m, uint8x16::make_const(0xf0));

    ai = _mm_shuffle_epi8(a, m1);
    bi = _mm_shuffle_epi8(b, m2);
    return bit_or(ai, bi);
#elif SIMDPP_USE_NEON
    uint8x8x4_t table = {{vget_low_u8(a), vget_high_u8(a),
                          vget_low_u8(b), vget_high_u8(b)}};
    uint8x8_t lo = vtbl4_u8(table, vget_low_u8(mask));
    uint8x8_t hi = vtbl4_u8(table, vget_high_u8(mask));
    return vcombine_u8(lo, hi);
#elif SIMDPP_USE_ALTIVEC
    return vec_perm((__vector uint8_t)a, (__vector uint8_t)b,
                    (__vector uint8_t)mask);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, mask);
#endif
}

inline float32x4 shuffle_bytes16(float32x4 a, float32x4 b, int128 mask)
{
    int32x4 r = shuffle_bytes16(int32x4(a), int32x4(b), mask);
    return float32x4(r);
}

inline float64x2 shuffle_bytes16(float64x2 a, float64x2 b, int128 mask)
{
    int64x2 r = shuffle_bytes16(int64x2(a), int64x2(b), mask);
    return float64x2(r);
}

inline int256 shuffle_bytes16(int256 a, int256 b, int256 mask)
{
#if SIMDPP_USE_AVX2
    int16x16 sel, ai, bi, r;
    sel = mask;
    sel = _mm256_slli_epi16(sel, 3); // the top 3 bits are already clear

    ai = _mm256_shuffle_epi8(a, mask);
    bi = _mm256_shuffle_epi8(b, mask);
    r = _mm256_blendv_epi8(ai, bi, sel);
    return r;
#else
    return {shuffle_bytes16(a[0], b[0], mask[0]), shuffle_bytes16(a[1], b[1], mask[1])};
#endif
}

inline float32x8 shuffle_bytes16(float32x8 a, float32x8 b, int256 mask)
{
    int32x8 r = shuffle_bytes16(int32x8(a), int32x8(b), mask);
    return float32x8(r);
}

inline float64x4 shuffle_bytes16(float64x4 a, float64x4 b, int256 mask)
{
    int64x4 r = shuffle_bytes16(int64x4(a), int64x4(b), mask);
    return float64x4(r);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

