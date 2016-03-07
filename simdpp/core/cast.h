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
namespace SIMDPP_ARCH_NAMESPACE {

namespace detail {

// on NEON mask-mask conversions may need unmasking or remasking
template<class R, class T> struct cast_mask_override { static const unsigned value = CAST_MASK_MEMCPY; };
#if SIMDPP_USE_NEON_NO_FLT_SP
template<unsigned N>
struct cast_mask_override<mask_float32<N>, mask_int32<N> > { static const unsigned value = CAST_MASK_UNMASK; };
template<unsigned N>
struct cast_mask_override<mask_int32<N>, mask_float32<N> > { static const unsigned value = CAST_MASK_REMASK; };
#endif
#if SIMDPP_USE_NEON
template<unsigned N>
struct cast_mask_override<mask_int64<N>, mask_float64<N> > { static const unsigned value = CAST_MASK_UNMASK; };
template<unsigned N>
struct cast_mask_override<mask_float64<N>, mask_int64<N> > { static const unsigned value = CAST_MASK_REMASK; };
#endif

} // namespace detail

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
template<class R, class T> SIMDPP_INL
R bit_cast(const T& t)
{
    SIMDPP_STATIC_ASSERT(is_vector<R>::value == is_vector<T>::value,
                  "bit_cast can't convert between vector and non-vector types");
    return detail::cast_wrapper<is_mask<R>::value,
                                is_mask<T>::value,
                                detail::cast_mask_override<R,T>::value>::template run<R>(t);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
