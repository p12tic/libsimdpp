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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_I_MULL_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_I_MULL_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/*  Note: widening integer multiplication instructions are very different among
    instruction sets. The main difference is in which half of the elements are
    selected for multiplication. Trying to abstract this incurs definite
    overhead.

     - SSE2-SSE4.1 and AVX2 provide only instructions with interfaces similar
        to mul_lo and mul_hi. The result vectors must be interleaved to obtain
        contiguous result values. Multiplying 2 vectors always incurs
        overhead of at least two interleaving instructions.

     - AVX512 only provides 32-bit integer support. Widening multiplication
        can be done only by using PMULDQ, which takes odd elements and produces
        widened multiplication results. Multiplication of two whole vectors
        always incurs overhead of at least two shifts or interleaving
        instructions.

     - NEON, NEONv2 provide instructions that take elements of either the lower
        or higher halves of two 128-bit vectors and multiply them. No
        additional overhead is incurred to obtain contiguous result values.

     - ALTIVEC hav multiply odd and multiply even instructions. No additional
        overhead is incurred to obtain contiguous result values.

    The abstraction below uses the NEON model. No additional overhead is
    incurred on SSE/AVX and NEON. On ALTIVEC, a single additional permute
    instruction is needed for each vector multiplication on average.
*/

/// @{
/** Multiplies signed 16-bit values in the lower halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    ...
    r3 = a3 * b3
    @endcode

    @icost{SSE2-AVX, ALTIVEC, 2-3}

    @par 256-bit version:

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, ALTIVEC, 4-6}
    @icost{AVX2, NEON, 2-3}
    @note Use with mull_hi on the same arguments to save instructions.
*/
inline int32x4 mull_lo(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = int32_t(a[i]) * b[i];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epi16(a, b);
    return zip_lo(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_s16(vget_low_s16(a), vget_low_s16(b));
#elif SIMDPP_USE_ALTIVEC
    int32x4 lo = vec_mule((__vector int16_t)a, (__vector int16_t)b);
    int32x4 hi = vec_mulo((__vector int16_t)a, (__vector int16_t)b);
    return zip_lo(lo, hi);
#endif
}

inline int32x8 mull_lo(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    int16x16 lo = _mm256_mullo_epi16(a, b);
    int16x16 hi = _mm256_mulhi_epi16(a, b);
    return zip_lo(lo, hi);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 16-bit values in the lower halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    ...
    r3 = a3 * b3
    @endcode

    @icost{SSE2-AVX2, ALTIVEC, 2-3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, ALTIVEC, 4-6}
    @icost{AVX2, 2-3}
    @icost{NEON, 2}
    @note Use with mull_hi on the same arguments to save instructions.
*/
inline uint32x4 mull_lo(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    uint32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = uint32_t(a[i]) * b[i];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epu16(a, b);
    return zip_lo(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_u16(vget_low_u16(a), vget_low_u16(b));
#elif SIMDPP_USE_ALTIVEC
    uint32x4 lo = vec_mule((__vector uint16_t)a, (__vector uint16_t)b);
    uint32x4 hi = vec_mulo((__vector uint16_t)a, (__vector uint16_t)b);
    return zip_lo(lo, hi);
#endif
}

inline uint32x8 mull_lo(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 lo = _mm256_mullo_epi16(a, b);
    uint16x16 hi = _mm256_mulhi_epu16(a, b);
    return zip_lo(lo, hi);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 16-bit values in the higher halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a4 * b4
    ...
    r3 = a7 * b7
    @endcode

    @icost{SSE2-AVX2, ALTIVEC, 2-3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, ALTIVEC, 4-6}
    @icost{AVX2, 2-3}
    @icost{NEON, 2}
    @note Use with mull_lo on the same arguments to save instructions.
*/
inline int32x4 mull_hi(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    int32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = int32_t(a[i+4]) * b[i+4];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epi16(a, b);
    return zip_hi(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_s16(vget_high_s16(a), vget_high_s16(b));
#elif SIMDPP_USE_ALTIVEC
    int32x4 lo = vec_mule((__vector int16_t)a, (__vector int16_t)b);
    int32x4 hi = vec_mulo((__vector int16_t)a, (__vector int16_t)b);
    return zip_hi(lo, hi);
#endif
}

inline int32x8 mull_hi(int16x16 a, int16x16 b)
{
#if SIMDPP_USE_AVX2
    int16x16 lo = _mm256_mullo_epi16(a, b);
    int16x16 hi = _mm256_mulhi_epi16(a, b);
    return zip_hi(lo, hi);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 16-bit values in the higher halves of the vectors and
    expands the results to 32 bits.

    @par 128-bit version:
    @code
    r0 = a4 * b4
    ...
    r3 = a7 * b7
    @endcode

    @icost{SSE2-AVX2, ALTIVEC, 2-3}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, ALTIVEC, 4-6}
    @icost{AVX2, 2-3}
    @icost{NEON, 2}
    @note Use with mull_lo on the same arguments to save instructions.
*/
inline uint32x4 mull_hi(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    uint32x4 r;
    for (unsigned i = 0; i < 4; i++) {
        r[i] = uint32_t(a[i+4]) * b[i+4];
    }
    return r;
#elif SIMDPP_USE_SSE2
    int16x8 lo = _mm_mullo_epi16(a, b);
    int16x8 hi = _mm_mulhi_epu16(a, b);
    return zip_hi(lo, hi);
#elif SIMDPP_USE_NEON
    return vmull_u16(vget_high_u16(a), vget_high_u16(b));
#elif SIMDPP_USE_ALTIVEC
    uint32x4 lo = vec_mule((__vector uint16_t)a, (__vector uint16_t)b);
    uint32x4 hi = vec_mulo((__vector uint16_t)a, (__vector uint16_t)b);
    return zip_hi(lo, hi);
#endif
}

inline uint32x8 mull_hi(uint16x16 a, uint16x16 b)
{
#if SIMDPP_USE_AVX2
    uint16x16 lo = _mm256_mullo_epi16(a, b);
    uint16x16 hi = _mm256_mulhi_epu16(a, b);
    return zip_hi(lo, hi);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 32-bit values in the lower halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    r1 = a1 * b1
    @endcode
    @icost{SSE4.1-AVX, 3}
    @unimp{SSE2-SSSE3, ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE4.1-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
    @unimp{SSE2-SSSE3, ALTIVEC}
*/
inline int64x2 mull_lo(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    int64x2 r;
    r[0] = int64_t(a[0]) * b[0];
    r[1] = int64_t(a[1]) * b[1];
    return r;
#elif SIMDPP_USE_SSE4_1
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm_mul_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_s32(vget_low_s32(a), vget_low_s32(b));
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline int64x4 mull_lo(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm256_mul_epi32(a, b);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 32-bit values in the lower halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a0 * b0
    r1 = a1 * b1
    @endcode
    @icost{SSE2-AVX, 3}
    @unimp{ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
    @unimp{ALTIVEC}
*/
inline uint64x2 mull_lo(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    detail::mem_block<uint64x2> r;
    detail::mem_block<uint32x4> ax(a), bx(b);
    r[0] = uint64_t(ax[0]) * bx[0];
    r[1] = uint64_t(ax[1]) * bx[1];
    return r;
#elif SIMDPP_USE_SSE2
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm_mul_epu32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_u32(vget_low_u32(a), vget_low_u32(b));
#endif
}

inline uint64x4 mull_lo(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_lo(a, a);
    b = zip_lo(b, b);
    return _mm256_mul_epu32(a, b);
#else
    return {mull_lo(a[0], b[0]), mull_lo(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies signed 32-bit values in the higher halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a2 * b2
    r1 = a3 * b3
    @endcode
    @icost{SSE4.1-AVX2, 3}
    @unimp{SSE2-SSSE3, ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE4.1-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
    @unimp{SSE2-SSSE3, ALTIVEC}
*/
inline int64x2 mull_hi(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    int64x2 r;
    r[0] = int64_t(a[2]) * b[2];
    r[1] = int64_t(a[3]) * b[3];
    return r;
#elif SIMDPP_USE_SSE4_1
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm_mul_epi32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_s32(vget_high_s32(a), vget_high_s32(b));
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, b);
#endif
}

inline int64x4 mull_hi(int32x8 a, int32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm256_mul_epi32(a, b);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

/// @{
/** Multiplies unsigned 32-bit values in the higher halves of the vectors and
    expands the results to 64 bits.

    @par 128-bit version:
    @code
    r0 = a2 * b2
    r1 = a3 * b3
    @endcode
    @icost{SSE2-AVX, 3}
    @novec{ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 6}
    @icost{AVX2, 3}
    @icost{NEON, 2}
    @novec{ALTIVEC}
*/
inline uint64x2 mull_hi(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    detail::mem_block<uint64x2> r;
    detail::mem_block<uint32x4> ax(a), bx(b);
    r[0] = uint64_t(ax[2]) * bx[2];
    r[1] = uint64_t(ax[3]) * bx[3];
    return r;
#elif SIMDPP_USE_SSE2
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm_mul_epu32(a, b);
#elif SIMDPP_USE_NEON
    return vmull_u32(vget_high_u32(a), vget_high_u32(b));
#endif
}

inline uint64x4 mull_hi(uint32x8 a, uint32x8 b)
{
#if SIMDPP_USE_AVX2
    a = zip_hi(a, a);
    b = zip_hi(b, b);
    return _mm256_mul_epu32(a, b);
#else
    return {mull_hi(a[0], b[0]), mull_hi(a[1], b[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

