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

#ifndef LIBSIMDPP_SIMDPP_CORE_SPLAT_H
#define LIBSIMDPP_SIMDPP_CORE_SPLAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/splat.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Broadcasts the specified 8-bit value to all elements within 128-bit lane

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    rN = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s, unsigned N, class E>
gint8<N, gint8<N>> splat(gint8<N,E> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::insn::i_splat<s>(a.eval());
}
/// @}

/// @{
/** Broadcasts the specified 16-bit value to all elements within a int16x8 vector

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    r7 = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s, unsigned N, class E>
gint16<N, gint16<N>> splat(gint16<N,E> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::insn::i_splat<s>(a.eval());
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within a int32x4 vector

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s, unsigned N, class E>
gint32<N, gint32<N>> splat(gint32<N,E> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::insn::i_splat<s>(a.eval());
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within a int64x2 vector

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 1-2}
*/
template<unsigned s, unsigned N, class E>
gint64<N, gint64<N>> splat(gint64<N,E> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::insn::i_splat<s>(a.eval());
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within a float32x4 vector

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned s, unsigned N, class E>
float32<N, float32<N>> splat(float32<N,E> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::insn::i_splat<s>(a.eval());
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within a float64x2 vector

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s, unsigned N, class E>
float64<N, float64<N>> splat(float64<N,E> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::insn::i_splat<s>(a.eval());
}
/// @}
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

