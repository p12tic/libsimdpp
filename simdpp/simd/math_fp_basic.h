/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_MATH_FP_BASIC_H
#define LIBSIMDPP_SIMD_MATH_FP_BASIC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/types.h>
#include <simdpp/simd/bitwise.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_math_fp Operations: floating point maths
/// @{

/** Computes absolute value of floating point values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 1-2}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{NEON, 2}
    @icost{AVX-AVX2, 1-2}
    @icost{ALTIVEC, 2-3}
*/
inline float32x4 abs(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::abs(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return bit_and(a, int32x4::make_const(0x7fffffff));
#elif SIMDPP_USE_NEON_FLT_SP
    return vabsq_f32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_abs((__vector float)a);
#endif
}

inline float32x8 abs(float32x8 a)
{
#if SIMDPP_USE_AVX
    return bit_and(a, int32x8::make_const(0x7fffffff));
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @{

/// @{
/** Computes absolute value of floating point values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-AVX2, 1-2}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX-AVX2, 1-2}
*/
inline float64x2 abs(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::abs(a);
#elif SIMDPP_USE_SSE2
    return bit_and(a, int64x2::make_const(0x7fffffffffffffff));
#endif
}

inline float64x4 abs(float64x4 a)
{
#if SIMDPP_USE_AVX
    return bit_and(a, int64x4::make_const(0x7fffffffffffffff));
#else
    return {abs(a[0]), abs(a[1])};
#endif
}
/// @}

/// @{
/** Extracts sign bits from the values in float32x4 vector

    @code
    r0 = a0 & 0x80000000
    ...
    rN = aN & 0x80000000
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, NEON, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, NEON, 2-3}
    @icost{AVX-AVX2, 1-2}
*/
inline float32x4 sign(float32x4 a)
{
    return bit_and(a, int32x4::make_const(0x80000000));
}

inline float32x8 sign(float32x8 a)
{
    return bit_and(a, int32x8::make_const(0x80000000));
}
/// @}

/// @{
/** Extracts sigh bit from the values in float64x2 vector.

    @code
    r0 = a0 & 0x8000000000000000
    ...
    r0 = aN & 0x8000000000000000
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 1-2}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX-AVX2, 1-2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 sign(float64x2 a)
{
    return bit_and(a, uint64x2::make_const(0x8000000000000000));
}

inline float64x4 sign(float64x4 a)
{
#if SIMDPP_USE_AVX
    return bit_and(a, uint64x4::make_const(0x8000000000000000));
#else
    return {sign(a[0]), sign(a[1])};
#endif
}
/// @}

/// @{
/** Adds the values of two vectors

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 add(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_ps(a, b);
#elif SIMDPP_USE_NEON_FLT_SP
    return vaddq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_add((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 add(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_add_ps(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Adds the values of two vectors

    @code
    r0 = a0 + b0
    ...
    rN = aN + bN
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 add(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_pd(a, b);
#endif
}

inline float64x4 add(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_add_pd(a, b);
#else
    return {add(a[0], b[0]), add(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Substracts the values of two vectors

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 sub(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_ps(a,b);
#elif SIMDPP_USE_NEON_FLT_SP
    return vsubq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_sub((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 sub(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_sub_ps(a, b);
#else
    return {sub(a[0], b[0]), sub(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Subtracts the values of two vectors

    @code
    r0 = a0 - b0
    ...
    rN = aN - bN
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 sub(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_pd(a, b);
#endif
}

inline float64x4 sub(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_sub_pd(a, b);
#else
    return {sub(a[0], b[0]), sub(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Negates the values of a float32x4 vector

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, 2-3}
    @icost{AVX-AVX2, NEON, 2}
*/
inline float32x4 neg(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::neg(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    // reversion of the sign bit required even for NaNs and zeros
    int32x4 zero = int32x4::make_const(0x80000000);
    return bit_xor(a, zero);
#elif SIMDPP_USE_NEON_FLT_SP
    return vnegq_f32(a);
#endif
}

inline float32x8 neg(float32x8 a)
{
#if SIMDPP_USE_AVX
    int32x8 zero = int32x8::make_const(0x80000000);
    return bit_xor(a, zero);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Negates the values of a vector

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 1-2}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX-AVX2, 1-2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 neg(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    int64x2 zero = int64x2::make_const(0x8000000000000000);
    return bit_xor(a, zero);
#endif
}

inline float64x4 neg(float64x4 a)
{
#if SIMDPP_USE_AVX
    int64x4 zero = int64x4::make_const(0x8000000000000000);
    return bit_xor(a, zero);
#else
    return {neg(a[0]), neg(a[1])};
#endif
}
/// @}

/// @{
/** Multiplies the values of two vectors

    @code
    r0 = a0 * b0
    ...
    rN = aN * bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 mul(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mul_ps(a,b);
#elif SIMDPP_USE_NEON_FLT_SP
    return vmulq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_madd((__vector float)a, (__vector float)b,
                    (__vector float)float32x4::zero());
#endif
}

inline float32x8 mul(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_mul_ps(a, b);
#else
    return {mul(a[0], b[0]), mul(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies the values of two vectors

    @code
    r0 = a0 * b0
    ...
    rN = aN * bN
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 mul(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mul_pd(a, b);
#endif
}

inline float64x4 mul(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_mul_pd(a, b);
#else
    return {mul(a[0], b[0]), mul(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Performs a fused multiply-add operation

    @code
    r0 = a0 * b0 + c0
    ...
    rN = aN * bN + cN
    @endcode

    Implemented only on architectures with either @c X86_FMA3 or @c X86_FMA4
    support.
*/
inline float32x4 fmadd(float32x4 a, float32x4 b, float32x4 c)
{
#if SIMDPP_USE_NULL
    return null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_macc_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

inline float32x8 fmadd(float32x8 a, float32x8 b, float32x8 c)
{
#if SIMDPP_USE_AVX
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_macc_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
#else
    return {fmadd(a[0], b[0], c[0]), fmadd(a[1], b[1], c[1])};
#endif
}

inline float64x2 fmadd(float64x2 a, float64x2 b, float64x2 c)
{
#if SIMDPP_USE_NULL
    return null::fmadd(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmadd_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_macc_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

inline float64x4 fmadd(float64x4 a, float64x4 b, float64x4 c)
{
#if SIMDPP_USE_AVX
#if SIMDPP_USE_FMA3
    return _mm256_fmadd_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_macc_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
#else
    return {fmadd(a[0], b[0], c[0]), fmadd(a[1], b[1], c[1])};
#endif
}
/// @}

/// @{
/** Performs a fused multiply-sutract operation

    @code
    r0 = a0 * b0 - c0
    ...
    rN = aN * bN - cN
    @endcode

    Implemented only on architectures with either @c X86_FMA3 or @c X86_FMA4
    support.
*/
inline float32x4 fmsub(float32x4 a, float32x4 b, float32x4 c)
{
#if SIMDPP_USE_NULL
    return null::fmsub(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmsub_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_msub_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

inline float32x8 fmsub(float32x8 a, float32x8 b, float32x8 c)
{
#if SIMDPP_USE_AVX
#if SIMDPP_USE_FMA3
    return _mm256_fmsub_ps(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_msub_ps(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
#else
    return {fmsub(a[0], b[0], c[0]), fmsub(a[1], b[1], c[1])};
#endif
}

inline float64x2 fmsub(float64x2 a, float64x2 b, float64x2 c)
{
#if SIMDPP_USE_NULL
    return null::fmsub(a, b, c);
#elif SIMDPP_USE_FMA3
    return _mm_fmsub_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm_msub_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
}

inline float64x4 fmsub(float64x4 a, float64x4 b, float64x4 c)
{
#if SIMDPP_USE_AVX
#if SIMDPP_USE_FMA3
    return _mm256_fmsub_pd(a, b, c);
#elif SIMDPP_USE_FMA4
    return _mm256_msub_pd(a, b, c);
#else
    return SIMDPP_NOT_IMPLEMENTED3(a, b, c);
#endif
#else
    return {fmsub(a[0], b[0], c[0]), fmsub(a[1], b[1], c[1])};
#endif
}
/// @}

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
