/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_MAKE_CONST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_MAKE_CONST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/set.h>
#include <simdpp/detail/traits.h>
#include <simdpp/detail/mem_block.h>

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {
namespace insn {

#if SIMDPP_USE_NEON_FLT_SP
template<class VE> SIMDPP_INL
void i_make_const(float32<4>& v, const expr_vec_make_const<VE,1>& e, unsigned)
{
    float rv = e.val(0);
    v = vld1q_dup_f32(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(float32<4>& v, const expr_vec_make_const<VE,2>& e, unsigned)
{
    union {
        float rv[2];
        float32x2_t r;
    } x;
    x.rv[0] = e.val(0);
    x.rv[1] = e.val(1);
    v = vcombine_f32(x.r, x.r);
}
#endif

template<class VE, unsigned N> SIMDPP_INL
void i_make_const(float32<4>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    v = detail::null::make_vec<float32<4>, float>(e.val(off+0), e.val(off+1),
                                                  e.val(off+2), e.val(off+3));
#elif SIMDPP_USE_SSE2
    v = _mm_set_ps(e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
#elif SIMDPP_USE_NEON
    detail::mem_block<float32<4>> x;
    x[0] = e.val(off+0);
    x[1] = e.val(off+1);
    x[2] = e.val(off+2);
    x[3] = e.val(off+3);
    v = x;
#elif SIMDPP_USE_ALTIVEC
    v = (__vector float){ float(e.val(off+0)), float(e.val(off+1)),
                          float(e.val(off+2)), float(e.val(off+3)) };
#endif
}

#if SIMDPP_USE_AVX
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(float32<8>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm256_set_ps(e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                      e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}

#endif

#if SIMDPP_USE_AVX512F
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(float32<16>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm512_set_ps(e.val(off+15), e.val(off+14), e.val(off+13), e.val(off+12),
                      e.val(off+11), e.val(off+10), e.val(off+9), e.val(off+8),
                      e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                      e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}
#endif

// -----------------------------------------------------------------------------

template<class VE, unsigned N> SIMDPP_INL
void i_make_const(float64<2>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    v = detail::null::make_vec<float64<2>, double>(e.val(off+0), e.val(off+1));
#elif SIMDPP_USE_NEON64
    detail::mem_block<float64<2>> x;
    x[0] = e.val(off+0);
    x[1] = e.val(off+1);
    v = x;
#elif SIMDPP_USE_SSE2
    v = _mm_set_pd(e.val(off+1), e.val(off+0));
#endif
}

#if SIMDPP_USE_AVX
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(float64<4>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm256_set_pd(e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}
#endif

#if SIMDPP_USE_AVX512F
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(float64<8>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm512_set_pd(e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                      e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE> SIMDPP_INL
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,1>& e, unsigned off)
{
    uint8_t rv = e.val(off+0);
    v = vld1q_dup_u8(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,2>& e, unsigned off)
{
    uint16_t rv = (e.val(off+0) & 0xff) | (e.val(off+1) & 0xff) << 8;
    v = (uint16<8>) vld1q_dup_u16(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,4>& e, unsigned off)
{
    uint32_t rv = (e.val(off+0) & 0xff) | (e.val(off+1) & 0xff) << 8 |
                  (e.val(off+2) & 0xff) << 16 | (e.val(off+3) & 0xff) << 24;
    v = (uint32<4>) vld1q_dup_u32(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,8>& e, unsigned off)
{
    union {
        uint8_t rvv[8];
        uint8x8_t r;
    } x;
    x.rvv[0] = e.val(off+0);  x.rvv[1] = e.val(off+1);  x.rvv[2] = e.val(off+2);  x.rvv[3] = e.val(off+3);
    x.rvv[4] = e.val(off+4);  x.rvv[5] = e.val(off+5);  x.rvv[6] = e.val(off+6);  x.rvv[7] = e.val(off+7);
    v = vcombine_u8(x.r, x.r);
}
#endif

template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint8<16>, uint8_t>(
            e.val(off+0), e.val(off+1), e.val(off+2), e.val(off+3),
            e.val(off+4), e.val(off+5), e.val(off+6), e.val(off+7),
            e.val(off+8), e.val(off+9), e.val(off+10), e.val(off+11),
            e.val(off+12), e.val(off+13), e.val(off+14), e.val(off+15));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi8(e.val(off+15), e.val(off+14), e.val(off+13), e.val(off+12),
                     e.val(off+11), e.val(off+10), e.val(off+9),  e.val(off+8),
                     e.val(off+7),  e.val(off+6),  e.val(off+5),  e.val(off+4),
                     e.val(off+3),  e.val(off+2),  e.val(off+1),  e.val(off+0));
#elif SIMDPP_USE_NEON
    detail::mem_block<uint8<16>> x;
    x[0] = e.val(off+0);   x[1] = e.val(off+1);   x[2] = e.val(off+2);   x[3] = e.val(off+3);
    x[4] = e.val(off+4);   x[5] = e.val(off+5);   x[6] = e.val(off+6);   x[7] = e.val(off+7);
    x[8] = e.val(off+8);   x[9] = e.val(off+9);   x[10] = e.val(off+10); x[11] = e.val(off+11);
    x[12] = e.val(off+12); x[13] = e.val(off+13); x[14] = e.val(off+14); x[15] = e.val(off+15);
    v = x;
#elif SIMDPP_USE_ALTIVEC
    v = (__vector uint8_t){
        uint8_t(e.val(off+0)),  uint8_t(e.val(off+1)),  uint8_t(e.val(off+2)),  uint8_t(e.val(off+3)),
        uint8_t(e.val(off+4)),  uint8_t(e.val(off+5)),  uint8_t(e.val(off+6)),  uint8_t(e.val(off+7)),
        uint8_t(e.val(off+8)),  uint8_t(e.val(off+9)),  uint8_t(e.val(off+10)), uint8_t(e.val(off+11)),
        uint8_t(e.val(off+12)), uint8_t(e.val(off+13)), uint8_t(e.val(off+14)), uint8_t(e.val(off+15))
    };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint8<32>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm256_set_epi8(e.val(off+31), e.val(off+30), e.val(off+29), e.val(off+28),
                        e.val(off+27), e.val(off+26), e.val(off+25), e.val(off+24),
                        e.val(off+23), e.val(off+22), e.val(off+21), e.val(off+20),
                        e.val(off+19), e.val(off+18), e.val(off+17), e.val(off+16),
                        e.val(off+15), e.val(off+14), e.val(off+13), e.val(off+12),
                        e.val(off+11), e.val(off+10), e.val(off+9),  e.val(off+8),
                        e.val(off+7),  e.val(off+6),  e.val(off+5),  e.val(off+4),
                        e.val(off+3),  e.val(off+2),  e.val(off+1),  e.val(off+0));
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE> SIMDPP_INL
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,1>& e, unsigned off)
{
    uint16_t rv = e.val(off+0);
    v = vld1q_dup_u16(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,2>& e, unsigned off)
{
    uint32_t rv = (e.val(off+0) & 0xffff) | (e.val(off+1) & 0xffff) << 16;
    v = (uint32<4>) vld1q_dup_u32(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,4>& e, unsigned off)
{
    union {
        uint16_t rvv[4];
        uint16x4_t r;
    } x;
    x.rvv[0] = e.val(off+0);  x.rvv[1] = e.val(off+1);
    x.rvv[2] = e.val(off+2);  x.rvv[3] = e.val(off+3);
    v = vcombine_u16(x.r, x.r);
}
#endif


template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint16<8>, uint16_t>(e.val(off+0), e.val(off+1), e.val(off+2), e.val(off+3),
                                            e.val(off+4), e.val(off+5), e.val(off+6), e.val(off+7));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi16(e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                      e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
#elif SIMDPP_USE_NEON
    detail::mem_block<uint16<8>> x;
    x[0] = e.val(off+0);  x[1] = e.val(off+1);  x[2] = e.val(off+2);  x[3] = e.val(off+3);
    x[4] = e.val(off+4);  x[5] = e.val(off+5);  x[6] = e.val(off+6);  x[7] = e.val(off+7);
    v = x;
#elif SIMDPP_USE_ALTIVEC
    v = (__vector uint16_t){
        uint16_t(e.val(off+0)), uint16_t(e.val(off+1)), uint16_t(e.val(off+2)), uint16_t(e.val(off+3)),
        uint16_t(e.val(off+4)), uint16_t(e.val(off+5)), uint16_t(e.val(off+6)), uint16_t(e.val(off+7))
    };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint16<16>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm256_set_epi16(e.val(off+15), e.val(off+14), e.val(off+13), e.val(off+12),
                         e.val(off+11), e.val(off+10), e.val(off+9),  e.val(off+8),
                         e.val(off+7),  e.val(off+6),  e.val(off+5),  e.val(off+4),
                         e.val(off+3),  e.val(off+2),  e.val(off+1),  e.val(off+0));
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE> SIMDPP_INL
void i_make_const(uint32<4>& v, const expr_vec_make_const<VE,1>& e, unsigned off)
{
    uint32_t rv = e.val(off+0);
    v = vld1q_dup_u32(&rv);
}

template<class VE> SIMDPP_INL
void i_make_const(uint32<4>& v, const expr_vec_make_const<VE,2>& e, unsigned off)
{
    union {
        uint32_t rvv[2];
        uint32x2_t r;
    } x;
    x.rvv[0] = e.val(off+0);
    x.rvv[1] = e.val(off+1);
    v = vcombine_u32(x.r, x.r);
}
#endif

template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint32<4>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint32<4>, uint32_t>(e.val(off+0), e.val(off+1), e.val(off+2), e.val(off+3));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi32(e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
#elif SIMDPP_USE_NEON
    detail::mem_block<uint32<4>> x;
    x[0] = e.val(off+0);  x[1] = e.val(off+1);
    x[2] = e.val(off+2);  x[3] = e.val(off+3);
    v = x;
#elif SIMDPP_USE_ALTIVEC
    v = (__vector uint32_t) { uint32_t(e.val(off+0)), uint32_t(e.val(off+1)),
                              uint32_t(e.val(off+2)), uint32_t(e.val(off+3)) };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint32<8>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm256_set_epi32(e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                         e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}
#endif

#if SIMDPP_USE_AVX512F
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint32<16>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm512_set_epi32(e.val(off+15), e.val(off+14), e.val(off+13), e.val(off+12),
                         e.val(off+11), e.val(off+10), e.val(off+9), e.val(off+8),
                         e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                         e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}
#endif

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE> SIMDPP_INL
void i_make_const(uint64<2>& v, const expr_vec_make_const<VE,1>& e, unsigned off)
{
    uint64x1_t r0 = vcreate_u64(uint64_t(e.val(off+0)));
    v = vcombine_u64(r0, r0);
}
#endif

template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint64<2>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    v = detail::null::make_vec<uint64<2>, uint64_t>(e.val(off+0), e.val(off+1));
#elif SIMDPP_USE_SSE2
#if SIMDPP_32_BITS && _MSC_VER
    // MSVC does not support _mm_set_epi64x in 32-bit mode
    uint64_t v1 = e.val(off+1);
    uint64_t v0 = e.val(off+0);
    v = _mm_set_epi32(v1 >> 32, v1 & 0xffffffff, v0 >> 32, v0 & 0xffffffff);
#else
    v = _mm_set_epi64x(e.val(off+1), e.val(off+0));
#endif
#elif SIMDPP_USE_NEON
    detail::mem_block<uint64<2>> x;
    x[0] = e.val(off+0);
    x[1] = e.val(off+1);
    v = x;
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint64<4>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
#if SIMDPP_32_BITS && _MSC_VER
    // MSVC does not support _mm256_set_epi64x in 32-bit mode
    uint64_t v3 = e.val(off+3);
    uint64_t v2 = e.val(off+2);
    uint64_t v1 = e.val(off+1);
    uint64_t v0 = e.val(off+0);
    v = _mm256_set_epi32(v3 >> 32, v3 & 0xffffffff, v2 >> 32, v2 & 0xffffffff,
                         v1 >> 32, v1 & 0xffffffff, v0 >> 32, v0 & 0xffffffff);
#else
    v = _mm256_set_epi64x(e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
#endif
}
#endif

#if SIMDPP_USE_AVX512F
template<class VE, unsigned N> SIMDPP_INL
void i_make_const(uint64<8>& v, const expr_vec_make_const<VE,N>& e, unsigned off)
{
    v = _mm512_set_epi64(e.val(off+7), e.val(off+6), e.val(off+5), e.val(off+4),
                         e.val(off+3), e.val(off+2), e.val(off+1), e.val(off+0));
}
#endif

// -----------------------------------------------------------------------------

template<class V, class VE, unsigned NE> SIMDPP_INL
void i_make_const(V& v, const expr_vec_make_const<VE,NE>& e, unsigned off)
{
    for (unsigned i = 0; i < v.vec_length; ++i) {
        i_make_const(v.vec(i), e, off + v.base_length * i);
    }
}

// -----------------------------------------------------------------------------

template<class V, class VE, unsigned N> SIMDPP_INL
V i_make_const_any(const expr_vec_make_const<VE,N>& e)
{
    typename detail::remove_sign<V>::type r;
    i_make_const(r, e, 0);
    return V(r);
}

// -----------------------------------------------------------------------------
} // namespace insn

template<class V, class VE, unsigned N> SIMDPP_INL
void construct_eval(V& v, const expr_vec_make_const<VE, N>& e)
{
    v = insn::i_make_const_any<V>(e);
}

template<class V> SIMDPP_INL
void construct_eval(V& v, const expr_vec_make_ones& e)
{
    (void) e;
    expr_vec_make_const<uint64_t,1> e2;
    e2.a[0] = -1;
    typename V::uint_vector_type u;
    insn::i_make_const(u, e2, 0);
    v = u;
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#if _MSC_VER
#pragma warning(pop)
#endif

#endif

