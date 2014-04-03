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

/** A class that contains some dummy mask vectors with test data.

    BE - bytes per vector element
    N - number of vectors
*/
template<unsigned BE, unsigned N>
struct Masks {
    simdpp::mask_int8<BE> u8[N];
    simdpp::mask_int16<BE/2> u16[N];
    simdpp::mask_int32<BE/4> u32[N];
    simdpp::mask_int64<BE/8> u64[N];
    simdpp::mask_float32<BE/4> f32[N];
    simdpp::mask_float64<BE/8> f64[N];

    Masks() { reset(); }

    void reset()
    {
        using namespace simdpp;

        for (unsigned i = 0; i < N; ++i) {
            u8[i] =  make_mask<mask_int8<BE>, uint8<BE>>(i);
            u16[i] = make_mask<mask_int16<BE/2>, uint16<BE/2>>(i);
            u32[i] = make_mask<mask_int32<BE/4>, uint32<BE/4>>(i);
            u64[i] = make_mask<mask_int64<BE/8>, uint64<BE/8>>(i);
            f32[i] = make_mask<mask_float32<BE/4>, float32<BE/4>>(i);
            f64[i] = make_mask<mask_float64<BE/8>, float64<BE/8>>(i);
        }
    }
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
