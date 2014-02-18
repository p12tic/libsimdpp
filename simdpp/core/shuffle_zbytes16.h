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

#ifndef LIBSIMDPP_SIMDPP_CORE_SHUFFLE_ZBYTES16_H
#define LIBSIMDPP_SIMDPP_CORE_SHUFFLE_ZBYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/shuffle_bytes16.h>
#include <simdpp/core/i_add.h>
#include <simdpp/detail/not_implemented.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Selects bytes from two vectors according to a mask, optionally selecting
    zero. Each byte within the mask defines which element to select:
     * Bit 7 results in the result byte being zeroed, if set.
     * Bits 6-5 must be zero or the behavior is undefined
     * Bit 4 defines which vector to select. 0 corresponds to @a a, 1 to @a b.
     * Bits 3-0 define the element within the selected vector.

    @par 128-bit version:
    @unimp{SSE2-SSE3}
    @icost{SSSE3, 9}
    @icost{SSE4.1-AVX2, 6}
    @icost{XOP, 1}
    @icost{NEON, 2}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.

    @unimp{SSE2-SSE3}
    @icost{SSSE3, 18}
    @icost{SSE4.1-AVX, 12}
    @icost{AVX2, 6}
    @icost{XOP, 2}
    @icost{NEON, 4}
    @icost{ALTIVEC, 2-3}

*/
inline gint8x16 shuffle_zbytes16(gint8x16 a, gint8x16 b, gint8x16 mask)
{
#if SIMDPP_USE_NULL
    uint8x16 ai = a;
    uint8x16 bi = b;
    uint8x16 mi = mask;
    uint8x16 r;

    for (unsigned i = 0; i < 16; i++) {
        unsigned j = mi.el(i) & 0x0f;
        unsigned which = mi.el(i) < 0x10;
        bool zero = mi.el(i) & 0x80;
        r.el(i) = zero ? 0 : (which ? ai.el(j) : bi.el(j));
    }
    return r;
#elif SIMDPP_USE_XOP
    return _mm_perm_epi8(a, b, mask);
#elif SIMDPP_USE_SSE4_1
    int8x16 sel, set_zero, ai, bi, r;
    sel = mask;
    set_zero = cmp_lt(sel, int8x16::zero());
    sel = _mm_slli_epi16(sel, 3);

    ai = _mm_shuffle_epi8(a, mask);
    bi = _mm_shuffle_epi8(b, mask);
    r = _mm_blendv_epi8(ai, bi, sel);
    r = bit_andnot(r, set_zero);
    return r;
#elif SIMDPP_USE_SSSE3
    int8x16 r, m, m1, m2, set_zero, ai, bi;
    m = mask;
    m1 = add(m, int8x16::make_const(0x70));
    m2 = add(m, int8x16::make_const(0xf0));
    set_zero = cmp_lt(m, int8x16::zero());

    ai = _mm_shuffle_epi8(a, m1);
    bi = _mm_shuffle_epi8(b, m2);
    r = bit_or(ai, bi);
    r = bit_andnot(r, set_zero);
    return r;
#elif SIMDPP_USE_NEON
    return shuffle_bytes16(a, b, mask);
#elif SIMDPP_USE_ALTIVEC
    int8x16 a0 = a, b0 = b;
    int8x16 zero_mask = mask;
    zero_mask = shift_r<7>(zero_mask); // shift in the sign bit
    a0 = shuffle_bytes16(a0, b0, mask);
    a0 = bit_andnot(a0, zero_mask);
    return a0;
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, mask);
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32 shuffle_zbytes16(gint8x32 a, gint8x32 b, gint8x32 mask)
{
    int8x32 sel, set_zero, ai, bi, r;
    sel = mask;
    set_zero = cmp_lt(sel, int8x32::zero());
    sel = _mm256_slli_epi16(sel, 3);

    ai = _mm256_shuffle_epi8(a, mask);
    bi = _mm256_shuffle_epi8(b, mask);
    r = _mm256_blendv_epi8(ai, bi, sel);
    r = bit_andnot(r, set_zero);
    return r;
}
#endif

template<unsigned N>
gint8<N> shuffle_zbytes16(gint8<N> a, gint8<N> b, gint8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(gint8<N>, shuffle_zbytes16, a, b, mask);
}

template<unsigned N>
gint16<N> shuffle_zbytes16(gint16<N> a, gint16<N> b, gint16<N> mask)
{
    return shuffle_zbytes16(gint8<N*2>(a), gint8<N*2>(b), gint8<N*2>(mask));
}
template<unsigned N>
gint32<N> shuffle_zbytes16(gint32<N> a, gint32<N> b, gint32<N> mask)
{
    return shuffle_zbytes16(gint8<N*4>(a), gint8<N*4>(b), gint8<N*4>(mask));
}
template<unsigned N>
gint64<N> shuffle_zbytes16(gint64<N> a, gint64<N> b, gint64<N> mask)
{
    return shuffle_zbytes16(gint8<N*8>(a), gint8<N*8>(b), gint8<N*8>(mask));
}
template<unsigned N>
float32<N> shuffle_zbytes16(float32<N> a, float32<N> b, gint32<N> mask)
{
    return float32<N>(shuffle_zbytes16(gint32<N>(a), gint32<N>(b), mask));
}
template<unsigned N>
float64<N> shuffle_zbytes16(float64<N> a, float64<N> b, gint64<N> mask)
{
    return float64<N>(shuffle_zbytes16(gint64<N>(a), gint64<N>(b), mask));
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

