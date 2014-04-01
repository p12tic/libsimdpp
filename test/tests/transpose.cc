/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
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
        Vectors<16*8> v;
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
        Vectors<32*8> v;
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
