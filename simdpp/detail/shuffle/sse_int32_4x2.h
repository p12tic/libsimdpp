/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_PERMUTE_SSE_INT32_4x2_H
#define LIBSIMDPP_SIMDPP_DETAIL_PERMUTE_SSE_INT32_4x2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types.h>
#include <simdpp/detail/shuffle/sse_float32_4x2.h>

#if SIMDPP_USE_SSE2

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace sse_shuffle4x2_int32 {

/*  The code below implements generalized permutations for 2 elements sets
    within uint32 vectors.
*/

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3>
struct impl_selector {

    // 0 1 2 3
    // 4 5 6 7
    static const bool is1_zip_lo1 = (s0==0 && s1==4 && s2==1 && s3==5);
    static const bool is2_zip_lo2 = (s0==4 && s1==0 && s2==5 && s3==1);
    static const bool is3_zip_hi1 = (s0==2 && s1==6 && s2==3 && s3==7);
    static const bool is4_zip_hi2 = (s0==6 && s1==2 && s2==7 && s3==3);
#if SIMDPP_USE_SSE4_1
    static const bool is5_blend = (s0==0 || s0==4) && (s1==1 || s1==5) &&
                                  (s2==2 || s2==6) && (s3==3 || s3==7);
#else
    static const bool is5_blend = false;
#endif

    static const int impl = is1_zip_lo1 ? 1 :
                            is2_zip_lo2 ? 2 :
                            is3_zip_hi1 ? 3 :
                            is4_zip_hi2 ? 4 :
                            is5_blend ? 5 : 6;
};

template<unsigned N> struct shuffle_impl {};

// zip_lo1
template<> struct shuffle_impl<1> {
    template<unsigned, unsigned, unsigned, unsigned> SIMDPP_INL
    static uint32<4> run(const uint32<4>& a, const uint32<4>& b)
    {
        return _mm_unpacklo_epi32(a, b);
    }
#if SIMDPP_USE_AVX2
    template<unsigned, unsigned, unsigned, unsigned> SIMDPP_INL
    static uint32<8> run(const uint32<8>& a, const uint32<8>& b)
    {
        return _mm256_unpacklo_epi32(a, b);
    }
#endif
#if SIMDPP_USE_AVX512
    template<unsigned, unsigned, unsigned, unsigned> SIMDPP_INL
    static uint32<16> run(const uint32<16>& a, const uint32<16>& b)
    {
        return _mm512_unpacklo_epi32(a, b);
    }
#endif
};

// zip_lo2
template<> struct shuffle_impl<2> {
    template<unsigned, unsigned, unsigned, unsigned, unsigned N> SIMDPP_INL
    static uint32<N> run(const uint32<N>& a, const uint32<N>& b)
    {
        return shuffle_impl<1>::run<0,0,0,0>(b, a);
    }
};

// zip_hi1
template<> struct shuffle_impl<3> {
    template<unsigned, unsigned, unsigned, unsigned> SIMDPP_INL
    static uint32<4> run(const uint32<4>& a, const uint32<4>& b)
    {
        return _mm_unpackhi_epi32(a, b);
    }
#if SIMDPP_USE_AVX2
    template<unsigned, unsigned, unsigned, unsigned> SIMDPP_INL
    static uint32<8> run(const uint32<8>& a, const uint32<8>& b)
    {
        return _mm256_unpackhi_epi32(a, b);
    }
#endif
#if SIMDPP_USE_AVX512
    template<unsigned, unsigned, unsigned, unsigned> SIMDPP_INL
    static uint32<16> run(const uint32<16>& a, const uint32<16>& b)
    {
        return _mm512_unpackhi_epi32(a, b);
    }
#endif
};

// zip_hi2
template<> struct shuffle_impl<4> {
    template<unsigned, unsigned, unsigned, unsigned, unsigned N> SIMDPP_INL
    static uint32<N> run(const uint32<N>& a, const uint32<N>& b)
    {
        return shuffle_impl<3>::run<0,0,0,0>(b, a);
    }
};

// is5_blend
#if SIMDPP_USE_SSE4_1
template<> struct shuffle_impl<5> {
    template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
    static uint32<4> run(const uint32<4>& a, const uint32<4>& b)
    {
        const unsigned mask = (s0<4 ? 0 : 0x3) | (s1<4 ? 0 : 0xc) | (s2<4 ? 0 : 0x30) | (s3<4 ? 0 : 0xc0);
        return _mm_blend_epi16(a, b, mask);
    }
#if SIMDPP_USE_AVX2
    template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
    static uint32<8> run(const uint32<8>& a, const uint32<8>& b)
    {
        const unsigned mask = (s0<4 ? 0 : 1) | (s1<4 ? 0 : 2) | (s2<4 ? 0 : 4) | (s3<4 ? 0 : 8);
        return _mm256_blend_epi32(a, b, mask | mask << 4);
    }
#endif
#if SIMDPP_USE_AVX512
    template<unsigned s0, unsigned s1, unsigned s2, unsigned s3> SIMDPP_INL
    static uint32<16> run(const uint32<16>& a, const uint32<16>& b)
    {
        const unsigned mask = (s0<4 ? 0 : 1) | (s1<4 ? 0 : 2) | (s2<4 ? 0 : 4) | (s3<4 ? 0 : 8);
        const unsigned mask2 = mask | mask << 4 | mask << 8 | mask << 12;
        return _mm512_mask_blend_epi32(mask2, a, b);
    }
#endif
};
#endif

// fallback to floats
template<> struct shuffle_impl<6> {
    template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N> SIMDPP_INL
    static uint32<N> run(const uint32<N>& a, const uint32<N>& b)
    {
        float32<N> fa, fb; fa = a; fb = b;
        return (uint32<N>) sse_shuffle4x2_float32::do_shuffle<s0,s1,s2,s3>(fa, fb);

    }
};


template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, unsigned N>
uint32<N> do_shuffle(const uint32<N>& a, const uint32<N>& b)
{
    return shuffle_impl<impl_selector<s0, s1, s2, s3>::impl>::template run<s0, s1, s2, s3>(a, b);
}

} // namespace sse_shuffle4x2_uint32
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
#endif
