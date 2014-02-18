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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_DIV_P_H
#define LIBSIMDPP_SIMDPP_CORE_I_DIV_P_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/null/math.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// FIXME: move to adv
/// @{
/** Divides one 8-bit unsigned number by another. The precision of the operation
    is configurable: only P least significant bits of both numerator and
    denumerator are considered.

    @code
    r0 = num0 / den0
    ...
    rN = numN / denN
    @endcode
    @par 128-bit version:
    The operations costs at least 9 instructions per bit of precision.

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 10}
    @icost{AVX2, 4}
*/
template<unsigned P>
uint8x16 div_p(uint8x16 num, uint8x16 den)
{
#if SIMDPP_USE_NULL
    return null::div_p<P>(num, den);
#else
    static_assert(P <= 8, "Precision too large");
    uint8x16 r, q, bit_mask;
    r = q = uint8x16::zero();
    bit_mask = uint8x16::make_const(1 << (P-1));

    for (unsigned i = P; i > 0; i--) {
        unsigned bit = i-1;
        uint8x16 n_bit;
        // we'll never shift out any bits, so larger shift doesn't matter
        r = shift_l<1>((uint16x8)r);

        n_bit = bit_and(num, bit_mask);
        n_bit = shift_r((uint16x8)n_bit, bit);
        r = bit_or(r, n_bit);

        uint8x16 cmp, csub, cbit;
        cmp = cmp_lt(r, den);

        csub = bit_andnot(den, cmp);
        cbit = bit_andnot(bit_mask, cmp);
        r = sub(r, csub);
        q = bit_or(q, cbit);

        bit_mask = shift_r<1>((uint16x8)bit_mask);
    }
    return q;

    /*
    The actual algorithm is as follows:
    N - numerator, D - denominator, R - remainder, Q - quetient
    R = 0; Q = 0;
    for (unsigned i = P; i > 0; i--) {
        unsigned bit = i-1;
        R <<= 1;
        R |= (N >> bit) & 1;
        if (R >= D) {
            R = R - D;
            Q |= 1 << bit;
        }
    }*/
#endif
}

template<unsigned P>
uint16x8 div_p(uint16x8 num, uint16x8 den)
{
#if SIMDPP_USE_NULL
    return null::div_p<P>(num, den);
#else
    static_assert(P <= 16, "Precision too large");
    uint16x8 r, q, bit_mask;

    r = q = uint16x8::zero();
    bit_mask = uint16x8::make_const(1 << (P-1));

    for (unsigned i = P; i > 0; i--) {
        unsigned bit = i-1; // TODO precision
        uint16x8 n_bit;
        r = shift_l<1>(r);

        n_bit = bit_and(num, bit_mask);
        n_bit = shift_r(n_bit, bit);
        r = bit_or(r, n_bit);

        uint16x8 cmp, csub, cbit;
        cmp = cmp_lt(r, den);

        csub = bit_andnot(den, cmp);
        cbit = bit_andnot(bit_mask, cmp);
        r = sub(r, csub);
        q = bit_or(q, cbit);

        bit_mask = shift_r<1>(bit_mask);
    }
    return q;
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

