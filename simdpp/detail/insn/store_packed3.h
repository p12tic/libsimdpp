/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_PACKED3_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_STORE_PACKED3_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/align.h>
#include <simdpp/detail/insn/mem_pack.h>
#include <simdpp/core/store.h>
#include <simdpp/detail/null/memory.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// collect some boilerplate
template<class V>
void v128_store_pack3(char* p, V a, V b, V c);
template<class V>
void v256_store_pack3(char* p, V a, V b, V c);
template<class V>
void v512_store_pack3(char* p, V a, V b, V c);
template<class V>
void v_store_pack3(char* p, V a, V b, V c);

// -----------------------------------------------------------------------------

inline void i_store_packed3(char* p,
                            uint8x16 a, uint8x16 b, uint8x16 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint8x16x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u8(reinterpret_cast<uint8_t*>(p), t);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed3(char* p,
                            uint8x32 a, uint8x32 b, uint8x32 c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

template<unsigned N>
void i_store_packed3(char* p,
                     uint8<N> a, uint8<N> b, uint8<N> c)
{
    v_store_pack3(p, a, b, c);
}

// -----------------------------------------------------------------------------

inline void i_store_packed3(char* p,
                            uint16x8 a, uint16x8 b, uint16x8 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint16x8x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u16(reinterpret_cast<uint16_t*>(p), t);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed3(char* p,
                            uint16x16 a, uint16x16 b, uint16x16 c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

template<unsigned N>
void i_store_packed3(char* p,
                     uint16<N> a, uint16<N> b, uint16<N> c)
{
    v_store_pack3(p, a, b, c);
}

// -----------------------------------------------------------------------------

inline void i_store_packed3(char* p,
                            uint32x4 a, uint32x4 b, uint32x4 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint32x4x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_u32(reinterpret_cast<uint32_t*>(p), t);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed3(char* p,
                            uint32x8 a, uint32x8 b, uint32x8 c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_packed3(char* p,
                            uint32<16> a, uint32<16> b, uint32<16> c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

template<unsigned N>
void i_store_packed3(char* p,
                     uint32<N> a, uint32<N> b, uint32<N> c)
{
    v_store_pack3(p, a, b, c);
}

// -----------------------------------------------------------------------------

inline void i_store_packed3(char* p,
                            uint64x2 a, uint64x2 b, uint64x2 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    uint64_t* q = reinterpret_cast<uint64_t*>(p);
    uint64x1x2_t t1, t2, t3;
    t1.val[0] = vget_low_u64(a);  t1.val[1] = vget_low_u64(b);
    t2.val[0] = vget_low_u64(c);  t2.val[1] = vget_high_u64(a);
    t3.val[0] = vget_high_u64(b);  t3.val[1] = vget_high_u64(c);

    vst2_u64(q, t1);
    vst2_u64(q+2, t2);
    vst2_u64(q+4, t3);
#endif
}

#if SIMDPP_USE_AVX2
inline void i_store_packed3(char* p,
                            uint64x4 a, uint64x4 b, uint64x4 c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_packed3(char* p,
                            uint64<8> a, uint64<8> b, uint64<8> c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

template<unsigned N>
void i_store_packed3(char* p,
                     uint64<N> a, uint64<N> b, uint64<N> c)
{
    v_store_pack3(p, a, b, c);
}

// -----------------------------------------------------------------------------

inline void i_store_packed3(char* p, float32x4 a, float32x4 b, float32x4 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL
    detail::null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    v128_store_pack3(p, a, b, c);
#elif SIMDPP_USE_NEON
    float32x4x3_t t;
    t.val[0] = a;
    t.val[1] = b;
    t.val[2] = c;
    vst3q_f32(p, t);
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_packed3(char* p,
                            float32x8 a, float32x8 b, float32x8 c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_packed3(char* p,
                            float32<16> a, float32<16> b, float32<16> c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

template<unsigned N>
void i_store_packed3(char* p,
                     float32<N> a, float32<N> b, float32<N> c)
{
    v_store_pack3(p, a, b, c);
}

// -----------------------------------------------------------------------------

inline void i_store_packed3(char* p, float64x2 a, float64x2 b, float64x2 c)
{
    p = detail::assume_aligned(p, 16);
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC || SIMDPP_USE_NEON
    detail::null::store_packed3(p, a, b, c);
#elif SIMDPP_USE_SSE2
    v128_store_pack3(p, a, b, c);
#endif
}

#if SIMDPP_USE_AVX
inline void i_store_packed3(char* p,
                            float64x4 a, float64x4 b, float64x4 c)
{
    v256_store_pack3(p, a, b, c);
}
#endif

#if SIMDPP_USE_AVX512
inline void i_store_packed3(char* p,
                            float64<8> a, float64<8> b, float64<8> c)
{
    v512_store_pack3(p, a, b, c);
}
#endif

template<unsigned N>
void i_store_packed3(char* p,
                     float64<N> a, float64<N> b, float64<N> c)
{
    v_store_pack3(p, a, b, c);
}

// -----------------------------------------------------------------------------

template<class V>
void v128_store_pack3(char* p, V a, V b, V c)
{
    p = detail::assume_aligned(p, 16);
    mem_pack3(a, b, c);
    i_store(p, a);
    i_store(p + 16, b);
    i_store(p + 32, c);
}

template<class V>
void v256_store_pack3(char* p, V a, V b, V c)
{
    p = detail::assume_aligned(p, 32);
    mem_pack3(a, b, c);
    i_store(p, a);
    i_store(p + 32, b);
    i_store(p + 64, c);
}

template<class V>
void v512_store_pack3(char* p, V a, V b, V c)
{
    p = detail::assume_aligned(p, 64);
    mem_pack3(a, b, c);
    i_store(p, a);
    i_store(p + 64, b);
    i_store(p + 128, c);
}

template<class V>
void v_store_pack3(char* p, V a, V b, V c)
{
    unsigned veclen = sizeof(typename V::base_vector_type);

    p = detail::assume_aligned(p, veclen);
    for (unsigned i = 0; i < V::vec_length; ++i) {
        i_store_packed3(p, a[i], b[i], c[i]);
        p += veclen*3;
    }
}

} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

