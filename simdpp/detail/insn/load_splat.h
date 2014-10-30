/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_SPLAT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_LOAD_SPLAT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/set_splat.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class V>
struct is_expr_vec_load_splat { static const bool value = false; };
template<>
struct is_expr_vec_load_splat<expr_vec_load_splat> { static const bool value = true; };

namespace insn {

SIMDPP_INL void i_load_splat(uint8x16& v, const void* p0)
{
    const uint8_t* v0 = reinterpret_cast<const uint8_t*>(p0);
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint8x16>(*v0);
#elif SIMDPP_USE_SSE2
    i_set_splat(v, *v0);
#elif SIMDPP_USE_NEON
    v = vld1q_dup_u8(v0);
#elif SIMDPP_USE_ALTIVEC
    v = altivec::load1_u(v, v0);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_splat(uint8x32& v, const void* p0)
{
    i_set_splat(v, *reinterpret_cast<const uint8_t*>(p0));
}
#endif

template<unsigned N> SIMDPP_INL
void i_load_splat(uint8<N>& v, const void* p0)
{
    const uint8_t* v0 = reinterpret_cast<const uint8_t*>(p0);
    uint8v tv;
    i_load_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v.vec(i) = tv;
    }
}

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_splat(uint16x8& v, const void* p0)
{
    const uint16_t* v0 = reinterpret_cast<const uint16_t*>(p0);
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint16x8>(*v0);
#elif SIMDPP_USE_SSE2
    i_set_splat(v, *v0);
#elif SIMDPP_USE_NEON
    v = vld1q_dup_u16(v0);
#elif SIMDPP_USE_ALTIVEC
    v = altivec::load1_u(v, v0);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_splat(uint16x16& v, const void* p0)
{
    i_set_splat(v, *reinterpret_cast<const uint16_t*>(p0));
}
#endif

template<unsigned N> SIMDPP_INL
void i_load_splat(uint16<N>& v, const void* p0)
{
    const uint16_t* v0 = reinterpret_cast<const uint16_t*>(p0);
    uint16v tv;
    i_load_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v.vec(i) = tv;
    }
}

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_splat(uint32x4& v, const void* p0)
{
    const uint32_t* v0 = reinterpret_cast<const uint32_t*>(p0);
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint32x4>(*v0);
#elif SIMDPP_USE_SSE2
    v = _mm_cvtsi32_si128(*v0);
    v = permute4<0,0,0,0>(v);
#elif SIMDPP_USE_NEON
    v =  vld1q_dup_u32(v0);
#elif SIMDPP_USE_ALTIVEC
    v = altivec::load1_u(v, v0);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_splat(uint32x8& v, const void* p0)
{
    i_set_splat(v, *reinterpret_cast<const uint32_t*>(p0));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL void i_load_splat(uint32<16>& v, const void* p0)
{
    __m128 x = _mm_load_ss(reinterpret_cast<const float*>(p0));
    v = _mm512_broadcastd_epi32(_mm_castps_si128(x));
}
#endif

template<unsigned N> SIMDPP_INL
void i_load_splat(uint32<N>& v, const void* p0)
{
    const uint32_t* v0 = reinterpret_cast<const uint32_t*>(p0);
    uint32v tv;
    i_load_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v.vec(i) = tv;
    }
}

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_splat(uint64x2& v, const void* p0)
{
    const uint64_t* v0 = reinterpret_cast<const uint64_t*>(p0);
#if SIMDPP_USE_NULL
    v = detail::null::make_vec<uint64x2>(*v0);
#elif SIMDPP_USE_SSE2
    v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(v0));
    v = permute2<0,0>(v);
#elif SIMDPP_USE_NEON
    v = vld1q_dup_u64(v0);
#elif SIMDPP_USE_ALTIVEC
    SIMDPP_ALIGN(16) uint64_t rv[2];
    rv[0] = *v0;
    v = load(rv);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX2
SIMDPP_INL void i_load_splat(uint64x4& v, const void* p0)
{
    __m128i x = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(p0));
    v = _mm256_broadcastq_epi64(x);
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL void i_load_splat(uint64<8>& v, const void* p0)
{
    __m128i x = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(p0));
    v = _mm512_broadcastq_epi64(x);
}
#endif

template<unsigned N> SIMDPP_INL
void i_load_splat(uint64<N>& v, const void* p0)
{
    const uint64_t* v0 = reinterpret_cast<const uint64_t*>(p0);
    uint64v tv;
    i_load_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v.vec(i) = tv;
    }
}

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_splat(float32x4& v, const void* p0)
{
    const float* v0 = reinterpret_cast<const float*>(p0);
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_NO_FLT_SP
    v = detail::null::make_vec<float32x4>(*v0);
#elif SIMDPP_USE_AVX
    v = _mm_broadcast_ss(v0);
#elif SIMDPP_USE_SSE2
    v = _mm_load_ss(v0);
    v = permute4<0,0,0,0>(v);
#elif SIMDPP_USE_NEON
    v = vld1q_dup_f32(v0);
#elif SIMDPP_USE_ALTIVEC
    v = altivec::load1_u(v, v0);
    v = splat<0>(v);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_load_splat(float32x8& v, const void* p0)
{
    v = _mm256_broadcast_ss(reinterpret_cast<const float*>(p0));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL void i_load_splat(float32<16>& v, const void* p0)
{
    __m128 x = _mm_load_ss(reinterpret_cast<const float*>(p0));
    v = _mm512_broadcastss_ps(x);
}
#endif

template<unsigned N> SIMDPP_INL
void i_load_splat(float32<N>& v, const void* p0)
{
    const float* v0 = reinterpret_cast<const float*>(p0);
    float32v tv;
    i_load_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v.vec(i) = tv;
    }
}

// -----------------------------------------------------------------------------

SIMDPP_INL void i_load_splat(float64x2& v, const void* p0)
{
    const double* v0 = reinterpret_cast<const double*>(p0);

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON32 || SIMDPP_USE_ALTIVEC
    v = detail::null::make_vec<float64x2>(*v0);
#elif SIMDPP_USE_SSE3
    v = _mm_loaddup_pd(v0);
#elif SIMDPP_USE_SSE2
    v = _mm_load_sd(v0);
    v = permute2<0,0>(v);
#elif SIMDPP_USE_NEON64
    v = vld1q_dup_f64(v0);
#endif
}

#if SIMDPP_USE_AVX
SIMDPP_INL void i_load_splat(float64x4& v, const void* p0)
{
    v = _mm256_broadcast_sd(reinterpret_cast<const double*>(p0));
}
#endif

#if SIMDPP_USE_AVX512
SIMDPP_INL void i_load_splat(float64<8>& v, const void* p0)
{
    __m128d x = _mm_load_sd(reinterpret_cast<const double*>(p0));
    v = _mm512_broadcastsd_pd(x);
}
#endif

template<unsigned N> SIMDPP_INL
void i_load_splat(float64<N>& v, const void* p0)
{
    const double* v0 = reinterpret_cast<const double*>(p0);
    float64v tv;
    i_load_splat(tv, v0);
    for (unsigned i = 0; i < v.vec_length; ++i) {
        v.vec(i) = tv;
    }
}

// -----------------------------------------------------------------------------

template<class V>
struct i_load_splat_dispatch
{
    static V run(const void* v)
    {
        V r;
        i_load_splat(r, v);
        return r;
    }
};

template<>
struct i_load_splat_dispatch<expr_vec_load_splat>
{
    static expr_vec_load_splat run(const void* v)
    {
        expr_vec_load_splat r;
        r.a = v;
        return r;
    }
};

// -----------------------------------------------------------------------------
} // namespace insn

template<class V> SIMDPP_INL
void construct_eval(V& v, const expr_vec_load_splat& e)
{
    typename detail::remove_sign<V>::type r;
    insn::i_load_splat(r, e.a);
    v = r;
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

