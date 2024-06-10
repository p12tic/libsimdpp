/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_REDUCE_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_REDUCE_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <iterator> 
#include <simdpp/detail/align.h>
#include <simdpp/types/traits.h>
#include <simdpp/detail/insn/store_u.h>
#include <simdpp/detail/insn/store.h>
#include <simdpp/detail/insn/load_u.h>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
T reduce(T const* first, T const* last, T init)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
        throw std::runtime_error("reduce - null ptr first.");
    if (!last)
        throw std::runtime_error("reduce - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;

    simd_type_T accusimd = splat((T)0);

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
        init += *first++;
    }
    //---main simd loop
    for (; i < size_simd_loop; i += simd_size)
    {
        simd_type_T element = load(first);
        accusimd = accusimd + element; //TODO need += 
        first += simd_size;
    }


    //---epilogue
    for (; i < size; ++i)
    {
        init += *first++;
    }

    //sum simd residual
    init += reduce_add(accusimd);
    return init;
}

template<typename T, typename BinOp>
T reduce(T const* first, T const* last, T init, T neutral, BinOp f) //need neutral element for simd part
{
#ifndef SIMDPP_DEBUG //precondition debug mode           
    if (!first)
        throw std::runtime_error("reduce - null ptr first.");
    if (!last)
        throw std::runtime_error("reduce - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;
    const auto alignment = simd_traits<T>::alignment;

    //Define loop counter
    const auto size = std::distance(first, last);
    const auto simd_size = simd_type_T::base_length;
    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    auto i = 0;
    simd_type_T accusimd = splat(T(neutral)); //think about product sum

    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
        init = f(init, *first++);
    }
    //---main simd loop
    for (; i < size_simd_loop; i += simd_size)
    {
        simd_type_T element = load(first);
        accusimd = f(accusimd, element);
        first += simd_size;
    }
    //---epilogue
    for (; i < size; ++i)
    {
        init = f(init, *first++);
    }

    //reduce simd residual
    for_each(accusimd, [&](T el) { init = f(init, el); });
    return init;
}
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_REDUCE_H

