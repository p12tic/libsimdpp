/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_TRANSPOSE_H
#define LIBSIMDPP_NULL_TRANSPOSE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/null/traits.h>
#include <utility>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
void transpose2(V& a0, V& a1)
{
    for (unsigned j = 0; j < traits<V>::length; j+=2) {
        std::swap(a0[j+1], a1[j]);
    }
}

template<class V>
void transpose4(V& a0, V& a1, V& a2, V& a3)
{
    for (unsigned j = 0; j < traits<V>::length; j+=4) {
        std::swap(a0[j+1], a1[j]);
        std::swap(a0[j+2], a2[j]);
        std::swap(a0[j+3], a3[j]);
        std::swap(a1[j+2], a2[j+1]);
        std::swap(a1[j+3], a3[j+1]);
        std::swap(a2[j+3], a3[j+2]);
    }
}

template<class V>
void transpose8(V& a0, V& a1, V& a2, V& a3, V& a4, V& a5, V& a6, V& a7)
{
    transpose4(a0, a1, a2, a3);
    transpose4(a4, a5, a6, a7);

    for (unsigned j = 0; j < traits<V>::length; j+=8) {
        for (unsigned i = 0; i < 4; i++) {
            std::swap(a0[j+4+i], a4[j+i]);
            std::swap(a1[j+4+i], a5[j+i]);
            std::swap(a2[j+4+i], a6[j+i]);
            std::swap(a3[j+4+i], a7[j+i]);
        }
    }
}

template<class V>
void transpose16(V& a0, V& a1, V& a2,  V& a3,  V& a4,  V& a5,  V& a6,  V& a7,
                 V& a8, V& a9, V& a10, V& a11, V& a12, V& a13, V& a14, V& a15)
{
    transpose8(a0, a1, a2,  a3,  a4,  a5,  a6,  a7 );
    transpose8(a8, a9, a10, a11, a12, a13, a14, a15);

    for (unsigned j = 0; j < traits<V>::length; j+=16) {
        for (unsigned i = 0; i < 8; i++) {
            std::swap(a0[j+8+i], a8[j+i]);
            std::swap(a1[j+8+i], a9[j+i]);
            std::swap(a2[j+8+i], a10[j+i]);
            std::swap(a3[j+8+i], a11[j+i]);
            std::swap(a4[j+8+i], a12[j+i]);
            std::swap(a5[j+8+i], a13[j+i]);
            std::swap(a6[j+8+i], a14[j+i]);
            std::swap(a7[j+8+i], a15[j+i]);
        }
    }
}

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
