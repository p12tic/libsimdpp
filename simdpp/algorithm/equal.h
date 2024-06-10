/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_EQUAL_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_EQUAL_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <algorithm>
#include <simdpp/algorithm/helper_input_range.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
      
template<typename T, typename BinaryPredicate> 
bool equal(const T* first1,  const T* last1, const T* first2,BinaryPredicate pred)
{
         
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first1)
    throw std::runtime_error("equal - null ptr first1.");
    if (!last1)                    
    throw std::runtime_error("equal - null ptr last1.");
    if (!first2)                    
    throw std::runtime_error("equal - null ptr first2.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;
    //using simd_mask_T = typename simd_traits<T>::simd_mask_type;
    auto alignment = simd_traits<T>::alignment;
         
    //define loopcounter
    const auto simd_size = simd_type_T::base_length;

    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first1, last1);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    //prologue
    auto last1prologue = first1 + size_prologue_loop;
    auto last2prologue = first2 + size_prologue_loop;
    if(!std::equal(first1, last1prologue,first2,pred)) return false;

    auto i=size_prologue_loop;
    //workaound no reduce_and for mask_type
    const simd_type_T on=splat(T(1));
    const simd_type_T off=splat(T(0));
    //---main simd loop
    if (detail::is_aligned(last2prologue, alignment)) 
    {
        for (; i < size_simd_loop; i += simd_size)
        {
            const simd_type_T element1 = load(last1prologue);
            const simd_type_T element2 = load(last2prologue);
            const simd_type_T res=blend(on,off,pred(element1,element2)); //workaound no reduce_and for mask_type               
            if(!reduce_and(res)) return false;
            last1prologue += simd_size;
            last2prologue += simd_size;
        }
    }
    else
    {
        for (; i < size_simd_loop; i += simd_size)
        {
        const simd_type_T element1 = load(last1prologue);
        const simd_type_T element2 = load_u(last2prologue);
        const simd_type_T res=blend(on,off,pred(element1,element2));//workaound no reduce_and for mask_type                              
        if(!reduce_and(res)) return false;
        last1prologue += simd_size;
        last2prologue += simd_size;
        }
    }

    if(!std::equal(last1prologue, last1,last2prologue,pred)) return false;   
    return true;
}
      
template<typename T> 
bool equal(const T* first1,  const T* last1, const T* first2)
{
    struct local_bynary_predicate_equal
    {
    using simd_type_T = typename simd_traits<T>::simd_type;
    using simd_mask_T = typename simd_traits<T>::simd_mask_type;
    SIMDPP_INL bool operator()(const T& a0,const T& a1) const SIMDPP_NOEXCEPT {return a0==a1;}
    SIMDPP_INL simd_mask_T operator()(const simd_type_T& a0,const simd_type_T& a1) const SIMDPP_NOEXCEPT {return cmp_eq(a0,a1);}
    };
    return equal(first1,last1,first2,local_bynary_predicate_equal());         
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_EQUAL_H
