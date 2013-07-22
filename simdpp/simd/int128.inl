/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_INT128_INL
#define LIBSIMDPP_INT128_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline int128 int128::zero()
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    int128 r;
    r = bit_xor(r, r);
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_setzero_si128();
#endif
}

inline int128 int128::ones()
{
    basic_int32x4 r;
    r = cmp_eq(r, r);
    return r;
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
