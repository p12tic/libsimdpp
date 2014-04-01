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
#include <simdpp/null/set.h>
#include <simdpp/detail/traits.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V>
struct is_expr_vec_make_const { static const bool value = false; };
template<class VE, unsigned N>
struct is_expr_vec_make_const<expr_vec_make_const<VE,N>> { static const bool value = true; };

namespace insn {

#if SIMDPP_USE_NEON
template<class VE>
void i_make_const(float32<4>& v, const expr_vec_make_const<VE,1>& e)
{
    float rv = e.val(0);
    v = vld1q_dup_f32(&rv);
}

template<class VE>
void i_make_const(float32<4>& v, const expr_vec_make_const<VE,2>& e)
{
    union {
        uint32<4> align;
        float rv[2];
    };
    rv[0] = e.val(0);
    rv[1] = e.val(1);
    float32x2_t r0 = vld1_f32(rv);
    v = vcombine_f32(r0, r0);
}
#endif

template<class VE, unsigned N>
void i_make_const(float32<4>& v, const expr_vec_make_const<VE,N>& e)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<float32<4>, float>(e.val(0), e.val(1),
                                          e.val(2), e.val(3));
#elif SIMDPP_USE_SSE2
    v = _mm_set_ps(e.val(3), e.val(2), e.val(1), e.val(0));
#elif SIMDPP_USE_NEON
    union {
        uint32<4> align;
        float rv[4];
    };
    rv[0] = e.val(0);
    rv[1] = e.val(1);
    rv[2] = e.val(2);
    rv[3] = e.val(3);
    v = vld1q_f32(rv);
#elif SIMDPP_USE_ALTIVEC
    v = (__vector float){ float(e.val(0)), float(e.val(1)),
                          float(e.val(2)), float(e.val(3)) };
#endif
}

#if SIMDPP_USE_AVX
template<class VE, unsigned N>
void i_make_const(float32<8>& v, const expr_vec_make_const<VE,N>& e)
{
    v = _mm256_set_ps(e.val(7), e.val(6), e.val(5), e.val(4),
                      e.val(3), e.val(2), e.val(1), e.val(0));
}

#endif


template<unsigned N, class VE, unsigned NE>
void i_make_const(float32<N>& v, const expr_vec_make_const<VE,NE>& e)
{
    float32v tv;
    i_make_const(tv, e);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

template<class VE, unsigned N>
void i_make_const(float64<2>& v, const expr_vec_make_const<VE,N>& e)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    v = null::make_vec<float64<2>, double>(e.val(0), e.val(1));
#elif SIMDPP_USE_SSE2
    v = _mm_set_pd(e.val(1), e.val(0));
#endif
}

#if SIMDPP_USE_AVX
template<class VE, unsigned N>
void i_make_const(float64<4>& v, const expr_vec_make_const<VE,N>& e)
{
    v = _mm256_set_pd(e.val(3), e.val(2), e.val(1), e.val(0));
}
#endif

template<unsigned N, class VE, unsigned NE>
void i_make_const(float64<N>& v, const expr_vec_make_const<VE,NE>& e)
{
    float64v tv;
    i_make_const(tv, e);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE>
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,1>& e)
{
    uint8_t rv = e.val(0);
    v = vld1q_dup_u8(&rv);
}

template<class VE>
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,2>& e)
{
    union {
        uint16_t rv[1];
        uint8_t rvv[2];
    };
    rvv[0] = e.val(0);
    rvv[1] = e.val(1);
    v = vld1q_dup_u16(rv);
}

template<class VE>
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,4>& e)
{
    union {
        uint32_t rv[1];
        uint8_t rvv[4];
    };
    rvv[0] = e.val(0);  rvv[1] = e.val(1);  rvv[2] = e.val(2);  rvv[3] = e.val(3);
    v = vld1q_dup_u32(rv);
}

template<class VE>
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,8>& e)
{
    union {
        uint8_t rvv[8];
        uint64_t align;
    };
    rvv[0] = e.val(0);  rvv[1] = e.val(1);  rvv[2] = e.val(2);  rvv[3] = e.val(3);
    rvv[4] = e.val(4);  rvv[5] = e.val(5);  rvv[6] = e.val(6);  rvv[7] = e.val(7);
    uint8x8_t r0 = vld1_u8(rvv);
    v = vcombine_u8(r0, r0);
}
#endif

template<class VE, unsigned N>
void i_make_const(uint8<16>& v, const expr_vec_make_const<VE,N>& e)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint8<16>, uint8_t>(e.val(0), e.val(1), e.val(2), e.val(3),
                                           e.val(4), e.val(5), e.val(6), e.val(7),
                                           e.val(8), e.val(9), e.val(10), e.val(11),
                                           e.val(12), e.val(13), e.val(14), e.val(15));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi8(e.val(15), e.val(14), e.val(13), e.val(12),
                     e.val(11), e.val(10), e.val(9),  e.val(8),
                     e.val(7),  e.val(6),  e.val(5),  e.val(4),
                     e.val(3),  e.val(2),  e.val(1),  e.val(0));
#elif SIMDPP_USE_NEON
    union {
        uint8x16 align;
        uint8_t rvv[16];
    };
    rvv[0] = e.val(0);   rvv[1] = e.val(1);   rvv[2] = e.val(2);   rvv[3] = e.val(3);
    rvv[4] = e.val(4);   rvv[5] = e.val(5);   rvv[6] = e.val(6);   rvv[7] = e.val(7);
    rvv[8] = e.val(8);   rvv[9] = e.val(9);   rvv[10] = e.val(10); rvv[11] = e.val(11);
    rvv[12] = e.val(12); rvv[13] = e.val(13); rvv[14] = e.val(14); rvv[15] = e.val(15);
    v = vld1q_u8(rv);
#elif SIMDPP_USE_ALTIVEC
    v = (__vector uint8_t){
        uint8_t(e.val(0)),  uint8_t(e.val(1)),  uint8_t(e.val(2)),  uint8_t(e.val(3)),
        uint8_t(e.val(4)),  uint8_t(e.val(5)),  uint8_t(e.val(6)),  uint8_t(e.val(7)),
        uint8_t(e.val(8)),  uint8_t(e.val(9)),  uint8_t(e.val(10)), uint8_t(e.val(11)),
        uint8_t(e.val(12)), uint8_t(e.val(13)), uint8_t(e.val(14)), uint8_t(e.val(15))
    };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N>
void i_make_const(uint8<32>& v, const expr_vec_make_const<VE,N>& e)
{
    v = _mm256_set_epi8(e.val(31), e.val(30), e.val(29), e.val(28),
                        e.val(27), e.val(26), e.val(25), e.val(24),
                        e.val(23), e.val(22), e.val(21), e.val(20),
                        e.val(19), e.val(18), e.val(17), e.val(16),
                        e.val(15), e.val(14), e.val(13), e.val(12),
                        e.val(11), e.val(10), e.val(9),  e.val(8),
                        e.val(7),  e.val(6),  e.val(5),  e.val(4),
                        e.val(3),  e.val(2),  e.val(1),  e.val(0));
}
#endif

template<unsigned N, class VE, unsigned NE>
void i_make_const(uint8<N>& v, const expr_vec_make_const<VE,NE>& e)
{
    uint8v tv;
    i_make_const(tv, e);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE>
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,1>& e)
{
    uint16_t rv = e.val(0);
    v = vld1q_dup_u16(&rv);
}

template<class VE>
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,2>& e)
{
    union {
        uint32_t rv[1];
        uint16_t rvv[2];
    };
    rvv[0] = e.val(0);
    rvv[1] = e.val(1);
    v = vld1q_dup_u32(rv);
}

template<class VE>
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,4>& e)
{
    union {
        uint64_t align;
        uint16_t rvv[4];
    };
    rvv[0] = e.val(0);  rvv[1] = e.val(1);
    rvv[2] = e.val(2);  rvv[3] = e.val(3);
    uint16x4_t r0 = vld1_u16(rvv);
    v = vcombine_u16(r0, r0);
}
#endif


template<class VE, unsigned N>
void i_make_const(uint16<8>& v, const expr_vec_make_const<VE,N>& e)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint16<8>, uint16_t>(e.val(0), e.val(1), e.val(2), e.val(3),
                                            e.val(4), e.val(5), e.val(6), e.val(7));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi16(e.val(7), e.val(6), e.val(5), e.val(4),
                      e.val(3), e.val(2), e.val(1), e.val(0));
#elif SIMDPP_USE_NEON
    union {
        uint16x8 align;
        uint16_t rvv[8];
    };
    rvv[0] = e.val(0);  rvv[1] = e.val(1);  rvv[2] = e.val(2);  rvv[3] = e.val(3);
    rvv[4] = e.val(4);  rvv[5] = e.val(5);  rvv[6] = e.val(6);  rvv[7] = e.val(7);
    v = vld1q_u16(rv);
#elif SIMDPP_USE_ALTIVEC
    v = (__vector uint16_t){
        uint16_t(e.val(0)), uint16_t(e.val(1)), uint16_t(e.val(2)), uint16_t(e.val(3)),
        uint16_t(e.val(4)), uint16_t(e.val(5)), uint16_t(e.val(6)), uint16_t(e.val(7))
    };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N>
void i_make_const(uint16<16>& v, const expr_vec_make_const<VE,N>& e)
{
    v = _mm256_set_epi16(e.val(15), e.val(14), e.val(13), e.val(12),
                         e.val(11), e.val(10), e.val(9),  e.val(8),
                         e.val(7),  e.val(6),  e.val(5),  e.val(4),
                         e.val(3),  e.val(2),  e.val(1),  e.val(0));
}
#endif


template<unsigned N, class VE, unsigned NE>
void i_make_const(uint16<N>& v, const expr_vec_make_const<VE,NE>& e)
{
    uint16v tv;
    i_make_const(tv, e);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

#if SIMDPP_USE_NEON
template<class VE>
void i_make_const(uint32<4>& v, const expr_vec_make_const<VE,1>& e)
{
    uint32_t rv = e.val(0);
    v = vld1q_dup_u32(&rv);
}

template<class VE>
void i_make_const(uint32<4>& v, const expr_vec_make_const<VE,2>& e)
{
    union {
        uint64_t align;
        uint32_t rvv[2];
    };
    rvv[0] = e.val(0);
    rvv[1] = e.val(1);
    uint32x2_t r0 = vld1_u32(rvv);
    v = vcombine_u32(r0, r0);
}
#endif

template<class VE, unsigned N>
void i_make_const(uint32<4>& v, const expr_vec_make_const<VE,N>& e)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint32<4>, uint32_t>(e.val(0), e.val(1), e.val(2), e.val(3));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi32(e.val(3), e.val(2), e.val(1), e.val(0));
#elif SIMDPP_USE_NEON
    union {
        uint32<4> align;
        uint32_t rvv[4];
    };
    rvv[0] = e.val(0);  rvv[1] = e.val(1);
    rvv[2] = e.val(2);  rvv[3] = e.val(3);
    v = vld1q_u32(rv);
#elif SIMDPP_USE_ALTIVEC
    v = (__vector uint32_t) { uint32_t(e.val(0)), uint32_t(e.val(1)),
                              uint32_t(e.val(2)), uint32_t(e.val(3)) };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N>
void i_make_const(uint32<8>& v, const expr_vec_make_const<VE,N>& e)
{
    v = _mm256_set_epi32(e.val(7), e.val(6), e.val(5), e.val(4),
                         e.val(3), e.val(2), e.val(1), e.val(0));
}
#endif

template<unsigned N, class VE, unsigned NE>
void i_make_const(uint32<N>& v, const expr_vec_make_const<VE,NE>& e)
{
    uint32v tv;
    i_make_const(tv, e);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------


#if SIMDPP_USE_NEON
template<class VE>
void i_make_const(uint64<2>& v, const expr_vec_make_const<VE,1>& e)
{
    uint64x1_t r0 = vcreate_u64(uint64_t(e.val(0)));
    return vcombine_u64(r0, r0);
}
#endif

template<class VE, unsigned N>
void i_make_const(uint64<2>& v, const expr_vec_make_const<VE,N>& e)
{
#if SIMDPP_USE_NULL
    v = null::make_vec<uint64<2>, uint64_t>(e.val(0), e.val(1));
#elif SIMDPP_USE_SSE2
    v = _mm_set_epi64x(e.val(1), e.val(0));
#elif SIMDPP_USE_NEON
    union {
        uint64<2> align;
        uint64_t rvv[2];
    };
    rvv[0] = e.val(0);
    rvv[1] = e.val(1);
    v = vld1q_u64(rv);
#elif SIMDPP_USE_ALTIVEC
    // big endian
    uint32_t v0 = uint64_t(e.val(0)) >> 32;
    uint32_t v1 = uint64_t(e.val(0));
    uint32_t v2 = uint64_t(e.val(1)) >> 32;
    uint32_t v3 = uint64_t(e.val(1));

    v = (__vector uint32_t) { v0, v1, v2, v3 };
#endif
}

#if SIMDPP_USE_AVX2
template<class VE, unsigned N>
void i_make_const(uint64<4>& v, const expr_vec_make_const<VE,N>& e)
{
    v = _mm256_set_epi64x(e.val(3), e.val(2), e.val(1), e.val(0));
}
#endif

template<unsigned N, class VE, unsigned NE>
void i_make_const(uint64<N>& v, const expr_vec_make_const<VE,NE>& e)
{
    uint64v tv;
    i_make_const(tv, e);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v[i] = tv;
    }
}

// -----------------------------------------------------------------------------

template<class V>
struct i_make_const_dispatch
{
    template<class VE, unsigned N>
    static V run(const expr_vec_make_const<VE,N>& e)
    {
        typename detail::remove_sign<V>::type r;
        i_make_const(r, e);
        return V(r);
    }
};

template<class VE, unsigned N>
struct i_make_const_dispatch<expr_vec_make_const<VE,N>>
{
    static expr_vec_make_const<VE,N> run(const expr_vec_make_const<VE,N>& e)
    {
        return e;
    }
};

// -----------------------------------------------------------------------------
} // namespace insn

template<class V, class VE, unsigned N>
void construct_eval(V& v, const expr_vec_make_const<VE, N>& e)
{
    typename detail::remove_sign<V>::type r;
    insn::i_make_const(r, e);
    v = r;
}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

