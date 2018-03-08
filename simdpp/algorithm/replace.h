/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_REPLACE_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_REPLACE_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/algorithm/transform.h>

namespace simdpp {
   namespace SIMDPP_ARCH_NAMESPACE {

      template<typename T>
         void replace(T* first, T* last, T const & old_val, T const & new_val)
      {
         struct local_predicate
         {
            using simd_type_T = typename typetraits<T>::simd_type;
            local_predicate(const T & old_val, const T & new_val) : m_old_val(old_val), m_new_val(new_val),m_old_val_simd(splat(old_val)), m_new_val_simd(splat(new_val)) {}

            T   operator()( const T& a) const { return a == m_old_val ? m_new_val : a;}
            simd_type_T operator()(const simd_type_T& a) const { return blend(m_new_val_simd,a,cmp_eq(a,m_old_val_simd)); }

            T m_old_val, m_new_val;
            simd_type_T  m_old_val_simd, m_new_val_simd;
         };

         transform(first, last, first, local_predicate(old_val, new_val));
      }
       
   } // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_REPLACE_H
