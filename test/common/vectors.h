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

#ifndef SIMDPP_TEST_COMMON_VECTORS_H
#define SIMDPP_TEST_COMMON_VECTORS_H

#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

// note: all data is read only
template<unsigned L>
struct Vectors {
    static const unsigned length = L;

    union {
        uint8_t c[L];
        uint8_t pu8[L];
        uint16_t pu16[L/2];
        uint32_t pu32[L/4];
        uint64_t pu64[L/8];
        int8_t pi8[L];
        int16_t pi16[L/2];
        int32_t pi32[L/4];
        int64_t pi64[L/8];
        float pf32[L/4];
        double pf64[L/8];

        simdpp::detail::align_type align;
    };

    simdpp::uint8x16 u8[L/16];
    simdpp::uint16x8 u16[L/16];
    simdpp::uint32x4 u32[L/16];
    simdpp::uint64x2 u64[L/16];
    simdpp::int8x16 i8[L/16];
    simdpp::int16x8 i16[L/16];
    simdpp::int32x4 i32[L/16];
    simdpp::int64x2 i64[L/16];
    simdpp::float32x4 f32[L/16];
    simdpp::float64x2 f64[L/16];
    simdpp::uint8x32 du8[L/32];
    simdpp::uint16x16 du16[L/32];
    simdpp::uint32x8 du32[L/32];
    simdpp::uint64x4 du64[L/32];
    simdpp::int8x32 di8[L/32];
    simdpp::int16x16 di16[L/32];
    simdpp::int32x8 di32[L/32];
    simdpp::int64x4 di64[L/32];
    simdpp::float32x8 df32[L/32];
    simdpp::float64x4 df64[L/32];


    Vectors() { reset(); }

    void reset()
    {
        for (unsigned i = 0; i < L; i++) {
            c[i] = i%256;
        }
        broadcast();
    }

    void zero()
    {
        for (unsigned i = 0; i < L; i++) {
            c[i] = 0;
        }
    }
private:
    void broadcast()
    {
        std::memcpy(u8, c, L);
        std::memcpy(u8, c, L);
        std::memcpy(u16, c, L);
        std::memcpy(u32, c, L);
        std::memcpy(u64, c, L);
        std::memcpy(i8, c, L);
        std::memcpy(i16, c, L);
        std::memcpy(i32, c, L);
        std::memcpy(i64, c, L);
        std::memcpy(f32, c, L);
        std::memcpy(f64, c, L);
        std::memcpy(du8, c, L);
        std::memcpy(du16, c, L);
        std::memcpy(du32, c, L);
        std::memcpy(du64, c, L);
        std::memcpy(di8, c, L);
        std::memcpy(di16, c, L);
        std::memcpy(di32, c, L);
        std::memcpy(di64, c, L);
        std::memcpy(df32, c, L);
        std::memcpy(df64, c, L);
    }
};

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
