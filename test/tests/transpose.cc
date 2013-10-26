/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#include "../test_helpers.h"
#include "../test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

void test_transpose(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "transpose");

    using namespace simdpp;

    // int8x16
    {
        Vectors<16*16> v;
        transpose16(v.u8[0], v.u8[1], v.u8[2], v.u8[3],
                    v.u8[4], v.u8[5], v.u8[6], v.u8[7],
                    v.u8[8], v.u8[9], v.u8[10], v.u8[11],
                    v.u8[12], v.u8[13], v.u8[14], v.u8[15]);
        TEST_ARRAY_PUSH(tc, uint8x16, v.u8);

        v.reset();
        transpose8(v.u8[0], v.u8[1], v.u8[2], v.u8[3],
                   v.u8[4], v.u8[5], v.u8[6], v.u8[7]);
        TEST_ARRAY_PUSH(tc, uint8x16, v.u8);

        v.reset();
        transpose4(v.u8[0], v.u8[1], v.u8[2], v.u8[3]);
        TEST_ARRAY_PUSH(tc, uint8x16, v.u8);
    }

    // int16x8
    {
        Vectors<16*8> v;
        transpose8(v.u16[0], v.u16[1], v.u16[2], v.u16[3],
                   v.u16[4], v.u16[5], v.u16[6], v.u16[7]);
        TEST_ARRAY_PUSH(tc, uint16x8, v.u16);

        v.reset();
        transpose4(v.u16[0], v.u16[1], v.u16[2], v.u16[3]);
        TEST_ARRAY_PUSH(tc, uint16x8, v.u16);

        v.reset();
        transpose2(v.u16[0], v.u16[1]);
        TEST_ARRAY_PUSH(tc, uint16x8, v.u16);
    }

    // int32x4
    {
        Vectors<16*4> v;
        transpose4(v.u32[0], v.u32[1], v.u32[2], v.u32[3]);
        TEST_ARRAY_PUSH(tc, uint32x4, v.u32);

        v.reset();
        transpose2(v.u32[0], v.u32[1]);
        TEST_ARRAY_PUSH(tc, uint32x4, v.u32);
    }

    // int64x2
    {
        Vectors<16*2> v;
        transpose2(v.u64[0], v.u64[1]);
        TEST_ARRAY_PUSH(tc, uint64x2, v.u64);
    }

    // float32x4
    {
        Vectors<16*4> v;
        transpose4(v.f32[0], v.f32[1], v.f32[2], v.f32[3]);
        TEST_ARRAY_PUSH(tc, float32x4, v.f32);

        v.reset();
        transpose2(v.f32[0], v.f32[1]);
        TEST_ARRAY_PUSH(tc, float32x4, v.f32);
    }

    // float64x2
    {
        Vectors<16*2> v;
        transpose2(v.f64[0], v.f64[1]);
        TEST_ARRAY_PUSH(tc, float64x2, v.f64);
    }


    // int8x32
    {
        Vectors<32*16> v;
        transpose16(v.du8[0], v.du8[1], v.du8[2], v.du8[3],
                    v.du8[4], v.du8[5], v.du8[6], v.du8[7],
                    v.du8[8], v.du8[9], v.du8[10], v.du8[11],
                    v.du8[12], v.du8[13], v.du8[14], v.du8[15]);
        TEST_ARRAY_PUSH(tc, uint8x32, v.du8);

        v.reset();
        transpose8(v.du8[0], v.du8[1], v.du8[2], v.du8[3],
                   v.du8[4], v.du8[5], v.du8[6], v.du8[7]);
        TEST_ARRAY_PUSH(tc, uint8x32, v.du8);

        v.reset();
        transpose4(v.du8[0], v.du8[1], v.du8[2], v.du8[3]);
        TEST_ARRAY_PUSH(tc, uint8x32, v.du8);
    }

    // int16x16
    {
        Vectors<32*8> v;
        transpose8(v.du16[0], v.du16[1], v.du16[2], v.du16[3],
                   v.du16[4], v.du16[5], v.du16[6], v.du16[7]);
        TEST_ARRAY_PUSH(tc, uint16x16, v.du16);

        v.reset();
        transpose4(v.du16[0], v.du16[1], v.du16[2], v.du16[3]);
        TEST_ARRAY_PUSH(tc, uint16x16, v.du16);

        v.reset();
        transpose2(v.du16[0], v.du16[1]);
        TEST_ARRAY_PUSH(tc, uint16x16, v.du16);
    }

    // int32x8
    {
        Vectors<32*4> v;
        transpose4(v.du32[0], v.du32[1], v.du32[2], v.du32[3]);
        TEST_ARRAY_PUSH(tc, uint32x8, v.du32);

        v.reset();
        transpose2(v.du32[0], v.du32[1]);
        TEST_ARRAY_PUSH(tc, uint32x8, v.du32);
    }

    // int64x4
    {
        Vectors<32*2> v;
        transpose2(v.du64[0], v.du64[1]);
        TEST_ARRAY_PUSH(tc, uint64x4, v.du64);
    }

    // float32x8
    {
        Vectors<32*4> v;
        transpose4(v.f32[0], v.f32[1], v.f32[2], v.f32[3]);
        TEST_ARRAY_PUSH(tc, float32x8, v.df32);

        v.reset();
        transpose2(v.f32[0], v.f32[1]);
        TEST_ARRAY_PUSH(tc, float32x8, v.df32);
    }

    // float64x4
    {
        Vectors<32*2> v;
        transpose2(v.df64[0], v.df64[1]);
        TEST_ARRAY_PUSH(tc, float64x4, v.df64);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
