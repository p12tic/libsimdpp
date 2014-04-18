/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BROADCAST_W_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BROADCAST_W_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/splat_n.h>
#include <simdpp/sse/extract_half.h>
#include <simdpp/detail/insn/shuffle128.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// forward decls for v_splat
template<unsigned s> uint8x16 i_splat(uint8x16 a);
template<unsigned s> uint16x8 i_splat(uint16x8 a);
template<unsigned s> uint32x4 i_splat(uint32x4 a);
template<unsigned s> uint64x2 i_splat(uint64x2 a);
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
uint8x16 i_splat(uint8x16 a)
{
    return i_splat16<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
uint8x32 i_splat(uint8x32 a)
{
    static_assert(s < 32, "Access out of bounds");
    uint8x16 lo;
    lo = s < 16 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move16_l<s % 16>(lo);
    return _mm256_broadcastb_epi8(lo);
}
#endif

template<unsigned s, unsigned N>
uint8<N> i_splat(uint8<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
uint16x8 i_splat(uint16x8 a)
{
    return i_splat8<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
uint16x16 i_splat(uint16x16 a)
{
    static_assert(s < 16, "Access out of bounds");
    uint16x8 lo;
    lo = s < 8 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move8_l<s % 8>(lo);
    return _mm256_broadcastw_epi16(lo);
}
#endif

template<unsigned s, unsigned N>
uint16<N> i_splat(uint16<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
uint32x4 i_splat(uint32x4 a)
{
    return i_splat4<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
uint32x8 i_splat(uint32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
    a = permute4<s%4,s%4,s%4,s%4>(a);
    a = detail::shuffle1_128<s/4, s/4>(a, a);
    return a;
}
#endif

template<unsigned s, unsigned N>
uint32<N> i_splat(uint32<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return v_splat<s>(a);
}

// -----------------------------------------------------------------------------

template<unsigned s>
uint64x2 i_splat(uint64x2 a)
{
    return i_splat2<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
uint64x4 i_splat(uint64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N>
uint64<N> i_splat(uint64<N> a)
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

    a = shuffle1_128<s/4,s/4>(a, a);
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
    a = detail::shuffle1_128<s/2,s/2>(a, a);
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
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

