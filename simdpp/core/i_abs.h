/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_ABS_H
#define LIBSIMDPP_SIMDPP_CORE_I_ABS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/expr/i_abs.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Computes absolute value of 8-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-4}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
uint8<N, _DETAIL_> abs(int8<N,E> a);
#else
template<unsigned N, class E>
uint8<N, expr_abs<int8<N,E>>> abs(int8<N,E> a)
{
    return { { a }, 0 };
}
#endif


/** Computes absolute value of 16-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-5}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
uint16<N, _DETAIL_> abs(int16<N,E> a);
#else
template<unsigned N, class E>
uint16<N, expr_abs<int16<N,E>>> abs(int16<N,E> a)
{
    return { { a }, 0 };
}
#endif

/** Computes absolute value of 32-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{ALTIVEC, 1-3}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, NEON, 2}
    @icost{ALTIVEC, 2-4}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
uint32<N, _DETAIL_> abs(int32<N,E> a);
#else
template<unsigned N, class E>
uint32<N, expr_abs<int32<N,E>>> abs(int32<N,E> a)
{
    return { { a }, 0 };
}
#endif

/** Computes absolute value of 64-bit integer values.

    @code
    r0 = abs(a0)
    ...
    rN = abs(aN)
    @endcode
    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{NEON, 6}
    @novec{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 10}
    @icost{NEON, 12}
    @icost{AVX2, 4}
    @novec{ALTIVEC}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
uint64<N, _DETAIL_> abs(int64<N,E> a);
#else
template<unsigned N, class E>
uint64<N, expr_abs<int64<N,E>>> abs(int64<N,E> a)
{
    return { { a }, 0 };
}
#endif

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

