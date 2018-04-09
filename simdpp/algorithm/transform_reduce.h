/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_TRANSFORM_REDUCE_H 
#define LIBSIMDPP_SIMDPP_ALGORITHM_TRANSFORM_REDUCE_H 

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <iterator> 
#include <simdpp/detail/align.h>
#include <simdpp/types/traits.h>
#include <simdpp/detail/insn/load_u.h>
#include <simdpp/detail/insn/load.h>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
template<typename T,typename BinaryOp, typename UnaryOp>
T transform_reduce( const T* first, const T* last, T init, BinaryOp binary_op,UnaryOp unary_op)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
    throw std::runtime_error("transform_reduce - null ptr first.");
    if (!last)
    throw std::runtime_error("transform_reduce - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;

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
    init = binary_op(init,unary_op(*first++));
    }

    simd_type_T accusimd=splat((T)0);
    //---main simd loop
    for (; i < size_simd_loop; i += simd_size)
    {
    simd_type_T element = unary_op(load(first));
    accusimd = binary_op(accusimd,element);
    first += simd_size;
    }
    //reduce simd residual
    for_each(accusimd, [&](T el) { init = binary_op(init, el); });
            
    //---epilogue
    for (; i < size; ++i)
    {
    init = binary_op(init,unary_op(*first++));
    }
    return init;
       
}

template <typename T1,typename T2,typename U, typename  BinaryOp1, typename BinaryOp2>
U transform_reduce(const T1* first1, const T1* last1, const T2* first2, U init, BinaryOp1 binary_op1, BinaryOp2 binary_op2)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first1)
    throw std::runtime_error("transform_reduce - null ptr first1.");
    if (!last1)
    throw std::runtime_error("transform_reduce - null ptr last1.");
    if (!first2)
    throw std::runtime_error("transform_reduce - null ptr first2.");         
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


    auto i = 0u;
    //---Prologue
    for(;i<size_prologue_loop;++i)
    {
    init= binary_op1(init, binary_op2(*first1++,*first2++));
    }

    simd_type_U accusimd=splat((U)0);
    //---main simd loop
    if (detail::is_aligned(first2, alignment))
    {
    for (; i < size_simd_loop; i += simd_size)
    {
        simd_type_T1 element1 = load(first1);
        simd_type_T2 element2 = load(first2);
        accusimd  = binary_op1(accusimd, binary_op2(element1,element2));
        first1 += simd_size;
        first2 += simd_size;
    }
    }
    else
    {
    for (; i < size_simd_loop; i += simd_size)
    {
        simd_type_T1 element1 = load(first1);
        simd_type_T2 element2 = load_u(first2);
        accusimd  = binary_op1(accusimd, binary_op2(element1,element2));
        first1 += simd_size;
        first2 += simd_size;
    }
    }
    //reduce simd residual
    for_each(accusimd, [&](U el) { init = binary_op1(init, el); });
      
    //---Epilogue
    for(;i<size;++i)
    {
    init=binary_op1(init,binary_op2(*first1++,*first2++));
    }
    return init;
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_TRANSFORM_REDUCE_H
