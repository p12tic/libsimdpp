/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_INT256_INL
#define LIBSIMDPP_INT256_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

inline int256 int256::zero()
{
    int256 r;
    r = bit_xor(r, r);
    return r;
}

inline int256 int256::ones()
{
    basic_int32x8 r;
    r = cmp_eq(r, r);
    return r;
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
