/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_INT16_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_TO_INT16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/insert.h>
#include <simdpp/detail/null/foreach.h>
#include <simdpp/core/detail/vec_insert.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

inline uint16x16 i_to_int16(int8x16 a)
{
#if SIMDPP_USE_NULL
    int16x16 r;
    for (unsigned i = 0; i < 16; i++) {
        r[i/8].el(i%8) = int16_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    int16x8 r1, r2;
    r1 = _mm_cvtepi8_epi16(a);
    r2 = _mm_cvtepi8_epi16(move16_r<8>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2
    int16x8 r1, r2;
    r1 = zip16_lo(int8x16::zero(), a);
    r1 = shift_r(r1, 8);
    r2 = zip16_hi(int8x16::zero(), a);
    r2 = shift_r(r2, 8);
    return combine(r1, r2);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_s8(vget_low_s8(a));
    r[1] = vmovl_s8(vget_high_s8(a));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int16x16 r;
    r[0] = vec_unpackh((__vector int8_t)a[0]);
    r[1] = vec_unpackl((__vector int8_t)a[0]);
    return r;
#endif
}

// TODO support arbitrary length vectors

// -----------------------------------------------------------------------------

inline uint16x16 i_to_int16(uint8x16 a)
{
#if SIMDPP_USE_NULL
    uint16x16 r;
    for (unsigned i = 0; i < 8; i++) {
        r[i/8].el(i%8) = uint16_t(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    int16x8 r1, r2;
    r1 = _mm_cvtepu8_epi16(a);
    r2 = _mm_cvtepu8_epi16(move16_r<8>(a).eval());
    return combine(r1, r2);
#elif SIMDPP_USE_SSE2
    int16x8 r1, r2;
    r1 = zip16_lo(a, uint8x16::zero());
    r2 = zip16_hi(a, uint8x16::zero());
    return combine(r1, r2);
#elif SIMDPP_USE_NEON
    int16x16 r;
    r[0] = vmovl_u8(vget_low_u8(a));
    r[1] = vmovl_u8(vget_high_u8(a));
    return r;
#elif SIMDPP_USE_ALTIVEC
    int16x16 r;
    r[0] = vmovl_u8(vget_low_u8(a[0]));
    r[1] = vmovl_u8(vget_high_u8(a[1]));
    return r;
#endif
}

// TODO support arbitrary length vectors


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


