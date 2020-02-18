/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_COPY_N_H
#define LIBSIMDPP_SIMDPP_ALGORITHM_COPY_N_H

#ifndef LIBSIMDPP_SIMD_H
#error "This file must be included through simd.h"
#endif

#include <simdpp/algorithm/copy.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<typename T, typename Size> T* copy_n(T const* first, Size n, T* out)
{
    if (n <= Size(0)) return out;
    return copy(first, first + n, out);
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif //LIBSIMDPP_SIMDPP_ALGORITHM_COPY_N_H
