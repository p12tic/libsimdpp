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
#include <simdpp/core/i_sub.h>
#include <simdpp/core/make_int.h>
#include <simdpp/detail/insn/split.h>
#include <simdpp/detail/mem_block.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Extracts the @a id-th element from int8x16 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2-SSSE3, 1-2}
    @icost{SSE4.1-AVX, 1}
    @icost{ALTIVEC, 2}
*/
template<unsigned id> SIMDPP_INL
uint8_t extract(const uint8x16& a)
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
#elif SIMDPP_USE_MSA
    return __msa_copy_u_b((v16i8)(v16u8) a, id);
#endif
}

template<unsigned id> SIMDPP_INL
int8_t extract(const int8x16& a)
{
#if SIMDPP_USE_MSA
    return __msa_copy_s_b(a, id);
#else
    return extract<id>(uint8x16(a));
#endif
}

/** Extracts the @a id-th element from int16x8 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{ALTIVEC, 2}
*/
template<unsigned id> SIMDPP_INL
uint16_t extract(const uint16x8& a)
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
#elif SIMDPP_USE_MSA
    return __msa_copy_u_h((v8i16)(v8u16) a, id);
#endif
}

template<unsigned id> SIMDPP_INL
int16_t extract(const int16x8& a)
{
    static_assert(id < 8, "index out of bounds");
#if SIMDPP_USE_MSA
    return __msa_copy_s_h(a, id);
#else
    return extract<id>(uint16x8(a));
#endif
}

/** Extracts the @a id-th element from int32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
    @icost{ALTIVEC, 2}
*/
template<unsigned id> SIMDPP_INL
uint32_t extract(const uint32x4& a)
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
#elif SIMDPP_USE_MSA
    return __msa_copy_u_w((v4i32)(v4u32) a, id);
#endif
}

template<unsigned id> SIMDPP_INL
int32_t extract(const int32x4& a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_MSA
    return __msa_copy_s_w(a, id);
#else
    return extract<id>(uint32x4(a));
#endif
}

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
template<unsigned id> SIMDPP_INL
uint64_t extract(const uint64x2& a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE4_1
#if SIMDPP_32_BITS
    uint32x4 t = uint32x4(a);
    uint64_t r = extract<id*2>(t);
    r |= uint64_t(extract<id*2+1>(t)) << 32;
    return r;
#else
    return _mm_extract_epi64(a.operator __m128i(), id);
#endif
#elif SIMDPP_USE_SSE2
#if SIMDPP_32_BITS
    uint32x4 t = uint32x4(a);
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
#elif SIMDPP_USE_MSA
#if SIMDPP_64_BITS
    return __msa_copy_u_d((v2i64)(v2u64) a, id);
#else
    v4i32 a32 = (int32<4>) a;
    uint64_t lo = __msa_copy_u_w(a32, id*2);
    uint64_t hi = __msa_copy_u_w(a32, id*2+1);
    return lo | (hi << 32);
#endif
#endif
}

template<unsigned id> SIMDPP_INL
int64_t extract(const int64x2& a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_MSA
#if SIMDPP_64_BITS
    return __msa_copy_s_d(a, id);
#else
    v4i32 a32 = (int32<4>) a;
    int64_t lo = __msa_copy_s_w(a32, id*2);
    int64_t hi = __msa_copy_s_w(a32, id*2+1);
    return lo | (hi << 32);
#endif
#else
    return extract<id>(uint64x2(a));
#endif
}

/** Extracts an element from float32x4 vector

    @code
    r = a[id]
    @endcode

    This function may have very high latency.

    @icost{SSE2, SSE3, SSSE3, 1-2}
    @icost{ALTIVEC, 2}
*/
template<unsigned id> SIMDPP_INL
float extract(const float32x4& a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return bit_cast<float>(extract<id>(int32x4(a)));
#elif SIMDPP_USE_NEON
    return vgetq_lane_f32(a, id);
#elif SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
    detail::mem_block<float32x4> ax(a);
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
template<unsigned id> SIMDPP_INL
double extract(const float64x2& a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return bit_cast<double>(extract<id>(int64x2(a)));
#elif SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
    detail::mem_block<float64x2> ax(a);
    return ax[id];
#elif SIMDPP_USE_NEON64
    return vgetq_lane_f64(a, id);
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
SIMDPP_INL uint16_t extract_bits_any(const uint8x16& ca)
{
    uint8<16> a = ca;
    // extract_bits_impl depends on the exact implementation of this function
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    for (unsigned i = 0; i < a.length; i++) {
        uint8_t x = ca.el(i);
        x = x & 1;
        r = (r >> 1) | (uint16_t(x) << 15);
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_movemask_epi8(a);
#elif SIMDPP_USE_NEON
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

    a = bit_and(a, mask);
    uint16<8> a16 = vpaddlq_u8(a);
    uint32<4> a32 = vpaddlq_u16(a16);
    uint8<16> a8 = (uint8<16>) (uint64<2>) vpaddlq_u32(a32);
    uint8x8_t r = vzip_u8(vget_low_u8(a8), vget_high_u8(a8)).val[0];
    return vget_lane_u16(vreinterpret_u16_u8(r), 0);
#elif SIMDPP_USE_ALTIVEC
    // Note: the implementation of extract_bits depends of the exact behavior
    // of this function
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);
    a = bit_and(a, mask);
    uint32x4 s = vec_sum4s((__vector uint8_t)a,
                           (__vector uint32_t)(uint32x4) make_zero());
    uint32x4 shifts = make_uint(0, 0, 8, 8);
    s = (__vector uint32_t) vec_sl((__vector uint32_t)s, (__vector uint32_t) shifts);
    s = (int32x4)vec_sums((__vector int32_t)(int32x4)s,
                          (__vector int32_t)(int32x4) make_zero());
#if SIMDPP_BIG_ENDIAN
    return extract<7>(uint16x8(s));
#else
    return extract<6>(uint16x8(s));
#endif
#elif SIMDPP_USE_MSA
    // Note: the implementation of extract_bits depends of the exact behavior
    // of this function
    uint8x16 mask = make_uint(0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80);

    a = bit_and(a, mask);
    uint16<8> a16 = __msa_hadd_u_h((v16u8)a, (v16u8)a);
    uint32<4> a32 = __msa_hadd_u_w((v8u16)a16, (v8u16)a16);
    a = (v16u8) __msa_hadd_u_d((v4u32)a32, (v4u32)a32);
    a = bit_or(a, move16_l<7>(a));
    return extract<0>((uint16<8>)a);
#endif
}

/** Extracts a bit from each byte of each element of a int8x32 vector.

This operation is only sensible if each byte within the vector is either
0x00 or 0xff.

@code
r = ((a[0] & 0x??) ? 0x01 : 0) |
    ((a[1] & 0x??) ? 0x02 : 0) |
    ...
@endcode
*/
SIMDPP_INL uint32_t extract_bits_any(const uint8x32& ca)
    {
        uint8<32> a = ca;
        // extract_bits_impl depends on the exact implementation of this function
#if SIMDPP_USE_NULL
        uint32_t r = 0;
    for (unsigned i = 0; i < a.length; i++) {
        uint8_t x = ca.el(i);
        x = x & 1;
        r = (r >> 1) | (uint32_t(x) << 31);
    }
    return r;
#elif SIMDPP_USE_SSE2
    uint8<16> A,B;
    split(a, A, B);
    return (extract_bits_any(A) << 16) + extract_bits_any(B);
#elif SIMDPP_USE_AVX2
        return _mm256_movemask_epi8(a);
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
template<unsigned id> SIMDPP_INL
uint16_t extract_bits(const uint8x16& ca)
{
    uint8<16> a = ca;
    static_assert(id < 8, "index out of bounds");
#if SIMDPP_USE_NULL
    uint16_t r = 0;
    for (unsigned i = 0; i < a.length; i++) {
        uint8_t x = ca.el(i);
        x = (x >> id) & 1;
        r = (r >> 1) | (uint16_t(x) << 15);
    }
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
#elif SIMDPP_USE_MSA
    int8x16 shifts = make_int(0-int(id), 1-int(id), 2-int(id), 3-int(id),
                              4-int(id), 5-int(id), 6-int(id), 7-int(id));
    uint8<16> a_l = (v16u8) __msa_sll_b((v16i8)(v16u8) a, shifts);
    shifts = sub((int8<16>) make_zero(), shifts);
    uint8<16> a_r = (v16u8) __msa_srl_b((v16i8)(v16u8) a, shifts);
    a = bit_or(a_l, a_r);
    return extract_bits_any(a);
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif


