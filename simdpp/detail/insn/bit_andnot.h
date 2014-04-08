/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_ANDNOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_ANDNOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/null/foreach.h>
#include <simdpp/detail/null/bitwise.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// see doc/src/expressions.md for the list of types we must cover

// -----------------------------------------------------------------------------
// uint8, uint8
inline uint8<16> i_bit_andnot(uint8<16> a, uint8<16> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_si128(b, a);
#elif SIMDPP_USE_NEON
    return vbicq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_andc((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8<32> i_bit_andnot(uint8<32> a, uint8<32> b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

template<unsigned N>
uint8<N> i_bit_andnot(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// uint8, mask_int8
inline uint8<16> i_bit_andnot(uint8<16> a, mask_int8<16> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint8<16>(b));
#endif
}

#if SIMDPP_USE_AVX2
inline uint8<32> i_bit_andnot(uint8<32> a, mask_int8<32> b)
{
    return i_bit_andnot(a, uint8<32>(b));
}
#endif

template<unsigned N>
uint8<N> i_bit_andnot(uint8<N> a, mask_int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// mask_int8, mask_int8
inline mask_int8<16> i_bit_andnot(mask_int8<16> a, mask_int8<16> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_int8<16>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8<32> i_bit_andnot(mask_int8<32> a, mask_int8<32> b)
{
    return mask_int8<32>(i_bit_andnot(uint8<32>(a), uint8<32>(b)));
}
#endif

template<unsigned N>
mask_int8<N> i_bit_andnot(mask_int8<N> a, mask_int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int8<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// uint16, uint16
inline uint16<8> i_bit_andnot(uint16<8> a, uint16<8> b)
{
    return uint16<8>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
}

#if SIMDPP_USE_AVX2
inline uint16<16> i_bit_andnot(uint16<16> a, uint16<16> b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

template<unsigned N>
uint16<N> i_bit_andnot(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// uint16, mask_int16
inline uint16<8> i_bit_andnot(uint16<8> a, mask_int16<8> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint16<8>(b));
#endif
}

#if SIMDPP_USE_AVX2
inline uint16<16> i_bit_andnot(uint16<16> a, mask_int16<16> b)
{
    return i_bit_andnot(a, uint16<16>(b));
}
#endif

template<unsigned N>
uint16<N> i_bit_andnot(uint16<N> a, mask_int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// mask_int16, mask_int16
inline mask_int16<8> i_bit_andnot(mask_int16<8> a, mask_int16<8> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_int16<8>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int16<16> i_bit_andnot(mask_int16<16> a, mask_int16<16> b)
{
    return mask_int16<16>(i_bit_andnot(uint16<16>(a), uint16<16>(b)));
}
#endif

template<unsigned N>
mask_int16<N> i_bit_andnot(mask_int16<N> a, mask_int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int16<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// uint32, uint32
inline uint32<4> i_bit_andnot(uint32<4> a, uint32<4> b)
{
    return uint32<4>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
}

#if SIMDPP_USE_AVX2
inline uint32<8> i_bit_andnot(uint32<8> a, uint32<8> b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

template<unsigned N>
uint32<N> i_bit_andnot(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// uint32, mask_int32
inline uint32<4> i_bit_andnot(uint32<4> a, mask_int32<4> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint32<4>(b));
#endif
}

#if SIMDPP_USE_AVX2
inline uint32<8> i_bit_andnot(uint32<8> a, mask_int32<8> b)
{
    return i_bit_andnot(a, uint32<8>(b));
}
#endif

template<unsigned N>
uint32<N> i_bit_andnot(uint32<N> a, mask_int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// mask_int32, mask_int32
inline mask_int32<4> i_bit_andnot(mask_int32<4> a, mask_int32<4> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_int32<4>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int32<8> i_bit_andnot(mask_int32<8> a, mask_int32<8> b)
{
    return mask_int32<8>(i_bit_andnot(uint32<8>(a), uint32<8>(b)));
}
#endif

template<unsigned N>
mask_int32<N> i_bit_andnot(mask_int32<N> a, mask_int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int32<N>, i_bit_andnot, a, b)
}


// -----------------------------------------------------------------------------
// uint64, uint64
inline uint64<2> i_bit_andnot(uint64<2> a, uint64<2> b)
{
    return uint64<2>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
}

#if SIMDPP_USE_AVX2
inline uint64<4> i_bit_andnot(uint64<4> a, uint64<4> b)
{
    return _mm256_andnot_si256(b, a);
}
#endif

template<unsigned N>
uint64<N> i_bit_andnot(uint64<N> a, uint64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// uint64, mask_int64
inline uint64<2> i_bit_andnot(uint64<2> a, mask_int64<2> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, uint64<2>(b));
#endif
}

#if SIMDPP_USE_AVX2
inline uint64<4> i_bit_andnot(uint64<4> a, mask_int64<4> b)
{
    return i_bit_andnot(a, uint64<4>(b));
}
#endif

template<unsigned N>
uint64<N> i_bit_andnot(uint64<N> a, mask_int64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint64<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// mask_int64, mask_int64
inline mask_int64<2> i_bit_andnot(mask_int64<2> a, mask_int64<2> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_int64<2>(i_bit_andnot(uint8<16>(a), uint8<16>(b)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int64<4> i_bit_andnot(mask_int64<4> a, mask_int64<4> b)
{
    return mask_int64<4>(i_bit_andnot(uint64<4>(a), uint64<4>(b)));
}
#endif

template<unsigned N>
mask_int64<N> i_bit_andnot(mask_int64<N> a, mask_int64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_int64<N>, i_bit_andnot, a, b)
}


// -----------------------------------------------------------------------------
// float32, float32
inline float32<4> i_bit_andnot(float32<4> a, float32<4> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_ps(b, a);
#elif SIMDPP_USE_NEON
    return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(a),
                                           vreinterpretq_u32_f32(b)));
#elif SIMDPP_USE_ALTIVEC
    return vec_andc((__vector float)a, (__vector float)b);
#endif
}

#if SIMDPP_USE_AVX
inline float32<8> i_bit_andnot(float32<8> a, float32<8> b)
{
    return _mm256_andnot_ps(b, a);
}
#endif

template<unsigned N>
float32<N> i_bit_andnot(float32<N> a, float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// float32, mask_float32
inline float32<4> i_bit_andnot(float32<4> a, mask_float32<4> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, float32<4>(b));
#endif
}

#if SIMDPP_USE_AVX
inline float32<8> i_bit_andnot(float32<8> a, mask_float32<8> b)
{
    return i_bit_andnot(a, float32<8>(b));
}
#endif

template<unsigned N>
float32<N> i_bit_andnot(float32<N> a, mask_float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float32<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// mask_float32, mask_float32
inline mask_float32<4> i_bit_andnot(mask_float32<4> a, mask_float32<4> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_float32<4>(i_bit_andnot(float32<4>(a), float32<4>(b)));
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32<8> i_bit_andnot(mask_float32<8> a, mask_float32<8> b)
{
    return mask_float32<8>(i_bit_andnot(float32<8>(a), float32<8>(b)));
}
#endif

template<unsigned N>
mask_float32<N> i_bit_andnot(mask_float32<N> a, mask_float32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float32<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// float64, float64
inline float64<2> i_bit_andnot(float64<2> a, float64<2> b)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::bit_andnot(a, b);
#elif SIMDPP_USE_SSE2
    return _mm_andnot_pd(b, a);
#endif
}

#if SIMDPP_USE_AVX
inline float64<4> i_bit_andnot(float64<4> a, float64<4> b)
{
    return _mm256_andnot_pd(b, a);
}
#endif

template<unsigned N>
float64<N> i_bit_andnot(float64<N> a, float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// float64, mask_float64
inline float64<2> i_bit_andnot(float64<2> a, mask_float64<2> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_vm(a, b);
#else
    return i_bit_andnot(a, float64<2>(b));
#endif
}

#if SIMDPP_USE_AVX
inline float64<4> i_bit_andnot(float64<4> a, mask_float64<4> b)
{
    return i_bit_andnot(a, float64<4>(b));
}
#endif

template<unsigned N>
float64<N> i_bit_andnot(float64<N> a, mask_float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(float64<N>, i_bit_andnot, a, b)
}

// -----------------------------------------------------------------------------
// mask_float64, mask_float64
inline mask_float64<2> i_bit_andnot(mask_float64<2> a, mask_float64<2> b)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_andnot_mm(a, b);
#else
    return mask_float64<2>(i_bit_andnot(float64<2>(a), float64<2>(b)));
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64<4> i_bit_andnot(mask_float64<4> a, mask_float64<4> b)
{
    return mask_float64<4>(i_bit_andnot(float64<4>(a), float64<4>(b)));
}
#endif

template<unsigned N>
mask_float64<N> i_bit_andnot(mask_float64<N> a, mask_float64<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(mask_float64<N>, i_bit_andnot, a, b)
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

