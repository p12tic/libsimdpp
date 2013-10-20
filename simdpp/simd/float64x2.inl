/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_FLOAT64X2_INL
#define LIBSIMDPP_SIMD_FLOAT64X2_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/simd/detail/word_size.h>

#if SIMDPP_USE_NEON
    #include <simdpp/null/set.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline float64x2 float64x2::zero()
{
    float64x2 r;
    r = bit_xor(r, r);
    return r;
}

inline float64x2 float64x2::load_broadcast(const double* v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    return null::make_vec<float64x2>(*v0);
#elif SIMDPP_USE_SSE3
    return _mm_loaddup_pd(v0);
#elif SIMDPP_USE_SSE2
    float64x2 r;
    r = _mm_load_sd(v0);
    r = permute<0,0>(r);
    return r;
#endif
}

inline float64x2 float64x2::set_broadcast(double v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    return null::make_vec<float64x2>(v0);
#elif SIMDPP_USE_SSE2
#if SIMDPP_SSE_32_BITS
    return float64x2::load_broadcast(&v0);
#else
    int64x2 r0;
    r0 = _mm_cvtsi64_si128(bit_cast<int64_t>(v0));
    return permute<0,0>(float64x2(r0));
#endif
#endif
}

inline float64x2 float64x2::make_const(double v0)
{
    return float64x2::make_const(v0, v0);
}

inline float64x2 float64x2::make_const(double v0, double v1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    return null::make_vec<float64x2>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_pd(v1, v0);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
