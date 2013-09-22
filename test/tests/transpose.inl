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

#ifndef LIBSIMDPP_TEST_TESTS_TRANSPOSE_H
#define LIBSIMDPP_TEST_TESTS_TRANSPOSE_H

namespace SIMDPP_ARCH_NAMESPACE {

void test_transpose(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "transpose");

    using namespace simdpp;

    struct Test {
        union {
            uint8_t c[512];
            uint8x16 u8[32];
            uint16x8 u16[32];
            uint32x4 u32[32];
            uint64x2 u64[32];
            float32x4 f32[32];
            float64x2 f64[32];
            uint8x32 du8[16];
            uint16x16 du16[16];
            uint32x8 du32[16];
            uint64x4 du64[16];
            float32x8 df32[16];
            float64x4 df64[16];
        };
    };

    Test t;
    for (unsigned z = 0; z < 512; z++) {
        t.c[z] = z % 256;
    }

    // int8x16
    {
        Test u = t;
        transpose16(u.u8[0], u.u8[1], u.u8[2], u.u8[3],
                    u.u8[4], u.u8[5], u.u8[6], u.u8[7],
                    u.u8[8], u.u8[9], u.u8[10], u.u8[11],
                    u.u8[12], u.u8[13], u.u8[14], u.u8[15]);
        TEST_ARRAY_PUSH(tc, uint8x16, u.u8);

        u = t;
        transpose8(u.u8[0], u.u8[1], u.u8[2], u.u8[3],
                   u.u8[4], u.u8[5], u.u8[6], u.u8[7]);
        TEST_ARRAY_PUSH(tc, uint8x16, u.u8);

        u = t;
        transpose4(u.u8[0], u.u8[1], u.u8[2], u.u8[3]);
        TEST_ARRAY_PUSH(tc, uint8x16, u.u8);
    }

    // int16x8
    {
        Test u = t;
        transpose8(u.u16[0], u.u16[1], u.u16[2], u.u16[3],
                   u.u16[4], u.u16[5], u.u16[6], u.u16[7]);
        TEST_ARRAY_PUSH(tc, uint16x8, u.u16);

        u = t;
        transpose4(u.u16[0], u.u16[1], u.u16[2], u.u16[3]);
        TEST_ARRAY_PUSH(tc, uint16x8, u.u16);

        u = t;
        transpose2(u.u16[0], u.u16[1]);
        TEST_ARRAY_PUSH(tc, uint16x8, u.u16);
    }

    // int32x4
    {
        Test u = t;
        transpose4(u.u32[0], u.u32[1], u.u32[2], u.u32[3]);
        TEST_ARRAY_PUSH(tc, uint32x4, u.u32);

        u = t;
        transpose2(u.u32[0], u.u32[1]);
        TEST_ARRAY_PUSH(tc, uint32x4, u.u32);
    }

    // int64x2
    {
        Test u = t;
        transpose2(u.u64[0], u.u64[1]);
        TEST_ARRAY_PUSH(tc, uint64x2, u.u64);
    }

    // float32x4
    {
        Test u = t;
        transpose4(u.f32[0], u.f32[1], u.f32[2], u.f32[3]);
        TEST_ARRAY_PUSH(tc, float32x4, u.f32);

        u = t;
        transpose2(u.f32[0], u.f32[1]);
        TEST_ARRAY_PUSH(tc, float32x4, u.f32);
    }

    // float64x2
    {
        Test u = t;
        transpose2(u.f64[0], u.f64[1]);
        TEST_ARRAY_PUSH(tc, float64x2, u.f64);
    }


    // int8x32
    {
        Test u = t;
        transpose16(u.du8[0], u.du8[1], u.du8[2], u.du8[3],
                    u.du8[4], u.du8[5], u.du8[6], u.du8[7],
                    u.du8[8], u.du8[9], u.du8[10], u.du8[11],
                    u.du8[12], u.du8[13], u.du8[14], u.du8[15]);
        TEST_ARRAY_PUSH(tc, uint8x32, u.du8);

        u = t;
        transpose8(u.du8[0], u.du8[1], u.du8[2], u.du8[3],
                   u.du8[4], u.du8[5], u.du8[6], u.du8[7]);
        TEST_ARRAY_PUSH(tc, uint8x32, u.du8);

        u = t;
        transpose4(u.du8[0], u.du8[1], u.du8[2], u.du8[3]);
        TEST_ARRAY_PUSH(tc, uint8x32, u.du8);
    }

    // int16x16
    {
        Test u = t;
        transpose8(u.du16[0], u.du16[1], u.du16[2], u.du16[3],
                   u.du16[4], u.du16[5], u.du16[6], u.du16[7]);
        TEST_ARRAY_PUSH(tc, uint16x16, u.du16);

        u = t;
        transpose4(u.du16[0], u.du16[1], u.du16[2], u.du16[3]);
        TEST_ARRAY_PUSH(tc, uint16x16, u.du16);

        u = t;
        transpose2(u.du16[0], u.du16[1]);
        TEST_ARRAY_PUSH(tc, uint16x16, u.du16);
    }

    // int32x8
    {
        Test u = t;
        transpose4(u.du32[0], u.du32[1], u.du32[2], u.du32[3]);
        TEST_ARRAY_PUSH(tc, uint32x8, u.du32);

        u = t;
        transpose2(u.du32[0], u.du32[1]);
        TEST_ARRAY_PUSH(tc, uint32x8, u.du32);
    }

    // int64x4
    {
        Test u = t;
        transpose2(u.du64[0], u.du64[1]);
        TEST_ARRAY_PUSH(tc, uint64x4, u.du64);
    }

    // float32x8
    {
        Test u = t;
        transpose4(u.f32[0], u.f32[1], u.f32[2], u.f32[3]);
        TEST_ARRAY_PUSH(tc, float32x8, u.f32);

        u = t;
        transpose2(u.f32[0], u.f32[1]);
        TEST_ARRAY_PUSH(tc, float32x8, u.f32);
    }

    // float64x4
    {
        Test u = t;
        transpose2(u.df64[0], u.df64[1]);
        TEST_ARRAY_PUSH(tc, float64x4, u.df64);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE

#endif
