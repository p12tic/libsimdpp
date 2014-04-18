/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_UNZIP_LO_H
#define LIBSIMDPP_SIMDPP_CORE_UNZIP_LO_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/unzip_lo.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** De-interleaves the odd(lower) elements of two int8x16 vectors

    @code
        | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  |
    r = [ a0  a2  a4  a6  a8  a10 a12 a14 b0  b2  b4  b6  b8  b10 b12 b14 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 8-9}
    @icost{NEON, 2}
    @icost{AVX2, 4-5}
    @icost{ALTIVEC, 2-3}

*/
template<unsigned N, class E1, class E2>
uint8<N, uint8<N>> unzip16_lo(uint8<N,E1> a, uint8<N,E2> b)
{
    return detail::insn::i_unzip16_lo(a.eval(), b.eval());
}

/** De-interleaves the odd(lower) elements of two int16x8 vectors

    @code
        | 0  1  2  3  4  5  6  7  |
    r = [ a0 a2 a4 a6 b0 b2 b4 b6 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX2, 4-5}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSSE3, 5}
    @icost{SSE4.1-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned N, class E1, class E2>
uint16<N, uint16<N>> unzip8_lo(uint16<N,E1> a, uint16<N,E2> b)
{
    return detail::insn::i_unzip8_lo(a.eval(), b.eval());
}

/** De-interleaves the odd(lower) elements of two int32x4 vectors

    @code
        | 0  1  2  3  |
    r = [ a0 a2 b0 b2 ]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
template<unsigned N, class E1, class E2>
uint32<N, uint32<N>> unzip4_lo(uint32<N,E1> a, uint32<N,E2> b)
{
    return detail::insn::i_unzip4_lo(a.eval(), b.eval());
}

/** De-interleaves the odd(lower) elements of two int64x2 vectors

    @code
        | 0  1  |
    r = [ a0 b0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
uint64<N, uint64<N>> unzip2_lo(uint64<N,E1> a, uint64<N,E2> b)
{
    return detail::insn::i_unzip2_lo(a.eval(), b.eval());
}

/** De-interleaves the odd(lower) elements of two float32x4 vectors

    @code
        | 0  1  2  3  |
    r = [ a0 a2 b0 b2 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE4.1, NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2>
float32<N, float32<N>> unzip4_lo(float32<N,E1> a, float32<N,E2> b)
{
    return detail::insn::i_unzip4_lo(a.eval(), b.eval());
}

/** De-interleaves the odd(lower) elements of two float64x2 vectors

    @code
        | 0  1  |
    r = [ a0 b0 ]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @novec{NEON, ALTIVEC}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
template<unsigned N, class E1, class E2>
float64<N, float64<N>> unzip2_lo(float64<N,E1> a, float64<N,E2> b)
{
    return detail::insn::i_unzip2_lo(a.eval(), b.eval());
}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

