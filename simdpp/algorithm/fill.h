/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_FILL_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_FILL_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <algorithm> 
#include <simdpp/detail/align.h>
#include <simdpp/types/traits.h>
#include <simdpp/detail/insn/store_u.h>
#include <simdpp/detail/insn/store.h>
#include <simdpp/detail/insn/load_u.h>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename U> 
void fill(T* first, T* last, U value)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
        throw std::runtime_error("fill - null ptr first.");
    if (!last)
        throw std::runtime_error("fill - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;
    const auto alignment = simd_traits<T>::alignment;

    simd_type_T valsimd = splat((T)value);

    //Define loop counter
    const auto simd_size = simd_type_T::base_length;
    const auto size = std::distance(first, last);
    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    auto i = 0u;
            
    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
        *first++=(T)value;
    }

    //---main simd loop
    for (; i < size_simd_loop; i += simd_size)
    {
        store(first, valsimd);
        first += simd_size;
    }


    //---epilogue
    for (; i < size; ++i)
    {
        *first++ = (T)value;
    }

}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_FILL_H
