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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SHIFT_L_H
#define LIBSIMDPP_SIMDPP_CORE_I_SHIFT_L_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_shift_l.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode


    @par 128-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
template<unsigned N, class E>
gint8<N, gint8<N>> shift_l(gint8<N,E> a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
template<unsigned N, class E>
gint16<N, gint16<N>> shift_l(gint16<N,E> a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
template<unsigned N, class E>
gint32<N, gint32<N>> shift_l(gint32<N,E> a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}


/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @unimp{ALTIVEC}
*/
template<unsigned N, class E>
gint64<N, gint64<N>> shift_l(gint64<N,E> a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/// @{
/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode


    @par 128-bit version:
    @icost{SSE2-AVX2, 2-3}
    @icost{NEON, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{AVX2,NEON, 2-3}
*/
template<unsigned count, unsigned N, class E>
gint8<N, gint8<N>> shift_l(gint8<N,E> a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return gint8<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}

/// @{
/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E>
gint16<N, gint16<N>> shift_l(gint16<N,E> a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return gint16<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}

/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E>
gint32<N, gint32<N>> shift_l(gint32<N,E> a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return gint32<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}

/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count, unsigned N, class E>
gint64<N, gint64<N>> shift_l(gint64<N,E> a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return gint64<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

