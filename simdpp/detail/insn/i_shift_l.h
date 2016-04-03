/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_L_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_I_SHIFT_L_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/set_splat.h>
#include <simdpp/detail/insn/i_shift.h>
#include <simdpp/detail/null/math.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL uint8x16 i_shift_l(const uint8x16& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, a16;
    mask = make_ones();
    mask = shift_r(mask, 16-count);
    mask = shift_l(mask, 8);

    a16 = a;
    a16 = shift_l(a16, count);
    a16 = bit_andnot(a16, mask);
    return uint8x16(a16);
#elif SIMDPP_USE_NEON
    int8x16 shift = splat(count);
    return vshlq_u8(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = splat(count);
    return vec_sl((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint8x32 i_shift_l(const uint8x32& a, unsigned count)
{
    uint16x16 mask, a16;
    mask = make_ones();
    mask = shift_r(mask, 16-count);
    mask = shift_l(mask, 8);

    a16 = a;
    a16 = shift_l(a16, count);
    a16 = bit_andnot(a16, mask);
    return uint8x32(a16);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint16x8 i_shift_l(const uint16x8& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_sll_epi16(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int16x8 shift = splat(count);
    return vshlq_u16(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = splat(count);
    return vec_sl((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint16x16 i_shift_l(const uint16x16& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsllw	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_sll_epi16(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint32x4 i_shift_l(const uint32x4& a, unsigned count)
{
#if SIMDPP_USE_NULL
    return detail::null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_sll_epi32(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int32x4 shift = splat(count);
    return vshlq_u32(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = splat(count);
    return vec_sl((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint32x8 i_shift_l(const uint32x8& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpslld	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_sll_epi32(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint32<16> i_shift_l(const uint32<16>& a, unsigned count)
{
    return _mm512_sll_epi32(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL uint64x2 i_shift_l(const uint64x2& a, unsigned count)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return detail::null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_sll_epi64(a, _mm_cvtsi32_si128(count));
#elif SIMDPP_USE_NEON
    int64x2 shift = splat(count);
    return vshlq_u64(a, shift);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL uint64x4 i_shift_l(const uint64x4& a, unsigned count)
{
#if SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS
    __m256i r = a;
    __m128i x = _mm_cvtsi32_si128(count);
    __asm("vpsllq	%1, %2, %0" : "=x"(r) : "x"(x), "x"(r));
    return r;
#else
    return _mm256_sll_epi64(a, _mm_cvtsi32_si128(count));
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL uint64<8> i_shift_l(const uint64<8>& a, unsigned count)
{
    return _mm512_sll_epi64(a, _mm_cvtsi32_si128(count));
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
V i_shift_l(const V& a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(V, i_shift_l, a, count);
}

// -----------------------------------------------------------------------------

template<unsigned count, unsigned N> SIMDPP_INL
uint8<N> shift_l_8(const uint8<N>& a)
{
#if SIMDPP_USE_SSE2
    uint8<N> mask = shift_u8_mask<8-count, uint8<N> >()();
    uint16<N/2> a16 = (uint16<N/2>) bit_and(a, mask);
    a16 = shift_l<count>(a16);
    return uint8<N>(a16);
#else
    return SIMDPP_NOT_IMPLEMENTED_TEMPLATE1(uint8<N>, a);
#endif
}

template<unsigned count> SIMDPP_INL
uint8x16 i_shift_l(const uint8x16& a)
{
    SIMDPP_STATIC_ASSERT(count <= 8, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_l(a, count);
#elif SIMDPP_USE_SSE2
    /*  SSE2-SSE4.1 and AVX-AVX2 instruction sets lack 8-bit shift. We emulate
        it using 16-bit shift.
    */
    return shift_l_8<count>(a);
#elif SIMDPP_USE_NEON
    return vshlq_n_u8(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = make_uint(count);
    return vec_sl((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint8<32> i_shift_l(const uint8<32>& a)
{
    SIMDPP_STATIC_ASSERT(count <= 8, "Shift out of bounds");
    uint16<16> mask, a16;
    mask = make_ones();
    mask = shift_r<16-count>(mask);
    mask = shift_l<8>(mask);

    a16 = a;
    a16 = shift_l<count>(a16);
    a16 = bit_andnot(a16, mask);
    return uint8<32>(a16);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
uint16x8 i_shift_l(const uint16x8& a)
{
    SIMDPP_STATIC_ASSERT(count <= 16, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi16(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u16(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = make_uint(count);
    return vec_sl((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint16x16 i_shift_l(const uint16x16& a)
{
    SIMDPP_STATIC_ASSERT(count <= 16, "Shift out of bounds");
    return _mm256_slli_epi16(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
uint32x4 i_shift_l(const uint32x4& a)
{
    SIMDPP_STATIC_ASSERT(count <= 32, "Shift out of bounds");
#if SIMDPP_USE_NULL
    return i_shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi32(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u32(a, count);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = make_uint(count);
    return vec_sl((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint32x8 i_shift_l(const uint32x8& a)
{
    SIMDPP_STATIC_ASSERT(count <= 32, "Shift out of bounds");
    return _mm256_slli_epi32(a, count);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned count> SIMDPP_INL
uint32<16> i_shift_l(const uint32<16>& a)
{
    SIMDPP_STATIC_ASSERT(count <= 32, "Shift out of bounds");
    return _mm512_slli_epi32(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count> SIMDPP_INL
uint64x2 i_shift_l(const uint64x2& a)
{
    SIMDPP_STATIC_ASSERT(count <= 64, "Shift out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    return i_shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi64(a, count);
#elif SIMDPP_USE_NEON
    return vshlq_n_u64(a, count);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count> SIMDPP_INL
uint64x4 i_shift_l(const uint64x4& a)
{
    SIMDPP_STATIC_ASSERT(count <= 64, "Shift out of bounds");
    return _mm256_slli_epi64(a, count);
}
#endif

#if SIMDPP_USE_AVX512F
template<unsigned count> SIMDPP_INL
uint64<8> i_shift_l(const uint64<8>& a)
{
    SIMDPP_STATIC_ASSERT(count <= 64, "Shift out of bounds");
    return _mm512_slli_epi64(a, count);
}
#endif

// -----------------------------------------------------------------------------

template<unsigned count, class V> SIMDPP_INL
V i_shift_l(const V& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(V, i_shift_l<count>, a);
}
/// @}

template<bool no_shift, bool full_shift>
struct i_shift_l_wrapper {
    template<unsigned count, class V>
    static SIMDPP_INL V run(const V& arg) { return i_shift_l<count>(arg); }
};
template<>
struct i_shift_l_wrapper<true, false> {
    template<unsigned count, class V>
    static SIMDPP_INL V run(const V& arg) { return arg; }
};
template<>
struct i_shift_l_wrapper<false, true> {
    template<unsigned count, class V>
    static SIMDPP_INL V run(const V&) { return (V) make_zero(); }
};

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

