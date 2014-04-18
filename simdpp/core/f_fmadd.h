/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_FMADD_H
#define LIBSIMDPP_SIMDPP_CORE_F_FMADD_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/expr/f_fmadd.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Performs a fused multiply-add operation

    @code
    r0 = a0 * b0 + c0
    ...
    rN = aN * bN + cN
    @endcode

    Implemented only on architectures with either @c X86_FMA3 or @c X86_FMA4
    support.
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2, class E3>
float32<N, _DETAIL_> fmadd(float32<N,E1> a,
                           float32<N,E2> b,
                           float32<N,E3> c);

template<unsigned N, class E1, class E2, class E3>
float64<N, _DETAIL_> fmadd(float64<N,E1> a,
                           float64<N,E2> b,
                           float64<N,E3> c);
#else
template<unsigned N, class E1, class E2, class E3>
float32<N, expr_fmadd<float32<N,E1>,
                      float32<N,E2>,
                      float32<N,E3>>> fmadd(float32<N,E1> a,
                                            float32<N,E2> b,
                                            float32<N,E3> c)
{
    return { { a, b, c }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
float64<N, expr_fmadd<float64<N,E1>,
                      float64<N,E2>,
                      float64<N,E3>>> fmadd(float64<N,E1> a,
                                            float64<N,E2> b,
                                            float64<N,E3> c)
{
    return { { a, b, c }, 0 };
}
#endif
/// @}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

