/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_TRANSFORM_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_TRANSFORM_H

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
#include <iostream>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename U, typename UnOp>
U* transform(T const* first, T const* last, U* out, UnOp f)
{
#ifdef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
        throw std::runtime_error("transform - null ptr first.");
    if (!last)
        throw std::runtime_error("transform - null ptr last.");
    if (!out)
        throw std::runtime_error("transform - null ptr out.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;
    using simd_type_U = typename simd_traits<U>::simd_type;

    static_assert (simd_type_T::base_length == simd_type_U::base_length
        , "mismatch base_length between T and U"
        );

    const auto alignment = simd_traits<T>::alignment;
            
    //Define loop counter
    const auto simd_size = simd_type_T::base_length;
    const auto size = std::distance(first, last);
    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;
            
    auto i = 0;

    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
        *out++ = f(*first++);
    }

    //---main simd loop
    if (detail::is_aligned(out, alignment))
    {
        for (; i < size_simd_loop; i += simd_size)
        {
            simd_type_T element = load(first);
            store(out, f(element));
            first += simd_size;
            out += simd_size;
        }
    }
    else
    {
        for (; i < size_simd_loop; i += simd_size)
        {
            simd_type_T element = load_u(first);
            store_u(out, f(element));
            first += simd_size;
            out += simd_size;
        }
    }
    //---epilogue
    for (; i < size; ++i)
    {
        *out++ = f(*first++);
    }
    return out;
}
template<typename T1, typename T2, typename U, typename BinOp>
U* transform(T1 const* first1, T1 const* last1, T2 const* first2, U* out, BinOp f)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first1)
        throw std::runtime_error("transform - null ptr first1.");
    if (!last1)
        throw std::runtime_error("transform - null ptr last1.");
    if (!first2)
        throw std::runtime_error("transform - null ptr first2.");
    if (!out)
        throw std::runtime_error("transform - null ptr out.");
#endif
    using simd_type_T1 = typename simd_traits<T1>::simd_type;
    using simd_type_T2 = typename simd_traits<T2>::simd_type;
    using simd_type_U = typename simd_traits<U>::simd_type;

    static_assert (simd_type_T1::base_length == simd_type_T2::base_length
        , "mismatch base_length between T1 and T2"
        );
    static_assert (simd_type_T1::base_length == simd_type_U::base_length
        , "mismatch base_length between T1 and U"
        );
    static_assert (simd_type_T2::base_length == simd_type_U::base_length
        , "mismatch base_length between T2 and U"
        );

    auto alignment = simd_traits<T1>::alignment;

    //Define loop counter
    const auto simd_size = simd_type_T1::base_length;
    const auto size = std::distance(first1, last1);
    const auto range = helper_input_range(first1, last1);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;


    auto i = 0;

    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
        *out++ = f(*first1++, *first2++);
    }

    //---main simd loop
    if (detail::is_aligned(first2, alignment) && detail::is_aligned(out, alignment))
    {
        for (; i < size_simd_loop; i += simd_size)
        {
            simd_type_T1 element1 = load(first1);
            simd_type_T2 element2 = load(first2);
            store(out, f(element1, element2));
            first1 += simd_size;
            first2 += simd_size;
            out += simd_size;
        }
    }
    else
    {
        for (; i < size_simd_loop; i += simd_size)
        {
            simd_type_T1 element1 = load(first1);
            simd_type_T2 element2 = load_u(first2);
            store_u(out, f(element1, element2));
            first1 += simd_size;
            first2 += simd_size;
            out += simd_size;
        }
    }
    //---epilogue
    for (; i < size; ++i)
    {
        *out++ = f(*first1++, *first2++);
    }
    return out;
}
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_TRANSFORM_H

