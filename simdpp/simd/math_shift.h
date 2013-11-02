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
#if SIMDPP_USE_NEON
    #include <simdpp/neon/detail/math_shift.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @defgroup simd_shift Operations: shift
    @{
*/

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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 12}
    @icost{AVX2, 6}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::set_broadcast(count);
    return vec_sra((__vector int8_t)a, (__vector uint8_t)shift);
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
    @icost{SSE2-AVX2, 4-5}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::set_broadcast(count);
    return vec_sr((__vector uint8_t)a, (__vector uint8_t)shift);
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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::set_broadcast(count);
    return vec_sra((__vector int16_t)a, (__vector uint16_t)shift);
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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::set_broadcast(count);
    return vec_sr((__vector uint16_t)a, (__vector uint16_t)shift);
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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::set_broadcast(count);
    return vec_sra((__vector int32_t)a, (__vector uint32_t)shift);
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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::set_broadcast(count);
    return vec_sr((__vector uint32_t)a, (__vector uint32_t)shift);
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
    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-10}
    @icost{AVX2, 4-6}
    @icost{NEON, 3}
    @unimp{ALTIVEC}
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
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
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
    @icost{NEON, 1-2}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @unimp{ALTIVEC}
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
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
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
    @icost{SSE2-AVX, 4-5}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::set_broadcast(count);
    return vec_sl((__vector uint8_t)a, (__vector uint8_t)shift);
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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::set_broadcast(count);
    return vec_sl((__vector uint16_t)a, (__vector uint16_t)shift);
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
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
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
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::set_broadcast(count);
    return vec_sl((__vector uint32_t)a, (__vector uint32_t)shift);
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
    @icost{NEON, 1-2}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @unimp{ALTIVEC}
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
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, count);
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
struct shift_u8_mask<0,V> { V operator()() { return V::make_const(0x00); } };
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
template<class V>
struct shift_u8_mask<8,V> { V operator()() { return V::make_const(0xff); } };

template<unsigned count>
uint8x16 shift_r_u8(uint8x16 a)
{
#if SIMDPP_USE_SSE2
    uint8x16 mask = detail::shift_u8_mask<count, uint8x16>()();
    uint16x8 a16 = bit_andnot(a, mask);
    a16 = shift_r<count>(a16);
    return a16;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

template<unsigned count>
uint8x32 shift_r_u8(uint8x32 a)
{
#if SIMDPP_USE_SSE2
    uint8x32 mask = detail::shift_u8_mask<count, uint8x32>()();
    uint16x16 a16 = bit_andnot(a, mask);
    a16 = shift_r<count>(a16);
    return a16;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

template<unsigned count>
basic_int8x16 shift_l_8(basic_int8x16 a)
{
#if SIMDPP_USE_SSE2
    uint8x16 mask = detail::shift_u8_mask<8-count, uint8x16>()();
    uint16x8 a16 = bit_and(a, mask);
    a16 = shift_l<count>(a16);
    return a16;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

template<unsigned count>
basic_int8x32 shift_l_8(basic_int8x32 a)
{
#if SIMDPP_USE_SSE2
    uint8x32 mask = detail::shift_u8_mask<8-count, uint8x32>()();
    uint16x16 a16 = bit_and(a, mask);
    a16 = shift_l<count>(a16);
    return a16;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
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
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 12}
    @icost{AVX2, 6}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
int8x16 shift_r(int8x16 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::make_const(count);
    return vec_sra((__vector int8_t)a, (__vector uint8_t)shift);
#endif
}

template<unsigned count>
int8x32 shift_r(int8x32 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;

    return detail::v256_shift_r<count>(a);
}
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
    @icost{ALTIVEC, 1-2}
    @icost{SSE2-AVX2, 2-3}

    @par 256-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{AVX2, 2-3}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
uint8x16 shift_r(uint8x16 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8x16::zero();

#if SIMDPP_USE_NULL
    return shift_r(a, count);
#elif SIMDPP_USE_SSE2
    /*  SSE2-SSE4.1 and AVX-AVx2 instruction sets lack 8-bit shift. The
        optimization below emulates it using 16-bit shift
    */
    return detail::shift_r_u8<count>(a);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::make_const(count);
    return vec_sr((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

template<unsigned count>
uint8x32 shift_r(uint8x32 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8x32::zero();

    return detail::v256_shift_r<count>(a);
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
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
int16x8 shift_r(int16x8 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;

#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_srai_epi16(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::make_const(count);
    return vec_sra((__vector int16_t)a, (__vector uint16_t)shift);
#endif
}

template<unsigned count>
int16x16 shift_r(int16x16 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;

    return detail::v256_shift_r<count>(a);
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
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
uint16x8 shift_r(uint16x8 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16x8::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::make_const(count);
    return vec_sr((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

template<unsigned count>
uint16x16 shift_r(uint16x16 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16x16::zero();

    return detail::v256_shift_r<count>(a);
}
/// @}

/// @{
/** Shifts signed 32-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
int32x4 shift_r(int32x4 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::make_const(count);
    return vec_sra((__vector int32_t)a, (__vector uint32_t)shift);
#endif
}

template<unsigned count>
int32x8 shift_r(int32x8 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;

    return detail::v256_shift_r<count>(a);
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
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
uint32x4 shift_r(uint32x4 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32x4::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::make_const(count);
    return vec_sr((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

template<unsigned count>
uint32x8 shift_r(uint32x8 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32x8::zero();

    return detail::v256_shift_r<count>(a);
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
    @novec{SSE2-AVX2}
    @icost{SSE2-AVX2, 4-6}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @novec{SSE2-AVX}
    @icost{SSE2-AVX, 8-10}
    @icost{AVX2, 4-6}
    @icost{NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count>
int64x2 shift_r(int64x2 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

template<unsigned count>
int64x4 shift_r(int64x4 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;

    return detail::v256_shift_r<count>(a);
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

    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count>
uint64x2 shift_r(uint64x2 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64x2::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

template<unsigned count>
uint64x4 shift_r(uint64x4 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64x4::zero();

    return detail::v256_shift_r<count>(a);
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
    @icost{SSE2-AVX2, 2-3}
    @icost{NEON, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{AVX2,NEON, 2-3}
*/
template<unsigned count>
basic_int8x16 shift_l(basic_int8x16 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8x16::zero();

#if SIMDPP_USE_NULL
    return shift_l(a, count);
#elif SIMDPP_USE_SSE2
    /*  SSE2-SSE4.1 and AVX-AVX2 instruction sets lack 8-bit shift. We emulate
        it using 16-bit shift.
    */
    return detail::shift_l_8<count>(a);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::make_const(count);
    return vec_sl((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

template<unsigned count>
inline basic_int8x32 shift_l(basic_int8x32 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8x32::zero();

    return detail::v256_shift_l<count>(a);
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
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
basic_int16x8 shift_l(basic_int16x8 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16x8::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::make_const(count);
    return vec_sl((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

template<unsigned count>
inline basic_int16x16 shift_l(basic_int16x16 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16x16::zero();

    return detail::v256_shift_l<count>(a);
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
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
basic_int32x4 shift_l(basic_int32x4 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32x4::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::make_const(count);
    return vec_sl((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

template<unsigned count>
inline basic_int32x8 shift_l(basic_int32x8 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32x8::zero();

    return detail::v256_shift_l<count>(a);
}
/// @}

/// @{
/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count>
basic_int64x2 shift_l(basic_int64x2 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64x2::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

template<unsigned count>
inline basic_int64x4 shift_l(basic_int64x4 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64x4::zero();

    return detail::v256_shift_l<count>(a);
}
/// @}

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
