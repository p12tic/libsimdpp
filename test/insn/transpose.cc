/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned B>
void test_transpose_n(TestResultsSet& tc)
{
    using namespace simdpp;
    Vectors<B,8> v;

    // int8x16
    transpose4(v.u8[0], v.u8[1], v.u8[2], v.u8[3]);
    TEST_PUSH_ARRAY(tc, uint8<B>, v.u8);
    v.reset();

    // int16
    transpose4(v.u16[0], v.u16[1], v.u16[2], v.u16[3]);
    TEST_PUSH_ARRAY(tc, uint16<B/2>, v.u16);
    v.reset();

    transpose2(v.u16[0], v.u16[1]);
    TEST_PUSH_ARRAY(tc, uint16<B/2>, v.u16);
    v.reset();

    // int32
    transpose4(v.u32[0], v.u32[1], v.u32[2], v.u32[3]);
    TEST_PUSH_ARRAY(tc, uint32<B/4>, v.u32);
    v.reset();

    transpose2(v.u32[0], v.u32[1]);
    TEST_PUSH_ARRAY(tc, uint32<B/4>, v.u32);
    v.reset();

    // int64
    transpose2(v.u64[0], v.u64[1]);
    TEST_PUSH_ARRAY(tc, uint64<B/8>, v.u64);
    v.reset();

    // float32
    transpose4(v.f32[0], v.f32[1], v.f32[2], v.f32[3]);
    TEST_PUSH_ARRAY(tc, float32<B/4>, v.f32);
    v.reset();

    transpose2(v.f32[0], v.f32[1]);
    TEST_PUSH_ARRAY(tc, float32<B/4>, v.f32);
    v.reset();

    // float64
    transpose2(v.f64[0], v.f64[1]);
    TEST_PUSH_ARRAY(tc, float64<B/8>, v.f64);
    v.reset();
}

void test_transpose(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("transpose");
    test_transpose_n<16>(tc);
    test_transpose_n<32>(tc);
    test_transpose_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
