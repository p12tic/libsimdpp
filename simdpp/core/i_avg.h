/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_AVG_H
#define LIBSIMDPP_SIMDPP_CORE_I_AVG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_avg.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Computes rounded average of the unsigned 8-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint8<N, uint8<N>> avg(uint8<N,E1> a, uint8<N,E2> b)
{
    return detail::insn::i_avg(a.eval(), b.eval());
}

/** Computes rounded average of signed 8-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
int8<N, int8<N>> avg(int8<N,E1> a, int8<N,E2> b)
{
    return detail::insn::i_avg(a.eval(), b.eval());
}

/** Computes rounded average of unsigned 16-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint16<N, uint16<N>> avg(uint16<N,E1> a, uint16<N,E2> b)
{
    return detail::insn::i_avg(a.eval(), b.eval());
}

/** Computes rounded average of signed 16-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
int16<N, int16<N>> avg(int16<N,E1> a, int16<N,E2> b)
{
    return detail::insn::i_avg(a.eval(), b.eval());
}

/** Computes rounded average of unsigned 32-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6-7}

    @par 256-bit version:
    @icost{SSE2-AVX, 12-13}
    @icost{AVX2, 6-7}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint32<N, uint32<N>> avg(uint32<N,E1> a, uint32<N,E2> b)
{
    return detail::insn::i_avg(a.eval(), b.eval());
}

/** Computes rounded average of signed 32-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 9-10}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 18-19}
    @icost{AVX2, 9-10}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
int32<N, int32<N>> avg(int32<N,E1> a, int32<N,E2> b)
{
    return detail::insn::i_avg(a.eval(), b.eval());
}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

