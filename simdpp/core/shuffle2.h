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

#ifndef LIBSIMDPP_SIMDPP_CORE_SHUFFLE2_H
#define LIBSIMDPP_SIMDPP_CORE_SHUFFLE2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/shuffle2.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Selects 32-bit floating-point values from two vectors. The first two values
    in each four consecutive values must come from @a a, the last two - from @a
    b. The selector values must be in range [0; 3].

    @code
    r0 = a[a0]
    r1 = a[a1]
    r2 = b[b0]
    r3 = b[b1]

    256-bit version:
    r4 = a[a0+4]
    r5 = a[a1+4]
    r6 = b[b0+4]
    r7 = b[b1+4]
    @endcode

    @par floating-point
    @par 128-bit version:
    @icost{ALTIVEC, 1-2}
    @icost{NEON, 1-4}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}

    @par integer
     @par 128-bit version:
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned sa0, unsigned sa1, unsigned sb0, unsigned sb1, unsigned N,
         class V1, class V2>
typename detail::get_expr2_nomask<V1, V2, void>::empty
    shuffle2(const any_vec32<N,V1>& a, const any_vec32<N,V2>& b)
{
    static_assert(sa0 < 4 && sa1 < 4 && sb0 < 4 && sb1 < 4, "Selector out of range");
    typename detail::get_expr2_nomask<V1,V2,void>::type a0 = a.vec().eval(),
                                                        b0 = b.vec().eval();
    return detail::insn::i_shuffle2<sa0,sa1,sb0,sb1>(a0, b0);
}

/** Selects 32-bit values from two vectors. The first two values in each four
    consecutive values must come from @a a, the last two - from @a b. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = b[s0]
    r3 = b[s1]

    256-bit version:
    r4 = a[s0+4]
    r5 = a[s1+4]
    r6 = b[s0+4]
    r7 = b[s1+4]
    @endcode

    @par floating-point
    @par 128-bit version:
    @icost{ALTIVEC, 1-2}
    @icost{NEON, 2-4}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 4-8}
    @icost{ALTIVEC, 2-3}

    @par integer
    @par 128-bit version:
    @icost{NEON, 2-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 4-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned N,
         class V1, class V2>
typename detail::get_expr2_nomask<V1, V2, void>::empty
    shuffle2(const any_vec32<N,V1>& a, const any_vec32<N,V2>& b)
{
    static_assert(s0 < 4 && s1 < 4, "Selector out of range");
    typename detail::get_expr2_nomask<V1,V2,void>::type a0 = a.vec().eval(),
                                                        b0 = b.vec().eval();
    return detail::insn::i_shuffle2<s0,s1,s0,s1>(a0, b0);
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

