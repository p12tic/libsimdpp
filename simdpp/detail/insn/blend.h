/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BLEND_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BLEND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/detail/null/shuffle.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

// see doc/src/expressions.md for the list of types we must cover

// -----------------------------------------------------------------------------
// uint8, uint8, uint8

inline uint8<16> i_blend(uint8<16> on, uint8<16> off, uint8<16> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend(on, off, mask);
#elif SIMDPP_USE_AVX2
    return _mm_blendv_epi8(off, on, mask);
#elif SIMDPP_USE_XOP
    return _mm_cmov_si128(on, off, mask);
#elif SIMDPP_USE_SSE2
    // _mm_blendv_epi8 needs xmm0 and occupies the shuffle ports, yet saves
    // only one uop
    uint8<16> r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON
    return vbslq_u8(mask, on, off);
#elif SIMDPP_USE_ALTIVEC
    return vec_sel((__vector uint8_t)off, (__vector uint8_t)on,
                   (__vector uint8_t)mask);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8<32> i_blend(uint8<32> on, uint8<32> off, uint8<32> mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

template<unsigned N>
uint8<N> i_blend(uint8<N> on, uint8<N> off, uint8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint8<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint8, uint8, mask_int8

inline uint8<16> i_blend(uint8<16> on, uint8<16> off, mask_int8<16> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, uint8<16>(mask));
#endif
}

#if SIMDPP_USE_AVX2
inline uint8<32> i_blend(uint8<32> on, uint8<32> off, mask_int8<32> mask)
{
    return i_blend(on, off, uint8<32>(mask));
}
#endif

template<unsigned N>
uint8<N> i_blend(uint8<N> on, uint8<N> off, mask_int8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint8<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// mask_int8, mask_int8, mask_int8

inline mask_int8<16> i_blend(mask_int8<16> on, mask_int8<16> off, mask_int8<16> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int8<16>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8<32> i_blend(mask_int8<32> on, mask_int8<32> off, mask_int8<32> mask)
{
    return mask_int8<32>(i_blend(uint8<32>(on), uint8<32>(off), uint8<32>(mask)));
}
#endif

template<unsigned N>
mask_int8<N> i_blend(mask_int8<N> on, mask_int8<N> off, mask_int8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(mask_int8<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint16, uint16, uint16

inline uint16<8> i_blend(uint16<8> on, uint16<8> off, uint16<8> mask)
{
    return uint16<8>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
}

#if SIMDPP_USE_AVX2
inline uint16<16> i_blend(uint16<16> on, uint16<16> off, uint16<16> mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

template<unsigned N>
uint16<N> i_blend(uint16<N> on, uint16<N> off, uint16<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint16<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint16, uint16, mask_int16

inline uint16<8> i_blend(uint16<8> on, uint16<8> off, mask_int16<8> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return uint16<8>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline uint16<16> i_blend(uint16<16> on, uint16<16> off, mask_int16<16> mask)
{
    return i_blend(on, off, uint16<16>(mask));
}
#endif

template<unsigned N>
uint16<N> i_blend(uint16<N> on, uint16<N> off, mask_int16<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint16<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// mask_int16, mask_int16, mask_int16

inline mask_int16<8> i_blend(mask_int16<8> on, mask_int16<8> off, mask_int16<8> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int16<8>(i_blend(uint16<8>(on), uint16<8>(off), uint16<8>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int16<16> i_blend(mask_int16<16> on, mask_int16<16> off, mask_int16<16> mask)
{
    return mask_int16<16>(i_blend(uint16<16>(on), uint16<16>(off), uint16<16>(mask)));
}
#endif

template<unsigned N>
mask_int16<N> i_blend(mask_int16<N> on, mask_int16<N> off, mask_int16<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(mask_int16<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint32, uint32, uint32

inline uint32<4> i_blend(uint32<4> on, uint32<4> off, uint32<4> mask)
{
    return uint32<4>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
}

#if SIMDPP_USE_AVX2
inline uint32<8> i_blend(uint32<8> on, uint32<8> off, uint32<8> mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

template<unsigned N>
uint32<N> i_blend(uint32<N> on, uint32<N> off, uint32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint32<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint32, uint32, mask_int32

inline uint32<4> i_blend(uint32<4> on, uint32<4> off, mask_int32<4> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return uint32<4>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline uint32<8> i_blend(uint32<8> on, uint32<8> off, mask_int32<8> mask)
{
    return i_blend(on, off, uint32<8>(mask));
}
#endif

template<unsigned N>
uint32<N> i_blend(uint32<N> on, uint32<N> off, mask_int32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint32<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// mask_int32, mask_int32, mask_int32

inline mask_int32<4> i_blend(mask_int32<4> on, mask_int32<4> off, mask_int32<4> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int32<4>(i_blend(uint32<4>(on), uint32<4>(off), uint32<4>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int32<8> i_blend(mask_int32<8> on, mask_int32<8> off, mask_int32<8> mask)
{
    return mask_int32<8>(i_blend(uint32<8>(on), uint32<8>(off), uint32<8>(mask)));
}
#endif

template<unsigned N>
mask_int32<N> i_blend(mask_int32<N> on, mask_int32<N> off, mask_int32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(mask_int32<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// float32, float32, float32

inline float32<4> i_blend(float32<4> on, float32<4> off, float32<4> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend(on, off, mask);
#elif SIMDPP_USE_AVX
    return _mm_blendv_ps(off, on, mask);
#elif SIMDPP_USE_SSE2
    float32x4 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#elif SIMDPP_USE_NEON
    return vbslq_f32(uint32x4(mask), on, off);
#elif SIMDPP_USE_ALTIVEC
    return vec_sel((__vector float)off, (__vector float)on,
                   (__vector float)mask);
#endif
}

#if SIMDPP_USE_AVX
inline float32<8> i_blend(float32<8> on, float32<8> off, float32<8> mask)
{
    return _mm256_blendv_ps(off, on, mask);
}
#endif

template<unsigned N>
float32<N> i_blend(float32<N> on, float32<N> off, float32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// float32, float32, mask_float32

inline float32<4> i_blend(float32<4> on, float32<4> off, mask_float32<4> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, float32<4>(mask));
#endif
}

#if SIMDPP_USE_AVX
inline float32<8> i_blend(float32<8> on, float32<8> off, mask_float32<8> mask)
{
    return i_blend(on, off, float32<8>(mask));
}
#endif

template<unsigned N>
float32<N> i_blend(float32<N> on, float32<N> off, mask_float32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// mask_float32, mask_float32, mask_float32

inline mask_float32<4> i_blend(mask_float32<4> on, mask_float32<4> off, mask_float32<4> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_float32<4>(i_blend(float32<4>(on), float32<4>(off), float32<4>(mask)));
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32<8> i_blend(mask_float32<8> on, mask_float32<8> off, mask_float32<8> mask)
{
    return mask_float32<8>(i_blend(float32<8>(on), float32<8>(off), float32<8>(mask)));
}
#endif

template<unsigned N>
mask_float32<N> i_blend(mask_float32<N> on, mask_float32<N> off, mask_float32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(mask_float32<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint64, uint64, uint64

inline uint64<2> i_blend(uint64<2> on, uint64<2> off, uint64<2> mask)
{
    return uint64<2>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
}

#if SIMDPP_USE_AVX2
inline uint64<4> i_blend(uint64<4> on, uint64<4> off, uint64<4> mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

template<unsigned N>
uint64<N> i_blend(uint64<N> on, uint64<N> off, uint64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint64<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// uint64, uint64, mask_int64

inline uint64<2> i_blend(uint64<2> on, uint64<2> off, mask_int64<2> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return uint64<2>(i_blend(uint8<16>(on), uint8<16>(off), uint8<16>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline uint64<4> i_blend(uint64<4> on, uint64<4> off, mask_int64<4> mask)
{
    return i_blend(on, off, uint64<4>(mask));
}
#endif

template<unsigned N>
uint64<N> i_blend(uint64<N> on, uint64<N> off, mask_int64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(uint64<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// mask_int64, mask_int64, mask_int64

inline mask_int64<2> i_blend(mask_int64<2> on, mask_int64<2> off, mask_int64<2> mask)
{
#if SIMDPP_USE_NULL
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_int64<2>(i_blend(uint64<2>(on), uint64<2>(off), uint64<2>(mask)));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int64<4> i_blend(mask_int64<4> on, mask_int64<4> off, mask_int64<4> mask)
{
    return mask_int64<4>(i_blend(uint64<4>(on), uint64<4>(off), uint64<4>(mask)));
}
#endif

template<unsigned N>
mask_int64<N> i_blend(mask_int64<N> on, mask_int64<N> off, mask_int64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(mask_int64<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// float64, float64, float64

inline float64<2> i_blend(float64<2> on, float64<2> off, float64<2> mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::blend(on, off, mask);
#elif SIMDPP_USE_AVX
    return _mm_blendv_pd(off, on, mask);
#elif SIMDPP_USE_SSE2
    float64x2 r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
#endif
}

#if SIMDPP_USE_AVX
inline float64<4> i_blend(float64<4> on, float64<4> off, float64<4> mask)
{
    return _mm256_blendv_pd(off, on, mask);
}
#endif

template<unsigned N>
float64<N> i_blend(float64<N> on, float64<N> off, float64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// float64, float64, mask_float64

inline float64<2> i_blend(float64<2> on, float64<2> off, mask_float64<2> mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, float64<2>(mask));
#endif
}

#if SIMDPP_USE_AVX
inline float64<4> i_blend(float64<4> on, float64<4> off, mask_float64<4> mask)
{
    return i_blend(on, off, float64<4>(mask));
}
#endif

template<unsigned N>
float64<N> i_blend(float64<N> on, float64<N> off, mask_float64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------
// mask_float64, mask_float64, mask_float64

inline mask_float64<2> i_blend(mask_float64<2> on, mask_float64<2> off, mask_float64<2> mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::blend_mask(on, off, mask);
#else
    return mask_float64<2>(i_blend(float64<2>(on), float64<2>(off), float64<2>(mask)));
#endif
}

#if SIMDPP_USE_AVX
inline mask_float64<4> i_blend(mask_float64<4> on, mask_float64<4> off, mask_float64<4> mask)
{
    return mask_float64<4>(i_blend(float64<4>(on), float64<4>(off), float64<4>(mask)));
}
#endif

template<unsigned N>
mask_float64<N> i_blend(mask_float64<N> on, mask_float64<N> off, mask_float64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(mask_float64<N>, i_blend, on, off, mask)
}


} // namespace insn
} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

