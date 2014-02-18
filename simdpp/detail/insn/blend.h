/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
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
#include <simdpp/null/shuffle.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline gint8x16 i_blend(gint8x16 on, gint8x16 off, gint8x16 mask)
{
#if SIMDPP_USE_NULL
    return null::blend(on, off, mask);
#elif SIMDPP_USE_AVX2
    return _mm_blendv_epi8(off, on, mask);
#elif SIMDPP_USE_XOP
    return _mm_cmov_si128(on, off, mask);
#elif SIMDPP_USE_SSE2
    // _mm_blendv_epi8 needs xmm0 and occupies the shuffle ports, yet saves
    // only one uop
    int8x16 r;
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

inline gint8x16 i_blend(gint8x16 on, gint8x16 off, mask_int8x16 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return i_blend(uint8x16(on), uint8x16(off), uint8x16(mask));
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32 i_blend(gint8x32 on, gint8x32 off, gint8x32 mask)
{
    return _mm256_blendv_epi8(off, on, mask);
}
#endif

template<unsigned N>
gint8<N> i_blend(gint8<N> on, gint8<N> off, gint8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(gint8<N>, i_blend, on, off, mask)
}

#if SIMDPP_USE_AVX2
inline gint8x32 i_blend(gint8x32 on, gint8x32 off, mask_int8x32 mask)
{
    return i_blend(uint8x32(on), uint8x32(off), uint8x32(mask));
}
#endif

template<unsigned N>
inline gint8<N> i_blend(gint8<N> on, gint8<N> off, mask_int8<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(gint8<N>, i_blend, on, off, mask)
}

// -----------------------------------------------------------------------------

template<unsigned N>
inline gint16<N> i_blend(gint16<N> on, gint16<N> off, gint16<N> mask)
{
    return (gint16<N>) i_blend((uint8<N*2>)on, (uint8<N*2>)off, (uint8<N*2>)mask);
}

template<unsigned N>
inline gint16<N> i_blend(gint16<N> on, gint16<N> off, mask_int16<N> mask)
{
    // FIXME: null::blend_mask(on, off, mask);
    return (gint16<N>) i_blend((uint8<N*2>)on, (uint8<N*2>)off, (uint8<N*2>)mask);
}

// -----------------------------------------------------------------------------

template<unsigned N>
inline gint32<N> i_blend(gint32<N> on, gint32<N> off, gint32<N> mask)
{
    return (gint32<N>) i_blend((uint8<N*4>)on, (uint8<N*4>)off, (uint8<N*4>)mask);
}

template<unsigned N>
inline gint32<N> i_blend(gint32<N> on, gint32<N> off, mask_int32<N> mask)
{
    // FIXME: null::blend_mask(on, off, mask);
    return (gint32<N>) i_blend((uint8<N*4>)on, (uint8<N*4>)off, (uint8<N*4>)mask);
}

// -----------------------------------------------------------------------------

template<unsigned N>
inline gint64<N> i_blend(gint64<N> on, gint64<N> off, gint64<N> mask)
{
    return (gint64<N>) i_blend((uint8<N*8>)on, (uint8<N*8>)off, (uint8<N*8>)mask);
}

template<unsigned N>
inline gint64<N> i_blend(gint64<N> on, gint64<N> off, mask_int64<N> mask)
{
    // FIXME: null::blend_mask(on, off, mask);
    return (gint64<N>) i_blend((uint8<N*8>)on, (uint8<N*8>)off, (uint8<N*8>)mask);
}

// -----------------------------------------------------------------------------

inline float32x4 i_blend(float32x4 on, float32x4 off, float32x4 mask)
{
#if SIMDPP_USE_NULL
    return null::blend(on, off, mask);
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
inline float32x8 i_blend(float32x8 on, float32x8 off, float32x8 mask)
{
    return _mm256_blendv_ps(off, on, mask);
}
#endif

template<unsigned N>
float32<N> i_blend(float32<N> on, float32<N> off, float32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, i_blend, on, off, mask);
}

template<unsigned N>
inline float32<N> i_blend(float32<N> on, float32<N> off, gint32<N> mask)
{
    return i_blend(on, off, float32<N>(mask));
}

inline float32x4 i_blend(float32x4 on, float32x4 off, mask_float32x4 mask)
{
#if SIMDPP_USE_NULL
    return null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, uint32x4(mask));
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_blend(float32x8 on, float32x8 off, mask_float32x8 mask)
{
    return i_blend(on, off, uint32x8(mask));
}
#endif

template<unsigned N>
float32<N> i_blend(float32<N> on, float32<N> off, mask_float32<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float32<N>, i_blend, on, off, mask);
}

// -----------------------------------------------------------------------------

inline float64x2 i_blend(float64x2 on, float64x2 off, float64x2 mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::blend(on, off, mask);
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
inline float64x4 i_blend(float64x4 on, float64x4 off, float64x4 mask)
{
    return _mm256_blendv_pd(off, on, mask);
}
#endif

template<unsigned N>
float64<N> i_blend(float64<N> on, float64<N> off, float64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, i_blend, on, off, mask);
}

template<unsigned N>
inline float64<N> i_blend(float64<N> on, float64<N> off, gint64<N> mask)
{
    return i_blend(on, off, float64<N>(mask));
}

inline float64x2 i_blend(float64x2 on, float64x2 off, mask_float64x2 mask)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::blend_mask(on, off, mask);
#else
    return i_blend(on, off, uint64x2(mask));
#endif
}

#if SIMDPP_USE_AVX
inline float64x4 i_blend(float64x4 on, float64x4 off, mask_float64x4 mask)
{
    return i_blend(on, off, uint64x4(mask));
}
#endif

template<unsigned N>
float64<N> i_blend(float64<N> on, float64<N> off, mask_float64<N> mask)
{
    SIMDPP_VEC_ARRAY_IMPL3(float64<N>, i_blend, on, off, mask);
}

} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

