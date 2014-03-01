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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/core/cast.h>

#include <cstring>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class R, class T>
R cast_memcpy(T t)
{
    static_assert(sizeof(R) == sizeof(T), "Size mismatch");
    R r;
    std::memcpy(&r, &t, sizeof(R));
    return r;
}

// Depending on vector types the compiler may not optimize the above memcpy
// to proper register moves and merges (yes, that indeed happens). In order to
// make sure this never happens we must overload the above function for all
// vector combinations. That's unfortunate

// Not all combinations are supported currently

#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC

// all entries must be defined, otherwise the templated version below results
// in an infinite recursion
gint8x16 cast(gint8x16, gint16x8);
gint8x16 cast(gint8x16, gint32x4);
gint8x16 cast(gint8x16, gint64x2);
gint8x16 cast(gint8x16, float32x4);
gint8x16 cast(gint8x16, float64x2);

gint16x8 cast(gint16x8, gint8x16);
gint16x8 cast(gint16x8, gint32x4);
gint16x8 cast(gint16x8, gint64x2);
gint16x8 cast(gint16x8, float32x4);
gint16x8 cast(gint16x8, float64x2);

gint32x4 cast(gint32x4, gint8x16);
gint32x4 cast(gint32x4, gint16x8);
gint32x4 cast(gint32x4, gint64x2);
gint32x4 cast(gint32x4, float32x4);
gint32x4 cast(gint32x4, float64x2);

gint64x2 cast(gint64x2, gint8x16);
gint64x2 cast(gint64x2, gint16x8);
gint64x2 cast(gint64x2, gint32x4);
gint64x2 cast(gint64x2, float32x4);
gint64x2 cast(gint64x2, float64x2);

float32x4 cast(float32x4, gint8x16);
float32x4 cast(float32x4, gint16x8);
float32x4 cast(float32x4, gint32x4);
float32x4 cast(float32x4, gint64x2);
float32x4 cast(float32x4, float64x2);

float64x2 cast(float64x2, gint8x16);
float64x2 cast(float64x2, gint16x8);
float64x2 cast(float64x2, gint32x4);
float64x2 cast(float64x2, gint64x2);
float64x2 cast(float64x2, float32x4);

#endif

#if SIMDPP_USE_AVX

gint8x32 cast(gint8x32, float32x8);
gint8x32 cast(gint8x32, float64x4);

gint16x16 cast(gint16x16, float32x8);
gint16x16 cast(gint16x16, float64x4);

gint32x8 cast(gint32x8, float32x8);
gint32x8 cast(gint32x8, float64x4);

gint64x4 cast(gint64x4, float32x8);
gint64x4 cast(gint64x4, float64x4);

float32x8 cast(float32x8, gint8x32);
float32x8 cast(float32x8, gint16x16);
float32x8 cast(float32x8, gint32x8);
float32x8 cast(float32x8, gint64x4);
float32x8 cast(float32x8, float64x4);

float64x4 cast(float64x4, gint8x32);
float64x4 cast(float64x4, gint16x16);
float64x4 cast(float64x4, gint32x8);
float64x4 cast(float64x4, gint64x4);
float64x4 cast(float64x4, float32x8);

#endif

#if SIMDPP_USE_NEON || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
template<unsigned N> gint8<N> cast(gint8<N>, gint16<N/2>);
template<unsigned N> gint8<N> cast(gint8<N>, gint32<N/4>);
template<unsigned N> gint8<N> cast(gint8<N>, gint64<N/8>);
template<unsigned N> gint8<N> cast(gint8<N>, float32<N/4>);
template<unsigned N> gint8<N> cast(gint8<N>, float64<N/8>);

template<unsigned N> gint16<N> cast(gint16<N>, gint8<N*2>);
template<unsigned N> gint16<N> cast(gint16<N>, gint32<N/2>);
template<unsigned N> gint16<N> cast(gint16<N>, gint64<N/4>);
template<unsigned N> gint16<N> cast(gint16<N>, float32<N/2>);
template<unsigned N> gint16<N> cast(gint16<N>, float64<N/4>);

template<unsigned N> gint32<N> cast(gint32<N>, gint8<N*4>);
template<unsigned N> gint32<N> cast(gint32<N>, gint16<N*2>);
template<unsigned N> gint32<N> cast(gint32<N>, gint64<N/2>);
template<unsigned N> gint32<N> cast(gint32<N>, float32<N>);
template<unsigned N> gint32<N> cast(gint32<N>, float64<N/2>);

template<unsigned N> gint64<N> cast(gint64<N>, gint8<N*8>);
template<unsigned N> gint64<N> cast(gint64<N>, gint16<N*4>);
template<unsigned N> gint64<N> cast(gint64<N>, gint32<N*2>);
template<unsigned N> gint64<N> cast(gint64<N>, float32<N*2>);
template<unsigned N> gint64<N> cast(gint64<N>, float64<N>);

template<unsigned N> float32<N> cast(float32<N>, gint8<N*4>);
template<unsigned N> float32<N> cast(float32<N>, gint16<N*2>);
template<unsigned N> float32<N> cast(float32<N>, gint32<N>);
template<unsigned N> float32<N> cast(float32<N>, gint64<N/2>);
template<unsigned N> float32<N> cast(float32<N>, float64<N/2>);

template<unsigned N> float64<N> cast(float64<N>, gint8<N*8>);
template<unsigned N> float64<N> cast(float64<N>, gint16<N*4>);
template<unsigned N> float64<N> cast(float64<N>, gint32<N*2>);
template<unsigned N> float64<N> cast(float64<N>, gint64<N>);
template<unsigned N> float64<N> cast(float64<N>, float32<N*2>);
#endif

template<unsigned N> gint8<N>   cast(gint8<N>,   gint8<N> a);
template<unsigned N> gint16<N>  cast(gint16<N>,  gint16<N> a);
template<unsigned N> gint32<N>  cast(gint32<N>,  gint32<N> a);
template<unsigned N> gint64<N>  cast(gint64<N>,  gint64<N> a);
template<unsigned N> float32<N> cast(float32<N>, float32<N> a);
template<unsigned N> float64<N> cast(float64<N>, float64<N> a);

template<bool isvector>
struct cast_wrapper;

template<>
struct cast_wrapper<true> {
    template<class R, class T>
    static R run(T t)
    {
#if SIMDPP_USE_NULL
        return cast_memcpy<R>(t);
#else
        return cast(R(), t);
#endif
    }
};

template<>
struct cast_wrapper<false> {
    template<class R, class T>
    static R run(T t)
    {
        static_assert(sizeof(R) == sizeof(T), "Size mismatch");
        R r;
        std::memcpy(&r, &t, sizeof(R));
        return r;
    }
};

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
