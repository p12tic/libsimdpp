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
    T&       operator[](unsigned id) { return d[id]; }
    const T& operator[](unsigned id) const { return d[id]; }
private:
    T d[N];
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
