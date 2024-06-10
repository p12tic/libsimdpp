/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_HELPER_INPUT_RANGE_H
#define LIBSIMDPP_SIMDPP_HELPER_INPUT_RANGE_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <iterator> 
#include <simdpp/types/traits.h>
#include <simdpp/detail/align.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
/**    
Extract from contigous range [first,last[
    The two loop counter 
    -the scalar prologue [start,size_prologue_loop[ i.e the range defined between the original begin and the first
    location to be properly aligned to be used through simd operators 
    - the main simd_loop_part,[size_prologue_loop,size_simd_loop[ i.e the range where we could apply simd operators
    - Note epilogue equals [size_simd_loop,stop[
*/
template<typename T>
const std::pair<ptrdiff_t, ptrdiff_t> SIMDPP_INL helper_input_range(const T* first, const T* last)
{
#ifndef SIMDPP_DEBUG  //precondition debug mode           
    if (!first)
        throw std::runtime_error("helper_input_range - null ptr first.");
    if (!last)
        throw std::runtime_error("helper_input_range - null ptr last.");
#endif
    using simd_type_T = typename simd_traits<T>::simd_type;            

    const auto simd_size = simd_type_T::base_length;
    const auto alignment = simd_traits<T>::alignment;

    const auto size = last - first;
    //get first aligned adress from first
    const T* ptr_aligned_first =detail::reach_next_aligned(first, alignment);
    // Next aligned address may be out of range, so make sure size_prologue_loop is not bigger than size
    const auto size_prologue_loop = std::min(size,std::distance(first, ptr_aligned_first));
    const auto size_simd_loop = (size >= size_prologue_loop) ? (simd_size * ((size- size_prologue_loop) / simd_size)) : (0u);

    return std::make_pair(size_prologue_loop, size_simd_loop);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_HELPER_INPUT_RANGE_H
