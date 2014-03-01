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

#ifndef LIBSIMDPP_SIMDPP_CORE_MOVE_R_H
#define LIBSIMDPP_SIMDPP_CORE_MOVE_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/move_r.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Moves the 8-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0   1    .  14  15  |
     0      r = [ a0  a1   .  a14 a15 ]
     1      r = [  0  a0   .  a13 a14 ]
     2      r = [  0   0   .  a12 a13 ]
      ...    ..   .. ..   ...  ..  .. ..
     14     r = [  0   0   .  a0  a1  ]
     15     r = [  0   0   .   0  a0  ]
     16     r = [  0   0   .   0   0  ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class E>
gint8<N, gint8<N>> move16_r(gint8<N,E> a)
{
    static_assert(shift <= 16, "Shift out of bounds");
    if (shift == 0) return a.eval();
    if (shift == 16) return uint8<N>::zero();

    return detail::insn::i_move16_r<shift>(a.eval());
}

/** Moves the 16-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1   . 6  7  |
     0      r = [ a0 a1  . a6 a7 ]
     1      r = [  0 a0  . a5 a6 ]
     2      r = [  0  0  . a4 a5 ]
      ...    ..   .. .. ... .. ..
     6      r = [  0  0  . a0 a1 ]
     7      r = [  0  0  .  0 a0 ]
     8      r = [  0  0  .  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class E>
gint16<N, gint16<N>> move8_r(gint16<N,E> a)
{
    static_assert(shift <= 8, "Shift out of bounds");
    if (shift == 0) return a.eval();
    if (shift == 8) return uint16<N>::zero();

    return detail::insn::i_move8_r<shift>(a.eval());
}

/** Moves the 32-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [  0 a0 a1 a2 ]
     2      r = [  0  0 a0 a1 ]
     3      r = [  0  0  0 a0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class E>
gint32<N, gint32<N>> move4_r(gint32<N,E> a)
{
    static_assert(shift <= 4, "Shift out of bounds");
    if (shift == 0) return a.eval();
    if (shift == 4) return uint32<N>::zero();

    return detail::insn::i_move4_r<shift>(a.eval());
}

/** Moves the 64-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [  0 a0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class E>
gint64<N, gint64<N>> move2_r(gint64<N,E> a)
{
    static_assert(shift <= 2, "Shift out of bounds");
    if (shift == 0) return a.eval();
    if (shift == 2) return uint64<N>::zero();

    return detail::insn::i_move2_r<shift>(a.eval());
}

/** Moves the 32-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  2  3  |
     0      r = [ a0 a1 a2 a3 ]
     1      r = [  0 a0 a1 a2 ]
     2      r = [  0  0 a0 a1 ]
     3      r = [  0  0  0 a0 ]
     4      r = [  0  0  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class E>
float32<N, float32<N>> move4_r(float32<N,E> a)
{
    static_assert(shift <= 4, "Shift out of bounds");
    if (shift == 0) return a.eval();
    if (shift == 4) return float32<N>::zero();

    return detail::insn::i_move4_r<shift>(a.eval());
}


/** Moves the 64-bit elements in a vector to the right by @a shift positions.

    @code
    shift:  pos:| 0  1  |
     0      r = [ a0 a1 ]
     1      r = [  0 a0 ]
     2      r = [  0  0 ]
    @endcode

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned shift, unsigned N, class E>
float64<N, float64<N>> move2_r(float64<N,E> a)
{
    static_assert(shift <= 2, "Shift out of bounds");
    if (shift == 0) return a.eval();
    if (shift == 2) return float64<N>::zero();

    return detail::insn::i_move2_r<shift>(a.eval());
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

