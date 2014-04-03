/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_COMMON_SEL_VECTORS_H
#define SIMDPP_TEST_COMMON_SEL_VECTORS_H

#include <simdpp/simd.h>
#include "masks.h"

namespace SIMDPP_ARCH_NAMESPACE {

template<class V>
V make_sel_vector(unsigned i)
{
    return (V) (typename V::uint_vector_type) simdpp::make_uint((i/2)%2 ? -1 : 0, i%2 ? -1 : 0);
}


/** A class that contains some dummy vectors with test data which is set so
    that each element has all bits either set or not set

    BE - bytes per vector element
    N - number of vectors
*/
template<unsigned BE, unsigned N>
struct SelVectors {
    simdpp::int8<BE> i8[N];
    simdpp::int16<BE/2> i16[N];
    simdpp::int32<BE/4> i32[N];
    simdpp::int64<BE/8> i64[N];
    simdpp::uint8<BE> u8[N];
    simdpp::uint16<BE/2> u16[N];
    simdpp::uint32<BE/4> u32[N];
    simdpp::uint64<BE/8> u64[N];
    simdpp::float32<BE/4> f32[N];
    simdpp::float64<BE/8> f64[N];

    SelVectors() { reset(); }

    void reset()
    {
        using namespace simdpp;

        for (unsigned i = 0; i < N; ++i) {
            u8[i] =  make_sel_vector<uint8<BE>>(i);
            u16[i] = make_sel_vector<uint16<BE/2>>(i);
            u32[i] = make_sel_vector<uint32<BE/4>>(i);
            u64[i] = make_sel_vector<uint64<BE/8>>(i);
            i8[i] =  make_sel_vector<uint8<BE>>(i);
            i16[i] = make_sel_vector<uint16<BE/2>>(i);
            i32[i] = make_sel_vector<uint32<BE/4>>(i);
            i64[i] = make_sel_vector<uint64<BE/8>>(i);
            f32[i] = make_sel_vector<float32<BE/4>>(i);
            f64[i] = make_sel_vector<float64<BE/8>>(i);
        }
    }
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
