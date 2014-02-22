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

#ifndef LIBSIMDPP_SIMDPP_CORE_SPLAT_N_H
#define LIBSIMDPP_SIMDPP_CORE_SPLAT_N_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/splat_n.h>
#include <simdpp/detail/expr/splat_n.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Broadcasts the specified 8-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    rN = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 7}
    @icost{SSSE3-AVX, 1-2}
    @icost{AVX2, 2}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE3, 14}
    @icost{SSSE3-AVX, 2-3}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s, unsigned N, class E>
gint8<N, expr_splat16<s,gint8<N,E>>> splat16(gint8<N,E> a)
{
    static_assert(s < 16, "Access out of bounds");
    return { { a }, 0 };
}
/// @}

/// @{
/** Broadcasts the specified 16-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    r7 = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE3, 3}
    @icost{SSSE3-AVX, 1-2}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-SSE3, 6}
    @icost{SSSE3-AVX, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
template<unsigned s, unsigned N, class E>
gint16<N, expr_splat8<s,gint16<N,E>>> splat8(gint16<N,E> a)
{
    static_assert(s < 8, "Access out of bounds");
    return { { a }, 0 };
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within 128-bit lanes.

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
gint32<N, expr_splat4<s,gint32<N,E>>> splat4(gint32<N,E> a)
{
    static_assert(s < 4, "Access out of bounds");
    return { { a }, 0 };
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within 128-bit lanes.

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned s, unsigned N, class E>
gint64<N, expr_splat2<s,gint64<N,E>>> splat2(gint64<N,E> a)
{
    static_assert(s < 2, "Access out of bounds");
    return { { a }, 0 };
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within 128-bit lanes.

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
float32<N, expr_splat4<s,float32<N,E>>> splat4(float32<N,E> a)
{
    static_assert(s < 4, "Access out of bounds");
    return { { a }, 0 };
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within 128-bit lanes.

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
float64<N, expr_splat2<s,float64<N,E>>> splat2(float64<N,E> a)
{
    static_assert(s < 2, "Access out of bounds");
    return { { a }, 0 };
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

