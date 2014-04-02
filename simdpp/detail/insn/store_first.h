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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
    i_store_first(p, uint8x32(a), n*4);
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
    i_store_first(p, uint8x32(a), n*8);
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
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON_FLT_SP
    i_store_first(p, int32x4(a), n);
#elif SIMDPP_USE_SSE2
    float* q = reinterpret_cast<float*>(p);
    static const uint32_t mask_d[8] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                       0x00000000, 0x00000000, 0x00000000, 0x00000000};

    const float* mask_dp = reinterpret_cast<const float*>(mask_d);
    float32x4 mask = load_u(mask_dp + 4-n);
    float32x4 old = load(q);
    a = blend(a, old, mask);
    store(q, a);
#elif SIMDPP_USE_NEON
    // + VFP
    if (n < 1) return;
    neon::store_lane<0,1>(p, a);
    if (n < 2) return;
    neon::store_lane<1,1>(p, a);
    if (n < 3) return;
    neon::store_lane<2,1>(p, a);
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_first(char* p, float32x8 a, unsigned n)
{
    float* q = reinterpret_cast<float*>(p);
    static const uint32_t mask_d[16] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                        0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
                                        0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                        0x00000000, 0x00000000, 0x00000000, 0x00000000};

    const float* mask_dp = reinterpret_cast<const float*>(mask_d);
    float32x8 mask = load_u(mask_dp + 8-n);
    float32x8 old = load(q);
    a = blend(a, old, mask);
    store(q, a);
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
    double* q = reinterpret_cast<double*>(p);
    static const uint64_t mask_d[16] = {0xffffffffffffffff, 0xffffffffffffffff,
                                        0xffffffffffffffff, 0xffffffffffffffff,
                                        0x0000000000000000, 0x0000000000000000,
                                        0x0000000000000000, 0x0000000000000000};

    const double* mask_dp = reinterpret_cast<const double*>(mask_d);
    float64x4 mask = load_u(mask_dp + 4-n);
    float64x4 old = load(q);
    a = blend(a, old, mask);
    store(q, a);
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
        store(p, a[curr_vec]);
        p += veclen;
    }

    if (mid_vec_fill_count > 0) {
        i_store_first(p, a[curr_vec], mid_vec_fill_count);
    }
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

