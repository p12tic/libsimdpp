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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BROADCAST_W_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BROADCAST_W_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/splat_n.h>
#include <simdpp/detail/insn/shuffle128.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// forward decls for v_splat
template<unsigned s> gint8x16 i_splat(gint8x16 a);
template<unsigned s> gint16x8 i_splat(gint16x8 a);
template<unsigned s> gint32x4 i_splat(gint32x4 a);
template<unsigned s> gint64x2 i_splat(gint64x2 a);
template<unsigned s> float32x4 i_splat(float32x4 a);
template<unsigned s> float64x2 i_splat(float64x2 a);

// collect some duplicate stuff here
template<unsigned s, class V>
V v_splat(V a)
{
    using U = typename V::base_vector_type;
    U one = a[s / U::length];

    one = i_splat<s % U::length>(one);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        a[i] = one;
    }
    return a;
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint8x16 i_splat(gint8x16 a)
{
    return i_splat16<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint8x32 i_splat(gint8x32 a)
{
    static_assert(s < 32, "Access out of bounds");
    gint8x16 lo;
    lo = s < 16 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move_l<s % 16>(lo);
    return _mm256_broadcastb_epi8(lo);
}
#endif

template<unsigned s, unsigned N>
gint8<N> i_splat(gint8<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint16x8 i_splat(gint16x8 a)
{
    return i_splat8<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint16x16 i_splat(gint16x16 a)
{
    static_assert(s < 16, "Access out of bounds");
    gint16x8 lo;
    lo = s < 8 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move_l<s % 8>(lo);
    return _mm256_broadcastw_epi16(lo);
}
#endif

template<unsigned s, unsigned N>
gint16<N> i_splat(gint16<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint32x4 i_splat(gint32x4 a)
{
    return i_splat4<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint32x8 i_splat(gint32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
    a = permute4<s%4,s%4,s%4,s%4>(a);
    a = detail::shuffle128<s/4, s/4>(a, a);
    return a;
}
#endif

template<unsigned s, unsigned N>
gint32<N> i_splat(gint32<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
gint64x2 i_splat(gint64x2 a)
{
    return i_splat2<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint64x4 i_splat(gint64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N>
gint64<N> i_splat(gint64<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
float32x4 i_splat(float32x4 a)
{
    return i_splat4<s>(a);
}

#if SIMDPP_USE_AVX
template<unsigned s>
float32x8 i_splat(float32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
    a = detail::shuffle128<s/4,s/4>(a, a);
    return permute4<s%4,s%4,s%4,s%4>(a);
}
#endif

template<unsigned s, unsigned N>
float32<N> i_splat(float32<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
float64x2 i_splat(float64x2 a)
{
    return i_splat2<s>(a);
}

#if SIMDPP_USE_AVX
template<unsigned s>
float64x4 i_splat(float64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_AVX2
    return permute4<s,s,s,s>(a);
#else // SIMDPP_USE_AVX
    a = detail::shuffle128<s/2,s/2>(a, a);
    a = permute2<s%2,s%2>(a);
    return a;
#endif
}
#endif

template<unsigned s, unsigned N>
float64<N> i_splat(float64<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

