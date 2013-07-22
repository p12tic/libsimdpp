/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_CAST_H
#define LIBSIMDPP_SIMD_CAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

/** Casts between unrelated types. No changes to the stored values are
    performed.
*/
template<class R, class T>
R bit_cast(T t)
{
    static_assert(sizeof(R) == sizeof(T), "Size mismatch");
    union {
        T ut;
        R ur;
    };
    ut = t;
    return ur;
}

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
