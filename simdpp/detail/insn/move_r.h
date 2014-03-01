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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_R_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_MOVE_R_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/neon/detail/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


template<unsigned shift>
gint8x16 i_move16_r(gint8x16 a)
{
    static_assert(shift <= 16, "Selector out of range");

#if SIMDPP_USE_NULL
    gint8x16 r;
    //use int to disable warnings wrt. comparison result always being true/false
    for (int i = 0; i < (int)shift; i++) {
        r.el(i) = 0;
    }
    for (unsigned i = shift; i < 16; i++) {
        r.el(i) = a.el(i - shift);
    }
    return r;
#elif SIMDPP_USE_SSE2
    return _mm_slli_si128(a, shift);
#elif SIMDPP_USE_NEON
    int8x16 z = int8x16::zero();
    return neon::detail::align<16-shift>(z, a);
#elif SIMDPP_USE_ALTIVEC
    // return align<16-shift>(uint8x16::zero(), a);
    return vec_sld((__vector uint8_t)uint8x16::zero(), (__vector uint8_t)a, 16-shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned shift>
gint8x32 i_move16_r(gint8x32 a)
{
    static_assert(shift <= 16, "Selector out of range");
    return _mm256_slli_si256(a, shift);
}
#endif

template<unsigned shift, unsigned N>
gint8<N> i_move16_r(gint8<N> a)
{
    static_assert(shift <= 16, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(gint8<N>, i_move16_r<shift>, a);
}

template<unsigned shift, unsigned N>
gint16<N> i_move8_r(gint16<N> a)
{
    return gint16<N>(i_move16_r<shift*2>(gint8<N*2>(a)));
}

template<unsigned shift, unsigned N>
gint32<N> i_move4_r(gint32<N> a)
{
    return gint32<N>(i_move16_r<shift*4>(gint8<N*4>(a)));
}

template<unsigned shift, unsigned N>
gint64<N> i_move2_r(gint64<N> a)
{
    return gint64<N>(i_move16_r<shift*8>(gint8<N*8>(a)));
}

template<unsigned shift, unsigned N>
float32<N> i_move4_r(float32<N> a)
{
    return float32<N>(i_move4_r<shift>(gint32<N>(a)));
}

template<unsigned shift, unsigned N>
float64<N> i_move2_r(float64<N> a)
{
    return float64<N>(i_move2_r<shift>(gint64<N>(a)));
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

