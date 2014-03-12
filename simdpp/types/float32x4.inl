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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/float32x4.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/splat.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

inline float32x4 float32x4::zero()
{
    float32x4 r;
    r = bit_xor(r, r);
    return r;
}

inline mask_float32<4>::mask_float32(const maskdata_float32<4>& d) : float32<4>(d), mask_(d) {}

#if SIMDPP_USE_SSE2
inline mask_float32<4>::mask_float32(__m128 d)     : float32<4>(d), mask_(d) {}
inline mask_float32<4>::mask_float32(float32<4> d) : float32<4>(d), mask_(d) {}
#elif SIMDPP_USE_NEON
inline mask_float32<4>::mask_float32(float32x4_t d) : float32<4>(d), mask_(d) {}
inline mask_float32<4>::mask_float32(float32<4> d)  : float32<4>(d), mask_(d) {}
#elif SIMDPP_USE_ALTIVEC
inline mask_float32<4>::mask_float32(__vector float d) : float32<4>(d), mask_(d) {}
inline mask_float32<4>::mask_float32(float32<4> d)     : float32<4>(d), mask_(d) {}
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
