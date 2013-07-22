/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_TRAITS_H
#define LIBSIMDPP_NULL_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/detail/traits.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace null {

template<class V>
using traits = detail::traits<V>;

} // namespace null
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
