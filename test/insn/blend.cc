/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/vectors.h"
#include "../common/sel_vectors.h"
#include "../common/masks.h"
#include <simdpp/simd.h>
#include <simdpp/detail/align_v128.h>
#include <vector>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned N>
void test_blend_n(TestResultsSet& tc)
{
    using namespace simdpp;

    Vectors<N,4> v;
    Masks<N,4> m;
    SelVectors<N,4> s;

    // this tests correctness, no need to test all combinations
    for (unsigned i = 0; i < 4; ++i) {
        TEST_PUSH(tc, uint8<N>, blend(m.u8[0], m.u8[1], m.u8[i]));
        TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.u8[i]));
        TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.u8[i]));
        TEST_PUSH(tc, uint16<N/2>, blend(m.u16[0], m.u16[1], m.u16[i]));
        TEST_PUSH(tc, uint16<N/2>, blend(v.u16[0], v.u16[1], s.u16[i]));
        TEST_PUSH(tc, uint16<N/2>, blend(v.u16[0], v.u16[1], m.u16[i]));
        TEST_PUSH(tc, uint32<N/4>, blend(m.u32[0], m.u32[1], m.u32[i]));
        TEST_PUSH(tc, uint32<N/4>, blend(v.u32[0], v.u32[1], s.u32[i]));
        TEST_PUSH(tc, uint32<N/4>, blend(v.u32[0], v.u32[1], m.u32[i]));
        TEST_PUSH(tc, uint64<N/8>, blend(m.u64[0], m.u64[1], m.u64[i]));
        TEST_PUSH(tc, uint64<N/8>, blend(v.u64[0], v.u64[1], s.u64[i]));
        TEST_PUSH(tc, uint64<N/8>, blend(v.u64[0], v.u64[1], m.u64[i]));
        TEST_PUSH(tc, float32<N/4>, blend(m.f32[0], m.f32[1], m.f32[i]));
        TEST_PUSH(tc, float32<N/4>, blend(v.f32[0], v.f32[1], s.f32[i]));
        TEST_PUSH(tc, float32<N/4>, blend(v.f32[0], v.f32[1], m.f32[i]));
        TEST_PUSH(tc, float64<N/8>, blend(m.f64[0], m.f64[1], m.f64[i]));
        TEST_PUSH(tc, float64<N/8>, blend(v.f64[0], v.f64[1], s.f64[i]));
        TEST_PUSH(tc, float64<N/8>, blend(v.f64[0], v.f64[1], m.f64[i]));
    }
    // the following tests whether we can compile and run the combinations of
    // arguments we advertise to support (i.e. all combinations :-) ). There are
    // 16*16*16 = 4096 combinations in total so we only test specific patterns
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.i8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.i16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.i32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.i64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], s.f64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u8[0], v.u8[1], m.f64[0]));

    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.i8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], m.u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.i16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], m.u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.i32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], m.u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.i64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], m.u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], m.f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], s.f64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.u16[0], v.i32[1], m.f64[0]));

    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.i8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], m.u8[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.i16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], m.u16[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.i32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], m.u32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.i64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], m.u64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], m.f32[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], s.f64[0]));
    TEST_PUSH(tc, uint8<N>, blend(v.f64[0], v.i32[1], m.f64[0]));

    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.u8[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.i8[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], m.u8[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.u16[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.i16[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], m.u16[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.u32[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.i32[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], m.u32[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.u64[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.i64[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], m.u64[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.f32[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], m.f32[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], v.f64[1], s.u64[1]));
    TEST_PUSH(tc, uint8<N>, blend(v.u64[0], m.f64[1], s.u64[1]));
}

void test_blend(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("blend");
    test_blend_n<16>(tc);
    test_blend_n<32>(tc);
    test_blend_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
