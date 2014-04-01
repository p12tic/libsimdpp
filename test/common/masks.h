/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_COMMON_MASKS_H
#define SIMDPP_TEST_COMMON_MASKS_H

#include <simdpp/simd.h>
#include "vectors.h"

namespace SIMDPP_ARCH_NAMESPACE {

template<class M, class V>
M make_mask(unsigned i)
{
    V v1 = simdpp::make_uint((i/2)%2, i%2);
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
