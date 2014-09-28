/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_MAX_H
#define LIBSIMDPP_SIMDPP_CORE_I_MAX_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_max.h>
#include <simdpp/core/detail/scalar_arg_impl.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Computes maximum of the signed 8-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 8}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
int8<N, _DETAIL_> max(int8<N,E1> a, int8<N,E2> b);
#else
template<unsigned N, class E1, class E2>
int8<N, int8<N>> max(int8<N,E1> a, int8<N,E2> b)
{
    return detail::insn::i_max(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(max, int8, int8)

/** Computes maximum of the unsigned 8-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
uint8<N, _DETAIL_> max(uint8<N,E1> a, uint8<N,E2> b);
#else
template<unsigned N, class E1, class E2>
uint8<N, uint8<N>> max(uint8<N,E1> a, uint8<N,E2> b)
{
    return detail::insn::i_max(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(max, uint8, uint8)

/** Computes maximum of the signed 16-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
int16<N, _DETAIL_> max(int16<N,E1> a, int16<N,E2> b);
#else
template<unsigned N, class E1, class E2>
int16<N, int16<N>> max(int16<N,E1> a, int16<N,E2> b)
{
    return detail::insn::i_max(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(max, int16, int16)

/** Computes maximum of the unsigned 16-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6-7}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12-13}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
uint16<N, _DETAIL_> max(uint16<N,E1> a, uint16<N,E2> b);
#else
template<unsigned N, class E1, class E2>
uint16<N, uint16<N>> max(uint16<N,E1> a, uint16<N,E2> b)
{
    return detail::insn::i_max(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(max, uint16, uint16)

/** Computes maximum of the signed 32-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 4}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 8}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
int32<N, _DETAIL_> max(int32<N,E1> a, int32<N,E2> b);
#else
template<unsigned N, class E1, class E2>
int32<N, int32<N>> max(int32<N,E1> a, int32<N,E2> b)
{
    return detail::insn::i_max(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(max, int32, int32)

/** Computes maximum of the unsigned 32-bit values.

    @code
    r0 = max(a0, b0)
    ...
    rN = max(aN, bN)
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 6-7}

    @par 256-bit version:
    @icost{SSE2-SSSE3, 12-13}
    @icost{SSE4.1-AVX, NEON, ALTIVEC, 2}
*/
#if SIMDPP_DOXYGEN
template<unsigned N, class E1, class E2>
uint32<N, _DETAIL_> max(uint32<N,E1> a, uint32<N,E2> b);
#else
template<unsigned N, class E1, class E2>
uint32<N, uint32<N>> max(uint32<N,E1> a, uint32<N,E2> b)
{
    return detail::insn::i_max(a.eval(), b.eval());
}
#endif

SIMDPP_SCALAR_ARG_IMPL_VEC(max, uint32, uint32)


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

