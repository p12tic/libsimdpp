/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SHIFT_R_H
#define LIBSIMDPP_SIMDPP_CORE_I_SHIFT_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/i_shift_r.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/** Shifts signed 8-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 12}
    @icost{AVX2, 6}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
template<unsigned N, class E> SIMDPP_INL
int8<N,expr_empty> shift_r(const int8<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts unsigned 8-bit values right by @a count bits while shifting in zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
template<unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_r(const uint8<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts signed 16-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
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
int16<N,expr_empty> shift_r(const int16<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts unsigned 16-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
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
uint16<N,expr_empty> shift_r(const uint16<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts signed 32-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode
    @icost{NEON, 2}

    @par 128-bit version:
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
template<unsigned N, class E> SIMDPP_INL
int32<N,expr_empty> shift_r(const int32<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts unsigned 32-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
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
uint32<N,expr_empty> shift_r(const uint32<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts signed 64-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-6}
    @icost{NEON, 2}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-10}
    @icost{AVX2, 4-6}
    @icost{NEON, 3}
    @unimp{ALTIVEC}
*/
template<unsigned N, class E> SIMDPP_INL
int64<N,expr_empty> shift_r(const int64<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts unsigned 64-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
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
uint64<N,expr_empty> shift_r(const uint64<N,E>& a, unsigned count)
{
    return detail::insn::i_shift_r(a.eval(), count);
}

/** Shifts signed 8-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6}
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 12}
    @icost{AVX2, 6}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int8<N,expr_empty> shift_r(const int8<N,E>& a)
{
    static_assert(count <= 8, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, false>::template run<count>(a.eval());
}

/** Shifts unsigned 8-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}
    @icost{SSE2-AVX2, 2-3}

    @par 256-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{AVX2, 2-3}
    @icost{NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint8<N,expr_empty> shift_r(const uint8<N,E>& a)
{
    static_assert(count <= 8, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, count == 8>::template run<count>(a.eval());
}

/** Shifts signed 16-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int16<N,expr_empty> shift_r(const int16<N,E>& a)
{
    static_assert(count <= 16, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, false>::template run<count>(a.eval());
}

/** Shifts unsigned 16-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint16<N,expr_empty> shift_r(const uint16<N,E>& a)
{
    static_assert(count <= 16, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, count == 16>::template run<count>(a.eval());
}

/** Shifts signed 32-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int32<N,expr_empty> shift_r(const int32<N,E>& a)
{
    static_assert(count <= 32, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, false>::template run<count>(a.eval());
}

/** Shifts unsigned 32-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint32<N,expr_empty> shift_r(const uint32<N,E>& a)
{
    static_assert(count <= 32, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, count == 32>::template run<count>(a.eval());
}

/** Shifts signed 64-bit values right by @a count bits while shifting in the
    sign bit.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @par 128-bit version:
    @novec{SSE2-AVX2}
    @icost{SSE2-AVX2, 4-6}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @novec{SSE2-AVX}
    @icost{SSE2-AVX, 8-10}
    @icost{AVX2, 4-6}
    @icost{NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
int64<N,expr_empty> shift_r(const int64<N,E>& a)
{
    static_assert(count <= 64, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, false>::template run<count>(a.eval());
}

/** Shifts unsigned 64-bit values right by @a count bits while shifting in
    zeros.

    @code
    r0 = a0 >> count
    ...
    rN = aN >> count
    @endcode

    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count, unsigned N, class E> SIMDPP_INL
uint64<N,expr_empty> shift_r(const uint64<N,E>& a)
{
    static_assert(count <= 64, "Shift out of bounds");
    return detail::insn::i_shift_r_wrapper<count == 0, count == 64>::template run<count>(a.eval());
}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

