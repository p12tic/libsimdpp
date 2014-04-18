/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_F_SIGN_H
#define LIBSIMDPP_SIMDPP_CORE_F_SIGN_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/f_sign.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Extracts sign bits from the values in float32x4 vector

    @code
    r0 = a0 & 0x80000000
    ...
    rN = aN & 0x80000000
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, NEON, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, ALTIVEC, NEON, 2-3}
    @icost{AVX-AVX2, 1-2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E>
float32<N, _DETAIL_> sign(float32<N,E> a);
#else
template<unsigned N, class E>
float32<N, float32<N>> sign(float32<N,E> a)
{
    return detail::insn::i_sign(a.eval());
}
#endif

/** Extracts sigh bit from the values in float64x2 vector.

    @code
    r0 = a0 & 0x8000000000000000
    ...
    r0 = aN & 0x8000000000000000
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
float64<N, _DETAIL_> abs(float64<N,E> a);
#else
template<unsigned N, class E>
float64<N, float64<N>> sign(float64<N,E> a)
{
    return detail::insn::i_sign(a.eval());
}
#endif


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

