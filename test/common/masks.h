 /*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef SIMDPP_TEST_COMMON_MASKS_H
#define SIMDPP_TEST_COMMON_MASKS_H

#include <simdpp/simd.h>
#include "vectors.h"

namespace SIMDPP_ARCH_NAMESPACE {

template<class M, class V>
M make_mask(unsigned i)
{
    V v1 = V::make_const((i/2)%2, i%2);
    V v2 = V::zero();
    return cmp_eq(v1, v2);
}

template<unsigned L>
struct Masks {
    static constexpr unsigned length = L;

    simdpp::mask_int8x16 u8[L/16];
    simdpp::mask_int16x8 u16[L/16];
    simdpp::mask_int32x4 u32[L/16];
    simdpp::mask_int64x2 u64[L/16];
    simdpp::mask_float32x4 f32[L/16];
    simdpp::mask_float64x2 f64[L/16];

    simdpp::mask_int8x32 du8[L/32];
    simdpp::mask_int16x16 du16[L/32];
    simdpp::mask_int32x8 du32[L/32];
    simdpp::mask_int64x4 du64[L/32];
    simdpp::mask_float32x8 df32[L/32];
    simdpp::mask_float64x4 df64[L/32];

    Masks() { reset(); }

    void reset()
    {
        using namespace simdpp;

        for (unsigned i = 0; i < L/16; ++i) {
            u8[i] = make_mask<mask_int8x16, uint8x16>(i);
            u16[i] = make_mask<mask_int16x8, uint16x8>(i);
            u32[i] = make_mask<mask_int32x4, uint32x4>(i);
            u64[i] = make_mask<mask_int64x2, uint64x2>(i);
            f32[i] = make_mask<mask_float32x4, float32x4>(i);
            f64[i] = make_mask<mask_float64x2, float64x2>(i);

        }
        for (unsigned i = 0; i < L/32; ++i) {
            du8[i] = make_mask<mask_int8x32, uint8x32>(i);
            du16[i] = make_mask<mask_int16x16, uint16x16>(i);
            du32[i] = make_mask<mask_int32x8, uint32x8>(i);
            du64[i] = make_mask<mask_int64x4, uint64x4>(i);
            df32[i] = make_mask<mask_float32x8, float32x8>(i);
            df64[i] = make_mask<mask_float64x4, float64x4>(i);
        }
    }
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
