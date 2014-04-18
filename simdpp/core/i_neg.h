/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_NEG_H
#define LIBSIMDPP_SIMDPP_CORE_I_NEG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/expr/i_neg.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Negates signed 8-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
int8<N, _DETAIL_> neg(int8<N,E> a);
#else
template<unsigned N, class E>
int8<N, expr_neg<int8<N,E>>> neg(int8<N,E> a)
{
    return { { a }, 0 };
}
#endif

/** Negates signed 16-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
int16<N, _DETAIL_> neg(int16<N,E> a);
#else
template<unsigned N, class E>
int16<N, expr_neg<int16<N,E>>> neg(int16<N,E> a)
{
    return { { a }, 0 };
}
#endif

/** Negates signed 32-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
int32<N, _DETAIL_> neg(int32<N,E> a);
#else
template<unsigned N, class E>
int32<N, expr_neg<int32<N,E>>> neg(int32<N,E> a)
{
    return { { a }, 0 };
}
#endif

/** Negates signed 64-bit values.

    @code
    r0 = -a0
    ...
    rN = -aN
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 8-9}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
int64<N, _DETAIL_> neg(int64<N,E> a);
#else
template<unsigned N, class E>
int64<N, expr_neg<int64<N,E>>> neg(int64<N,E> a)
{
    return { { a }, 0 };
}
#endif

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

