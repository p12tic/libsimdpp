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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_INL
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/cast.h>
#include <simdpp/core/insert.h>
#include <simdpp/sse/extract_half.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

// The duplication below can be reduced a lot via use of templates.
// Let's prefer clarity.

#if SIMDPP_USE_SSE2

inline gint8x16 cast(gint8x16, gint16x8 a)     { return __m128i(a); }
inline gint8x16 cast(gint8x16, gint32x4 a)     { return __m128i(a); }
inline gint8x16 cast(gint8x16, gint64x2 a)     { return __m128i(a); }
inline gint8x16 cast(gint8x16, float32x4 a)    { return _mm_castps_si128(a); }
inline gint8x16 cast(gint8x16, float64x2 a)    { return _mm_castpd_si128(a); }

inline gint16x8 cast(gint16x8, gint8x16 a)     { return __m128i(a); }
inline gint16x8 cast(gint16x8, gint32x4 a)     { return __m128i(a); }
inline gint16x8 cast(gint16x8, gint64x2 a)     { return __m128i(a); }
inline gint16x8 cast(gint16x8, float32x4 a)    { return _mm_castps_si128(a); }
inline gint16x8 cast(gint16x8, float64x2 a)    { return _mm_castpd_si128(a); }

inline gint32x4 cast(gint32x4, gint8x16 a)     { return __m128i(a); }
inline gint32x4 cast(gint32x4, gint16x8 a)     { return __m128i(a); }
inline gint32x4 cast(gint32x4, gint64x2 a)     { return __m128i(a); }
inline gint32x4 cast(gint32x4, float32x4 a)    { return _mm_castps_si128(a); }
inline gint32x4 cast(gint32x4, float64x2 a)    { return _mm_castpd_si128(a); }

inline gint64x2 cast(gint64x2, gint8x16 a)     { return __m128i(a); }
inline gint64x2 cast(gint64x2, gint16x8 a)     { return __m128i(a); }
inline gint64x2 cast(gint64x2, gint32x4 a)     { return __m128i(a); }
inline gint64x2 cast(gint64x2, float32x4 a)    { return _mm_castps_si128(a); }
inline gint64x2 cast(gint64x2, float64x2 a)    { return _mm_castpd_si128(a); }

inline float32x4 cast(float32x4, gint8x16 a)   { return _mm_castsi128_ps(a); }
inline float32x4 cast(float32x4, gint16x8 a)   { return _mm_castsi128_ps(a); }
inline float32x4 cast(float32x4, gint32x4 a)   { return _mm_castsi128_ps(a); }
inline float32x4 cast(float32x4, gint64x2 a)   { return _mm_castsi128_ps(a); }
inline float32x4 cast(float32x4, float64x2 a)  { return _mm_castpd_ps(a); }

inline float64x2 cast(float64x2, gint8x16 a)   { return _mm_castsi128_pd(a); }
inline float64x2 cast(float64x2, gint16x8 a)   { return _mm_castsi128_pd(a); }
inline float64x2 cast(float64x2, gint32x4 a)   { return _mm_castsi128_pd(a); }
inline float64x2 cast(float64x2, gint64x2 a)   { return _mm_castsi128_pd(a); }
inline float64x2 cast(float64x2, float32x4 a)  { return _mm_castps_pd(a); }

#elif SIMDPP_USE_NEON

inline gint8x16 cast(gint8x16, gint16x8 a)     { return vreinterpretq_u8_u16(a); }
inline gint8x16 cast(gint8x16, gint32x4 a)     { return vreinterpretq_u8_u32(a); }
inline gint8x16 cast(gint8x16, gint64x2 a)     { return vreinterpretq_u8_u64(a); }
inline gint8x16 cast(gint8x16, float32x4 a)    { return vreinterpretq_u8_f32(a); }
inline gint8x16 cast(gint8x16, float64x2 a)    { return cast_memcpy<gint8x16>(a); }

inline gint16x8 cast(gint16x8, gint8x16 a)     { return vreinterpretq_u16_u8(a); }
inline gint16x8 cast(gint16x8, gint32x4 a)     { return vreinterpretq_u16_u32(a); }
inline gint16x8 cast(gint16x8, gint64x2 a)     { return vreinterpretq_u16_u64(a); }
inline gint16x8 cast(gint16x8, float32x4 a)    { return vreinterpretq_u16_f32(a); }
inline gint16x8 cast(gint16x8, float64x2 a)    { return cast_memcpy<gint16x8>(a); }

inline gint32x4 cast(gint32x4, gint8x16 a)     { return vreinterpretq_u32_u8(a); }
inline gint32x4 cast(gint32x4, gint16x8 a)     { return vreinterpretq_u32_u16(a); }
inline gint32x4 cast(gint32x4, gint64x2 a)     { return vreinterpretq_u32_u64(a); }
inline gint32x4 cast(gint32x4, float32x4 a)    { return vreinterpretq_u32_f32(a); }
inline gint32x4 cast(gint32x4, float64x2 a)    { return cast_memcpy<gint32x4>(a); }

inline gint64x2 cast(gint64x2, gint8x16 a)     { return vreinterpretq_u64_u8(a); }
inline gint64x2 cast(gint64x2, gint16x8 a)     { return vreinterpretq_u64_u16(a); }
inline gint64x2 cast(gint64x2, gint32x4 a)     { return vreinterpretq_u64_u32(a); }
inline gint64x2 cast(gint64x2, float32x4 a)    { return vreinterpretq_u64_f32(a); }
inline gint64x2 cast(gint64x2, float64x2 a)    { return cast_memcpy<gint64x2>(a); }

inline float32x4 cast(float32x4, gint8x16 a)   { return vreinterpretq_f32_u8(a); }
inline float32x4 cast(float32x4, gint16x8 a)   { return vreinterpretq_f32_u16(a); }
inline float32x4 cast(float32x4, gint32x4 a)   { return vreinterpretq_f32_u32(a); }
inline float32x4 cast(float32x4, gint64x2 a)   { return vreinterpretq_f32_u64(a); }
inline float32x4 cast(float32x4, float64x2 a)  { return cast_memcpy<float32x4>(a); }

inline float64x2 cast(float64x2, gint8x16 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, gint16x8 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, gint32x4 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, gint64x2 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, float32x4 a)  { return cast_memcpy<float64x2>(a); }

#elif SIMDPP_USE_ALTIVEC

inline gint8x16 cast(gint8x16, gint16x8 a)     { return (__vector uint8_t)(a); }
inline gint8x16 cast(gint8x16, gint32x4 a)     { return (__vector uint8_t)(a); }
inline gint8x16 cast(gint8x16, gint64x2 a)     { return (__vector uint8_t)(a); }
inline gint8x16 cast(gint8x16, float32x4 a)    { return (__vector uint8_t)(a); }
inline gint8x16 cast(gint8x16, float64x2 a)    { return cast_memcpy<gint8x16>(a); }

inline gint16x8 cast(gint16x8, gint8x16 a)     { return (__vector uint16_t)(a); }
inline gint16x8 cast(gint16x8, gint32x4 a)     { return (__vector uint16_t)(a); }
inline gint16x8 cast(gint16x8, gint64x2 a)     { return (__vector uint16_t)(a); }
inline gint16x8 cast(gint16x8, float32x4 a)    { return (__vector uint16_t)(a); }
inline gint16x8 cast(gint16x8, float64x2 a)    { return cast_memcpy<gint16x8>(a); }

inline gint32x4 cast(gint32x4, gint8x16 a)     { return (__vector uint32_t)(a); }
inline gint32x4 cast(gint32x4, gint16x8 a)     { return (__vector uint32_t)(a); }
inline gint32x4 cast(gint32x4, gint64x2 a)     { return (__vector uint32_t)(a); }
inline gint32x4 cast(gint32x4, float32x4 a)    { return (__vector uint32_t)(a); }
inline gint32x4 cast(gint32x4, float64x2 a)    { return cast_memcpy<gint32x4>(a); }

inline gint64x2 cast(gint64x2, gint8x16 a)     { return (__vector uint32_t)(a); }
inline gint64x2 cast(gint64x2, gint16x8 a)     { return (__vector uint32_t)(a); }
inline gint64x2 cast(gint64x2, gint32x4 a)     { return (__vector uint32_t)(a); }
inline gint64x2 cast(gint64x2, float32x4 a)    { return (__vector uint32_t)(a); }
inline gint64x2 cast(gint64x2, float64x2 a)    { return cast_memcpy<gint64x2>(a); }

inline float32x4 cast(float32x4, gint8x16 a)   { return (__vector float)(a); }
inline float32x4 cast(float32x4, gint16x8 a)   { return (__vector float)(a); }
inline float32x4 cast(float32x4, gint32x4 a)   { return (__vector float)(a); }
inline float32x4 cast(float32x4, gint64x2 a)   { return (__vector float)(a); }
inline float32x4 cast(float32x4, float64x2 a)  { return cast_memcpy<float32x4>(a); }

inline float64x2 cast(float64x2, gint8x16 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, gint16x8 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, gint32x4 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, gint64x2 a)   { return cast_memcpy<float64x2>(a); }
inline float64x2 cast(float64x2, float32x4 a)  { return cast_memcpy<float64x2>(a); }

#endif

#if SIMDPP_USE_AVX2

inline gint8x32 cast(gint8x32, gint16x16 a)    { return __m256(a); }
inline gint8x32 cast(gint8x32, gint32x8 a)     { return __m256(a); }
inline gint8x32 cast(gint8x32, gint64x4 a)     { return __m256(a); }
inline gint8x32 cast(gint8x32, float32x8 a)    { return _mm256_castps_si256(a); }
inline gint8x32 cast(gint8x32, float64x4 a)    { return _mm256_castpd_si256(a); }

inline gint16x16 cast(gint16x16, gint8x32 a)   { return __m256(a); }
inline gint16x16 cast(gint16x16, gint32x8 a)   { return __m256(a); }
inline gint16x16 cast(gint16x16, gint64x4 a)   { return __m256(a); }
inline gint16x16 cast(gint16x16, float32x8 a)  { return _mm256_castps_si256(a); }
inline gint16x16 cast(gint16x16, float64x4 a)  { return _mm256_castpd_si256(a); }

inline gint32x8 cast(gint32x8, gint8x32 a)     { return __m256(a); }
inline gint32x8 cast(gint32x8, gint16x16 a)    { return __m256(a); }
inline gint32x8 cast(gint32x8, gint64x4 a)     { return __m256(a); }
inline gint32x8 cast(gint32x8, float32x8 a)    { return _mm256_castps_si256(a); }
inline gint32x8 cast(gint32x8, float64x4 a)    { return _mm256_castpd_si256(a); }

inline gint64x4 cast(gint64x4, gint8x32 a)     { return __m256(a); }
inline gint64x4 cast(gint64x4, gint16x16 a)    { return __m256(a); }
inline gint64x4 cast(gint64x4, gint32x8 a)     { return __m256(a); }
inline gint64x4 cast(gint64x4, float32x8 a)    { return _mm256_castps_si256(a); }
inline gint64x4 cast(gint64x4, float64x4 a)    { return _mm256_castpd_si256(a); }

inline float32x8 cast(float32x8, gint8x32 a)   { return _mm256_castsi256_ps(a); }
inline float32x8 cast(float32x8, gint16x16 a)  { return _mm256_castsi256_ps(a); }
inline float32x8 cast(float32x8, gint32x8 a)   { return _mm256_castsi256_ps(a); }
inline float32x8 cast(float32x8, gint64x4 a)   { return _mm256_castsi256_ps(a); }
inline float32x8 cast(float32x8, float64x4 a)  { return _mm256_castpd_ps(a); }

inline float64x4 cast(float64x4, gint8x32 a)   { return _mm256_castsi256_pd(a); }
inline float64x4 cast(float64x4, gint16x16 a)  { return _mm256_castsi256_pd(a); }
inline float64x4 cast(float64x4, gint32x8 a)   { return _mm256_castsi256_pd(a); }
inline float64x4 cast(float64x4, gint64x4 a)   { return _mm256_castsi256_pd(a); }
inline float64x4 cast(float64x4, float32x8 a)  { return _mm256_castps_pd(a); }

#elif SIMDPP_USE_AVX

inline gint8x32 cast(gint8x32, float32x8 a)    { gint8x32 r; r[0] = _mm_castps_si128(sse::extract_lo(a));
                                                             r[1] = _mm_castps_si128(sse::extract_hi(a)); return r; }
inline gint8x32 cast(gint8x32, float64x4 a)    { gint8x32 r; r[0] = _mm_castpd_si128(sse::extract_lo(a));
                                                             r[1] = _mm_castpd_si128(sse::extract_hi(a)); return r; }

inline gint16x16 cast(gint16x16, float32x8 a)  { gint16x16 r; r[0] = _mm_castps_si128(sse::extract_lo(a));
                                                              r[1] = _mm_castps_si128(sse::extract_hi(a)); return r; }
inline gint16x16 cast(gint16x16, float64x4 a)  { gint16x16 r; r[0] = _mm_castpd_si128(sse::extract_lo(a));
                                                              r[1] = _mm_castpd_si128(sse::extract_hi(a)); return r; }

inline gint32x8 cast(gint32x8, float32x8 a)    { gint32x8 r; r[0] = _mm_castps_si128(sse::extract_lo(a));
                                                             r[1] = _mm_castps_si128(sse::extract_hi(a)); return r; }
inline gint32x8 cast(gint32x8, float64x4 a)    { gint32x8 r; r[0] = _mm_castpd_si128(sse::extract_lo(a));
                                                             r[1] = _mm_castpd_si128(sse::extract_hi(a)); return r; }

inline gint64x4 cast(gint64x4, float32x8 a)    { gint64x4 r; r[0] = _mm_castps_si128(sse::extract_lo(a));
                                                             r[1] = _mm_castps_si128(sse::extract_hi(a)); return r; }
inline gint64x4 cast(gint64x4, float64x4 a)    { gint64x4 r; r[0] = _mm_castpd_si128(sse::extract_lo(a));
                                                             r[1] = _mm_castpd_si128(sse::extract_hi(a)); return r; }

inline float32x8 cast(float32x8, gint8x32 a)   { return combine(_mm_castsi128_ps(a[0]), _mm_castsi128_ps(a[1])); }
inline float32x8 cast(float32x8, gint16x16 a)  { return combine(_mm_castsi128_ps(a[0]), _mm_castsi128_ps(a[1])); }
inline float32x8 cast(float32x8, gint32x8 a)   { return combine(_mm_castsi128_ps(a[0]), _mm_castsi128_ps(a[1])); }
inline float32x8 cast(float32x8, gint64x4 a)   { return combine(_mm_castsi128_ps(a[0]), _mm_castsi128_ps(a[1])); }
inline float32x8 cast(float32x8, float64x4 a)  { return _mm256_castps_pd(a); }

inline float64x4 cast(float64x4, gint8x32 a)   { return combine(_mm_castsi128_pd(a[0]), _mm_castsi128_pd(a[1])); }
inline float64x4 cast(float64x4, gint16x16 a)  { return combine(_mm_castsi128_pd(a[0]), _mm_castsi128_pd(a[1])); }
inline float64x4 cast(float64x4, gint32x8 a)   { return combine(_mm_castsi128_pd(a[0]), _mm_castsi128_pd(a[1])); }
inline float64x4 cast(float64x4, gint64x4 a)   { return combine(_mm_castsi128_pd(a[0]), _mm_castsi128_pd(a[1])); }
inline float64x4 cast(float64x4, float32x8 a)  { return _mm256_castpd_ps(a); }

#endif

/*  Depending on the sizes of the vector registers for different types we
    may need to combine several registers into one or the other way round.
    The implementation below does exactly that for different architectures
*/

#define SIMDPP_LOOP_BIT_CAST_BODY(TYPE, TYPE_V, ARG)        \
    TYPE r;                                                 \
    for (unsigned i = 0; i < TYPE::vec_length; ++i) {       \
        r[i] = cast(TYPE_V(), ARG[i]);                        \
    }                                                       \
    return r;

#define SIMDPP_LOOP_BIT_CAST_BODY_2X(TYPE, TYPE_V, ARG)     \
    TYPE r;                                                 \
    for (unsigned i = 0; i < TYPE::vec_length/2; ++i) {     \
        r[i*2]   = cast(TYPE_V(), sse::extract_lo(ARG[i]));   \
        r[i*2+1] = cast(TYPE_V(), sse::extract_hi(ARG[i]));   \
    }                                                       \
    return r;

#define SIMDPP_LOOP_BIT_CAST_BODY_X2(TYPE, TYPE_V, ARG)     \
    TYPE r;                                                 \
    for (unsigned i = 0; i < TYPE::vec_length; ++i) {       \
        r[i]   = combine(cast(TYPE_V(), ARG[i*2]),          \
                         cast(TYPE_V(), ARG[i*2+1]));       \
    }                                                       \
    return r;

#if SIMDPP_USE_NEON || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC

// always
template<unsigned N> gint8<N> cast(gint8<N>, gint16<N/2> a)     { SIMDPP_LOOP_BIT_CAST_BODY(gint8<N>, gint8v, a) }
template<unsigned N> gint8<N> cast(gint8<N>, gint32<N/4> a)     { SIMDPP_LOOP_BIT_CAST_BODY(gint8<N>, gint8v, a) }
template<unsigned N> gint8<N> cast(gint8<N>, gint64<N/8> a)     { SIMDPP_LOOP_BIT_CAST_BODY(gint8<N>, gint8v, a) }

template<unsigned N> gint16<N> cast(gint16<N>, gint8<N*2> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint16<N>, gint16v, a) }
template<unsigned N> gint16<N> cast(gint16<N>, gint32<N/2> a)   { SIMDPP_LOOP_BIT_CAST_BODY(gint16<N>, gint16v, a) }
template<unsigned N> gint16<N> cast(gint16<N>, gint64<N/4> a)   { SIMDPP_LOOP_BIT_CAST_BODY(gint16<N>, gint16v, a) }

template<unsigned N> gint32<N> cast(gint32<N>, gint8<N*4> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint32<N>, gint32v, a) }
template<unsigned N> gint32<N> cast(gint32<N>, gint16<N*2> a)   { SIMDPP_LOOP_BIT_CAST_BODY(gint32<N>, gint32v, a) }
template<unsigned N> gint32<N> cast(gint32<N>, gint64<N/2> a)   { SIMDPP_LOOP_BIT_CAST_BODY(gint32<N>, gint32v, a) }

template<unsigned N> gint64<N> cast(gint64<N>, gint8<N*8> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint64<N>, gint64v, a) }
template<unsigned N> gint64<N> cast(gint64<N>, gint16<N*4> a)   { SIMDPP_LOOP_BIT_CAST_BODY(gint64<N>, gint64v, a) }
template<unsigned N> gint64<N> cast(gint64<N>, gint32<N*2> a)   { SIMDPP_LOOP_BIT_CAST_BODY(gint64<N>, gint64v, a) }

#if SIMDPP_USE_AVX2 || !SIMDPP_USE_AVX
// ^^^ i.e. always except when plain AVX (no AVX2)

template<unsigned N> gint8<N> cast(gint8<N>, float32<N/4> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint8<N>, gint8v, a) }
template<unsigned N> gint8<N> cast(gint8<N>, float64<N/8> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint8<N>, gint8v, a) }
template<unsigned N> gint16<N> cast(gint16<N>, float32<N/2> a)  { SIMDPP_LOOP_BIT_CAST_BODY(gint16<N>, gint16v, a) }
template<unsigned N> gint16<N> cast(gint16<N>, float64<N/4> a)  { SIMDPP_LOOP_BIT_CAST_BODY(gint16<N>, gint16v, a) }
template<unsigned N> gint32<N> cast(gint32<N>, float32<N> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint32<N>, gint32v, a) }
template<unsigned N> gint32<N> cast(gint32<N>, float64<N/2> a)  { SIMDPP_LOOP_BIT_CAST_BODY(gint32<N>, gint32v, a) }
template<unsigned N> gint64<N> cast(gint64<N>, float32<N*2> a)  { SIMDPP_LOOP_BIT_CAST_BODY(gint64<N>, gint64v, a) }
template<unsigned N> gint64<N> cast(gint64<N>, float64<N> a)    { SIMDPP_LOOP_BIT_CAST_BODY(gint64<N>, gint64v, a) }

template<unsigned N> float32<N> cast(float32<N>, gint8<N*4> a)  { SIMDPP_LOOP_BIT_CAST_BODY(float32<N>, float32v, a) }
template<unsigned N> float32<N> cast(float32<N>, gint16<N*2> a) { SIMDPP_LOOP_BIT_CAST_BODY(float32<N>, float32v, a) }
template<unsigned N> float32<N> cast(float32<N>, gint32<N> a)   { SIMDPP_LOOP_BIT_CAST_BODY(float32<N>, float32v, a) }
template<unsigned N> float32<N> cast(float32<N>, gint64<N/2> a) { SIMDPP_LOOP_BIT_CAST_BODY(float32<N>, float32v, a) }
template<unsigned N> float32<N> cast(float32<N>, float64<N/2> a){ SIMDPP_LOOP_BIT_CAST_BODY(float32<N>, float32v, a) }

template<unsigned N> float64<N> cast(float64<N>, gint8<N*8> a)  { SIMDPP_LOOP_BIT_CAST_BODY(float64<N>, float64v, a) }
template<unsigned N> float64<N> cast(float64<N>, gint16<N*4> a) { SIMDPP_LOOP_BIT_CAST_BODY(float64<N>, float64v, a) }
template<unsigned N> float64<N> cast(float64<N>, gint32<N*2> a) { SIMDPP_LOOP_BIT_CAST_BODY(float64<N>, float64v, a) }
template<unsigned N> float64<N> cast(float64<N>, gint64<N> a)   { SIMDPP_LOOP_BIT_CAST_BODY(float64<N>, float64v, a) }
template<unsigned N> float64<N> cast(float64<N>, float32<N*2> a){ SIMDPP_LOOP_BIT_CAST_BODY(float64<N>, float64v, a) }

#else
// AVX
template<unsigned N> gint8<N> cast(gint8<N>, float32<N/4> a)    { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint8<N>, gint8v, a) }
template<unsigned N> gint8<N> cast(gint8<N>, float64<N/8> a)    { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint8<N>, gint8v, a) }
template<unsigned N> gint16<N> cast(gint16<N>, float32<N/2> a)  { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint16<N>, gint16v, a) }
template<unsigned N> gint16<N> cast(gint16<N>, float64<N/4> a)  { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint16<N>, gint16v, a) }
template<unsigned N> gint32<N> cast(gint32<N>, float32<N> a)    { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint32<N>, gint32v, a) }
template<unsigned N> gint32<N> cast(gint32<N>, float64<N/2> a)  { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint32<N>, gint32v, a) }
template<unsigned N> gint64<N> cast(gint64<N>, float32<N*2> a)  { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint64<N>, gint64v, a) }
template<unsigned N> gint64<N> cast(gint64<N>, float64<N> a)    { SIMDPP_LOOP_BIT_CAST_BODY_2X(gint64<N>, gint64v, a) }

template<unsigned N> float32<N> cast(float32<N>, gint8<N*4> a)  { SIMDPP_LOOP_BIT_CAST_BODY_X2(float32<N>, float32x4, a) }
template<unsigned N> float32<N> cast(float32<N>, gint16<N*2> a) { SIMDPP_LOOP_BIT_CAST_BODY_X2(float32<N>, float32x4, a) }
template<unsigned N> float32<N> cast(float32<N>, gint32<N> a)   { SIMDPP_LOOP_BIT_CAST_BODY_X2(float32<N>, float32x4, a) }
template<unsigned N> float32<N> cast(float32<N>, gint64<N/2> a) { SIMDPP_LOOP_BIT_CAST_BODY_X2(float32<N>, float32x4, a) }
template<unsigned N> float32<N> cast(float32<N>, float64<N/2> a){ SIMDPP_LOOP_BIT_CAST_BODY_X2(float32<N>, float32x4, a) }

template<unsigned N> float64<N> cast(float64<N>, gint8<N*8> a)  { SIMDPP_LOOP_BIT_CAST_BODY_X2(float64<N>, float64x2, a) }
template<unsigned N> float64<N> cast(float64<N>, gint16<N*4> a) { SIMDPP_LOOP_BIT_CAST_BODY_X2(float64<N>, float64x2, a) }
template<unsigned N> float64<N> cast(float64<N>, gint32<N*2> a) { SIMDPP_LOOP_BIT_CAST_BODY_X2(float64<N>, float64x2, a) }
template<unsigned N> float64<N> cast(float64<N>, gint64<N> a)   { SIMDPP_LOOP_BIT_CAST_BODY_X2(float64<N>, float64x2, a) }
template<unsigned N> float64<N> cast(float64<N>, float32<N*2> a){ SIMDPP_LOOP_BIT_CAST_BODY_X2(float64<N>, float64x2, a) }

#endif
#endif

template<unsigned N> gint8<N>   cast(gint8<N>,   gint8<N> a)    { return a; }
template<unsigned N> gint16<N>  cast(gint16<N>,  gint16<N> a)   { return a; }
template<unsigned N> gint32<N>  cast(gint32<N>,  gint32<N> a)   { return a; }
template<unsigned N> gint64<N>  cast(gint64<N>,  gint64<N> a)   { return a; }
template<unsigned N> float32<N> cast(float32<N>, float32<N> a)  { return a; }
template<unsigned N> float64<N> cast(float64<N>, float64<N> a)  { return a; }


} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
