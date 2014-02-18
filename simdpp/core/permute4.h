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

#ifndef LIBSIMDPP_SIMDPP_CORE_PERMUTE4_H
#define LIBSIMDPP_SIMDPP_CORE_PERMUTE4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/permute4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Permutes the 16-bit values within each 4 consecutive values of the vector.
    The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]

    256-bit version:

    r8 = a[s0+8]
    ...
    r11 = a[s3+8]
    r12 = a[s0+12]
    ...
    r15 = a[s3+12]
    @endcode

    @par: 128-bit version:
    @icost{SSE2-AVX2, 2}
    @icost{NEON, 1-5}
    @icost{ALTIVEC, 1-2}

    @par: 256-bit version:
    @icost{SSE2-AVX, 4}
    @icost{AVX2, 2}
    @icost{NEON, 2-10}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3,
         unsigned N, class E>
gint16<N, gint16<N>> permute4(gint16<N,E> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return detail::insn::i_permute4<s0,s1,s2,s3>(a.eval());
}

/** Permutes the values of each set of four consecutive 32-bit values. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]

    256-bit version:
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3,
         unsigned N, class E>
gint32<N, gint32<N>> permute4(gint32<N,E> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return detail::insn::i_permute4<s0,s1,s2,s3>(a.eval());
}

/** Permutes the values of each set of four consecutive 32-bit floating point
    values. The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    ...
    r3 = a[s3]

    256-bit version:
    r4 = a[s0+4]
    ...
    r7 = a[s3+4]
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2}
    @icost{NEON, 2-8}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3,
         unsigned N, class E>
float32<N, float32<N>> permute4(float32<N,E> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return detail::insn::i_permute4<s0,s1,s2,s3>(a.eval());
}

/** Permutes the values of each set of four consecutive 64-bit values. The
    selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s2]
    r3 = a[s3]
    @endcode
    @icost{SSE2-AVX, 2}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3,
         unsigned N, class E>
gint64<N, gint64<N>> permute4(gint64<N,E> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return detail::insn::i_permute4<s0,s1,s2,s3>(a.eval());
}

/** Permutes the values of each set of four consecutive 64-bit floating-point
    values. The selector values must be in range [0; 3].

    @code
    r0 = a[s0]
    r1 = a[s1]
    r2 = a[s2]
    r3 = a[s3]
    @endcode

    @icost{SSE2-AVX, 1-2}
    @icost{NEON, 1-4}
    @icost{ALTIVEC, 1-4}
*/
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3,
         unsigned N, class E>
float64<N, float64<N>> permute4(float64<N,E> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return detail::insn::i_permute4<s0,s1,s2,s3>(a.eval());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

