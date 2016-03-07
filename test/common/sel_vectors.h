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
    simdpp::int8<BE>* volatile i8;
    simdpp::int16<BE/2>* volatile i16;
    simdpp::int32<BE/4>* volatile i32;
    simdpp::int64<BE/8>* volatile i64;
    simdpp::uint8<BE>* volatile u8;
    simdpp::uint16<BE/2>* volatile u16;
    simdpp::uint32<BE/4>* volatile u32;
    simdpp::uint64<BE/8>* volatile u64;
    simdpp::float32<BE/4>* volatile f32;
    simdpp::float64<BE/8>* volatile f64;

    SelVectors() { reset(); }

    void reset()
    {
        using namespace simdpp;

        for (unsigned i = 0; i < N; ++i) {
            du8[i] =  make_sel_vector<uint8<BE>>(i);
            du16[i] = make_sel_vector<uint16<BE/2>>(i);
            du32[i] = make_sel_vector<uint32<BE/4>>(i);
            du64[i] = make_sel_vector<uint64<BE/8>>(i);
            di8[i] =  make_sel_vector<uint8<BE>>(i);
            di16[i] = make_sel_vector<uint16<BE/2>>(i);
            di32[i] = make_sel_vector<uint32<BE/4>>(i);
            di64[i] = make_sel_vector<uint64<BE/8>>(i);
            df32[i] = make_sel_vector<float32<BE/4>>(i);
            df64[i] = make_sel_vector<float64<BE/8>>(i);
        }
        u8 = du8;
        u16 = du16;
        u32 = du32;
        u64 = du64;
        i8 = di8;
        i16 = di16;
        i32 = di32;
        i64 = di64;
        f32 = df32;
        f64 = df64;
    }
private:
    simdpp::int8<BE> di8[N];
    simdpp::int16<BE/2> di16[N];
    simdpp::int32<BE/4> di32[N];
    simdpp::int64<BE/8> di64[N];
    simdpp::uint8<BE> du8[N];
    simdpp::uint16<BE/2> du16[N];
    simdpp::uint32<BE/4> du32[N];
    simdpp::uint64<BE/8> du64[N];
    simdpp::float32<BE/4> df32[N];
    simdpp::float64<BE/8> df64[N];
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
