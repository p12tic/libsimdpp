/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_EXTRACT_H
#define LIBSIMDPP_SIMD_EXTRACT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/i_shift_l.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_insert_extract
/// @{

/// @{
/** Extracts the @a id-th element from int8x16 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 1-2}
    @icost{SSE4.1-AVX, 1}
    @icost{ALTIVEC, 2}
*/
template<unsigned id>
uint8_t extract(uint8x16 a)
{
    static_assert(id < 16, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE4_1
    // Explicit cast is needed due to bug in Clang headers (intrinsic
    // implemented as a macro with no appropriate casts) and a bug in Clang
    // (thinks explicit conversion operators have the same rank as the regular
    // ones)
    return _mm_extract_epi8(a.operator __m128i(), id);
#elif SIMDPP_USE_SSE2
    unsigned shift = (id % 2 == 1) ? 8 : 0;
    return _mm_extract_epi16(a, id/2) >> shift;
#elif SIMDPP_USE_NEON
    return vgetq_lane_u8(a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint8x16> ax(a);
    vec_ste((__vector uint8_t)a, 0, &ax[id]);
    return ax[id];
#endif
}

template<unsigned id>
int8_t extract(int8x16 a)
{
    return extract<id>(uint8x16(a));
}
/// @}

/// @{
/** Extracts the @a id-th element from int16x8 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{ALTIVEC, 2}
*/
template<unsigned id>
uint16_t extract(uint16x8 a)
{
    static_assert(id < 8, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return _mm_extract_epi16(a, id);
#elif SIMDPP_USE_NEON
    return vgetq_lane_u16(a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint16x8> ax(a);
    vec_ste((__vector uint16_t)a, 0, &ax[id]);
    return ax[id];
#endif
}

template<unsigned id>
int16_t extract(int16x8 a)
{
    return extract<id>(uint16x8(a));
}
/// @}

/// @{
/** Extracts the @a id-th element from int32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
    @icost{ALTIVEC, 2}
*/
template<unsigned id>
uint32_t extract(uint32x4 a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE4_1
    return _mm_extract_epi32(a.operator __m128i(), id);
#elif SIMDPP_USE_SSE2
    // when id==0, move_l is template-specialized and does nothing
    return _mm_cvtsi128_si32(move4_l<id>(a).eval());
#elif SIMDPP_USE_NEON
    return vgetq_lane_u32(a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint32x4> ax(a);
    vec_ste((__vector uint32_t)a, 0, &ax[id]);
    return ax[id];
#endif
}

template<unsigned id>
int32_t extract(int32x4 a)
{
    return extract<id>(uint32x4(a));
}
/// @}

/// @{
/** Extracts an element from int64x2 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
    @icost{SSE4_1, 1}
    @icost{SSE2_32bit, SSE3_32bit, SSSE3_32bit, 3-4}
    @icost{SSE4_1_32bit, 2}
    @icost{ALTIVEC, 2}
*/
template<unsigned id>
uint64_t extract(uint64x2 a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE4_1
#if SIMDPP_SSE_32_BITS
    uint32x4 t = a;
    uint64_t r = extract<id*2>(t);
    r |= uint64_t(extract<id*2+1>(t)) << 32;
    return r;
#else
    return _mm_extract_epi64(a.operator __m128i(), id);
#endif
#elif SIMDPP_USE_SSE2
#if SIMDPP_SSE_32_BITS
    uint32x4 t = a;
    uint64_t r = 0;
    t = move4_l<id*2>(t); // when id==0, move_l is template-specialized and does nothing
    r = extract<0>(t);
    t = move4_l<1>(t);
    r |= uint64_t(extract<0>(t)) << 32;
    return r;
#else
    uint64x2 t = a;
    if (id != 0) {
        t = move2_l<id>(t);
    }
    return _mm_cvtsi128_si64(t);
#endif
#elif SIMDPP_USE_NEON
    return vgetq_lane_u64(a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<uint64x2> ax(a);
    return ax[id];
#endif
}

template<unsigned id>
int64_t extract(int64x2 a)
{
    return extract<id>(uint64x2(a));
}
/// @}

/** Extracts an element from float32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
    @icost{ALTIVEC, 2}
*/
template<unsigned id>
float extract(float32x4 a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return bit_cast<float>(extract<id>(int32x4(a)));
#elif SIMDPP_USE_NEON
    return vgetq_lane_f32(a, id);
#elif SIMDPP_USE_ALTIVEC
    detail::mem_block<float32x4> ax(a);
    vec_ste((__vector float)a, 0, &ax[id]);
    return ax[id];
#endif
}

/** Extracts an element from float64x2 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned id>
double extract(float64x2 a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return bit_cast<double>(extract<id>(int64x2(a)));
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<float64x2> ax(a);
    return a.el(id);
#endif
}

/** Extracts a bit from each byte of each element of a int8x16 vector.

    This operation is only sensible if each byte within the vector is either
    0x00 or 0xff.

    @code
    r = ((a[0] & 0x??) ? 0x01 : 0) |
        ((a[1] & 0x??) ? 0x02 : 0) |
        ...
        ((a[15] & 0x??) ? 0x80 : 0)
    @endcode

    @icost{NEON, 6-7}
    @icost{ALTIVEC, 8-9}
*/
inline uint16_t extract_bits_any(uint8x16 a)
{
    // extract_bits_impl depends on the exact implementation of this function
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    null::foreach<uint8x16>(a, [&r](uint8_t x){
        x = x & 1;
        r = (r >> 1) | (uint16_t(x) << 15);
        return 0; // dummy
    });
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_movemask_epi8(a);
#elif SIMDPP_USE_NEON
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

    a = bit_and(a, mask);
    a = vpaddlq_u8(a);
    a = vpaddlq_u16(a);
    a = vpaddlq_u32(a);
    uint8x8_t r = vzip_u8(vget_low_u8(a), vget_high_u8(a)).val[0];
    return vget_lane_u16(vreinterpret_u16_u8(r), 0);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);
    a = bit_and(a, mask);
    uint32x4 s = vec_sum4s((__vector uint8_t)a,
                           (__vector uint32_t)uint32x4::zero());
    uint32x4 s2 = (__vector uint32_t)vec_mergel((__vector uint8_t)a,
                                                (__vector uint8_t)uint8x16::zero());
    s = bit_or(s, s2);
    s = (int32x4)vec_sums((__vector int32_t)s,
                          (__vector int32_t)int32x4::zero());
    return extract<7>(uint16x8(s));
#endif
}

/** Extracts specific bit from each byte of each element of a int8x16 vector.

    The default template argument selects the bits from each byte in most
    efficient way.

    @code
    r = (a[0] & 0x80 >> 7) | (a[1] & 0x80 >> 6) | ...  | (a[15] & 0x80 << 8)
    @endcode

    @icost{SSE2-AVX2, 2}
    @icost{NEON, 7-9}
    @icost{ALTIVEC, 9-11}
*/
template<unsigned id>
uint16_t extract_bits(uint8x16 a)
{
    static_assert(id < 8, "index out of bounds");
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    null::foreach<uint8x16>(a, [&r](uint8_t x){
        x = (x >> id) & 1;
        r = (r >> 1) | (uint16_t(x) << 15);
        return 0; // dummy
    });
    return r;
#elif SIMDPP_USE_SSE2
    a = shift_l<7-id>((uint16x8) a);
    return extract_bits_any(a);
#elif SIMDPP_USE_NEON
    int8x16 shift_mask = make_int(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                                  4-int(id), 5-int(id), 6-int(id), 7-int(id));

    a = vshlq_u8(a, shift_mask);
    return extract_bits_any(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 rot_mask = make_int(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                                 4-int(id), 5-int(id), 6-int(id), 7-int(id));
    a = vec_rl((__vector uint8_t)a, (__vector uint8_t)rot_mask);
    return extract_bits_any(a);
#endif
}

namespace detail {

template<class A, class R>
void v256_split(A a, R& r1, R& r2)
{
#if SIMDPP_USE_AVX2
    r1 = _mm256_extracti128_si256(a, 0);
    r2 = _mm256_extracti128_si256(a, 1);
#else
    r1 = a[0];
    r2 = a[1];
#endif
}

} // namespcae detail
/// @{
/** Splits a 256-bit vector into two 128-bit vectors.

    @code
    [ r1, r2 ] = a
    @endcode

    @icost{AVX2, 1}
    @icost{SSE2-AVX, NEON, ALTIVEC, 0}
*/
inline void split(uint8x32 a, uint8x16& r1, uint8x16& r2)  { detail::v256_split(a, r1, r2); }
inline void split(uint16x16 a, uint16x8& r1, uint16x8& r2) { detail::v256_split(a, r1, r2); }
inline void split(uint32x8 a, uint32x4& r1, uint32x4& r2)  { detail::v256_split(a, r1, r2); }
inline void split(uint64x4 a, uint64x2& r1, uint64x2& r2)  { detail::v256_split(a, r1, r2); }

inline void split(int8x32 a, int8x16& r1, int8x16& r2)  { detail::v256_split(a, r1, r2); }
inline void split(int16x16 a, int16x8& r1, int16x8& r2) { detail::v256_split(a, r1, r2); }
inline void split(int32x8 a, int32x4& r1, int32x4& r2)  { detail::v256_split(a, r1, r2); }
inline void split(int64x4 a, int64x2& r1, int64x2& r2)  { detail::v256_split(a, r1, r2); }

inline void split(float32x8 a, float32x4& r1, float32x4& r2)
{
#if SIMDPP_USE_AVX
    r1 = _mm256_extractf128_ps(a, 0);
    r2 = _mm256_extractf128_ps(a, 1);
#else
    r1 = a[0];
    r2 = a[1];
#endif
}

inline void split(float64x4 a, float64x2& r1, float64x2& r2)
{
#if SIMDPP_USE_AVX
    r1 = _mm256_extractf128_pd(a, 0);
    r2 = _mm256_extractf128_pd(a, 1);
#else
    r1 = a[0];
    r2 = a[1];
#endif
}

namespace detail {

template<class V, class H>
void v_split(V a, H& r1, H& r2)
{
    unsigned h = H::vec_length;
    for (unsigned i = 0; i < h; ++i) { r1[i] = a[i]; }
    for (unsigned i = 0; i < h; ++i) { r2[i] = a[i+h]; }
}

} // namespace detail

template<unsigned N>
void split(uint8<N> a, uint8<N/2>& r1, uint8<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(uint16<N> a, uint16<N/2>& r1, uint16<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(uint32<N> a, uint32<N/2>& r1, uint32<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(uint64<N> a, uint64<N/2>& r1, uint64<N/2>& r2) { detail::v_split(a, r1, r2); }

template<unsigned N>
void split(int8<N> a, int8<N/2>& r1, int8<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(int16<N> a, int16<N/2>& r1, int16<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(int32<N> a, int32<N/2>& r1, int32<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(int64<N> a, int64<N/2>& r1, int64<N/2>& r2) { detail::v_split(a, r1, r2); }

template<unsigned N>
void split(float32<N> a, float32<N/2>& r1, float32<N/2>& r2) { detail::v_split(a, r1, r2); }
template<unsigned N>
void split(float64<N> a, float64<N/2>& r1, float64<N/2>& r2) { detail::v_split(a, r1, r2); }

/// @}

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


