/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_FLOOR_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_FLOOR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cmath>
#include <simdpp/types.h>
#include <simdpp/core/f_abs.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/cmp_eq.h>
#include <simdpp/core/cmp_gt.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/core/to_float32.h>
#include <simdpp/core/to_int32.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {


SIMDPP_INL float32x4 i_floor(const float32x4& a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    float32x4 r;
    for (unsigned i = 0; i < a.length; i++) {
        r.el(i) = std::floor(a.el(i));
    }
    return r;
#elif SIMDPP_USE_SSE4_1
    return _mm_floor_ps(a);
#elif SIMDPP_USE_NEON64
    return vrndmq_f32(a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large, or is zero
    float32x4 ba = abs(a);
    mask_float32x4 mask_range = cmp_le(ba, 8388607.0f);
    mask_float32x4 mask_nonzero = cmp_gt(ba, 0);
    mask_float32x4 mask = bit_and(mask_range, mask_nonzero); // takes care of nans and zeros

    //calculate the i_floor using trunc
    int32x4 s = shift_r((uint32x4)a, 31); //=1 if a<0
    float32x4 at = (float32x4) sub((int32x4)a, s); //=nextafter towards +inf, if a<0
    int32x4 ia = to_int32(at);
            ia = sub(ia, s);
    float32x4 fa = to_float32(ia);

    //combine the results
    return blend(fa, a, mask);
#elif SIMDPP_USE_ALTIVEC
    return vec_floor((__vector float)a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL float32x8 i_floor(const float32x8& a)
{
    return _mm256_floor_ps(a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL float32<16> i_floor(const float32<16>& a)
{
    return _mm512_floor_ps(a);
}
#endif

template<unsigned N> SIMDPP_INL
float32<N> i_floor(const float32<N>& a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_floor, a);
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

