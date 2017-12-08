/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_ARRAY_H
#define LIBSIMDPP_SIMDPP_DETAIL_ARRAY_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

/* A simple array class to reduce diff with C++03 branch. Implements a subset
 * of std::array that we use
 */
template<class T, unsigned N>
class array {
public:
    SIMDPP_INL T&       operator[](unsigned id) { return d[id]; }
    SIMDPP_INL const T& operator[](unsigned id) const { return d[id]; }
private:
    T d[N];
};

/*  It looks like arrays are too opaque for most compilers to be able to figure
    out whith store corresponds to which load. As a workaround, separate
    variables are used.
*/
template<class T>
class array2 {
public:
    SIMDPP_INL T&       operator[](unsigned id) { return id == 0 ? d0 : d1; }
    SIMDPP_INL const T& operator[](unsigned id) const { return id == 0 ? d0 : d1; }
private:
    T d0, d1;
};

template<class T>
class array4 {
public:
    SIMDPP_INL T& operator[](unsigned id)
    {
        switch (id) {
        case 0: return d0;
        case 1: return d1;
        case 2: return d2;
        default: return d3;
        }
    }

    SIMDPP_INL const T& operator[](unsigned id) const
    {
        switch (id) {
        case 0: return d0;
        case 1: return d1;
        case 2: return d2;
        default: return d3;
        }
    }

private:
    T d0, d1, d2, d3;
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
