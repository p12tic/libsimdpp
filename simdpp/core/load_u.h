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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_U_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_U_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/detail/mem_unpack.h>
#include <simdpp/adv/transpose.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Loads a 128-bit or 256-bit integer, 32-bit or 64-bit float vector from an
    unaligned memory location.

    @par 128-bit version:

    @code
    a[0..127] = *(p)
    @endcode

    @a p must be aligned to the element size. If @a p is aligned to 16 bytes
    only the referenced 16 byte block is accessed. Otherwise, memory within the
    smallest 16-byte aligned 32-byte block may be accessed.

    @icost{ALTIVEC, 4}

    @par 256-bit version:

    @code
    a[0..255] = *(p)
    @endcode
    @a p must be aligned to 32 bytes.
    @icost{SSE2-SSE4.1, NEON, 2}
    @icost{ALTIVEC, 6}

    @a p must be aligned to the element size. If @a p is aligned to 32 bytes
    only the referenced 16 byte block is accessed. Otherwise, memory within the
    smallest 32-byte aligned 64-byte block may be accessed.
*/
// Each integer type is handled separately because higher aligment guarantees
// offer better performance on e.g. ARM. Note, we don't use LDDQU on SSE,
// because it has usage restrictions and offers improved performance only on
// Pentium 4 era processors.
inline basic_int8x16 load_u(basic_int8x16& a, const void* p)
{
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u8(reinterpret_cast<const uint8_t*>(p));
    return a;
#elif SIMDPP_USE_ALTIVEC
    const uint8_t* q = reinterpret_cast<const uint8_t*>(p);
    uint8x16 l1, l2, mask;
    l1 = vec_ldl(0, q);
    l2 = vec_ldl(16, q);
    mask = vec_lvsl(0, q);
    l1 = vec_perm((__vector uint8_t)l1, (__vector uint8_t)l2,
                 (__vector uint8_t)mask);
    return l1;
#endif
}

inline basic_int16x8 load_u(basic_int16x8& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b = load_u(b, p);
    a = b;
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u16(reinterpret_cast<const uint16_t*>(p));
    return a;
#endif
}

inline basic_int32x4 load_u(basic_int32x4& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b = load_u(b, p);
    a = b;
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u32(reinterpret_cast<const uint32_t*>(p));
    return a;
#endif
}

inline basic_int64x2 load_u(basic_int64x2& a, const void* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    uint8x16 b = load_u(b, p);
    a = b;
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_u64(reinterpret_cast<const uint64_t*>(p));
    return a;
#endif
}

inline float32x4 load_u(float32x4& a, const float* p)
{
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_ps(p);
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_f32(p);
    return a;
#elif SIMDPP_USE_ALTIVEC
    uint32x4 b = load_u(b, reinterpret_cast<const uint32_t*>(p));
    a = b;
    return a;
#endif
}

inline float64x2 load_u(float64x2& a, const double* p)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_loadu_pd(p);
    return a;
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, p);
#endif
}

inline basic_int8x32 load_u(basic_int8x32& a, const void* p)
{
#if SIMDPP_USE_AVX2
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
    return a;
#elif SIMDPP_USE_ALTIVEC
    const uint8_t* q = reinterpret_cast<const uint8_t*>(p);
    uint8x16 l1, l2, l3, mask;
    l1 = vec_ldl(0, q);
    l2 = vec_ldl(16, q);
    l3 = vec_ldl(32, q);
    mask = vec_lvsl(0, q);
    l1 = vec_perm((__vector uint8_t)l1, (__vector uint8_t)l2,
                  (__vector uint8_t)mask);
    l2 = vec_perm((__vector uint8_t)l2, (__vector uint8_t)l3,
                  (__vector uint8_t)mask);
    return basic_int8x32(l1, l2);
#else
    const char* q = reinterpret_cast<const char*>(p);
    load_u(a[0], q);
    load_u(a[1], q+16);
    return a;
#endif
}

inline basic_int16x16 load_u(basic_int16x16& a, const void* p)
{
#if SIMDPP_USE_AVX2
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
    return a;
#elif SIMDPP_USE_ALTIVEC
    basic_int8x32 a0;
    load_u(a0, p);
    a = a0;
    return a;
#else
    const char* q = reinterpret_cast<const char*>(p);
    load_u(a[0], q);
    load_u(a[1], q+16);
    return a;
#endif
}

inline basic_int32x8 load_u(basic_int32x8& a, const void* p)
{
#if SIMDPP_USE_AVX2
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
    return a;
#elif SIMDPP_USE_ALTIVEC
    basic_int8x32 a0;
    load_u(a0, p);
    a = a0;
    return a;
#else
    const char* q = reinterpret_cast<const char*>(p);
    load_u(a[0], q);
    load_u(a[1], q+16);
    return a;
#endif
}

inline basic_int64x4 load_u(basic_int64x4& a, const void* p)
{
#if SIMDPP_USE_AVX2
    a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p));
    return a;
#elif SIMDPP_USE_ALTIVEC
    basic_int8x32 a0;
    load_u(a0, p);
    a = a0;
    return a;
#else
    const char* q = reinterpret_cast<const char*>(p);
    load_u(a[0], q);
    load_u(a[1], q+16);
    return a;
#endif
}

inline float32x8 load_u(float32x8& a, const float* p)
{
#if SIMDPP_USE_AVX
    a = _mm256_loadu_ps(p);
    return a;
#elif SIMDPP_USE_ALTIVEC
    basic_int32x8 a0;
    load_u(a0, p);
    a = a0;
    return a;
#else
    load_u(a[0], p);
    load_u(a[1], p+4);
    return a;
#endif
}

inline float64x4 load_u(float64x4& a, const double* p)
{
#if SIMDPP_USE_AVX
    a = _mm256_loadu_pd(p);
    return a;
#else
    load_u(a[0], p);
    load_u(a[1], p+2);
    return a;
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

