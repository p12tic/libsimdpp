/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_CAST_H
#define LIBSIMDPP_SIMDPP_CORE_CAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/detail/cast.h>
#include <simdpp/types/traits.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @ingroup simd_convert
    Casts between unrelated types. No changes to the stored values are
    performed.

    Conversions between vector and non-vector types are not allowed.

    Conversion from non-mask type to mask type is not allowed.
 
    Conversion from mask type to a non-mask type is not a costless operation 
    because masks may have different logical and physical layout (e.g., in
    some implementations one bit represents entire element in a vector).

    Conversions between mask types is only allowed if the element size is the
    same.
*/
template<class R, class T>
R bit_cast(T t)
{
    static_assert(is_vector<R>::value == is_vector<T>::value,
                  "bit_cast can't convert between vector and non-vector types");
    return detail::cast_wrapper<is_mask<R>::value, is_mask<T>::value>::template run<R>(t);
}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
