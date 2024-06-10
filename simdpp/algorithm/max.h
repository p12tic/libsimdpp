/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_MAX_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_MAX_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <limits> //numeric_limits
#include <algorithm>//max
#include <simdpp/detail/align.h>
#include <simdpp/types/traits.h>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

//Returns the value of the element with the largest value in the range[first, last[ over comp,
//The lowest possible value for the order if the range is empty.
template<typename T, typename Comp>
T max(T const* first, T const* last, Comp comp)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
        throw std::runtime_error("max - null ptr first.");
    if (!last)
        throw std::runtime_error("max - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;
    using simd_mask_T = typename simd_traits<T>::simd_mask_type;

    if (first == last) return comp(T(0), T(1)) ? std::numeric_limits<T>::max() : std::numeric_limits<T>::lowest(); //stolen from boost::simd

    //Define loop counter
    const auto simd_size = simd_type_T::base_length;
    const auto size = std::distance(first, last);
    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    auto i = 0u;
    auto max_val = *first; //initialize with thirst element

    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
        if (comp(*first, max_val))
        {
            max_val = *first;
        }
        first++;
    }

    //---main simd loop
    simd_type_T current_max_simd = splat(max_val);
    for (; i < size_simd_loop; i += simd_size)
    {
        const simd_type_T element = load(first);
        const simd_mask_T mask = comp(current_max_simd, element);
        current_max_simd = blend(current_max_simd, element, mask);
        first += simd_size;
    }
    //extract max from simdtype
    for_each(current_max_simd, [&](T el) {if (comp(el, max_val)) { max_val = el; }});

    //---epilogue
    for (; i < size; ++i)
    {
        if (comp(*first, max_val))
        {
            max_val = *first;
        }
        first++;
    }
    return max_val;
}

//Returns the value of the element with the largest value in the range[first, last[,
//The lowest possible value for the order if the range is empty.
template<typename T>
T max(T const* first, T const* last)
{
#ifndef SIMDPP_DEBUG //precondition debug mode           
    if (!first)
        throw std::runtime_error("max - null ptr first.");
    if (!last)
        throw std::runtime_error("max - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;

    if (first == last) return std::numeric_limits<T>::lowest();

    //Define loop counter
    const auto simd_size = simd_type_T::base_length;
    const auto size = std::distance(first, last);
    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    auto i = 0u;
    auto max_val = *first; //initialize with thirst element

    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
        max_val = std::max(max_val, *first++);
    }
    //---main simd loop
    simd_type_T current_max_simd = splat(max_val);
    for (; i < size_simd_loop; i += simd_size)
    {
        const simd_type_T el = load(first);
        current_max_simd = max(current_max_simd, el);
        first += simd_size;
    }
    //extract max from simdtype
    max_val = reduce_max(current_max_simd);

    //---epilogue
    for (; i < size; ++i)
    {
        max_val = std::max(max_val, *first++);
    }

    return max_val;
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp
#endif //LIBSIMDPP_SIMDPP_ALGORITHM_MAX_H
