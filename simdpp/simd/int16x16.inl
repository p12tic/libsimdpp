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

#ifndef LIBSIMDPP_SIMD_INT16X16_INL
#define LIBSIMDPP_SIMD_INT16X16_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline int16x16 int16x16::zero()
{
    return int256::zero();
}

inline int16x16 int16x16::load_broadcast(const int16_t* v0)
{
    return uint16x16::load_broadcast(reinterpret_cast<const uint16_t*>(v0));
}

inline int16x16 int16x16::set_broadcast(int16_t v0)
{
    return uint16x16::set_broadcast(v0);
}

inline int16x16 int16x16::make_const(int16_t v0)
{
    return uint16x16::make_const(v0);
}

inline int16x16 int16x16::make_const(int16_t v0, int16_t v1)
{
    return uint16x16::make_const(v0, v1);
}

inline int16x16 int16x16::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3)
{
    return uint16x16::make_const(v0, v1, v2, v3);
}

inline int16x16 int16x16::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                                     int16_t v4, int16_t v5, int16_t v6, int16_t v7)
{
    return uint16x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline int16x16 int16x16::make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                                     int16_t v4, int16_t v5, int16_t v6, int16_t v7,
                                     int16_t v8, int16_t v9, int16_t v10, int16_t v11,
                                     int16_t v12, int16_t v13, int16_t v14, int16_t v15)
{
    return uint16x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                 v8, v9, v10, v11, v12, v13, v14, v15);
}

inline uint16x16 uint16x16::zero()
{
    return int256::zero();
}

inline uint16x16 uint16x16::load_broadcast(const uint16_t* v0)
{
#if SIMDPP_USE_AVX2
    return uint16x16::set_broadcast(*v0);
#else
    uint16x8 a = uint16x8::load_broadcast(v0);
    return {a, a};
#endif
}

inline uint16x16 uint16x16::set_broadcast(uint16_t v0)
{
#if SIMDPP_USE_AVX2
    int128 a = _mm_cvtsi32_si128(v0);
    return _mm256_broadcastw_epi16(a);
#else
    uint16x8 a = uint16x8::set_broadcast(v0);
    return {a, a};
#endif
}

inline uint16x16 uint16x16::make_const(uint16_t v0)
{
    return uint16x16::make_const(v0, v0, v0, v0, v0, v0, v0, v0,
                                 v0, v0, v0, v0, v0, v0, v0, v0);
}

inline uint16x16 uint16x16::make_const(uint16_t v0, uint16_t v1)
{
    return uint16x16::make_const(v0, v1, v0, v1, v0, v1, v0, v1,
                                 v0, v1, v0, v1, v0, v1, v0, v1);
}

inline uint16x16 uint16x16::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3)
{
    return uint16x16::make_const(v0, v1, v2, v3, v0, v1, v2, v3,
                                 v0, v1, v2, v3, v0, v1, v2, v3);
}

inline uint16x16 uint16x16::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                       uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7)
{
    return uint16x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                 v0, v1, v2, v3, v4, v5, v6, v7);
}

inline uint16x16 uint16x16::make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                       uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7,
                                       uint16_t v8, uint16_t v9, uint16_t v10, uint16_t v11,
                                       uint16_t v12, uint16_t v13, uint16_t v14, uint16_t v15)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi16(v15, v14, v13, v12, v11, v10, v9, v8,
                            v7, v6, v5, v4, v3, v2, v1, v0);
#else
    return {uint16x8::make_const(v0, v1, v2, v3, v4, v5, v6, v7),
            uint16x8::make_const(v8, v9, v10, v11, v12, v13, v14, v15)};
#endif
}

inline mask_int16x16::operator basic_int16x16() const
{
#if SIMDPP_USE_AVX2
    return d_;
#else
    return basic_int16x16(m_[0], m_[1]);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
