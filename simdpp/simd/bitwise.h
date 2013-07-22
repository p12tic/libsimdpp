/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_BITWISE_H
#define LIBSIMDPP_SIMD_BITWISE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/bitwise.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** @defgroup simd_bitwise
    @{
*/

/// @{
/** Computes bitwise AND.

    @code
    r = a & b
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int128 bit_and(int128 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_and_si128(a, b);
#elif SIMDPP_USE_NEON
    return vandq_u32(a, b);
#endif
}

inline int256 bit_and(int256 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_and_si256(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise AND.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline float32x4 bit_and(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_and(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_and_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32(a),
                                           vreinterpretq_u32_f32(b)));
#endif
}

inline float32x8 bit_and(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_and_ps(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline float32x4 bit_and(float32x4 a, int128 b)
{
    return bit_and(a, float32x4(b));
}

inline float32x8 bit_and(float32x8 a, int256 b)
{
    return bit_and(a, float32x8(b));
}
/// @}

/// @{
/** Computes bitwise AND.

    @code
    r0 = a0 & b0
    ...
    rN = aN & bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
*/
inline float64x2 bit_and(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::bit_and(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_and_pd(a, b);
#elif SIMDPP_USE_NEON
    return float64x2(bit_and(int64x2(a), int64x2(b)));
#endif
}

inline float64x4 bit_and(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_and_pd(a, b);
#else
    return {bit_and(a[0], b[0]), bit_and(a[1], b[1])};
#endif
}

inline float64x2 bit_and(float64x2 a, int128 b)
{
    return bit_and(a, float64x2(b));
}

inline float64x4 bit_and(float64x4 a, int256 b)
{
    return bit_and(a, float64x4(b));
}
/// @}

/// @{
/** Computes bitwise AND NOT.

    @code
    r = a & ~b
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int128 bit_andnot(int128 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_si128(b, a);
#elif SIMDPP_USE_NEON
    return vbicq_u32(a, b);
#endif
}

inline int256 bit_andnot(int256 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_andnot_si256(b, a);
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise AND NOT.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline float32x4 bit_andnot(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_ps(b, a);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_s32(vbicq_s32(vreinterpretq_s32_f32(a), vreinterpretq_s32_f32(b)));
#endif
}

inline float32x8 bit_andnot(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_andnot_ps(b, a);
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline float32x4 bit_andnot(float32x4 a, int128 b)
{
    return bit_andnot(a, float32x4(b));
}

inline float32x8 bit_andnot(float32x8 a, int256 b)
{
    return bit_andnot(a, float32x8(b));
}
/// @}

/// @{
/** Computes bitwise AND NOT.

    @code
    r0 = a0 & ~b0
    ...
    rN = aN & ~bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
*/
inline float64x2 bit_andnot(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_pd(b, a);
#elif SIMDPP_USE_NEON
    return float64x2(bit_andnot(int64x2(a), int64x2(b)));
#endif
}

inline float64x4 bit_andnot(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_andnot_pd(b, a);
#else
    return {bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1])};
#endif
}

inline float64x2 bit_andnot(float64x2 a, int128 b)
{
    return bit_andnot(a, float64x2(b));
}

inline float64x4 bit_andnot(float64x4 a, int256 b)
{
    return bit_andnot(a, float64x4(b));
}
/// @}

/// @{
/** Computes bitwise OR.

    @code
    r = a | b
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int128 bit_or(int128 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_or_si128(a, b);
#elif SIMDPP_USE_NEON
    return vorrq_u32(a, b);
#endif
}

inline int256 bit_or(int256 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_or_si256(a, b);
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise OR.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline float32x4 bit_or(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_or(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_or_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(a), vreinterpretq_s32_f32(b)));
#endif
}

inline float32x8 bit_or(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_or_ps(a, b);
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline float32x4 bit_or(float32x4 a, int128 b)
{
    return bit_or(a, float32x4(b));
}

inline float32x8 bit_or(float32x8 a, int256 b)
{
    return bit_or(a, float32x8(b));
}
/// @}

/// @{
/** Computes bitwise OR.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
*/
inline float64x2 bit_or(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::bit_or(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_or_pd(a, b);
#elif SIMDPP_USE_NEON
    return float64x2(bit_or(int64x2(a), int64x2(b)));
#endif
}

inline float64x4 bit_or(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_or_pd(a, b);
#else
    return {bit_or(a[0], b[0]), bit_or(a[1], b[1])};
#endif
}

inline float64x2 bit_or(float64x2 a, int128 b)
{
    return bit_or(a, float64x2(b));
}

inline float64x4 bit_or(float64x4 a, int256 b)
{
    return bit_or(a, float64x4(b));
}
/// @}

/// @{
/** Computes bitwise XOR.

    @code
    r = a ^ b
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline int128 bit_xor(int128 a, int128 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_si128(a, b);
#elif SIMDPP_USE_NEON
    return veorq_u32(a, b);
#endif
}

inline int256 bit_xor(int256 a, int256 b)
{
#if SIMDPP_USE_AVX2
    return _mm256_xor_si256(a, b);
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise XOR.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
inline float32x4 bit_xor(float32x4 a, float32x4 b)
{
#if SIMDPP_USE_NULL
    return null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_ps(a, b);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(a), vreinterpretq_s32_f32(b)));
#endif
}

inline float32x8 bit_xor(float32x8 a, float32x8 b)
{
#if SIMDPP_USE_AVX
    return _mm256_xor_ps(a, b);
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline float32x4 bit_xor(float32x4 a, int128 b)
{
    return bit_xor(a, float32x4(b));
}

inline float32x8 bit_xor(float32x8 a, int256 b)
{
    return bit_xor(a, float32x8(b));
}
/// @}

/// @{
/** Computes bitwise XOR.

    @code
    r0 = a0 | b0
    ...
    rN = aN | bN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
*/
inline float64x2 bit_xor(float64x2 a, float64x2 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_DP
    return null::bit_xor(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_xor_pd(a, b);
#elif SIMDPP_USE_NEON
    return float64x2(bit_xor(int64x2(a), int64x2(b)));
#endif
}

inline float64x4 bit_xor(float64x4 a, float64x4 b)
{
#if SIMDPP_USE_AVX
    return _mm256_xor_pd(a, b);
#else
    return {bit_xor(a[0], b[0]), bit_xor(a[1], b[1])};
#endif
}

inline float64x2 bit_xor(float64x2 a, int128 b)
{
    return bit_xor(a, float64x2(b));
}

inline float64x4 bit_xor(float64x4 a, int256 b)
{
    return bit_xor(a, float64x4(b));
}
/// @}

/// @{
/** Computes bitwise NOT of a 128-bit integer vector

    @code
    r = ~a
    @endcode


    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 4}
    @icost{AVX2, 2}
*/
inline int128 bit_not(int128 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<int128>(a, [](uint64_t a){ return ~a; });
#elif SIMDPP_USE_SSE2
    int128 ones = int128::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return vmvnq_u32(a);
#endif
}

inline int256 bit_not(int256 a)
{
#if SIMDPP_USE_AVX2
    int256 ones = int256::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}
/// @}

/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
