/*  Copyright (C) 2011-2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_EXTRACT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_EXTRACT_H

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
namespace detail {
namespace insn {

template<unsigned id> SIMDPP_INL
uint8_t i_extract(const uint8x16& a)
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
int8_t i_extract(const int8x16& a)
{
#if SIMDPP_USE_MSA
    return __msa_copy_s_b(a, id);
#else
    return i_extract<id>(uint8x16(a));
#endif
}

template<unsigned id> SIMDPP_INL
uint16_t i_extract(const uint16x8& a)
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
int16_t i_extract(const int16x8& a)
{
    static_assert(id < 8, "index out of bounds");
#if SIMDPP_USE_MSA
    return __msa_copy_s_h(a, id);
#else
    return i_extract<id>(uint16x8(a));
#endif
}

template<unsigned id> SIMDPP_INL
uint32_t i_extract(const uint32x4& a)
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
int32_t i_extract(const int32x4& a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_MSA
    return __msa_copy_s_w(a, id);
#else
    return i_extract<id>(uint32x4(a));
#endif
}

template<unsigned id> SIMDPP_INL
uint64_t i_extract(const uint64x2& a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE4_1
#if SIMDPP_32_BITS
    uint32x4 t = uint32x4(a);
    uint64_t r = i_extract<id*2>(t);
    r |= uint64_t(i_extract<id*2+1>(t)) << 32;
    return r;
#else
    return _mm_extract_epi64(a.operator __m128i(), id);
#endif
#elif SIMDPP_USE_SSE2
#if SIMDPP_32_BITS
    uint32x4 t = uint32x4(a);
    uint64_t r = 0;
    t = move4_l<id*2>(t); // when id==0, move_l is template-specialized and does nothing
    r = i_extract<0>(t);
    t = move4_l<1>(t);
    r |= uint64_t(i_extract<0>(t)) << 32;
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
int64_t i_extract(const int64x2& a)
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
    return i_extract<id>(uint64x2(a));
#endif
}

template<unsigned id> SIMDPP_INL
float i_extract(const float32x4& a)
{
    static_assert(id < 4, "index out of bounds");
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return bit_cast<float>(i_extract<id>(int32x4(a)));
#elif SIMDPP_USE_NEON
    return vgetq_lane_f32(a, id);
#elif SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
    detail::mem_block<float32x4> ax(a);
    return ax[id];
#endif
}

template<unsigned id> SIMDPP_INL
double i_extract(const float64x2& a)
{
    static_assert(id < 2, "index out of bounds");
#if SIMDPP_USE_NULL
    return a.el(id);
#elif SIMDPP_USE_SSE2
    return bit_cast<double>(i_extract<id>(int64x2(a)));
#elif SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC || SIMDPP_USE_MSA
    detail::mem_block<float64x2> ax(a);
    return ax[id];
#elif SIMDPP_USE_NEON64
    return vgetq_lane_f64(a, id);
#endif
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
