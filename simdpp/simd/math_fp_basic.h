/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_MATH_FP_BASIC_H
#define LIBSIMDPP_SIMD_MATH_FP_BASIC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd/types.h>
#include <simdpp/simd/bitwise.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP || SIMDPP_USE_NEON_VFP_DP
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/// @defgroup simd_math_fp
/// @{

/** Computes absolute value of floating point values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2, SSE3, SSSE3, SSE4.1, NEON, 2}

    @par 256-bit version:
    @icost{SSE2, SSE3, SSSE3, SSE4.1, NEON, 4}
    @icost{AVX-AVX2, 2}
*/
inline float32x4 abs(float32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP
    return null::abs(a);
#elif SIMDPP_USE_SSE2
    return bit_and(a, int32x4::make_const(0x7fffffff));
#elif SIMDPP_USE_NEON
    return vabsq_f32(a);
#endif
}

inline float32x8 abs(float32x8 a)
{
#if SIMDPP_USE_AVX
    return bit_and(a, float32x8::make_const(0x7fffffff));
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
    @unimp{NEON}
    @icost{SSE2, SSE3, SSSE3, SSE4.1, 2}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2, SSE3, SSSE3, SSE4.1, 4}
    @icost{AVX-AVX2, 2}
*/
inline float64x2 abs(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::abs(a);
#elif SIMDPP_USE_SSE2
    return bit_and(a, int64x2::make_const(0x7fffffffffffffff));
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

inline float64x4 abs(float64x4 a)
{
#if SIMDPP_USE_AVX
    return bit_and(a, float64x4::make_const(0x7fffffffffffffff));
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
    @icost{SSE2, SSE3, SSSE3, SSE4.1, NEON, 2}

    @par 256-bit version:
    @icost{SSE2, SSE3, SSSE3, SSE4.1, NEON, 3}
    @icost{AVX-AVX2, 2}
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
    @icost{SSE2-AVX2, 2}
    @unimp{NEON}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 3}
    @icost{AVX-AVX2, 2}
    @unimp{NEON}
*/
inline float64x2 sign(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_VFP_DP
    return bit_and(a, uint64x2::make_const(0x8000000000000000));
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
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
    @icost{SSE2-SSE4.1, NEON, 2}
*/
inline float32x4 add(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_ps(a, b);
#elif SIMDPP_USE_NEON
    return vaddq_f32(a, b);
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 add(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::add(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_add_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
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
    @icost{SSE2-SSE4.1, NEON, 2}
*/
inline float32x4 sub(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_ps(a,b);
#elif SIMDPP_USE_NEON
    return vsubq_f32(a, b);
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 sub(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::sub(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_sub_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
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
    @icost{SSE2-AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 3}
    @icost{AVX-AVX2, NEON, 2}
*/
inline float32x4 neg(float32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    // reversion of the sign bit required even for NaNs and zeros
    int32x4 zero = int32x4::make_const(0x80000000);
    return bit_xor(a, zero);
#elif SIMDPP_USE_NEON
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
    @icost{SSE2-AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 3}
    @icost{AVX-AVX2, NEON, 2}
    @unimp{NEON}
*/
inline float64x2 neg(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::neg(a);
#elif SIMDPP_USE_SSE2
    int64x2 zero = int64x2::make_const(0x8000000000000000);
    return bit_xor(a, zero);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
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
    @icost{SSE2-SSE4.1, NEON, 2}
*/
inline float32x4 mul(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP
    return null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mul_ps(a,b);
#elif SIMDPP_USE_NEON
    return vmulq_f32(a, b);
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
    @unimp{NEON}

    @par 256-bit version:
    @unimp{NEON}
    @icost{SSE2-SSE4.1, 2}
*/
inline float64x2 mul(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::mul(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_mul_pd(a, b);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
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

/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
