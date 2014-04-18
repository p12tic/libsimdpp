/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_NEG_H
#define LIBSIMDPP_SIMDPP_CORE_F_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/expr/f_neg.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Negates the values of a float32x4 vector

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, 2-3}
    @icost{AVX-AVX2, NEON, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
float32<N, _DETAIL_> neg(float32<N,E> a);
#else
template<unsigned N, class E>
float32<N, expr_neg<float32<N,E>>> neg(float32<N,E> a)
{
    return { { a }, 0 };
}
#endif

/** Negates the values of a vector

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 1-2}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX-AVX2, 1-2}
    @novec{NEON, ALTIVEC}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
float64<N, _DETAIL_> neg(float64<N,E> a);
#else
template<unsigned N, class E>
float64<N, expr_neg<float64<N,E>>> neg(float64<N,E> a)
{
    return { { a }, 0 };
}
#endif


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

