/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_ANY_OF_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_ANY_OF_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <algorithm>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename UnaryPredicate>
bool any_of(T const* first, T const* last, UnaryPredicate pred)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
    throw std::runtime_error("any_of - null ptr first.");
    if (!last)                    
    throw std::runtime_error("any_of - null ptr last.");
#endif

    using simd_type_T = typename simd_traits<T>::simd_type;
    using simd_mask_T = typename simd_traits<T>::simd_mask_type;

    //define loopcounter
    const auto simd_size = simd_type_T::base_length;

    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    //prologue
    auto lastprologue = first + size_prologue_loop;
    if (std::any_of(first, lastprologue, pred))
    {
        return true;
    }

    //simd loop
    auto i = size_prologue_loop;
    //workaraund not test_bits_any for mask type
    const simd_type_T on = splat(T(1)); //TODO factorize
    const simd_type_T off = splat(T(0));
    for (; i < size_simd_loop; i += simd_size)
    {
    simd_mask_T mask = pred(load(lastprologue)); //TODO factorize
    const auto res = blend(on, off, mask);
    if (test_bits_any(res))
    {
        return true;
    }
    lastprologue += simd_size;
    }
    return std::any_of(lastprologue,last, pred);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_ANY_OF_H
