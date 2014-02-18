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

#ifndef LIBSIMDPP_SIMDPP_CORE_ALIGN_H
#define LIBSIMDPP_SIMDPP_CORE_ALIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/move_r.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Extracts a int8x16 vector from two concatenated int8x16 vectors

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ l0  l1   .  l14 l15 ]
     1      r = [ l1  l2   .  l15 u0  ]
     2      r = [ l2  l3   .  u0  l1  ]
      ...    ..   .. ..  ... .. ..
     15     r = [ l15 u0   .  u13 u14 ]
     16     r = [ u0  u1   .  u14 u15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
gint8x16 align(gint8x16 lower, gint8x16 upper)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return lower;
    if (shift == 16) return upper;

#if SIMDPP_USE_NULL
    gint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)(16-shift); i++) {
        r.el(i) = lower.el(i + shift);
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r.el(i) = upper.el(i - 16 + shift);
    }
    return r;
#elif SIMDPP_USE_SSSE3
    return _mm_alignr_epi8(upper, lower, shift);
#elif SIMDPP_USE_SSE2
    gint8x16 a;
    lower = move_l<shift>(lower);
    upper = move_r<16-shift>(upper);
    a = bit_or(upper, lower);
    return a;
#elif SIMDPP_USE_NEON
    return neon::detail::align<shift>(lower, upper);
#elif SIMDPP_USE_ALTIVEC
    return vec_sld((__vector uint8_t)lower, (__vector uint8_t)upper, (unsigned)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
gint8x32 align(gint8x32 lower, gint8x32 upper)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return lower;
    if (shift == 16) return upper;

    return _mm256_alignr_epi8(upper, lower, shift);
}
#endif

template<unsigned shift, unsigned N>
gint8<N> align(gint8<N> lower, gint8<N> upper)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return lower;
    if (shift == 16) return upper;

    SIMDPP_VEC_ARRAY_IMPL2(gint8<N>, align<shift>, lower, upper);
}
/// @}

/** Extracts a int16x8 vector from two concatenated int16x8 vectors

    @code
    shift:  pos:| 0  1    .  6  7  |
     0      r = [ l0 l1   .  l6 l7 ]
     1      r = [ l1 l2   .  l7 u0 ]
     2      r = [ l2 l3   .  u0 l1 ]
      ...    ..   .. ..  ... .. ..
     7      r = [ l3 u0   .  u5 u6 ]
     8      r = [ u0 u1   .  u6 u7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N>
gint16<N> align(gint16<N> lower, gint16<N> upper)
{
    static_assert(shift <= 8, "Shift out of bounds");
    return align<shift*2>(gint8<N*2>(lower), gint8<N*2>(upper));
}

/** Extracts a int32x4 vector from two concatenated int32x4 vectors

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ l0 l1 l2 l3 ]
     1      r = [ l1 l2 l3 u0 ]
     2      r = [ l2 l3 u0 u1 ]
     3      r = [ l3 u0 u1 u2 ]
     4      r = [ u0 u1 u2 u3 ]
    @endcode

   @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N>
gint32<N> align(gint32<N> lower, gint32<N> upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    return align<shift*4>(gint8<N*4>(lower), gint8<N*4>(upper));
}

/** Extracts a int64x2 vector from two concatenated int64x2 vectors

    @code
    shift:  pos:| 0  1  |
     0      r = [ l0 l1 ]
     1      r = [ l1 u0 ]
     2      r = [ u0 u1 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N>
gint64<N> align(gint64<N> lower, gint64<N> upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    return align<shift*8>(gint8<N*8>(lower), gint8<N*8>(upper));
}

/** Extracts a float32x4 vector from two concatenated float32x4 vectors

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ l0 l1 l2 l3 ]
     1      r = [ l1 l2 l3 u0 ]
     2      r = [ l2 l3 u0 u1 ]
     3      r = [ l3 u0 u1 u2 ]
     4      r = [ u0 u1 u2 u3 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-SSE4.1 NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N>
float32<N> align(float32<N> lower, float32<N> upper)
{
    static_assert(shift <= 4, "Shift out of bounds");
    return float32<N>(align<shift>(gint32<N>(lower),
                                   gint32<N>(upper)));
}

/** Extracts a float64x2 vector from two concatenated float64x2 vectors

    @code
    shift:  pos:| 0  1  |
     0      r = [ l0 l1 ]
     1      r = [ l1 u0 ]
     2      r = [ u0 u1 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned shift, unsigned N>
float64<N> align(float64<N> lower, float64<N> upper)
{
    static_assert(shift <= 2, "Shift out of bounds");
    return float64<N>(align<shift>(gint64<N>(lower),
                                   gint64<N>(upper)));
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

