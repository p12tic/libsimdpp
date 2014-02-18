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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE4_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/detail/insn/shuffle_emul.h>
#include <simdpp/null/shuffle.h>
#include <simdpp/sse/shuffle.h>
#include <simdpp/neon/detail/shuffle_int16x8.h>
#include <simdpp/neon/detail/shuffle_int32x4.h>
#include <simdpp/neon/detail/shuffle_int64x2.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// forward declarations due to circular dependencies
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint64x4 permute_emul(gint64x4 a);
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float64x4 permute_emul(float64x4 a);

// ----

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint16x8 i_permute4(gint16x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_SSE2
    a = sse::permute_lo<s0,s1,s2,s3>(a);
    a = sse::permute_hi<s0,s1,s2,s3>(a);
    return a;
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int16x8::permute4<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint16x8 mask = make_shuffle_bytes16_mask<s0,s1,s2,s3>(mask);
    return permute_bytes16(a, mask);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint16x16 i_permute4(gint16x16 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    a = sse::permute_lo<s0,s1,s2,s3>(a);
    a = sse::permute_hi<s0,s1,s2,s3>(a);
    return a;
}
#endif

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
gint16<N> i_permute4(gint16<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(gint16<N>, (i_permute4<s0,s1,s2,s3>), a);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint32x4 i_permute4(gint32x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_SSE2
    return _mm_shuffle_epi32(a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_NEON
    return neon::detail::shuffle_int32x4::permute4<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint32x4 mask = make_shuffle_bytes16_mask<s0,s1,s2,s3>(mask);
    return permute_bytes16(a, mask);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint32x8 i_permute4(gint32x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shuffle_epi32(a, _MM_SHUFFLE(s3, s2, s1, s0));
}
#endif

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
gint32<N> i_permute4(gint32<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(gint32<N>, (i_permute4<s0,s1,s2,s3>), a);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float32x4 i_permute4(float32x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return null::permute<s0,s1,s2,s3>(a);
#elif SIMDPP_USE_SSE2
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_NEON
    return float32x4(neon::detail::shuffle_int32x4::permute4<s0,s1,s2,s3>(int32x4(a)));
#elif SIMDPP_USE_ALTIVEC
    // TODO optimize
    uint32x4 mask = make_shuffle_bytes16_mask<s0,s1,s2,s3>(mask);
    return permute_bytes16(a, mask);
#endif
}

#if SIMDPP_USE_AVX
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float32x8 i_permute4(float32x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shuffle_ps(a, a, _MM_SHUFFLE(s3, s2, s1, s0));
}
#endif

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
float32<N> i_permute4(float32<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, (i_permute4<s0,s1,s2,s3>), a);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
gint64x4 i_permute4(gint64x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    uint64x4 r;
    r[0].el(0) = a[s0/2].el(s0%2);
    r[0].el(1) = a[s1/2].el(s1%2);
    r[1].el(0) = a[s2/2].el(s2%2);
    r[1].el(1) = a[s3/2].el(s3%2);
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_permute4x64_epi64(a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return permute_emul<s0,s1,s2,s3>(a);
#endif
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
gint64<N> i_permute4(gint64<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(gint64<N>, (i_permute4<s0,s1,s2,s3>), a);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float64x4 i_permute4(float64x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    float64x4 r;
    r[0].el(0) = a[s0/2].el(s0%2);
    r[0].el(1) = a[s1/2].el(s1%2);
    r[1].el(0) = a[s2/2].el(s2%2);
    r[1].el(1) = a[s3/2].el(s3%2);
    return r;
#elif SIMDPP_USE_AVX2
    return _mm256_permute4x64_pd(a, _MM_SHUFFLE(s3, s2, s1, s0));
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return permute_emul<s0,s1,s2,s3>(a);
#endif
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
float64<N> i_permute4(float64<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, (i_permute4<s0,s1,s2,s3>), a);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

