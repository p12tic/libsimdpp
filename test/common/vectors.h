/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_COMMON_VECTORS_H
#define SIMDPP_TEST_COMMON_VECTORS_H

#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

/** A class that contains some dummy vectors with test data.

    BE - bytes per vector element
    N - number of vectors
*/
template<unsigned BE, unsigned N>
struct Vectors {

    union {
        uint8_t c[BE*N];
        uint8_t pu8[BE*N];
        uint16_t pu16[BE*N/2];
        uint32_t pu32[BE*N/4];
        uint64_t pu64[BE*N/8];
        int8_t pi8[BE*N];
        int16_t pi16[BE*N/2];
        int32_t pi32[BE*N/4];
        int64_t pi64[BE*N/8];
        float pf32[BE*N/4];
        double pf64[BE*N/8];

        simdpp::uint8<BE> u8[N];
        simdpp::uint16<BE/2> u16[N];
        simdpp::uint32<BE/4> u32[N];
        simdpp::uint64<BE/8> u64[N];
        simdpp::int8<BE> i8[N];
        simdpp::int16<BE/2> i16[N];
        simdpp::int32<BE/4> i32[N];
        simdpp::int64<BE/8> i64[N];
        simdpp::float32<BE/4> f32[N];
        simdpp::float64<BE/8> f64[N];
    };

    Vectors() { reset(); }

    void reset()
    {
        for (unsigned i = 0; i < BE*N; i++) {
            c[i] = i%256;
        }
    }

    void zero()
    {
        for (unsigned i = 0; i < BE*N; i++) {
            c[i] = 0;
        }
    }
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
