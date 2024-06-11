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

/*  A compile-time array that uses variables instead of array for underlying
    storage when element count is small.

    Variables are used as a workaround because arrays are too opaque for most
    older compilers to be able to figure out whith store corresponds to which
    load.
*/
template<class T, unsigned N>
class vararray {
public:
    SIMDPP_INL T&       operator[](unsigned id) { return d[id]; }
    SIMDPP_INL const T& operator[](unsigned id) const { return d[id]; }
private:
    T d[N];
};


template<class T>
class vararray<T,2> {
public:
    SIMDPP_INL T&       operator[](unsigned id) { return id == 0 ? d0 : d1; }
    SIMDPP_INL const T& operator[](unsigned id) const { return id == 0 ? d0 : d1; }
private:
    T d0, d1;
};

template<class T>
class vararray<T,4> {
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

template<class T>
class vararray<T,8> {
public:
    SIMDPP_INL T& operator[](unsigned id)
    {
        switch (id) {
        case 0: return d0;
        case 1: return d1;
        case 2: return d2;
        case 3: return d3;
        case 4: return d4;
        case 5: return d5;
        case 6: return d6;
        default: return d7;
        }
    }

    SIMDPP_INL const T& operator[](unsigned id) const
    {
        switch (id) {
        case 0: return d0;
        case 1: return d1;
        case 2: return d2;
        case 3: return d3;
        case 4: return d4;
        case 5: return d5;
        case 6: return d6;
        default: return d7;
        }
    }

private:
    T d0, d1, d2, d3, d4, d5, d6, d7;
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
