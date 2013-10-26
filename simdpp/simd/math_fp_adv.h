/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_MATH_FP_ADV_H
#define LIBSIMDPP_SIMD_MATH_FP_ADV_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/types.h>
#include <simdpp/simd/compare.h>
#include <simdpp/simd/math_fp_basic.h>
#include <simdpp/simd/math_shift.h>
#include <simdpp/simd/convert.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    #include <cmath>
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_math_fp
/// @{

/// @{
/** Checks whether elements in @a a are IEEE754 NaN.

    @code
    r0 = isnan(a0) ? 0xffffffff : 0
    ...
    rN = isnan(aN) ? 0xffffffff : 0
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline mask_float32x4 isnan(float32x4 a)
{
#if SIMDPP_USE_NULL
    return null::isnan(a);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, a, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return (mask_float32x4) _mm_cmpunord_ps(a, a);
#elif SIMDPP_USE_NEON
    return vceqq_f32(a, a);
#elif SIMDPP_USE_ALTIVEC
    return (mask_float32x4) vec_cmpeq((__vector float)a, (__vector float)a);
#endif
}

inline mask_float32x8 isnan(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, a, _CMP_UNORD_Q);
#else
    return {isnan(a[0]), isnan(a[1])};
#endif
}
/// @}

/// @{
/** Checks whether elements in @a a are IEEE754 NaN.

    @code
    r0 = isnan(a0) ? 0xffffffffffffffff : 0
    ...
    rN = isnan(aN) ? 0xffffffffffffffff : 0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 isnan(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::isnan(a);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, a, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return _mm_cmpunord_pd(a, a);
#endif
}

inline mask_float64x4 isnan(float64x4 a)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, a, _CMP_UNORD_Q);
#else
    return {isnan(a[0]), isnan(a[1])};
#endif
}
/// @}

/// @{
/** Checks whether corresponding elements in either @a a or @a b are IEEE754 NaN.

    @code
    r0 = isnan(a0) || isnan(b0) ? 0xffffffff : 0
    ...
    rN = isnan(aN) || isnan(bN) ? 0xffffffff : 0
    @endcode

    @par 128-bit version:
    @icost{NEON, ALTIVEC, 3}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, ALTIVEC, 6}
*/
inline mask_float32x4 isnan2(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::isnan2(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_ps(a, b, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return (mask_float32x4) _mm_cmpunord_ps(a, b);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return bit_or(isnan(a), isnan(b));
#endif
}

inline mask_float32x8 isnan2(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_ps(a, b, _CMP_UNORD_Q);
#else
    return {isnan2(a[0], b[0]), isnan2(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Checks whether corresponding elements in either @a a or @a b are IEEE754
    NaN.

    @code
    r0 = isnan(a0) || isnan(b0) ? 0xffffffffffffffff : 0
    ...
    rN = isnan(aN) || isnan(bN) ? 0xffffffffffffffff : 0
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline mask_float64x2 isnan2(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::isnan2(a, b);
#elif SIMDPP_USE_AVX
    return _mm_cmp_pd(a, b, _CMP_UNORD_Q);
#elif SIMDPP_USE_SSE2
    return _mm_cmpunord_pd(a, b);
#endif
}

inline mask_float64x4 isnan2(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_cmp_pd(a, b, _CMP_UNORD_Q);
#else
    return {isnan2(a[0], b[0]), isnan2(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes approximate reciprocal.

    Relative error is as follows:
     - 1/2 ULP for NULL and NEON
     - ~1/2730 for SSE2
     - 1/4096 for ALTIVEC
     - 1/256 for NEON_FLT_SP

    @code
    r0 = approx(1.0f / a0)
    ...
    rN = approx(1.0f / aN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 rcp_e(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float a){ return 1.0f / a; });
#elif SIMDPP_USE_SSE2
    return _mm_rcp_ps(a);
#elif SIMDPP_USE_NEON_FLT_SP
    return vrecpeq_f32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_re((__vector float)a);
#endif
}

inline float32x8 rcp_e(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_rcp_ps(a);
#else
    return {rcp_e(a[0]), rcp_e(a[1])};
#endif
}
/// @}

/// @{
/** Computes one Newton-Rhapson iterations for reciprocal. @a x is the current
    estimate, @a a are the values to estimate reciprocal for.

    @code
    r0 = x0 * (2 - x0*a0)
    ...
    rN = xN * (2 - xN*aN)
    @endcode

    Using this function, one can the division can be implemented as follows:
    @code
    // a/b
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b);
    return mul(a, x);
    @endcode

    Precision can be controlled by selecting the number of @c rcp_rh steps.

    @par 128-bit version:
    @icost{SSE2-AVX2, 3-4}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}

    @par 256-bit version:
    @icost{AVX-AVX2, 3-4}
    @icost{SSE2-SSE4.1, 6-7}
    @icost{NEON, 4}
    @icost{ALTIVEC, 4-5}
*/
inline float32x4 rcp_rh(float32x4 x, float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(x, a, [](float x, float a){ return x*(2.0f - x*a); });
#elif SIMDPP_USE_SSE2
    float32x4 c2, r;
    c2 = float32x4::make_const(2.0f);

    r = mul(a, x);
    r = sub(c2, r);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 r;
    r = vrecpsq_f32(a, x);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_ALTIVEC
    float32x4 r, c2;
    c2 = float32x4::make_const(2.0f);
    // -(x*a-c2)
    r = vec_nmsub((__vector float)x, (__vector float)a, (__vector float)c2);
    x = mul(x, r);
    return x;
#endif
}

inline float32x8 rcp_rh(float32x8 x, float32x8 a)
{
#if SIMDPP_USE_AVX
    float32x8 c2, r;
    c2 = float32x8::make_const(2.0f);

    r = mul(a, x);
    r = sub(c2, r);
    x = mul(x, r);

    return x;
#else
    return {rcp_rh(x[0], a[0]), rcp_rh(x[1], a[1])};
#endif
}
/// @}

/// @{
/** Divides the values of two vectors.

    @code
    r0 = a0 / b0
    ...
    rN = aN / bN
    @endcode

    @icost{NEON, 6}
    @icost{ALTIVEC, 10}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 12}
    @icost{ALTIVEC, 19}
*/
inline float32x4 div(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, b, [](float a, float b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_ps(a, b);
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b);
    return mul(a, x);
#elif SIMDPP_USE_ALTIVEC
    float32x4 x;
    x = rcp_e(b);
    x = rcp_rh(x, b);
    x = rcp_rh(x, b); // TODO: check how many approximation steps are needed
    return mul(a, x);
#endif
}

inline float32x8 div(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_div_ps(a, b);
#else
    return {div(a[0], b[0]), div(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Divides the values of two vectors

    @code
    r0 = a0 / b0
    ...
    rN = aN / bN
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 div(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::foreach<float64x2>(a, b, [](double a, double b){ return a / b; });
#elif SIMDPP_USE_SSE2
    return _mm_div_pd(a, b);
#endif
}

inline float64x4 div(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_div_pd(a, b);
#else
    return {div(a[0], b[0]), div(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes approximate reciprocal square root.

    Relative error is as follows:
     - 1/2 ULP for NULL and NEON
     - ~1/2730 for SSE2
     - 1/4096 for ALTIVEC
     - 1/256 for NEON_FLT_SP

    @code
    r0 = approx(1 / sqrt(a0))
    ...
    rN = approx(1 / sqrt(aN))
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 rsqrt_e(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float a){ return 1.0f / std::sqrt(a); });
#elif SIMDPP_USE_SSE2
    return _mm_rsqrt_ps(a);
#elif SIMDPP_USE_NEON_FLT_SP
    return vrsqrteq_f32(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_rsqrte((__vector float)a);
#endif
}

inline float32x8 rsqrt_e(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_rsqrt_ps(a);
#else
    return {rsqrt_e(a[0]), rsqrt_e(a[1])};
#endif
}
/// @}

/// @{
/** Computes one Newton-Rhapson iteration for inverse of square root. @a x is
    the current estimate, @a a are the values to estimate the inverse square
    root for.

    @code
    r0 = x0 * (3 - a0*x0*x0) * 0.5
    ...
    rN = xN * (3 - aN*xN*xN) * 0.5
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, SSE4.1, 5-7}
    @icost{NEON, 3}
    @icost{ALTIVEC, 4-6}

    @par 256-bit version:
    @icost{AVX-AVX2, 7}
    @icost{SSE2, SSE3, SSSE3, SSE4.1, 10-12}
    @icost{NEON, 6}
    @icost{ALTIVEC, 8-10}
*/
inline float32x4 rsqrt_rh(float32x4 x, float32x4 a)
{
    // x_n = x*(3-d*x*x)/2
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(x, a, [](float x, float a){ return x * (3.0f - a*x*x) * 0.5f; });
#elif SIMDPP_USE_SSE2
    float32x4 x2, c3, c0p5, r;

    c3 = float32x4::make_const(3.0f);
    c0p5 = float32x4::make_const(0.5f);

    x2 = mul(x, x);
    r = mul(a, x2);
    r = sub(c3, r);
    x = mul(x, c0p5);
    r = mul(x, r);

    return r;
#elif SIMDPP_USE_NEON_FLT_SP
    float32x4 x2, r;

    x2 = mul(x, x);
    r = vrsqrtsq_f32(a, x2);
    x = mul(x, r);

    return x;
#elif SIMDPP_USE_ALTIVEC
    float32x4 c3, c0p5, x2, r, xp5;

    c3 = float32x4::make_const(3.0f);
    c0p5 = float32x4::make_const(0.5f);

    x2 = mul(x, x);
    // r = (c3 - a*x2)
    r = vec_nmsub((__vector float)a, (__vector float)x2, (__vector float)c3);
    xp5 = mul(x, c0p5);
    r = mul(xp5, r);

    return r;
#endif
}

inline float32x8 rsqrt_rh(float32x8 x, float32x8 a)
{
#if SIMDPP_USE_AVX
    float32x8 x2, c3, c0p5, r;

    c3 = float32x8::make_const(3.0f);
    c0p5 = float32x8::make_const(0.5f);

    x2 = mul(x, x);
    r = mul(a, x2);
    r = sub(c3, r);
    x = mul(x, c0p5);
    r = mul(x, r);

    return r;
#else
    return {rsqrt_rh(x[0], a[0]), rsqrt_rh(x[1], a[1])};
#endif
}
/// @}

/// @{
/** Computes square root.

    @code
    r0 = sqrt(a0)
    ...
    rN = sqrt(aN)
    @endcode

    @par 128-bit version:
    @icost{NEON, 5}
    @icost{ALTIVEC, 5-7}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 10}
    @icost{ALTIVEC, 10-12}
*/
inline float32x4 sqrt(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float a){ return std::sqrt(a); });
#elif SIMDPP_USE_SSE2
    return _mm_sqrt_ps(a);
#elif SIMDPP_USE_NEON_FLT_SP || SIMDPP_USE_ALTIVEC
    float32x4 x;
    x = rsqrt_e(a);
    x = rsqrt_rh(x, a);
    return mul(a, x);
#endif
}

inline float32x8 sqrt(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_sqrt_ps(a);
#else
    return {sqrt(a[0]), sqrt(a[1])};
#endif
}
/// @}

/// @{
/** Computes square root.

    @code
    r0 = sqrt(a0)
    ...
    rN = sqrt(aN)
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 sqrt(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::foreach<float64x2>(a, [](double a){ return std::sqrt(a); });
#elif SIMDPP_USE_SSE2
    return _mm_sqrt_pd(a);
#endif
}

inline float64x4 sqrt(float64x4 a)
{
#if SIMDPP_USE_AVX
    return _mm256_sqrt_pd(a);
#else
    return {sqrt(a[0]), sqrt(a[1])};
#endif
}
/// @}

// note: SSE doesn't provide a way to propagate NaNs in min/max
/// @{
/** Computes minimum of the values in two vectors. If at least one of the
    values is NaN, or both values are zeroes, it is unspecified which value
    will be returned.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)

    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 min(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_ps(a, b);
#elif SIMDPP_USE_NEON
    return vminq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_min((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 min(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_min_ps(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes minima of the values in two vectors. If at least one of the values
    is NaN, or both values are zeroes, it is unspecified which value will be
    returned.

    @code
    r0 = min(a0, b0)
    ...
    rN = min(aN, bN)
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @novec{NEON, ALTIVEC}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 min(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::min(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_min_pd(a, b);
#endif
}

inline float64x4 min(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_min_pd(a, b);
#else
    return {min(a[0], b[0]), min(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maxima of the values of two vectors. If at least one of the values
    is NaN, or both values are zeroes, it is unspecified which value will be
    returned.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
inline float32x4 max(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_ps(a, b);
#elif SIMDPP_USE_NEON
    return vmaxq_f32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_max((__vector float)a, (__vector float)b);
#endif
}

inline float32x8 max(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_max_ps(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes maxima of the values of two vectors. If at least one of the values
    is NaN, or both values are zeroes, it is unspecified which value will be
    returned.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
inline float64x2 max(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::max(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_max_pd(a, b);
#endif
}

inline float64x4 max(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_max_pd(a, b);
#else
    return {max(a[0], b[0]), max(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Rounds the values of a vector towards negative infinity

    @code
    r0 = floor(a0)
    ...
    rN = floor(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 12-14}
    @icost{NEON, 10-11}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 24-26}
    @icost{NEON, 20-21}
    @icost{ALTIVEC, 2}
*/
inline float32x4 floor(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float x){ return std::floor(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_floor_ps(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large, or is zero
    float32x4 ba = abs(a);
    mask_float32x4 large_mask, zero_mask, mask;
    large_mask = cmp_gt(ba, float32x4::make_const(8388607.0f));
    zero_mask = cmp_eq(ba, float32x4::zero());
    mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the floor using trunc
    int32x4 s = shift_r((uint32x4)a, 31); //=1 if a<0
    float32x4 at = (float32x4) sub((int32x4)a, s); //=nextafter towards +inf, if a<0
    int32x4 ia = to_int32x4(at);
            ia = sub(ia, s);
    float32x4 fa = to_float32x4(ia);

    //combine the results
    a = blend(a, fa, mask);
    return a;
#elif SIMDPP_USE_ALTIVEC
    return vec_floor((__vector float)a);
#endif
}

inline float32x8 floor(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_floor_ps(a);
#else
    return {floor(a[0]), floor(a[1])};
#endif
}

/// @{
/** Rounds the values a vector towards positive infinity

    @code
    r0 = ceil(a0)
    ...
    rN = ceil(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, 13-15}
    @icost{NEON, 11-13}

    @par 256-bit version:
    @icost{SSE2, SSE3, SSSE3, 26-28}
    @icost{NEON, 22-24}
    @icost{ALTIVEC, 2}
*/
inline float32x4 ceil(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float x){ return std::ceil(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_ceil_ps(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large, or is zero
    float32x4 ba = abs(a);
    mask_float32x4 large_mask, zero_mask, mask;
    large_mask = cmp_gt(ba, float32x4::make_const(8388607.0f));
    zero_mask = cmp_eq(ba, float32x4::zero());
    mask = bit_or(large_mask, zero_mask); // takes care of nans and zeros

    //calculate the ceil using trunc
    int32x4 s = shift_r((uint32x4)a, 31);
            s = bit_xor(s, int32x4::make_const(0x00000001)); //=1 if a>0
    float32x4 at = (float32x4) sub((int32x4)a, s); //=nextafter towards -inf if a>0
    int32x4 ia = to_int32x4(at);
            ia = add(ia, s);
    float32x4 fa = to_float32x4(ia);

    //combine the results
    a = blend(a, fa, mask);
    return a;
#elif SIMDPP_USE_ALTIVEC
    return vec_ceil((__vector float)a);
#endif
}

inline float32x8 ceil(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_ceil_ps(a);
#else
    return {ceil(a[0]), ceil(a[1])};
#endif
}
/// @}

/// @{
/** Rounds the values of a vector towards zero
    @code
    r0 = trunc(a0)
    ...
    rN = trunc(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, 7-9}
    @icost{NEON, 5-6}

    @par 256-bit version:
    @icost{SSE2, SSE3, SSSE3, 14-16}
    @icost{NEON, 10-11}
    @icost{SSE4.1, ALTIVEC, 2}
*/
inline float32x4 trunc(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return null::foreach<float32x4>(a, [](float x){ return std::trunc(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_round_ps(a, 3); // 3 = truncate
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large
    float32x4 af = abs(a);
    mask_float32x4 mask = cmp_gt(af, float32x4::make_const(8388607.0f));

    //truncate
    int32x4 ia = to_int32x4(a);
    float32x4 fa = to_float32x4(ia);

    //combine the results
    a = blend(a, fa, mask);     // takes care of NaNs
    return a;
#elif SIMDPP_USE_ALTIVEC
    return vec_trunc((__vector float)a);
#endif
}

inline float32x8 trunc(float32x8 a)
{
#if SIMDPP_USE_AVX
    return _mm256_round_ps(a, 3); // 3 = truncate
#else
    return {ceil(a[0]), ceil(a[1])};
#endif
}
/// @}

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
