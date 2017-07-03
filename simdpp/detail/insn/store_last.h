/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_LAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_LAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/load.h>
#include <simdpp/core/load_u.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/store.h>
#include <simdpp/detail/neon/memory_store.h>
#include <simdpp/detail/null/memory.h>
#include <simdpp/detail/extract128.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_last(char* p, const uint8x16& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    static const uint8_t mask_d[32] = {0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

    uint8x16 mask = load_u(mask_d + n);
    uint8x16 b = load(p);
    b = blend(a, b, mask);
    store(p, b);
#else
    detail::null::store_last(p, a, n);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_last(char* p, const uint8x32& a, unsigned n)
{
    p = detail::assume_aligned(p, 32);
    static const uint8_t mask_d[64] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    uint8x32 mask = load_u(mask_d + n);
    uint8x32 b = load(p);
    b = blend(a, b, mask);
    store(p, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_last(char* p, const uint16x8& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_last(p, (uint8x16)a, n*2);
#else
    detail::null::store_last(p, a, n);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_last(char* p, const uint16x16& a, unsigned n)
{
    i_store_last(p, uint8x32(a), n*2);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_last(char* p, const uint32x4& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_AVX2
    static const int32_t mask_d[8] = {0, 0, 0, 0, -1, -1, -1, -1};
    uint32x4 mask = load_u(mask_d + n);
    _mm_maskstore_epi32(reinterpret_cast<int*>(p), mask, a);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_last(p, (uint8x16)a, n*4);
#else
    detail::null::store_last(p, a, n);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_last(char* p, const uint32x8& a, unsigned n)
{
    static const int32_t mask_d[16] = {0, 0, 0, 0, 0, 0, 0, 0,
                                      -1, -1, -1, -1, -1, -1, -1, -1};
    uint32<8> mask = load_u(mask_d + n);
    _mm256_maskstore_epi32(reinterpret_cast<int*>(p), mask, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_last(char* p, const uint32<16>& a, unsigned n)
{
    _mm512_mask_store_epi32(p, 0xffff << (16-n), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_last(char* p, const uint64x2& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_SSE2
    if (n == 1) {
        uint64x2 b = move2_l<1>(a);
        _mm_store_sd(reinterpret_cast<double*>(p+8), _mm_castsi128_pd(b));
    }
#elif SIMDPP_USE_NEON
    if (n == 1) {
        neon::store_lane<1,1>(p+8, a);
    }
#else
    detail::null::store_last(p, a, n);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_last(char* p, const uint64x4& a, unsigned n)
{
    static const int64_t mask_d[8] = { 0, 0, 0, 0, -1, -1, -1, -1 };
    uint64<4> mask = load_u(mask_d + n);
#if __INTEL_COMPILER
    _mm256_maskstore_epi64(reinterpret_cast<__int64*>(p), mask, a);
#else
    _mm256_maskstore_epi64(reinterpret_cast<long long*>(p), mask, a);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_last(char* p, const uint64<8>& a, unsigned n)
{
    _mm512_mask_store_epi64(p, 0xff << (8-n), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_last(char* p, const float32x4& ca, unsigned n)
{
    float32<4> a = ca;
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_AVX && !SIMDPP_USE_AMD
    static const int32_t mask_d[8] = { 0, 0, 0, 0, -1, -1, -1, -1 };
    float32x4 mask = load_u(mask_d + n);
    _mm_maskstore_ps(reinterpret_cast<float*>(p), _mm_castps_si128(mask), a);
#elif SIMDPP_USE_SSE2
    static const int32_t mask_d[8] = { 0, 0, 0, 0, -1, -1, -1, -1 };
    float32x4 mask = load_u(mask_d + n);
    float32x4 old = load(p);
    a = blend(a, old, mask);
    store(p, a);
#elif SIMDPP_USE_NEON
    float* q = reinterpret_cast<float*>(p);
    // + VFP
    if (n < 1) return;
    neon::store_lane<3,1>(q+3, a);
    if (n < 2) return;
    neon::store_lane<2,1>(q+2, a);
    if (n < 3) return;
    neon::store_lane<1,1>(q+1, a);
#else
    i_store_last(p, int32x4(a), n);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_last(char* p, const float32x8& ca, unsigned n)
{
    float32<8> a = ca;
    static const int32_t mask_d[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                        -1, -1, -1, -1, -1, -1, -1, -1 };

    float32x8 mask = load_u(mask_d + n);
#if !SIMDPP_USE_AMD
    _mm256_maskstore_ps(reinterpret_cast<float*>(p), _mm256_castps_si256(mask), a);
#else
    float32x8 old = load(p);
    a = blend(a, old, mask);
    store(v, a);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_last(char* p, const float32<16>& a, unsigned n)
{
    _mm512_mask_store_ps(p, 0xffff << (16-n), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_last(char* p, const float64x2& a, unsigned n)
{
    double* q = reinterpret_cast<double*>(p);
    q = detail::assume_aligned(q, 16);
#if SIMDPP_USE_SSE2
    if (n == 1) {
        float64x2 b = zip2_hi(a, a);
        _mm_store_sd(q+1, b);
    }
#elif SIMDPP_USE_NEON64
    if (n == 1) {
        vst1_f64(q+1, vget_high_f64(a));
    }
#else
    detail::null::store_last(p, a, n);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_last(char* p, const float64x4& a, unsigned n)
{
    static const int64_t mask_d[8] = { 0, 0, 0, 0, -1, -1, -1, -1 };
    float64x4 mask = load_u(mask_d + n);

#if !SIMDPP_USE_AMD
    _mm256_maskstore_pd(reinterpret_cast<double*>(p), _mm256_castpd_si256(mask), a);
#else
    float64x4 old = load(p);
    a = blend(a, old, mask);
    store(v, a);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_last(char* p, const float64<8>& a, unsigned n)
{
    _mm512_mask_store_pd(p, 0xff << (8-n), a);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void i_store_last(char* p, const V& ca, unsigned n)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    typename detail::remove_sign<V>::type a = ca;
    p = detail::assume_aligned(p, veclen);
    unsigned el_to_skip = V::length - n;

    unsigned n_empty_vec = el_to_skip / V::base_vector_type::length;
    unsigned mid_vec_skip_count = n % V::base_vector_type::length;
    unsigned curr_vec = 0;

    p += n_empty_vec * veclen;
    curr_vec += n_empty_vec;
    if (mid_vec_skip_count > 0) {
        i_store_last(p, a.vec(curr_vec), mid_vec_skip_count);
        p += veclen;
        curr_vec++;
    }

    for (; curr_vec < V::vec_length; ++curr_vec) {
        i_store(p, a.vec(curr_vec));
        p += veclen;
    }
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
