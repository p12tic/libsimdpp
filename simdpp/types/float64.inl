/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64_INL
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/float64.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<unsigned N> maskdata_float64<N>::operator float64<N>() const
{
    float64<N> r;
    for (unsigned i = 0; i < vec_length; ++i) r[i] = d_[i];
    return r;
}

template<unsigned N> mask_float64<N>::mask_float64(const maskdata_float64<N>& d) : float64<N>(d), mask_(d) {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
