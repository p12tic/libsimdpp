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

    uint8_t* volatile pu8;
    uint16_t* volatile pu16;
    uint32_t* volatile pu32;
    uint64_t* volatile pu64;
    int8_t* volatile pi8;
    int16_t* volatile pi16;
    int32_t* volatile pi32;
    int64_t* volatile pi64;
    float* volatile pf32;
    double* volatile pf64;

    simdpp::uint8<BE>* volatile u8;
    simdpp::uint16<BE/2>* volatile u16;
    simdpp::uint32<BE/4>* volatile u32;
    simdpp::uint64<BE/8>* volatile u64;
    simdpp::int8<BE>* volatile i8;
    simdpp::int16<BE/2>* volatile i16;
    simdpp::int32<BE/4>* volatile i32;
    simdpp::int64<BE/8>* volatile i64;
    simdpp::float32<BE/4>* volatile f32;
    simdpp::float64<BE/8>* volatile f64;

    Vectors() { reset(); }

    void reset()
    {
        for (unsigned i = 0; i < BE*N; i++) {
            c[i] = i%256;
        }
        broadcast();
    }

    void broadcast()
    {
        pu8 = reinterpret_cast<uint8_t*>(c);
        pu16 = reinterpret_cast<uint16_t*>(c);
        pu32 = reinterpret_cast<uint32_t*>(c);
        pu64 = reinterpret_cast<uint64_t*>(c);
        pi8 = reinterpret_cast<int8_t*>(c);
        pi16 = reinterpret_cast<int16_t*>(c);
        pi32 = reinterpret_cast<int32_t*>(c);
        pi64 = reinterpret_cast<int64_t*>(c);
        pf32 = reinterpret_cast<float*>(c);
        pf64 = reinterpret_cast<double*>(c);

        u8 = reinterpret_cast<simdpp::uint8<BE>*>(c);
        u16 = reinterpret_cast<simdpp::uint16<BE/2>*>(c);
        u32 = reinterpret_cast<simdpp::uint32<BE/4>*>(c);
        u64 = reinterpret_cast<simdpp::uint64<BE/8>*>(c);
        i8 = reinterpret_cast<simdpp::int8<BE>*>(c);
        i16 = reinterpret_cast<simdpp::int16<BE/2>*>(c);
        i32 = reinterpret_cast<simdpp::int32<BE/4>*>(c);
        i64 = reinterpret_cast<simdpp::int64<BE/8>*>(c);
        f32 = reinterpret_cast<simdpp::float32<BE/4>*>(c);
        f64 = reinterpret_cast<simdpp::float64<BE/8>*>(c);
    }

    void zero()
    {
        for (unsigned i = 0; i < BE*N; i++) {
            c[i] = 0;
        }
        broadcast();
    }
private:
    SIMDPP_ALIGN(64) uint8_t c[BE*N];
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
