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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SUB_H
#define LIBSIMDPP_SIMDPP_CORE_I_SUB_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Subtracts 8-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint8x16 sub(gint8x16 a, gint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi8(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32 sub(gint8x32 a, gint8x32 b)
{
    return _mm256_sub_epi8(a, b);
}
#endif

template<unsigned N>
gint8<N> sub(gint8<N> a, gint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint8<N>, sub, a, b);
}
/// @}

/// @{
/** Subtracts 16-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint16x8 sub(gint16x8 a, gint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi16(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint16x16 sub(gint16x16 a, gint16x16 b)
{
    return _mm256_sub_epi16(a, b);
}
#endif

template<unsigned N>
gint16<N> sub(gint16<N> a, gint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint16<N>, sub, a, b);
}
/// @}

/// @{
/** Subtracts 32-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline gint32x4 sub(gint32x4 a, gint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline gint32x8 sub(gint32x8 a, gint32x8 b)
{
    return _mm256_sub_epi32(a, b);
}
#endif

template<unsigned N>
gint32<N> sub(gint32<N> a, gint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint32<N>, sub, a, b);
}
/// @}

/// @{
/** Subtracts 64-bit integer values.

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 5-6}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 10-11}
*/
inline gint64x2 sub(gint64x2 a, gint64x2 b)
{
#if SIMDPP_USE_NULL
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_epi64(a, b);
#elif SIMDPP_USE_NEON
    return vsubq_u64(a, b);
#else
    uint64x2 c1 = uint64x2::make_const(1);
    uint32x4 r, carry;
    carry = vec_subc((__vector uint32_t) a, (__vector uint32_t) b);
    carry = move_l<1>(carry);
    r = sub((uint32x4)a, (uint32x4)b);
    carry = bit_and(carry, c1);
    r = sub(r, carry);
    return r;
#endif
}

#if SIMDPP_USE_AVX2
inline gint64x4 sub(gint64x4 a, gint64x4 b)
{
    return _mm256_sub_epi64(a, b);
}
#endif

template<unsigned N>
gint64<N> sub(gint64<N> a, gint64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(gint64<N>, sub, a, b);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

