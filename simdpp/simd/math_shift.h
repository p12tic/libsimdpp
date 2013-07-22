/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_MATH_SHIFT_H
#define LIBSIMDPP_SIMD_MATH_SHIFT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle_generic.h>
#include <simdpp/simd/extract.h>

#if SIMDPP_USE_NULL
    #include <simdpp/null/math.h>
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/// @{
/** Shifts signed 8-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 12}
    @icost{AVX2, 6}
    @icost{NEON, 3}
*/
inline int8x16 shift_r(int8x16 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r(int16x8(lo), count);
    lo = shift_r<8>(lo);

    hi = shift_r(int16x8(hi), 8+count);
    hi = shift_l<8>(hi);
    a = bit_or(lo, hi);    //higher part of lo is already clear
    return a;
#elif SIMDPP_USE_NEON
    int8x16 shift = int8x16::set_broadcast(-int(count));
    return vshlq_s8(a, shift);
#endif
}

inline int8x32 shift_r(int8x32 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    uint16x16 hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r(int16x16(lo), count);
    lo = shift_r<8>(lo);

    hi = shift_r(int16x16(hi), 8+count);
    hi = shift_l<8>(hi);
    a = bit_or(lo, hi);    //higher part of lo is already clear
    return a;
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts unsigned 8-bit values right by @a count bits while shifting in zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 5}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 10}
    @icost{AVX2, 5}
    @icost{NEON, 3}
*/
inline uint8x16 shift_r(uint8x16 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, a16;
    mask = int128::ones();
    mask = shift_l(mask, 16-count);
    mask = shift_r<8>(mask);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
#elif SIMDPP_USE_NEON
    int8x16 shift = int8x16::set_broadcast(-int(count));
    return vshlq_u8(a, shift);
#endif
}

inline uint8x32 shift_r(uint8x32 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    uint16x16 mask, a16;
    mask = int256::ones();
    mask = shift_l(mask, 16-count);
    mask = shift_r<8>(mask);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts signed 16-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline int16x8 shift_r(int16x8 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srai_epi16(a, count);
#elif SIMDPP_USE_NEON
    int16x8 shift = int16x8::set_broadcast(-int(count));
    return vshlq_s16(a, shift);
#endif
}

inline int16x16 shift_r(int16x16 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_srai_epi16(a, count);
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts unsigned 16-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline uint16x8 shift_r(uint16x8 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srli_epi16(a, count);
#elif SIMDPP_USE_NEON
    int16x8 shift = int16x8::set_broadcast(-int(count));
    return vshlq_u16(a, shift);
#endif
}

inline uint16x16 shift_r(uint16x16 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_srli_epi16(a, count);
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts signed 32-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode
    @icost{NEON, 2}

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline int32x4 shift_r(int32x4 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srai_epi32(a, count);
#elif SIMDPP_USE_NEON
    int32x4 shift = int32x4::set_broadcast(-int(count));
    return vshlq_s32(a, shift);
#endif
}

inline int32x8 shift_r(int32x8 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_srai_epi32(a, count);
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts unsigned 32-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline uint32x4 shift_r(uint32x4 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srli_epi32(a, count);
#elif SIMDPP_USE_NEON
    int32x4 shift = int32x4::set_broadcast(-int(count));
    return vshlq_u32(a, shift);
#endif
}

inline uint32x8 shift_r(uint32x8 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_srli_epi32(a, count);
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts signed 64-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-6}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-10}
    @icost{AVX2, 4-6}
    @icost{NEON, 3}
*/
inline int64x2 shift_r(int64x2 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    if (count > 31) {
        int32x4 s, v;
        v = a;
        s = shift_r<31>(v);
        v = shift_r(v, count - 32);
        v = shuffle2<1,3,1,3>(v, s);
        v = permute<0,2,1,3>(v);
        return v;
    } else {
        uint64x2 v, mask;
        int32x4 sgn;
        v = sgn = a;
        v = shift_r(v, count);
        sgn = shift_r(sgn, count);
        mask = int128::ones();
        mask = shift_l(mask, 64 - count);
        sgn = bit_and(sgn, mask);
        v = bit_or(v, sgn);
        return v;
    }
#elif SIMDPP_USE_NEON
    int64x2 shift = int64x2::set_broadcast(-int(count));
    return vshlq_s64(a, shift);
#endif
}

inline int64x4 shift_r(int64x4 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    // a copy of the 128-bit implementation
    if (count > 31) {
        int32x8 s, v;
        v = a;
        s = shift_r<31>(v);
        v = shift_r(v, count - 32);
        v = shuffle2<1,3,1,3>(v, s);
        v = permute<0,2,1,3>(v);
        return v;
    } else {
        uint64x4 v, mask;
        int32x8 sgn;
        v = sgn = a;
        v = shift_r(v, count);
        sgn = shift_r(sgn, count);
        mask = int256::ones();
        mask = shift_l(mask, 64 - count);
        sgn = bit_and(sgn, mask);
        v = bit_or(v, sgn);
        return v;
    }
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts unsigned 64-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline uint64x2 shift_r(uint64x2 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srli_epi64(a, count);
#elif SIMDPP_USE_NEON
    int64x2 shift = int64x2::set_broadcast(-int(count));
    return vshlq_u64(a, shift);
#endif
}

inline uint64x4 shift_r(uint64x4 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_srli_epi64(a, count);
#else
    return {shift_r(a[0], count), shift_r(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode


    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 10}
    @icost{AVX2, 5}
    @icost{NEON, 3}
*/
inline basic_int8x16 shift_l(basic_int8x16 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, a16;
    mask = int128::ones();
    mask = shift_r(mask, 16-count);
    mask = shift_l(mask, 8);

    a16 = a;
    a16 = shift_l(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
#elif SIMDPP_USE_NEON
    int8x16 shift = int8x16::set_broadcast(count);
    return vshlq_u8(a, shift);
#endif
}

inline basic_int8x32 shift_l(basic_int8x32 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    uint16x16 mask, a16;
    mask = int256::ones();
    mask = shift_r(mask, 16-count);
    mask = shift_l(mask, 8);

    a16 = a;
    a16 = shift_l(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
#else
    return {shift_l(a[0], count), shift_l(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline basic_int16x8 shift_l(basic_int16x8 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi16(a, count);
#elif SIMDPP_USE_NEON
    int16x8 shift = int16x8::set_broadcast(count);
    return vshlq_u16(a, shift);
#endif
}

inline basic_int16x16 shift_l(basic_int16x16 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_slli_epi16(a, count);
#else
    return {shift_l(a[0], count), shift_l(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline basic_int32x4 shift_l(basic_int32x4 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi32(a, count);
#elif SIMDPP_USE_NEON
    int32x4 shift = int32x4::set_broadcast(count);
    return vshlq_u32(a, shift);
#endif
}

inline basic_int32x8 shift_l(basic_int32x8 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_slli_epi32(a, count);
#else
    return {shift_l(a[0], count), shift_l(a[1], count)};
#endif
}
/// @}

/// @{
/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 3}
*/
inline basic_int64x2 shift_l(basic_int64x2 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi64(a, count);
#elif SIMDPP_USE_NEON
    int64x2 shift = int64x2::set_broadcast(count);
    return vshlq_u64(a, shift);
#endif
}

inline basic_int64x4 shift_l(basic_int64x4 a, unsigned count)
{
#if SIMDPP_USE_AVX2
    return _mm256_slli_epi64(a, count);
#else
    return {shift_l(a[0], count), shift_l(a[1], count)};
#endif
}
/// @}

namespace detail {

// 256-bit cases are boilerplate code to use a dynamic version on
// AVX2 or half-width static version otherwise.
template<unsigned count, class V>
V v256_shift_r(V a)
{
#if SIMDPP_USE_AVX2
    return shift_r(a, count);
#else
    return {shift_r<count>(a[0]), shift_r<count>(a[1])};
#endif
}

template<unsigned count, class V>
V v256_shift_l(V a)
{
#if SIMDPP_USE_AVX2
    return shift_l(a, count);
#else
    return {shift_l<count>(a[0]), shift_l<count>(a[1])};
#endif
}

template<unsigned count, class V>
struct shift_u8_mask;

template<class V>
struct shift_u8_mask<1,V> { V operator()() { return V::make_const(0x01); } };
template<class V>
struct shift_u8_mask<2,V> { V operator()() { return V::make_const(0x03); } };
template<class V>
struct shift_u8_mask<3,V> { V operator()() { return V::make_const(0x07); } };
template<class V>
struct shift_u8_mask<4,V> { V operator()() { return V::make_const(0x0f); } };
template<class V>
struct shift_u8_mask<5,V> { V operator()() { return V::make_const(0x1f); } };
template<class V>
struct shift_u8_mask<6,V> { V operator()() { return V::make_const(0x3f); } };
template<class V>
struct shift_u8_mask<7,V> { V operator()() { return V::make_const(0x7f); } };

template<unsigned count>
uint8x16 shift_r_u8(uint8x16 a)
{
#if SIMDPP_USE_NULL
    return shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint8x16 mask = detail::shift_u8_mask<count, uint8x16>()();
    uint16x8 a16 = bit_andnot(a, mask);
    a16 = shift_r<count>(a16);
    return a16;
#elif SIMDPP_USE_NEON
    return vshrq_n_u8(a, count);
#endif
}

template<unsigned count>
uint8x32 shift_r_u8(uint8x32 a)
{
#if SIMDPP_USE_NULL
    return shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint8x32 mask = detail::shift_u8_mask<count, uint8x32>()();
    uint16x16 a16 = bit_andnot(a, mask);
    a16 = shift_r<count>(a16);
    return a16;
#elif SIMDPP_USE_NEON
    return { shift_r_u8<count>(a[0]), shift_r_u8<count>(a[1]) };
#endif
}

template<unsigned count>
basic_int8x16 shift_l_8(basic_int8x16 a)
{
#if SIMDPP_USE_NULL
    return shift_l(a, count);
#elif SIMDPP_USE_SSE2
    uint8x16 mask = detail::shift_u8_mask<8-count, uint8x16>()();
    uint16x8 a16 = bit_and(a, mask);
    a16 = shift_l<count>(a16);
    return a16;
#elif SIMDPP_USE_NEON
    return vshlq_n_u8(a, count);
#endif
}

template<unsigned count>
basic_int8x32 shift_l_8(basic_int8x32 a)
{
#if SIMDPP_USE_NULL
    return shift_l(a, count);
#elif SIMDPP_USE_SSE2
    uint8x32 mask = detail::shift_u8_mask<8-count, uint8x32>()();
    uint16x16 a16 = bit_and(a, mask);
    a16 = shift_l<count>(a16);
    return a16;
#elif SIMDPP_USE_NEON
    return { shift_l_8<count>(a[0]), shift_l_8<count>(a[1]) };
#endif
}

} // namespace detail

/// @{
/** Shifts signed 8-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 12}
    @icost{AVX2, 5}
    @icost{NEON, 3}
*/
template<unsigned count>
int8x16 shift_r(int8x16 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_s8(a, count);
#endif
}

template<unsigned count>
int8x32 shift_r(int8x32 a) { return detail::v256_shift_r<count>(a); }

template<> inline int8x16 shift_r<0>(int8x16 a) { return a; }
template<> inline int8x32 shift_r<0>(int8x32 a) { return a; }
/// @}

/// @{
/** Shifts unsigned 8-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 3}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2,NEON, 3}
*/
template<unsigned count>
uint8x16 shift_r(uint8x16 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u8(a, count);
#endif
}

template<unsigned count>
uint8x32 shift_r(uint8x32 a) { return detail::v256_shift_r<count>(a); }

template<> inline uint8x16 shift_r<0>(uint8x16 a) { return a; }
template<> inline uint8x32 shift_r<0>(uint8x32 a) { return a; }

template<> inline uint8x16 shift_r<1>(uint8x16 a) { return detail::shift_r_u8<1>(a); }
template<> inline uint8x32 shift_r<1>(uint8x32 a) { return detail::shift_r_u8<1>(a); }
template<> inline uint8x16 shift_r<2>(uint8x16 a) { return detail::shift_r_u8<2>(a); }
template<> inline uint8x32 shift_r<2>(uint8x32 a) { return detail::shift_r_u8<2>(a); }
template<> inline uint8x16 shift_r<3>(uint8x16 a) { return detail::shift_r_u8<3>(a); }
template<> inline uint8x32 shift_r<3>(uint8x32 a) { return detail::shift_r_u8<3>(a); }
template<> inline uint8x16 shift_r<4>(uint8x16 a) { return detail::shift_r_u8<4>(a); }
template<> inline uint8x32 shift_r<4>(uint8x32 a) { return detail::shift_r_u8<4>(a); }
template<> inline uint8x16 shift_r<5>(uint8x16 a) { return detail::shift_r_u8<5>(a); }
template<> inline uint8x32 shift_r<5>(uint8x32 a) { return detail::shift_r_u8<5>(a); }
template<> inline uint8x16 shift_r<6>(uint8x16 a) { return detail::shift_r_u8<6>(a); }
template<> inline uint8x32 shift_r<6>(uint8x32 a) { return detail::shift_r_u8<6>(a); }
template<> inline uint8x16 shift_r<7>(uint8x16 a) { return detail::shift_r_u8<7>(a); }
template<> inline uint8x32 shift_r<7>(uint8x32 a) { return detail::shift_r_u8<7>(a); }

template<> inline uint8x16 shift_r<8>(uint8x16) { return uint8x16::zero(); }
template<> inline uint8x32 shift_r<8>(uint8x32) { return uint8x32::zero(); }
/// @}

/// @{
/** Shifts signed 16-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
int16x8 shift_r(int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srai_epi16(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_s16(a, count);
#endif
}

template<unsigned count>
int16x16 shift_r(int16x16 a) { return detail::v256_shift_r<count>(a); }

template<> inline int16x8  shift_r<0>(int16x8 a) { return a; }
template<> inline int16x16 shift_r<0>(int16x16 a) { return a; }
/// @}

/// @{
/** Shifts unsigned 16-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
uint16x8 shift_r(uint16x8 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u16(a, count);
#endif
}

template<unsigned count>
uint16x16 shift_r(uint16x16 a) { return detail::v256_shift_r<count>(a); }

template<> inline uint16x8 shift_r<0>(uint16x8 a) { return a; }
template<> inline uint16x16 shift_r<0>(uint16x16 a) { return a; }
/// @}

/// @{
/** Shifts signed 32-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
int32x4 shift_r(int32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_s32(a, count);
#endif
}

template<unsigned count>
int32x8 shift_r(int32x8 a) { return detail::v256_shift_r<count>(a); }

template<> inline int32x4 shift_r<0>(int32x4 a) { return a; }
template<> inline int32x8 shift_r<0>(int32x8 a) { return a; }
/// @}

/// @{
/** Shifts unsigned 32-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
uint32x4 shift_r(uint32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u32(a, count);
#endif
}

template<unsigned count>
uint32x8 shift_r(uint32x8 a) { return detail::v256_shift_r<count>(a); }

template<> inline uint32x4 shift_r<0>(uint32x4 a) { return a; }
template<> inline uint32x8 shift_r<0>(uint32x8 a) { return a; }
/// @}

/// @{
/** Shifts signed 64-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @novec{SSE2-AVX2}
    @icost{SSE2-AVX2, 4-8}

    @par 256-bit version:
    @novec{SSE2-AVX}
    @icost{SSE2-AVX, 8-16}
    @icost{AVX2, 4-8}
    @icost{NEON, 2}
*/
template<unsigned count>
int64x2 shift_r(int64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_s64(a, count);
#endif
}

template<unsigned count>
int64x4 shift_r(int64x4 a)
{
    return detail::v256_shift_r<count>(a);
}

template<> inline int64x2 shift_r<0>(int64x2 a) { return a; }
template<> inline int64x4 shift_r<0>(int64x4 a) { return a; }
/// @}

/// @{
/** Shifts unsigned 64-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
uint64x2 shift_r(uint64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return vshrq_n_u64(a, count);
#endif
}

template<unsigned count>
uint64x4 shift_r(uint64x4 a)
{
    return detail::v256_shift_r<count>(a);
}

template<> inline uint64x2 shift_r<0>(uint64x2 a) { return a; }
template<> inline uint64x4 shift_r<0>(uint64x4 a) { return a; }
/// @}

/// @{
/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode


    @par 128-bit version:
    @icost{SSE2-AVX2, 3}
    @icost{NEON, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2,NEON, 3}
*/
template<unsigned count>
basic_int8x16 shift_l(basic_int8x16 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u8(a, count);
#endif
}

template<unsigned count>
inline basic_int8x32 shift_l(basic_int8x32 a)
{
    return detail::v256_shift_l<count>(a);
}

template<> inline basic_int8x16 shift_l<0>(basic_int8x16 a) { return a; }
template<> inline basic_int8x32 shift_l<0>(basic_int8x32 a) { return a; }

template<> inline basic_int8x16 shift_l<1>(basic_int8x16 a) { return detail::shift_l_8<1>(a); }
template<> inline basic_int8x32 shift_l<1>(basic_int8x32 a) { return detail::shift_l_8<1>(a); }
template<> inline basic_int8x16 shift_l<2>(basic_int8x16 a) { return detail::shift_l_8<2>(a); }
template<> inline basic_int8x32 shift_l<2>(basic_int8x32 a) { return detail::shift_l_8<2>(a); }
template<> inline basic_int8x16 shift_l<3>(basic_int8x16 a) { return detail::shift_l_8<3>(a); }
template<> inline basic_int8x32 shift_l<3>(basic_int8x32 a) { return detail::shift_l_8<3>(a); }
template<> inline basic_int8x16 shift_l<4>(basic_int8x16 a) { return detail::shift_l_8<4>(a); }
template<> inline basic_int8x32 shift_l<4>(basic_int8x32 a) { return detail::shift_l_8<4>(a); }
template<> inline basic_int8x16 shift_l<5>(basic_int8x16 a) { return detail::shift_l_8<5>(a); }
template<> inline basic_int8x32 shift_l<5>(basic_int8x32 a) { return detail::shift_l_8<5>(a); }
template<> inline basic_int8x16 shift_l<6>(basic_int8x16 a) { return detail::shift_l_8<6>(a); }
template<> inline basic_int8x32 shift_l<6>(basic_int8x32 a) { return detail::shift_l_8<6>(a); }
template<> inline basic_int8x16 shift_l<7>(basic_int8x16 a) { return detail::shift_l_8<7>(a); }
template<> inline basic_int8x32 shift_l<7>(basic_int8x32 a) { return detail::shift_l_8<7>(a); }

template<> inline basic_int8x16 shift_l<8>(basic_int8x16) { return uint8x16::zero(); }
template<> inline basic_int8x32 shift_l<8>(basic_int8x32) { return uint8x32::zero(); }
/// @}

/// @{
/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
basic_int16x8 shift_l(basic_int16x8 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u16(a, count);
#endif
}

template<unsigned count>
inline basic_int16x16 shift_l(basic_int16x16 a)
{
    return detail::v256_shift_l<count>(a);
}

template<> inline basic_int16x8  shift_l<0>(basic_int16x8 a) { return a; }
template<> inline basic_int16x16 shift_l<0>(basic_int16x16 a) { return a; }
/// @}

/// @{
/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
basic_int32x4 shift_l(basic_int32x4 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u32(a, count);
#endif
}

template<unsigned count>
inline basic_int32x8 shift_l(basic_int32x8 a)
{
    return detail::v256_shift_l<count>(a);
}

template<> inline basic_int32x4 shift_l<0>(basic_int32x4 a) { return a; }
template<> inline basic_int32x8 shift_l<0>(basic_int32x8 a) { return a; }
/// @}

/// @{
/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
*/
template<unsigned count>
basic_int64x2 shift_l(basic_int64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u64(a, count);
#endif
}

template<unsigned count>
inline basic_int64x4 shift_l(basic_int64x4 a)
{
    return detail::v256_shift_l<count>(a);
}

template<> inline basic_int64x2 shift_l<0>(basic_int64x2 a) { return a; }
template<> inline basic_int64x4 shift_l<0>(basic_int64x4 a) { return a; }
/// @}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
