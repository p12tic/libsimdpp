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

#ifndef LIBSIMDPP_SIMD_BITWISE_H
#define LIBSIMDPP_SIMD_BITWISE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/bitwise.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @defgroup simd_bitwise Operations: bitwise
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
    return int256(bit_and(a[0], b[0]), bit_and(a[1], b[1]));
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
    return float32x8(bit_and(a[0], b[0]), bit_and(a[1], b[1]));
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
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
    return float64x4(bit_and(a[0], b[0]), bit_and(a[1], b[1]));
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
    return int256(bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1]));
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
    return float32x8(bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1]));
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
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
    return float64x4(bit_andnot(a[0], b[0]), bit_andnot(a[1], b[1]));
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
    return int256(bit_or(a[0], b[0]), bit_or(a[1], b[1]));
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
    return float32x8(bit_or(a[0], b[0]), bit_or(a[1], b[1]));
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
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
    return float64x4(bit_or(a[0], b[0]), bit_or(a[1], b[1]));
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
    return int256(bit_xor(a[0], b[0]), bit_xor(a[1], b[1]));
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
    return float32x8(bit_xor(a[0], b[0]), bit_xor(a[1], b[1]));
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
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
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
    return float64x4(bit_xor(a[0], b[0]), bit_xor(a[1], b[1]));
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

SIMDPP_DEF_FUNCTOR(null_bit_not, x, ~x);

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
    return null::foreach<int128>(a, null_bit_not<uint64_t>());
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
    return int256(bit_not(a[0]), bit_not(a[1]));
#endif
}
/// @}

/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
