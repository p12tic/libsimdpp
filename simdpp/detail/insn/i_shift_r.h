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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_R_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/detail/insn/i_shift.h>
#include <simdpp/null/math.h>
#include <simdpp/neon/detail/math_shift.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline int8x16 i_shift_r(int8x16 a, unsigned count)
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

#if SIMDPP_USE_AVX2
inline int8x32 i_shift_r(int8x32 a, unsigned count)
{
    uint16x16 hi, lo;
    lo = hi = a;

    lo = shift_l<8>(lo);
    lo = shift_r(int16x16(lo), count);
    lo = shift_r<8>(lo);

    hi = shift_r(int16x16(hi), 8+count);
    hi = shift_l<8>(hi);
    a = bit_or(lo, hi);    //higher part of lo is already clear
    return a;
}
#endif

template<unsigned N>
int8<N> i_shift_r(int8<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(int8<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline uint8x16 i_shift_r(uint8x16 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_r(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, a16;
    mask = uint16x8::ones();
    mask = shift_l(mask, 16-count);
    mask = shift_r<8>(mask);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return uint8x16(a16);
#elif SIMDPP_USE_NEON
    int8x16 shift = int8x16::set_broadcast(-int(count));
    return vshlq_u8(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::set_broadcast(count);
    return vec_sr((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 i_shift_r(uint8x32 a, unsigned count)
{
    uint16x16 mask, a16;
    mask = uint16x16::ones();
    mask = shift_l(mask, 16-count);
    mask = shift_r<8>(mask);

    a16 = a;
    a16 = shift_r(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
}
#endif

template<unsigned N>
uint8<N> i_shift_r(uint8<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(uint8<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline int16x8 i_shift_r(int16x8 a, unsigned count)
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

#if SIMDPP_USE_AVX2
inline int16x16 i_shift_r(int16x16 a, unsigned count)
{
    return _mm256_srai_epi16(a, count);
}
#endif

template<unsigned N>
int16<N> i_shift_r(int16<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(int16<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline uint16x8 i_shift_r(uint16x8 a, unsigned count)
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

#if SIMDPP_USE_AVX2
inline uint16x16 i_shift_r(uint16x16 a, unsigned count)
{
    return _mm256_srli_epi16(a, count);
}
#endif

template<unsigned N>
uint16<N> i_shift_r(uint16<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(uint16<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline int32x4 i_shift_r(int32x4 a, unsigned count)
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

#if SIMDPP_USE_AVX2
inline int32x8 i_shift_r(int32x8 a, unsigned count)
{
    return _mm256_srai_epi32(a, count);
}
#endif

template<unsigned N>
int32<N> i_shift_r(int32<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(int32<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline uint32x4 i_shift_r(uint32x4 a, unsigned count)
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

#if SIMDPP_USE_AVX2
inline uint32x8 i_shift_r(uint32x8 a, unsigned count)
{
    return _mm256_srli_epi32(a, count);
}
#endif

template<unsigned N>
uint32<N> i_shift_r(uint32<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(uint32<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline int64x2 i_shift_r(int64x2 a, unsigned count)
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
        v = permute4<0,2,1,3>(v);
        return int64x2(v);
    } else {
        // shift the sign bit using 32-bit shift, then combine the result with
        // the unsigned shift using a mask
        uint64x2 v, mask, sgn;
        v = sgn = a;
        v = shift_r(v, count);
        sgn = shift_r(int32x4(sgn), count);
        mask = uint64x2::ones();
        mask = shift_l(mask, 64 - count);
        sgn = bit_and(sgn, mask);
        v = bit_or(v, sgn);
        return int64x2(v);
    }
#elif SIMDPP_USE_NEON
    int64x2 shift = int64x2::set_broadcast(-int(count));
    return vshlq_s64(a, shift);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

#if SIMDPP_USE_AVX2
inline int64x4 i_shift_r(int64x4 a, unsigned count)
{
    // a copy of the 128-bit implementation
    if (count > 31) {
        int32x8 s, v;
        v = a;
        s = shift_r<31>(v);
        v = shift_r(v, count - 32);
        v = shuffle2<1,3,1,3>(v, s);
        v = permute4<0,2,1,3>(v);
        return v;
    } else {
        uint64x4 v, mask;
        int32x8 sgn;
        v = sgn = a;
        v = shift_r(v, count);
        sgn = shift_r(sgn, count);
        mask = uint64x4::ones();
        mask = shift_l(mask, 64 - count);
        sgn = bit_and(sgn, mask);
        v = bit_or(v, sgn);
        return v;
    }
}
#endif

template<unsigned N>
int64<N> i_shift_r(int64<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(int64<N>, i_shift_r, a, count);
}

// -----------------------------------------------------------------------------

inline uint64x2 i_shift_r(uint64x2 a, unsigned count)
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

#if SIMDPP_USE_AVX2
inline uint64x4 i_shift_r(uint64x4 a, unsigned count)
{
    return _mm256_srli_epi64(a, count);
}
#endif

template<unsigned N>
uint64<N> i_shift_r(uint64<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(uint64<N>, i_shift_r, a, count);
}


// -----------------------------------------------------------------------------

template<unsigned count, unsigned N>
uint8<N> shift_r_u8(uint8<N> a);


template<unsigned count>
int8x16 i_shift_r(int8x16 a)
{
    static_assert(count <= 8, "Shift out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return i_shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::make_const(count);
    return vec_sra((__vector int8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
int8x32 i_shift_r(int8x32 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
int8<N> i_shift_r(int8<N> a)
{
    static_assert(count <= 8, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(int8<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
uint8x16 i_shift_r(uint8x16 a)
{
    static_assert(count <= 8, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_r(a, count);
#elif SIMDPP_USE_SSE2
    /*  SSE2-SSE4.1 and AVX-AVx2 instruction sets lack 8-bit shift. The
        optimization below emulates it using 16-bit shift
    */
    return shift_r_u8<count>(a);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::make_const(count);
    return vec_sr((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
uint8x32 i_shift_r(uint8x32 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
uint8<N> i_shift_r(uint8<N> a)
{
    static_assert(count <= 8, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
int16x8 i_shift_r(int16x8 a)
{
    static_assert(count <= 16, "Shift out of bounds");
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

#if SIMDPP_USE_AVX2
template<unsigned count>
int16x16 i_shift_r(int16x16 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
int16<N> i_shift_r(int16<N> a)
{
    static_assert(count <= 16, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(int16<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
uint16x8 i_shift_r(uint16x8 a)
{
    static_assert(count <= 16, "Shift out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return i_shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::make_const(count);
    return vec_sr((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
uint16x16 i_shift_r(uint16x16 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
uint16<N> i_shift_r(uint16<N> a)
{
    static_assert(count <= 16, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint16<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
int32x4 i_shift_r(int32x4 a)
{
    static_assert(count <= 32, "Shift out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return i_shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::make_const(count);
    return vec_sra((__vector int32_t)a, (__vector uint32_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
int32x8 i_shift_r(int32x8 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
int32<N> i_shift_r(int32<N> a)
{
    static_assert(count <= 32, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(int32<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
uint32x4 i_shift_r(uint32x4 a)
{
    static_assert(count <= 32, "Shift out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return i_shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::make_const(count);
    return vec_sr((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
uint32x8 i_shift_r(uint32x8 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
uint32<N> i_shift_r(uint32<N> a)
{
    static_assert(count <= 32, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
int64x2 i_shift_r(int64x2 a)
{
    static_assert(count <= 64, "Shift out of bounds");

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return i_shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
int64x4 i_shift_r(int64x4 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
int64<N> i_shift_r(int64<N> a)
{
    static_assert(count <= 64, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(int64<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count>
uint64x2 i_shift_r(uint64x2 a)
{
    static_assert(count <= 64, "Shift out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return i_shift_r(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_r<count>(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
uint64x4 i_shift_r(uint64x4 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    return i_shift_r(a, count);
}
#endif

template<unsigned count, unsigned N>
uint64<N> i_shift_r(uint64<N> a)
{
    static_assert(count <= 64, "Shift out of bounds");
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, i_shift_r<count>, a);
}

// -----------------------------------------------------------------------------

template<unsigned count, unsigned N>
uint8<N> shift_r_u8(uint8<N> a)
{
#if SIMDPP_USE_SSE2
    uint8<N> mask = shift_u8_mask<count, uint8<N>>()();
    uint16<N/2> a16 = (uint16<N/2>) bit_andnot(a, mask);
    a16 = i_shift_r<count>(a16);
    return uint8<N>(a16);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

