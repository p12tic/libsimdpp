/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_F_TRUNC_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_F_TRUNC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <cmath>
#include <simdpp/types.h>
#include <simdpp/core/f_ceil.h>
#include <simdpp/detail/null/foreach.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline float32x4 i_trunc(float32x4 a)
{
#if SIMDPP_USE_NULL || (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)
    return detail::null::foreach<float32x4>(a, [](float x){ return std::trunc(x); });
#elif SIMDPP_USE_SSE4_1
    return _mm_round_ps(a, 3); // 3 = i_truncate
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON_FLT_SP
    //check if the value is not too large
    float32x4 af = abs(a);
    mask_float32x4 mask = cmp_gt(af, float32x4(make_float(8388607.0f)));

    //truncate
    int32x4 ia = to_int32(a);
    float32x4 fa = to_float32(ia);

    //combine the results
    a = blend(a, fa, mask);     // takes care of NaNs
    return a;
#elif SIMDPP_USE_ALTIVEC
    return vec_trunc((__vector float)a);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_trunc(float32x8 a)
{
    return _mm256_round_ps(a, 3); // 3 = i_truncate
}
#endif

template<unsigned N>
float32<N> i_trunc(float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_trunc, a);
}


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

