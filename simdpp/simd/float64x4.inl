/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_FLOAT64X4_INL
#define LIBSIMDPP_SIMD_FLOAT64X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline float64x4 float64x4::zero()
{
    float64x4 r;
    r = bit_xor(r, r);
    return r;
}

#if SIMDPP_USE_AVX2
#elif SIMDPP_USE_AVX
inline float64x4::float64x4(basic_int64x4 d)
{
    d_ = float64x4(float64x2(d[0]), float64x2(d[1]));
}
#endif

inline float64x4 float64x4::load_broadcast(const double* v0)
{
#if SIMDPP_USE_AVX
    return _mm256_broadcast_sd(v0);
#else
    float64x2 a = float64x2::load_broadcast(v0);
    return {a, a};
#endif
}

inline float64x4 float64x4::set_broadcast(double v0)
{
#if SIMDPP_USE_AVX
    return float64x4::load_broadcast(&v0);
#else
    float64x2 a = float64x2::set_broadcast(v0);
    return {a, a};
#endif
}

inline float64x4 float64x4::make_const(double v0)
{
    return float64x4::make_const(v0, v0, v0, v0);
}

inline float64x4 float64x4::make_const(double v0, double v1)
{
    return float64x4::make_const(v0, v1, v0, v1);
}

inline float64x4 float64x4::make_const(double v0, double v1, double v2, double v3)
{
#if SIMDPP_USE_AVX
    return _mm256_set_pd(v3, v2, v1, v0);
#else
    return {float64x2::make_const(v0, v1),
            float64x2::make_const(v2, v3)};
#endif
}

inline mask_float64x4::operator float64x4() const
{
#if SIMDPP_USE_AVX
    return d_;
#else
    return float64x4(m_[0], m_[1]);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
