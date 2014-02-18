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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_CMP_NEQ_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_CMP_NEQ_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/functions/bit_not.h>
#include <simdpp/functions/cmp_eq.h>
#include <simdpp/simd/detail/not_implemented.h>
#include <simdpp/null/compare.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Compares the values of two int8x16 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xff : 0x0
    ...
    rN = (aN != bN) ? 0xff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
inline mask_int8x16 cmp_neq(basic_int8x16 a, basic_int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi8(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_int8x32 cmp_neq(basic_int8x32 a, basic_int8x32 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return { cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]) };
#endif
}
/// @}

/// @{
/** Compares the values of two int16x8 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffff : 0x0
    ...
    rN = (aN != bN) ? 0xffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
inline mask_int16x8 cmp_neq(basic_int16x8 a, basic_int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi16(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_int16x16 cmp_neq(basic_int16x16 a, basic_int16x16 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return { cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]) };
#endif
}
/// @}

/// @{
/** Compares the values of two int32x4 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
    @icost{XOP, 1}

    @par 256-bit version
    @icost{SSE2-AVX, NEON, ALTIVEC, 4}
    @icost{AVX2, 2}
    @icost{XOP, 2}
*/
inline mask_int32x4 cmp_neq(basic_int32x4 a, basic_int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi32(a, b);
#else
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_int32x8 cmp_neq(basic_int32x8 a, basic_int32x8 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return { cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1]) };
#endif
}
/// @}

/// @{
/** Compares the values of two int64x2 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1, AVX, 2}
    @icost{XOP, 1}
    @icost{NEON, 4}
    @icost{ALTIVEC, 3-5}

    @par 256-bit version:
    @icost{SSE2-SSSE3, AVX, 10}
    @icost{SSE4.1, NEON, 4}
    @icost{AVX2, XOP, 2}
    @icost{NEON, 8}
    @icost{ALTIVEC, 6-8}
*/
inline mask_int64x2 cmp_neq(basic_int64x2 a, basic_int64x2 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_XOP
    return _mm_comneq_epi64(a, b);
#elif SIMDPP_USE_SSE4_1 || SIMDPP_USE_NEON
    return bit_not(cmp_eq(a, b));
#elif SIMDPP_USE_SSE2
    uint64x2 r32, r32s;
    r32 = cmp_eq(uint32x4(a), uint32x4(b));
    // swap the 32-bit halves
    r32s = bit_or(shift_l<32>(r32), shift_r<32>(r32));
    // combine the results. Each 32-bit half is ORed with the neighbouring pair
    r32 = bit_or(r32, r32s);
    return r32;
#elif SIMDPP_USE_ALTIVEC
    uint16x8 mask = make_shuffle_bytes16_mask<0, 2, 1, 3>(mask);
    uint32x4 a0, b0, r, ones;
    ones = int128::ones();

    a0 = a;  b0 = b;
    r = cmp_eq(a, b);
    r = permute_bytes16(uint16x8(a), mask);
    r = cmp_eq(r, ones);
    return r;
#endif
}

inline mask_int64x4 cmp_neq(basic_int64x4 a, basic_int64x4 b)
{
#if SIMDPP_USE_AVX2
    return bit_not(cmp_eq(a, b));
#else
    return {cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float32x4 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffff : 0x0
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 2}

    @par 256-bit version
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, ALTIVEC, 4}
*/
inline mask_float32x4 cmp_neq(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_ps(a, b);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return bit_not(cmp_eq(a, b));
#endif
}

inline mask_float32x8 cmp_neq(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_NEQ_UQ);
#else
    return {cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Compares the values of two float64x2 vectors for inequality

    @code
    r0 = (a0 != b0) ? 0xffffffffffffffff : 0x0
    ...
    rN = (aN != bN) ? 0xffffffffffffffff : 0x0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 cmp_neq(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::cmp_neq(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_NEQ_UQ);
#elif SIMDPP_USE_SSE2
    return _mm_cmpneq_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline mask_float64x4 cmp_neq(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_NEQ_UQ);
#else
    return {cmp_neq(a[0], b[0]), cmp_neq(a[1], b[1])};
#endif
}
/// @}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

