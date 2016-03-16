/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_FIRST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_FIRST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/load.h>
#include <simdpp/core/load_u.h>
#include <simdpp/core/store.h>
#include <simdpp/detail/neon/memory_store.h>
#include <simdpp/detail/null/memory.h>
#include <simdpp/detail/extract128.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

SIMDPP_INL void i_store_first(char* p, const uint8x16& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    static const uint8_t mask_d[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0};

    uint8x16 mask = load_u(mask_d + 16 - n);
    uint8x16 b = load(p);
    b = blend(a, b, mask);
    store(p, b);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_first(char* p, const uint8x32& a, unsigned n)
{
    static const uint8_t mask_d[64] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0};

    uint8x32 mask = load_u(mask_d + 32 - n);
    uint8x32 b = load(p);
    b = blend(a, b, mask);
    store(p, b);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_first(char* p, const uint16x8& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_first(p, (uint8x16)a, n*2);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_first(char* p, const uint16x16& a, unsigned n)
{
    i_store_first(p, uint8x32(a), n*2);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_first(char* p, const uint32x4& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_first(p, (uint8x16)a, n*4);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_first(char* p, const uint32x8& a, unsigned n)
{
    static const int32_t mask_d[16] = { -1, -1, -1, -1, -1, -1, -1, -1,
                                        0, 0, 0, 0, 0, 0, 0, 0 };
    uint32<8> mask = load_u(mask_d + 8-n);
    _mm256_maskstore_epi32(reinterpret_cast<int*>(p), mask, a);
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_first(char* p, const uint32<16>& a, unsigned n)
{
    _mm512_mask_store_epi32(p, 0xffff >> (16-n), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_first(char* p, const uint64x2& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        _mm_store_sd(reinterpret_cast<double*>(p), _mm_castsi128_pd(a));
    }
#elif SIMDPP_USE_NEON
    if (n == 1) {
        neon::store_lane<0,1>(p, a);
    }
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_store_first(char* p, const uint64x4& a, unsigned n)
{
    static const int64_t mask_d[8] = { -1, -1, -1, -1, 0, 0, 0, 0 };
    uint64<4> mask = load_u(mask_d + 4-n);
#if __INTEL_COMPILER
    _mm256_maskstore_epi64(reinterpret_cast<__int64*>(p), mask, a);
#else
    _mm256_maskstore_epi64(reinterpret_cast<long long*>(p), mask, a);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_first(char* p, const uint64<8>& a, unsigned n)
{
    _mm512_mask_store_epi64(p, 0xff >> (8-n), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_first(char* p, const float32x4& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON_NO_FLT_SP
    i_store_first(p, int32x4(a), n);
#elif SIMDPP_USE_AVX && !SIMDPP_USE_AMD
    static const int32_t mask_d[8] = { -1, -1, -1, -1, 0, 0, 0, 0 };
    float32x4 mask = load_u(mask_d + 4-n);
    _mm_maskstore_ps(reinterpret_cast<float*>(p), _mm_castps_si128(mask), a);
#elif SIMDPP_USE_SSE2
    static const int32_t mask_d[8] = { -1, -1, -1, -1, 0, 0, 0, 0 };
    float32x4 mask = load_u(mask_d + 4-n);
    float32x4 b = load(p);
    b = blend(a, b, mask);
    store(p, b);
#elif SIMDPP_USE_NEON
    float* q = reinterpret_cast<float*>(p);
    // + VFP
    if (n < 1) return;
    neon::store_lane<0,1>(q, a);
    if (n < 2) return;
    neon::store_lane<1,1>(q+1, a);
    if (n < 3) return;
    neon::store_lane<2,1>(q+2, a);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_first(char* p, const float32x8& a, unsigned n)
{
    static const int32_t mask_d[16] = { -1, -1, -1, -1, -1, -1, -1, -1,
                                         0, 0, 0, 0, 0, 0, 0, 0 };

    float32x8 mask = load_u(mask_d + 8-n);
#if !SIMDPP_USE_AMD
    _mm256_maskstore_ps(reinterpret_cast<float*>(p), _mm256_castps_si256(mask), a);
#else
    float32x8 b = load(p);
    b = blend(a, b, mask);
    store(v, b);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_first(char* p, const float32<16>& a, unsigned n)
{
    _mm512_mask_store_ps(p, 0xffff >> (16-n), a);
}
#endif

// -----------------------------------------------------------------------------

SIMDPP_INL void i_store_first(char* p, const float64x2& a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        _mm_store_sd(reinterpret_cast<double*>(p), a);
    }
#elif SIMDPP_USE_NEON64
    if (n == 1) {
        vst1_f64(reinterpret_cast<double*>(p), vget_low_f64(a));
    }
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_store_first(char* p, const float64x4& a, unsigned n)
{
    static const int64_t mask_d[16] = { -1, -1, -1, -1, 0, 0, 0, 0 };
    float64x4 mask = load_u(mask_d + 4-n);
#if !SIMDPP_USE_AMD
    _mm256_maskstore_pd(reinterpret_cast<double*>(p), _mm256_castpd_si256(mask), a);
#else
    float64x4 b = load(p);
    b = blend(a, b, mask);
    store(v, b);
#endif
}
#endif

#if SIMDPP_USE_AVX512F
SIMDPP_INL void i_store_first(char* p, const float64<8>& a, unsigned n)
{
    _mm512_mask_store_pd(p, 0xff >> (8-n), a);
}
#endif

// -----------------------------------------------------------------------------

template<class V> SIMDPP_INL
void i_store_first(char* p, const V& a, unsigned n)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);

    unsigned n_full_vec = n / V::base_vector_type::length;
    unsigned mid_vec_fill_count = n % V::base_vector_type::length;
    unsigned curr_vec = 0;

    for (; curr_vec < n_full_vec; ++curr_vec) {
        store(p, a.vec(curr_vec));
        p += veclen;
    }

    if (mid_vec_fill_count > 0) {
        i_store_first(p, a.vec(curr_vec), mid_vec_fill_count);
    }
}

} // namespace insn
} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

