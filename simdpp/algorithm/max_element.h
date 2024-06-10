/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_MAX_ELEMENT_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_MAX_ELEMENT_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <limits> //numeric_limits
#include <algorithm>//max
#include <simdpp/detail/align.h>
#include <simdpp/types/traits.h>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>
#include <simdpp/algorithm/max.h>
#include <simdpp/algorithm/find.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename Compare>
T const * max_element(T const* first, T const* last, Compare comp)
{
    if (first == last) return last;
    return find(first, last, simdpp::max(first, last, comp));
}

template<typename T>
T const * max_element(T const* first, T const* last)
{
    if (first == last) return last;
    return find(first, last, simdpp::max(first, last));
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp
#endif //LIBSIMDPP_SIMDPP_ALGORITHM_MAX_ELEMENT_H
