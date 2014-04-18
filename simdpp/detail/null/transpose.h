/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_DETAIL_NULL_TRANSPOSE_H
#define LIBSIMDPP_DETAIL_NULL_TRANSPOSE_H
#if SIMDPP_USE_NULL || defined(SIMDPP_DOXYGEN)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <utility>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace null {

template<class V>
void transpose2(V& a0, V& a1)
{
    for (unsigned j = 0; j < V::length; j+=2) {
        std::swap(a0.el(j+1), a1.el(j));
    }
}

template<class V>
void transpose4(V& a0, V& a1, V& a2, V& a3)
{
    for (unsigned j = 0; j < V::length; j+=4) {
        std::swap(a0.el(j+1), a1.el(j));
        std::swap(a0.el(j+2), a2.el(j));
        std::swap(a0.el(j+3), a3.el(j));
        std::swap(a1.el(j+2), a2.el(j+1));
        std::swap(a1.el(j+3), a3.el(j+1));
        std::swap(a2.el(j+3), a3.el(j+2));
    }
}

template<class V>
void transpose8(V& a0, V& a1, V& a2, V& a3, V& a4, V& a5, V& a6, V& a7)
{
    transpose4(a0, a1, a2, a3);
    transpose4(a4, a5, a6, a7);

    for (unsigned j = 0; j < V::length; j+=8) {
        for (unsigned i = 0; i < 4; i++) {
            std::swap(a0.el(j+4+i), a4.el(j+i));
            std::swap(a1.el(j+4+i), a5.el(j+i));
            std::swap(a2.el(j+4+i), a6.el(j+i));
            std::swap(a3.el(j+4+i), a7.el(j+i));
        }
    }
}

} // namespace null
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
