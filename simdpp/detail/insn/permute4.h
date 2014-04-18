/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE4_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_PERMUTE4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/detail/null/shuffle.h>
#include <simdpp/sse/shuffle.h>
#include <simdpp/neon/detail/shuffle_int16x8.h>
#include <simdpp/neon/detail/shuffle_int32x4.h>
#include <simdpp/neon/detail/shuffle_int64x2.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// forward declarations due to circular dependencies
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
uint64x4 permute_emul(uint64x4 a);
template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float64x4 permute_emul(float64x4 a);

// ----

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
uint16x8 i_permute4(uint16x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return detail::null::permute<s0,s1,s2,s3>(a);
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
uint16x16 i_permute4(uint16x16 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    a = sse::permute_lo<s0,s1,s2,s3>(a);
    a = sse::permute_hi<s0,s1,s2,s3>(a);
    return a;
}
#endif

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
uint16<N> i_permute4(uint16<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(uint16<N>, (i_permute4<s0,s1,s2,s3>), a);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
uint32x4 i_permute4(uint32x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return detail::null::permute<s0,s1,s2,s3>(a);
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
uint32x8 i_permute4(uint32x8 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    return _mm256_shuffle_epi32(a, _MM_SHUFFLE(s3, s2, s1, s0));
}
#endif

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
uint32<N> i_permute4(uint32<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(uint32<N>, (i_permute4<s0,s1,s2,s3>), a);
}

// -----------------------------------------------------------------------------

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
float32x4 i_permute4(float32x4 a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
#if SIMDPP_USE_NULL
    return detail::null::permute<s0,s1,s2,s3>(a);
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
uint64x4 i_permute4(uint64x4 a)
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
uint64<N> i_permute4(uint64<N> a)
{
    static_assert(s0 < 4 && s1 < 4 && s2 < 4 && s3 < 4, "Selector out of range");
    SIMDPP_VEC_ARRAY_IMPL1(uint64<N>, (i_permute4<s0,s1,s2,s3>), a);
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
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

