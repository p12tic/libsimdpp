/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_COUNT_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_COUNT_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/algorithm/transform.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename U>
typename std::iterator_traits<const T*>::difference_type
count(T const* first, T const* last, U val)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
        throw std::runtime_error("count - null ptr first.");
    if (!last)
        throw std::runtime_error("count - null ptr last.");
#endif

    using simd_type_T = typename simd_traits<T>::simd_type;
    using simd_mask_T = typename simd_traits<T>::simd_mask_type;
    using return_type = typename std::iterator_traits<const T*>::difference_type;
    if (first == last) return (return_type)0;
    //define loopcounter
    const auto simd_size = simd_type_T::base_length;

    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    //prologue
    auto lastprologue = first + size_prologue_loop;
    return_type res = std::count(first, lastprologue, val);

    //simd loop
    auto i = size_prologue_loop;

    //workaraund not reduce_add for mask type
    const simd_type_T on = splat(T(1));
    const simd_type_T off = splat(T(0));
    const simd_type_T valsimd = splat(U(val));

    for (; i < size_simd_loop; i += simd_size)
    {
        const simd_type_T el = load(lastprologue);
        const simd_mask_T mask = cmp_eq(el, valsimd);
        const auto rescurrentsimd = blend(on, off, mask);
        res += (return_type)reduce_add(rescurrentsimd);
        lastprologue += simd_size;
    }
    res += std::count(lastprologue, last, val);
    return res;
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_COUNT_H
