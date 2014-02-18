/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_UNZIP_LO_H
#define LIBSIMDPP_SIMDPP_CORE_UNZIP_LO_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/unzip_lo.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
gint8<N, gint8<N>> unzip_lo(gint8<N,E1> a, gint8<N,E2> b)
{
    return detail::insn::i_unzip_lo(a.eval(), b.eval());
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
gint16<N, gint16<N>> unzip_lo(gint16<N,E1> a, gint16<N,E2> b)
{
    return detail::insn::i_unzip_lo(a.eval(), b.eval());
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
gint32<N, gint32<N>> unzip_lo(gint32<N,E1> a, gint32<N,E2> b)
{
    return detail::insn::i_unzip_lo(a.eval(), b.eval());
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
gint64<N, gint64<N>> unzip_lo(gint64<N,E1> a, gint64<N,E2> b)
{
    return detail::insn::i_unzip_lo(a.eval(), b.eval());
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
float32<N, float32<N>> unzip_lo(float32<N,E1> a, float32<N,E2> b)
{
    return detail::insn::i_unzip_lo(a.eval(), b.eval());
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
float64<N, float64<N>> unzip_lo(float64<N,E1> a, float64<N,E2> b)
{
    return detail::insn::i_unzip_lo(a.eval(), b.eval());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

