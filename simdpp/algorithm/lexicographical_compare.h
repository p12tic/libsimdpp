/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_LEXICOGRAPHICAL8COMPARE_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_LEXICOGRAPHICAL8COMPARE_H

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

template<typename T, typename BinarayPredicate>
bool lexicographical_compare(const T* first1, const T* last1, const T* first2, const T* last2,BinarayPredicate comp)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first1)
    throw std::runtime_error("lexicographical_compare - null ptr first1.");
    if (!last1)
    throw std::runtime_error("lexicographical_compare - null ptr last1.");
    if (!first2)
    throw std::runtime_error("lexicographical_compare - null ptr first2.");
    if (!last2)
    throw std::runtime_error("lexicographical_compare - null ptr last2.");
#endif
      
    using simd_type_T = typename simd_traits<T>::simd_type;

    auto alignment = simd_traits<T>::alignment;   
    using  difference_type_T = typename std::iterator_traits<const T*>::difference_type;
    difference_type_T d1 =  std::distance(first1, last1);
    difference_type_T d2 =  std::distance(first2, last2);
    bool shorter =  d1 < d2;
    auto last = shorter ?  last1 : first1+d2;
    auto size = shorter ?  d1 : d2;

    //define loopcounter
    const auto simd_size = simd_type_T::base_length;
      
    //note enforce that input is aligned when we start the main simd loop
    const auto range = helper_input_range(first1, last);
    const auto size_prologue_loop = range.first;
    const auto size_simd_loop = range.second;

    auto i=0u;
    //---prologue
    for (; i < size_prologue_loop; ++i)
    {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
    ++first1;
    ++first2;        
    }
      
    //---main simd loop  
    if (detail::is_aligned(first2, alignment))
    {
    for (; i < size_simd_loop; i += simd_size)
    {
        simd_type_T element1 = load(first1);
        simd_type_T element2 = load(first2);
        if(comp(element1, element2)) return true;
        if(comp(element2, element1)) return false;
        first1 += simd_size;
        first2 += simd_size;
    }
    }
    else
    {
    for (; i < size_simd_loop; i += simd_size)
    {
        simd_type_T element1 = load(first1);
        simd_type_T element2 = load_u(first2);
        if(comp(element1, element2)) return true;
        if(comp(element2, element1)) return false;
        first1 += simd_size;
        first2 += simd_size;
    }
    }
    //---epilogue
    for (; i < size; ++i)
    {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
    ++first1;
    ++first2;     
    }
    return shorter;
}

template<typename T>
bool lexicographical_compare(const T* first1, const T* last1, const T* first2, const T* last2)
{
    struct local_binary_predicate_less
    {
    using simd_type_T = typename simd_traits<T>::simd_type;
            
    local_binary_predicate_less():on(splat(T(1))),off(splat(T(0))) {}

    SIMDPP_INL bool operator()(T a0,T a1) const SIMDPP_NOEXCEPT { return a0<a1;}
    SIMDPP_INL bool operator()(const simd_type_T& a0,const simd_type_T& a1) const SIMDPP_NOEXCEPT
    {
        return test_bits_any(blend(on,off, cmp_lt(a0,a1)));
    }

    simd_type_T on,off;//workaround mask
            
    };
            
    return lexicographical_compare(first1,last1,first2,last2,local_binary_predicate_less());      
}
      
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_LEXICOGRAPHICAL8COMPARE_H

