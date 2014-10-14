/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SHIFT_L_H
#define LIBSIMDPP_SIMDPP_CORE_I_SHIFT_L_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_shift_l.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
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
template<unsigned N, class E> SIMDPP_INL
int8<N, int8<N>> shift_l(const int8<N,E>& a, unsigned count)
{
    uint8<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint8<N, uint8<N>> shift_l(const uint8<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}
/// @}

/// @{
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
template<unsigned N, class E> SIMDPP_INL
int16<N, int16<N>> shift_l(const int16<N,E>& a, unsigned count)
{
    uint16<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint16<N, uint16<N>> shift_l(const uint16<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}
/// @}

/// @{
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
template<unsigned N, class E> SIMDPP_INL
int32<N, int32<N>> shift_l(const int32<N,E>& a, unsigned count)
{
    uint32<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint32<N, uint32<N>> shift_l(const uint32<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}
/// @}

/// @{
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
template<unsigned N, class E> SIMDPP_INL
int64<N, int64<N>> shift_l(const int64<N,E>& a, unsigned count)
{
    uint64<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint64<N, uint64<N>> shift_l(const uint64<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}
/// @}

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
template<unsigned count, unsigned N, class E> SIMDPP_INL
int8<N, int8<N>> shift_l(const int8<N,E>& a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return int8<N>::zero();

    uint8<N> qa = a.eval();
    return detail::insn::i_shift_l<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint8<N, uint8<N>> shift_l(const uint8<N,E>& a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}
/// @}

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
template<unsigned count, unsigned N, class E> SIMDPP_INL
int16<N, int16<N>> shift_l(const int16<N,E>& a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return int16<N>::zero();

    uint16<N> qa = a.eval();
    return detail::insn::i_shift_l<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint16<N, uint16<N>> shift_l(const uint16<N,E>& a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}
/// @}

/// @{
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
template<unsigned count, unsigned N, class E> SIMDPP_INL
int32<N, int32<N>> shift_l(const int32<N,E>& a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return int32<N>::zero();

    uint32<N> qa = a.eval();
    return detail::insn::i_shift_l<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint32<N, uint32<N>> shift_l(const uint32<N,E>& a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}
/// @}

/// @{
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
template<unsigned count, unsigned N, class E> SIMDPP_INL
int64<N, int64<N>> shift_l(const int64<N,E>& a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return int64<N>::zero();

    uint64<N> qa = a.eval();
    return detail::insn::i_shift_l<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint64<N, uint64<N>> shift_l(const uint64<N,E>& a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64<N>::zero();
    return detail::insn::i_shift_l<count>(a.eval());
}
/// @}

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

