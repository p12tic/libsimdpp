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

#ifndef LIBSIMDPP_SIMDPP_CORE_SHUFFLE1_H
#define LIBSIMDPP_SIMDPP_CORE_SHUFFLE1_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/shuffle1.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Selects 64-bit floating-point values from two vectors. The first value in
    each pair of values must come from @a a, the second - from @a b. The
    selector values must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = b[s1]

    256-bit version:
    r2 = a[s0+2]
    r3 = b[s1+2]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s0, unsigned s1, unsigned N, class E1, class E2>
float64<N, float64<N>> shuffle1(float64<N,E1> a,
                                float64<N,E2> b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return detail::insn::i_shuffle1<s0,s1>(a.eval(), b.eval());
}

/** Selects 64-bit values from two vectors. The first value in each pair of
    values must come from @a a, the second - from @a b. The selector values
    must be in range [0; 1].

    @code
    r0 = a[s0]
    r1 = b[s1]

    256-bit version:
    r2 = a[s0+2]
    r3 = b[s1+2]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned N, class E1, class E2>
gint64<N, gint64<N>> shuffle1(gint64<N,E1> a,
                              gint64<N,E2> b)
{
    static_assert(s0 < 2 && s1 < 2, "Selector out of range");
    return detail::insn::i_shuffle1<s0,s1>(a.eval(), b.eval());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

