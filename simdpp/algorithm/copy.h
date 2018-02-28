/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_COPY_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_COPY_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/algorithm/transform.h>

namespace simdpp {
    namespace SIMDPP_ARCH_NAMESPACE {

        template<typename T> 
            T* copy(T const* first, T const* last, T* out)
        {
            struct UnaryOpCopy
            {
                using simd_type_T = typename typetraits<T>::simd_type;
                SIMDPP_INL T operator()(T const &a) const  noexcept
                {
                    return a;
                }

                SIMDPP_INL simd_type_T operator()(simd_type_T const &a) const  noexcept
                {
                    return a;
                }
            };

            return transform(first, last, out, UnaryOpCopy{});
        }

    } // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_COPY_H
