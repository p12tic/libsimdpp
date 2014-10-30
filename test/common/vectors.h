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

    // MSVC does not support alignment as a compile-time constant. Use largest
    // needed alignment as a literal.
    SIMDPP_ALIGN(64) uint8_t c[BE*N];
    SIMDPP_ALIGN(64) uint8_t pu8[BE*N];
    SIMDPP_ALIGN(64) uint16_t pu16[BE*N/2];
    SIMDPP_ALIGN(64) uint32_t pu32[BE*N/4];
    SIMDPP_ALIGN(64) uint64_t pu64[BE*N/8];
    SIMDPP_ALIGN(64) int8_t pi8[BE*N];
    SIMDPP_ALIGN(64) int16_t pi16[BE*N/2];
    SIMDPP_ALIGN(64) int32_t pi32[BE*N/4];
    SIMDPP_ALIGN(64) int64_t pi64[BE*N/8];
    SIMDPP_ALIGN(64) float pf32[BE*N/4];
    SIMDPP_ALIGN(64) double pf64[BE*N / 8];

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
        std::memcpy(u8, c, sizeof(u8));
        std::memcpy(u16, c, sizeof(u16));
        std::memcpy(u32, c, sizeof(u32));
        std::memcpy(u64, c, sizeof(u64));
        std::memcpy(i8, c, sizeof(i8));
        std::memcpy(i16, c, sizeof(i16));
        std::memcpy(i32, c, sizeof(i32));
        std::memcpy(i64, c, sizeof(i64));
        std::memcpy(f32, c, sizeof(f32));
        std::memcpy(f64, c, sizeof(f64));
        std::memcpy(pu8, c, sizeof(pu8));
        std::memcpy(pu16, c, sizeof(pu16));
        std::memcpy(pu32, c, sizeof(pu32));
        std::memcpy(pu64, c, sizeof(pu64));
        std::memcpy(pi8, c, sizeof(pi8));
        std::memcpy(pi16, c, sizeof(pi16));
        std::memcpy(pi32, c, sizeof(pi32));
        std::memcpy(pi64, c, sizeof(pi64));
        std::memcpy(pf32, c, sizeof(pf32));
        std::memcpy(pf64, c, sizeof(pf64));
    }

    void zero()
    {
        for (unsigned i = 0; i < BE*N; i++) {
            c[i] = 0;
        }
        broadcast();
    }
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
