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

#ifndef LIBSIMDPP_SIMDPP_CORE_MOVE_R_H
#define LIBSIMDPP_SIMDPP_CORE_MOVE_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/neon/detail/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Moves the 8-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ a0  a1   .  a14 a15 ]
     1      r = [  0  a0   .  a13 a14 ]
     2      r = [  0   0   .  a12 a13 ]
      ...    ..   .. ..   ...  ..  .. ..
     14     r = [  0   0   .  a0  a1  ]
     15     r = [  0   0   .   0  a0  ]
     16     r = [  0   0   .   0   0  ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
gint8x16 move_r(gint8x16 a)
{
    static_assert(shift <= 16, "Selector out of range");
    if (shift == 0) return a;
    if (shift == 16) return uint8x16::zero();

#if SIMDPP_USE_NULL
    gint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)shift; i++) {
        r[i] = 0;
    }
    for (unsigned i = shift; i < 16; i++) {
        r[i] = a[i - shift];
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_slli_si128(a, shift);
#elif SIMDPP_USE_NEON
    int8x16 z = int8x16::zero();
    return neon::detail::align<16-shift>(z, a);
#elif SIMDPP_USE_ALTIVEC
    // return align<16-shift>(uint8x16::zero(), a);
    return vec_sld((__vector uint8_t)uint8x16::zero(), (__vector uint8_t)a, 16-shift);
#endif
}

template<unsigned shift>
gint8x32 move_r(gint8x32 a)
{
    static_assert(shift <= 16, "Selector out of range");
    if (shift == 0) return a;
    if (shift == 16) return uint8x32::zero();

#if SIMDPP_USE_AVX2
    return _mm256_slli_si256(a, shift);
#else
    return {move_r<shift>(a[0]), move_r<shift>(a[1])};
#endif
}
/// @}

/// @{
/** Moves the 16-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1   . 6  7  |
     0      r = [ a0 a1  . a6 a7 ]
     1      r = [  0 a0  . a5 a6 ]
     2      r = [  0  0  . a4 a5 ]
      ...    ..   .. .. ... .. ..
     6      r = [  0  0  . a0 a1 ]
     7      r = [  0  0  .  0 a0 ]
     8      r = [  0  0  .  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
gint16x8 move_r(gint16x8 a)
{
    return move_r<shift*2>(gint8x16(a));
}

template<unsigned shift>
gint16x16 move_r(gint16x16 a)
{
    return move_r<shift*2>(gint8x32(a));
}
/// @}

/// @{
/** Moves the 32-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [  0 a0 a1 a2 ]
     2      r = [  0  0 a0 a1 ]
     3      r = [  0  0  0 a0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
gint32x4 move_r(gint32x4 a)
{
    return move_r<shift*4>(gint8x16(a));
}

template<unsigned shift>
gint32x8 move_r(gint32x8 a)
{
    return move_r<shift*4>(gint8x32(a));
}
/// @}

/// @{
/** Moves the 64-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [  0 a0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
gint64x2 move_r(gint64x2 a)
{
    return move_r<shift*8>(gint8x16(a));
}

template<unsigned shift>
gint64x4 move_r(gint64x4 a)
{
    return move_r<shift*8>(gint8x32(a));
}
/// @}

/// @{
/** Moves the 32-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [  0 a0 a1 a2 ]
     2      r = [  0  0 a0 a1 ]
     3      r = [  0  0  0 a0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float32x4 move_r(float32x4 a)
{
    return float32x4(move_r<shift>(gint32x4(a)));
}

template<unsigned shift>
float32x8 move_r(float32x8 a)
{
    return float32x8(move_r<shift>(gint32x8(a)));
}
/// @}

/// @{
/** Moves the 64-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [  0 a0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift>
float64x2 move_r(float64x2 a)
{
    return float64x2(move_r<shift>(gint64x2(a)));
}

template<unsigned shift>
float64x4 move_r(float64x4 a)
{
    return float64x4(move_r<shift>(gint64x4(a)));
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

