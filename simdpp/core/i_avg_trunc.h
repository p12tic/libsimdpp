/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_AVG_TRUNC_H
#define LIBSIMDPP_SIMDPP_CORE_I_AVG_TRUNC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_avg_trunc.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Computes truncated average of the unsigned 8-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint8<N, uint8<N>> avg_trunc(uint8<N,E1> a, uint8<N,E2> b)
{
    return detail::insn::i_avg_trunc(a.eval(), b.eval());
}

/** Computes truncated average of signed 8-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
int8<N, int8<N>> avg_trunc(int8<N,E1> a, int8<N,E2> b)
{
    return detail::insn::i_avg_trunc(a.eval(), b.eval());
}

/** Computes truncated average of unsigned 16-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint16<N, uint16<N>> avg_trunc(uint16<N,E1> a, uint16<N,E2> b)
{
    return detail::insn::i_avg_trunc(a.eval(), b.eval());
}

/** Computes truncated average of signed 16-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
int16<N, int16<N>> avg_trunc(int16<N,E1> a, int16<N,E2> b)
{
    return detail::insn::i_avg_trunc(a.eval(), b.eval());
}

/** Computes truncated average of unsigned 32-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint32<N, uint32<N>> avg_trunc(uint32<N,E1> a, uint32<N,E2> b)
{
    return detail::insn::i_avg_trunc(a.eval(), b.eval());
}

/** Computes truncated average of signed 32-bit values.

    @code
    r0 = (a0 + b0) / 2
    ...
    rN = (aN + bN) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 7-8}
    @icost{ALTIVEC, 4}

    @par 256-bit version:
    @icost{SSE2-AVX, 14-15}
    @icost{AVX2, 7-8}
    @icost{ALTIVEC, 8}
    @icost{NEON, 2}
*/
template<unsigned N, class E1, class E2>
int32<N, int32<N>> avg_trunc(int32<N,E1> a, int32<N,E2> b)
{
    return detail::insn::i_avg_trunc(a.eval(), b.eval());
}


#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

