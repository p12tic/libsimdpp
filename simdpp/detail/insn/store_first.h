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
#include <simdpp/neon/memory_store.h>
#include <simdpp/detail/null/memory.h>
#include <simdpp/sse/extract_half.h>
#include <simdpp/sse/memory_store.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// Multi-vector i_store_first is mostly boilerplate
template<class V>
void v_store_first(char* p, V a, unsigned n);


inline void i_store_first(char* p, uint8x16 a, unsigned n)
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
    uint8x16 old = load(p);
    a = blend(a, old, mask);
    store(p, a);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_first(char* p, uint8x32 a, unsigned n)
{
    static const uint8_t mask_d[64] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                       0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0};

    uint8x32 mask = load_u(mask_d + 32 - n);
    uint8x32 old = load(p);
    a = blend(a, old, mask);
    store(p, a);
}
#endif

template<unsigned N>
void i_store_first(char* p, uint8<N> a, unsigned n)
{
    v_store_first(p, a, n);
}

// 16 bits

inline void i_store_first(char* p, uint16x8 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_first(p, (uint8x16)a, n*2);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_first(char* p, uint16x16 a, unsigned n)
{
    i_store_first(p, uint8x32(a), n*2);
}
#endif

template<unsigned N>
void i_store_first(char* p, uint16<N> a, unsigned n)
{
    v_store_first(p, a, n);
}

// 32 bits

inline void i_store_first(char* p, uint32x4 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    i_store_first(p, (uint8x16)a, n*4);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_first(char* p, uint32x8 a, unsigned n)
{
    static const int32_t mask_d[16] = { -1, -1, -1, -1, -1, -1, -1, -1,
                                        0, 0, 0, 0, 0, 0, 0, 0 };
    uint32<8> mask = load_u(mask_d + 8-n);
    _mm256_maskstore_epi32(reinterpret_cast<int*>(p), mask, a);
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_first(char* p, uint32<16> a, unsigned n)
{
    _mm512_mask_store_epi32(p, 0xffff >> (16-n), a);
}
#endif

template<unsigned N>
void i_store_first(char* p, uint32<N> a, unsigned n)
{
    v_store_first(p, a, n);
}

// 64 bits

inline void i_store_first(char* p, uint64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_NEON
    if (n == 1) {
        neon::store_lane<0,1>(p, a);
    }
#elif SIMDPP_USE_ALTIVEC
    if (n == 1) {
        vec_ste((__vector uint32_t)a, 0, reinterpret_cast<uint32_t*>(p));
        vec_ste((__vector uint32_t)a, 4, reinterpret_cast<uint32_t*>(p));
    }
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_first(char* p, uint64x4 a, unsigned n)
{
    static const int64_t mask_d[8] = { -1, -1, -1, -1, 0, 0, 0, 0 };
    uint64<4> mask = load_u(mask_d + 4-n);
    _mm256_maskstore_epi64(reinterpret_cast<long long*>(p), mask, a);
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_first(char* p, uint64<8> a, unsigned n)
{
    _mm512_mask_store_epi64(p, 0xff >> (8-n), a);
}
#endif

template<unsigned N>
void i_store_first(char* p, uint64<N> a, unsigned n)
{
    v_store_first(p, a, n);
}

// 32 bits float

inline void i_store_first(char* p, float32x4 a, unsigned n)
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
    float32x4 old = load(p);
    a = blend(a, old, mask);
    store(p, a);
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
inline void i_store_first(char* p, float32x8 a, unsigned n)
{
    static const int32_t mask_d[16] = { -1, -1, -1, -1, -1, -1, -1, -1,
                                         0, 0, 0, 0, 0, 0, 0, 0 };

    float32x8 mask = load_u(mask_d + 8-n);
#if !SIMDPP_USE_AMD
    _mm256_maskstore_ps(reinterpret_cast<float*>(p), _mm256_castps_si256(mask), a);
#else
    float32x8 old = load(p);
    a = blend(a, old, mask);
    store(v, a);
#endif
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_first(char* p, float32<16> a, unsigned n)
{
    _mm512_mask_store_ps(p, 0xffff >> (16-n), a);
}
#endif

template<unsigned N>
void i_store_first(char* p, float32<N> a, unsigned n)
{
    v_store_first(p, a, n);
}

// 64 bit float

inline void i_store_first(char* p, float64x2 a, unsigned n)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::null::store_first(p, a, n);
#elif SIMDPP_USE_SSE2
    if (n == 1) {
        sse::store_lane<0,1>(p, a);
    }
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_first(char* p, float64x4 a, unsigned n)
{
    static const int64_t mask_d[16] = { -1, -1, -1, -1, 0, 0, 0, 0 };

    float64x4 mask = load_u(mask_d + 4-n);
#if !SIMDPP_USE_AMD
    _mm256_maskstore_pd(reinterpret_cast<double*>(p), _mm256_castpd_si256(mask), a);
#else
    float64x4 old = load(p);
    a = blend(a, old, mask);
    store(v, a);
#endif
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_first(char* p, float64<8> a, unsigned n)
{
    _mm512_mask_store_pd(p, 0xff >> (8-n), a);
}
#endif

template<unsigned N>
void i_store_first(char* p, float64<N> a, unsigned n)
{
    v_store_first(p, a, n);
}

// -----------------------------------------------------------------------------

template<class V>
void v_store_first(char* p, V a, unsigned n)
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
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

