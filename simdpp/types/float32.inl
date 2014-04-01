/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32_INL
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/float32.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<unsigned N> maskdata_float32<N>::operator float32<N>() const
{
    float32<N> r;
    for (unsigned i = 0; i < vec_length; ++i) r[i] = d_[i];
    return r;
}

template<unsigned N> mask_float32<N>::mask_float32(const maskdata_float32<N>& d) : float32<N>(d), mask_(d) {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
