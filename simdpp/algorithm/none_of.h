/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_NONE_OF_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_NONE_OF_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/algorithm/any_of.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename UnaryPredicate>
bool none_of(T const* first, T const* last, UnaryPredicate pred)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
    throw std::runtime_error("none_of - null ptr first.");
    if (!last)
    throw std::runtime_error("none_of - null ptr last.");
#endif
    return !any_of(first,last,pred);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_NONE_OF_H
