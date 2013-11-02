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

#ifndef LIBSIMDPP_SIMD_MEMORY_LOAD_H
#define LIBSIMDPP_SIMD_MEMORY_LOAD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/transpose.h>
#include <simdpp/simd/detail/align.h>
#include <simdpp/simd/detail/mem_unpack.h>
#include <simdpp/null/memory.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @defgroup simd_load Operations: load from memory to register
/// @{

/// @{
/** Loads a 128-bit or 256-bit integer, 32-bit or 64-bit float vector
    from an aligned memory location.

    @par 128-bit version:

    @code
    a[0..127] = *(p)
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:

    @code
    a[0..255] = *(p)
    @endcode
    @a p must be aligned to 32 bytes.

    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
    @icost{AVX (integer vectors), 2}
*/
inline int128 load(int128& a, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_si128(reinterpret_cast<const __m128i*>(p));
    return a;
#elif SIMDPP_USE_NEON
    a = vreinterpretq_u32_u64(vld1q_u64(reinterpret_cast<const uint64_t*>(p)));
    return a;
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, reinterpret_cast<const uint8_t*>(p));
    return a;
#endif
}

inline int256 load(int256& a, const void* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX2
    a = _mm256_load_si256(reinterpret_cast<const __m256i*>(p));
    return a;
#else
    const char* q = reinterpret_cast<const char*>(p);
    a = int256{load(a[0], q), load(a[1], q+16)};
    return a;
#endif
}

inline float32x4 load(float32x4& a, const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_ps(p);
    return a;
#elif SIMDPP_USE_NEON
    a = vld1q_f32(p);
    return a;
#elif SIMDPP_USE_ALTIVEC
    a = vec_ldl(0, p);
    return a;
#endif
}

inline float32x8 load(float32x8& a, const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    a = _mm256_load_ps(p);
    return a;
#else
    a = float32x8{load(a[0], p), load(a[1], p+4)};
    return a;
#endif
}

inline float64x2 load(float64x2& a, const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    null::load(a, p);
    return a;
#elif SIMDPP_USE_SSE2
    a = _mm_load_pd(p);
    return a;
#endif
}

inline float64x4 load(float64x4& a, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    a = _mm256_load_pd(p);
    return a;
#else
    a = float64x4{load(a[0], p), load(a[1], p+2)};
    return a;
#endif
}
/// @}

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

namespace detail {

// the 256-bit versions are mostly boilerplate. Collect that stuff here.
template<class V>
void v256_load_i_packed2(V& a, V& b, const void* p)
{
    p = detail::assume_aligned(p, 32);
    const char* q = reinterpret_cast<const char*>(p);
#if SIMDPP_USE_AVX2
    load(a, q);
    load(b, q + 32);
    detail::mem_unpack2(a, b);
#else
    load_packed2(a[0], b[0], q);
    load_packed2(a[1], b[1], q + 32);
#endif
}

template<class V>
void v256_load_i_packed3(V& a, V& b, V& c, const void* p)
{
    p = detail::assume_aligned(p, 32);
    const char* q = reinterpret_cast<const char*>(p);
#if SIMDPP_USE_AVX2
    load(a, q);
    load(b, q + 32);
    load(c, q + 64);
    detail::mem_unpack3(a, b, c);
#else
    load_packed3(a[0], b[0], c[0], q);
    load_packed3(a[1], b[1], c[1], q + 48);
#endif
}

template<class V>
void v256_load_i_packed4(V& a, V& b, V& c, V& d, const void* p)
{
    p = detail::assume_aligned(p, 32);
    const char* q = reinterpret_cast<const char*>(p);
#if SIMDPP_USE_AVX2
    load(a, q);
    load(b, q + 32);
    load(c, q + 64);
    load(d, q + 96);
    detail::mem_unpack4(a, b, c, d);
#else
    load_packed4(a[0], b[0], c[0], d[0], q);
    load_packed4(a[1], b[1], c[1], d[1], q + 64);
#endif
}

} // namespace detail
/// @{
/** Loads 8-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+30) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+62) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+63) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(basic_int8x16& a, basic_int8x16& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(basic_int8x32& a, basic_int8x32& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @{
/** Loads 16-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+30) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(basic_int16x8& a, basic_int16x8& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(basic_int16x16& a, basic_int16x16& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @{
/** Loads 32-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), *(p+6) ]
    b = [ *(p+1), *(p+3), *(p+5), *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(basic_int32x4& a, basic_int32x4& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);

    load(a, q);
    load(b, q+16);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(basic_int32x8& a, basic_int32x8& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @{
/** Loads 64-bit values packed in pairs, de-interleaves them and stores the
    result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2) ]
    b = [ *(p+1), *(p+3) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(basic_int64x2& a, basic_int64x2& b, const void* p)
{
    p = detail::assume_aligned(p, 16);
    const char* q = reinterpret_cast<const char*>(p);
    a = load(a, q);
    b = load(b, q+16);
    transpose2(a, b);
}

inline void load_packed2(basic_int64x4& a, basic_int64x4& b, const void* p)
{
    detail::v256_load_i_packed2(a, b, p);
}
/// @}

/// @}
/** Loads 32-bit float values packed in pairs, de-interleaves them and stores
    the result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+6) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), ... , *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.

*/
inline void load_packed2(float32x4& a, float32x4& b, const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed2(a, b, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    load(a, p);
    load(b, p+4);
    detail::mem_unpack2(a, b);
#elif SIMDPP_USE_NEON
    auto r = vld2q_f32(p);
    a = r.val[0];
    b = r.val[1];
#endif
}

inline void load_packed2(float32x8& a, float32x8& b, const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 8);
    detail::mem_unpack2(a, b);
#else
    load_packed2(a[0], b[0], p);
    load_packed2(a[1], b[1], p + 8);
#endif
}
/// @}

/// @{
/** Loads 64-bit float values packed in pairs, de-interleaves them and stores
    the result into two vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+2) ]
    b = [ *(p+1), *(p+3) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+2), *(p+4), *(p+14) ]
    b = [ *(p+1), *(p+3), *(p+5), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed2(float64x2& a, float64x2& b, const double* p)
{
    p = detail::assume_aligned(p, 16);
    a = load(a, p);
    b = load(b, p+2);
    transpose2(a, b);
}

inline void load_packed2(float64x4& a, float64x4& b, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 4);
    detail::mem_unpack2(a, b);
#else
    load_packed2(a[0], b[0], p);
    load_packed2(a[1], b[1], p + 4);
#endif
}
/// @}

/// @{
/** Loads 8-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+45) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+93) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+94) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+95) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(basic_int8x16& a, basic_int8x16& b, basic_int8x16& c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

inline void load_packed3(basic_int8x32& a, basic_int8x32& b, basic_int8x32& c,
                         const void* p)
{
    detail::v256_load_i_packed3(a, b, c, p);
}
/// @}

/// @{
/** Loads 16-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+45) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(basic_int16x8& a, basic_int16x8& b, basic_int16x8& c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

inline void load_packed3(basic_int16x16& a, basic_int16x16& b, basic_int16x16& c,
                         const void* p)
{
    detail::v256_load_i_packed3(a, b, c, p);
}
/// @}

/// @{
/** Loads 32-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(basic_int32x4& a, basic_int32x4& b, basic_int32x4&c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

inline void load_packed3(basic_int32x8& a, basic_int32x8& b, basic_int32x8& c,
                         const void* p)
{
    detail::v256_load_i_packed3(a, b, c, p);
}
/// @}

/// @{
/** Loads 64-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3) ]
    b = [ *(p+1), *(p+4) ]
    c = [ *(p+2), *(p+5) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(basic_int64x2& a, basic_int64x2& b, basic_int64x2& c,
                         const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    const char* q = reinterpret_cast<const char*>(p);
    uint64x2 a0, b0, c0;
    a0 = load(a0, q);
    b0 = load(b0, q+16);
    c0 = load(c0, q+32);

    int64x1_t al, bl, cl, ah, bh, ch;
    al = vget_low_u64(a0);
    ah = vget_high_u64(a0);
    bl = vget_low_u64(b0);
    bh = vget_high_u64(b0);
    cl = vget_low_u64(c0);
    ch = vget_high_u64(c0);
    a = vcombine_u64(al, bh);
    b = vcombine_u64(ah, cl);
    c = vcombine_u64(bl, ch);
#endif
}

inline void load_packed3(basic_int64x4& a, basic_int64x4& b, basic_int64x4& c,
                         const void* p)
{
    detail::v256_load_i_packed3(a, b, c, p);
}
/// @}

/// @{
/** Loads 32-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(float32x4& a, float32x4& b, float32x4& c,
                         const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    load(a, p);
    load(b, p+4);
    load(c, p+8);
    detail::mem_unpack3(a, b, c);
#elif SIMDPP_USE_NEON
    auto r = vld3q_f32(p);
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
#endif
}

inline void load_packed3(float32x8& a, float32x8& b, float32x8& c,
                         const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 8);
    load(c, p + 16);
    detail::mem_unpack3(a, b, c);
#else
    load_packed3(a[0], b[0], c[0], p);
    load_packed3(a[1], b[1], c[1], p + 12);
#endif
}
/// @}

/// @{
/** Loads 64-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3) ]
    b = [ *(p+1), *(p+4) ]
    c = [ *(p+2), *(p+5) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed3(float64x2& a, float64x2& b, float64x2& c, const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::load_packed3(a, b, c, p);
#elif SIMDPP_USE_SSE2
    load(a, p);
    load(b, p+2);
    load(c, p+4);
    detail::mem_unpack3(a, b, c);
#endif
}

inline void load_packed3(float64x4& a, float64x4& b, float64x4& c, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 4);
    load(c, p + 8);
    detail::mem_unpack3(a, b, c);
#else
    load_packed3(a[0], b[0], c[0], p);
    load_packed3(a[1], b[1], c[1], p + 6);
#endif
}
/// @}

/// @{
/** Loads 8-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+124) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+125) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+126) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+127) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(basic_int8x16& a, basic_int8x16& b,
                         basic_int8x16& c, basic_int8x16& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u8(reinterpret_cast<const uint8_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(basic_int8x32& a, basic_int8x32& b,
                         basic_int8x32& c, basic_int8x32& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 16-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+60) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+61) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+62) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+63) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(basic_int16x8& a, basic_int16x8& b,
                         basic_int16x8& c, basic_int16x8& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u16(reinterpret_cast<const uint16_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(basic_int16x16& a, basic_int16x16& b,
                         basic_int16x16& c, basic_int16x16& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 32-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(basic_int32x4& a, basic_int32x4& b,
                         basic_int32x4& c, basic_int32x4& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    const char* q = reinterpret_cast<const char*>(p);
    load(a, q);
    load(b, q+16);
    load(c, q+32);
    load(d, q+48);
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_u32(reinterpret_cast<const uint32_t*>(p));
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(basic_int32x8& a, basic_int32x8& b,
                         basic_int32x8& c, basic_int32x8& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 64-bit values packed in quartets, de-interleaves them and stores the
    result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4) ]
    b = [ *(p+1), *(p+5) ]
    c = [ *(p+2), *(p+6) ]
    d = [ *(p+3), *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(basic_int64x2& a, basic_int64x2& b,
                         basic_int64x2& c, basic_int64x2& d, const void* p)
{
    p = detail::assume_aligned(p, 16);
    const char* q = reinterpret_cast<const char*>(p);
    a = load(a, q);
    c = load(c, q+16);
    b = load(b, q+32);
    d = load(d, q+48);
    transpose2(a, b);
    transpose2(c, d);
}

inline void load_packed4(basic_int64x4& a, basic_int64x4& b,
                         basic_int64x4& c, basic_int64x4& d, const void* p)
{
    detail::v256_load_i_packed4(a, b, c, d, p);
}
/// @}

/// @{
/** Loads 32-bit floating-point values packed in quartets, de-interleaves them
    and stores the result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  ... , *(p+28) ]
    b = [ *(p+1), *(p+5), *(p+9),  ... , *(p+29) ]
    c = [ *(p+2), *(p+6), *(p+10), ... , *(p+30) ]
    d = [ *(p+3), *(p+7), *(p+11), ... , *(p+31) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(float32x4& a, float32x4& b, float32x4& c, float32x4& d,
                         const float* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    load(a, p);
    load(b, p+4);
    load(c, p+8);
    load(d, p+12);
    detail::mem_unpack4(a, b, c, d);
#elif SIMDPP_USE_NEON
    auto r = vld4q_f32(p);
    a = r.val[0];
    b = r.val[1];
    c = r.val[2];
    d = r.val[3];
#endif
}

inline void load_packed4(float32x8& a, float32x8& b,
                         float32x8& c, float32x8& d, const float* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 8);
    load(c, p + 16);
    load(d, p + 24);
    detail::mem_unpack4(a, b, c, d);
#else
    load_packed4(a[0], b[0], c[0], d[0], p);
    load_packed4(a[1], b[1], c[1], d[1], p + 16);
#endif
}
/// @}

/// @{
/** Loads 64-bit floating-point values packed in quartets, de-interleaves them
    and stores the result into four vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+4) ]
    b = [ *(p+1), *(p+5) ]
    c = [ *(p+2), *(p+6) ]
    d = [ *(p+3), *(p+7) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+4), *(p+8),  *(p+12) ]
    b = [ *(p+1), *(p+5), *(p+9),  *(p+13) ]
    c = [ *(p+2), *(p+6), *(p+10), *(p+14) ]
    d = [ *(p+3), *(p+7), *(p+11), *(p+15) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
inline void load_packed4(float64x2& a, float64x2& b, float64x2& c, float64x2& d,
                         const double* p)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    null::load_packed4(a, b, c, d, p);
#elif SIMDPP_USE_SSE2
    load(a, p);
    load(b, p+2);
    load(c, p+4);
    load(d, p+6);
    detail::mem_unpack4(a, b, c, d);
#endif
}

inline void load_packed4(float64x4& a, float64x4& b,
                         float64x4& c, float64x4& d, const double* p)
{
    p = detail::assume_aligned(p, 32);
#if SIMDPP_USE_AVX
    load(a, p);
    load(b, p + 4);
    load(c, p + 8);
    load(d, p + 12);
    detail::mem_unpack4(a, b, c, d);
#else
    load_packed4(a[0], b[0], c[0], d[0], p);
    load_packed4(a[1], b[1], c[1], d[1], p + 8);
#endif
}
/// @}

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
