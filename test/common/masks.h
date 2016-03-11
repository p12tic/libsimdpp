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
SIMDPP_INL M make_mask(unsigned i)
{
    V v1 = simdpp::make_uint((i/2)%2, i%2);
    V v2 = simdpp::make_zero();
    return cmp_eq(v1, v2);
}

/** A class that contains some dummy mask vectors with test data.

    BE - bytes per vector element
    N - number of vectors
*/
template<unsigned BE, unsigned N>
struct Masks {
    simdpp::mask_int8<BE>* volatile u8;
    simdpp::mask_int16<BE/2>* volatile u16;
    simdpp::mask_int32<BE/4>* volatile u32;
    simdpp::mask_int64<BE/8>* volatile u64;
    simdpp::mask_float32<BE/4>* volatile f32;
    simdpp::mask_float64<BE/8>* volatile f64;

    Masks() { reset(); }

    void reset()
    {
        using namespace simdpp;

        for (unsigned i = 0; i < N; ++i) {
            du8[i] =  make_mask<mask_int8<BE>, uint8<BE>>(i);
            du16[i] = make_mask<mask_int16<BE/2>, uint16<BE/2>>(i);
            du32[i] = make_mask<mask_int32<BE/4>, uint32<BE/4>>(i);
            du64[i] = make_mask<mask_int64<BE/8>, uint64<BE/8>>(i);
            df32[i] = make_mask<mask_float32<BE/4>, float32<BE/4>>(i);
            df64[i] = make_mask<mask_float64<BE/8>, float64<BE/8>>(i);
        }
        u8 = du8;
        u16 = du16;
        u32 = du32;
        u64 = du64;
        f32 = df32;
        f64 = df64;
    }

private:
    simdpp::mask_int8<BE> du8[N];
    simdpp::mask_int16<BE/2> du16[N];
    simdpp::mask_int32<BE/4> du32[N];
    simdpp::mask_int64<BE/8> du64[N];
    simdpp::mask_float32<BE/4> df32[N];
    simdpp::mask_float64<BE/8> df64[N];
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
