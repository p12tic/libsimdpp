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
namespace SIMDPP_ARCH_NAMESPACE {

/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned N, class E> SIMDPP_INL
int8<N,expr_empty> shift_l(const int8<N,E>& a, unsigned count)
{
    uint8<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_l(const uint8<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned N, class E> SIMDPP_INL
int16<N,expr_empty> shift_l(const int16<N,E>& a, unsigned count)
{
    uint16<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_l(const uint16<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned N, class E> SIMDPP_INL
int32<N,expr_empty> shift_l(const int32<N,E>& a, unsigned count)
{
    uint32<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_l(const uint32<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned N, class E> SIMDPP_INL
int64<N,expr_empty> shift_l(const int64<N,E>& a, unsigned count)
{
    uint64<N> qa = a.eval();
    return detail::insn::i_shift_l(qa, count);
}

template<unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_l(const uint64<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_l(a.eval(), count);
}

/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int8<N,expr_empty> shift_l(const int8<N,E>& a)
{
    static_assert(count < 8, "Shift out of bounds");
    uint8<N> qa = a.eval();
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_l(const uint8<N,E>& a)
{
    static_assert(count < 8, "Shift out of bounds");
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
}

/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int16<N,expr_empty> shift_l(const int16<N,E>& a)
{
    static_assert(count < 16, "Shift out of bounds");
    uint16<N> qa = a.eval();
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_l(const uint16<N,E>& a)
{
    static_assert(count < 16, "Shift out of bounds");
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
}

/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int32<N,expr_empty> shift_l(const int32<N,E>& a)
{
    static_assert(count < 32, "Shift out of bounds");
    uint32<N> qa = a.eval();
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_l(const uint32<N,E>& a)
{
    static_assert(count < 32, "Shift out of bounds");
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
}

/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int64<N,expr_empty> shift_l(const int64<N,E>& a)
{
    static_assert(count < 64, "Shift out of bounds");
    uint64<N> qa = a.eval();
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(qa);
}

template<unsigned count, unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_l(const uint64<N,E>& a)
{
    static_assert(count < 64, "Shift out of bounds");
    return detail::insn::i_shift_l_wrapper<count == 0>::template run<count>(a.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

