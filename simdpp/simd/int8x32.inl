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

#ifndef LIBSIMDPP_SIMD_INT8X32_INL
#define LIBSIMDPP_SIMD_INT8X32_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/simd.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline int8x32 int8x32::zero()
{
    return int256::zero();
}

inline int8x32 int8x32::load_broadcast(const int8_t* v0)
{
    return uint8x32::load_broadcast(reinterpret_cast<const uint8_t*>(v0));
}

inline int8x32 int8x32::set_broadcast(int8_t v0)
{
    return uint8x32::set_broadcast(v0);
}

inline int8x32 int8x32::make_const(int8_t v0)
{
    return uint8x32::make_const(v0);
}

inline int8x32 int8x32::make_const(int8_t v0, int8_t v1)
{
    return uint8x32::make_const(v0, v1);
}

inline int8x32 int8x32::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3)
{
    return uint8x32::make_const(v0, v1, v2, v3);
}

inline int8x32 int8x32::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7)
{
    return uint8x32::make_const(v0, v1, v2, v3, v4, v5, v6, v7);
}

inline int8x32 int8x32::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                                   int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                                   int8_t v12, int8_t v13, int8_t v14, int8_t v15)
{
    return uint8x32::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v8, v9, v10, v11, v12, v13, v14, v15);
}

inline int8x32 int8x32::make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                                   int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                                   int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                                   int8_t v12, int8_t v13, int8_t v14, int8_t v15,
                                   int8_t v16, int8_t v17, int8_t v18, int8_t v19,
                                   int8_t v20, int8_t v21, int8_t v22, int8_t v23,
                                   int8_t v24, int8_t v25, int8_t v26, int8_t v27,
                                   int8_t v28, int8_t v29, int8_t v30, int8_t v31)
{
    return uint8x32::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v8, v9, v10, v11, v12, v13, v14, v15,
                                v16, v17, v18, v19, v20, v21, v22, v23,
                                v24, v25, v26, v27, v28, v29, v30, v31);
}

inline uint8x32 uint8x32::zero()
{
    return int256::zero();
}

inline uint8x32 uint8x32::load_broadcast(const uint8_t* v0)
{
#if SIMDPP_USE_AVX2
    return uint8x32::set_broadcast(*v0);
#else
    uint8x16 a = uint8x16::load_broadcast(v0);
    return uint8x32(a, a);
#endif
}

inline uint8x32 uint8x32::set_broadcast(uint8_t v0)
{

#if SIMDPP_USE_AVX2
    int128 a = _mm_cvtsi32_si128(v0);
    return _mm256_broadcastb_epi8(a);
#else
    uint8x16 a = uint8x16::set_broadcast(v0);
    return uint8x32(a, a);
#endif
}

inline uint8x32 uint8x32::make_const(uint8_t v0)
{
    return uint8x32::make_const(v0, v0, v0, v0, v0, v0, v0, v0,
                                v0, v0, v0, v0, v0, v0, v0, v0,
                                v0, v0, v0, v0, v0, v0, v0, v0,
                                v0, v0, v0, v0, v0, v0, v0, v0);
}

inline uint8x32 uint8x32::make_const(uint8_t v0, uint8_t v1)
{
    return uint8x32::make_const(v0, v1, v0, v1, v0, v1, v0, v1,
                                v0, v1, v0, v1, v0, v1, v0, v1,
                                v0, v1, v0, v1, v0, v1, v0, v1,
                                v0, v1, v0, v1, v0, v1, v0, v1);
}

inline uint8x32 uint8x32::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3)
{
    return uint8x32::make_const(v0, v1, v2, v3, v0, v1, v2, v3,
                                v0, v1, v2, v3, v0, v1, v2, v3,
                                v0, v1, v2, v3, v0, v1, v2, v3,
                                v0, v1, v2, v3, v0, v1, v2, v3);
}

inline uint8x32 uint8x32::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7)
{
    return uint8x32::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                v0, v1, v2, v3, v4, v5, v6, v7,
                                v0, v1, v2, v3, v4, v5, v6, v7,
                                v0, v1, v2, v3, v4, v5, v6, v7);
}

inline uint8x32 uint8x32::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                                     uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                                     uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15)
{
    return uint8x32::make_const(v0, v1, v2,  v3,  v4,  v5,  v6,  v7,
                                v8, v9, v10, v11, v12, v13, v14, v15,
                                v0, v1, v2,  v3,  v4,  v5,  v6,  v7,
                                v8, v9, v10, v11, v12, v13, v14, v15);
}

inline uint8x32 uint8x32::make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                                     uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                                     uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                                     uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15,
                                     uint8_t v16, uint8_t v17, uint8_t v18, uint8_t v19,
                                     uint8_t v20, uint8_t v21, uint8_t v22, uint8_t v23,
                                     uint8_t v24, uint8_t v25, uint8_t v26, uint8_t v27,
                                     uint8_t v28, uint8_t v29, uint8_t v30, uint8_t v31)
{
#if SIMDPP_USE_AVX2
    return _mm256_set_epi8(v31, v30, v29, v28, v27, v26, v25, v24,
                           v23, v22, v21, v20, v19, v18, v17, v16,
                           v15, v14, v13, v12, v11, v10, v9, v8,
                           v7, v6, v5, v4, v3, v2, v1, v0);
#else
    return {uint8x16::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                 v8, v9, v10, v11, v12, v13, v14, v15),
            uint8x16::make_const(v16, v17, v18, v19, v20, v21, v22, v23,
                                 v24, v25, v26, v27, v28, v29, v30, v31)};
#endif
}

inline mask_int8x32::operator basic_int8x32() const
{
#if SIMDPP_USE_AVX2
    return d_;
#else
    return basic_int8x32(m_[0], m_[1]);
#endif
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
