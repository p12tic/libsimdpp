/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "../common/masks.h"
#include "../common/vectors.h"
#include "../common/sel_vectors.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned B>
void test_test_utils_n(TestResultsSet& tc)
{
    using namespace simdpp;

    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

    // masks
    Vectors<B,4> v;
    SelVectors<B,4> s;
    Masks<B,4> m;

    for (unsigned i = 0; i < 4; i++) {
        TEST_PUSH(tc, uint8_n,   v.u8[i]);
        TEST_PUSH(tc, uint16_n,  v.u16[i]);
        TEST_PUSH(tc, uint32_n,  v.u32[i]);
        TEST_PUSH(tc, uint64_n,  v.u64[i]);
        TEST_PUSH(tc, float32_n, v.f32[i]);
        TEST_PUSH(tc, float64_n, v.f64[i]);
        TEST_PUSH(tc, uint8_n,   m.u8[i]);
        TEST_PUSH(tc, uint16_n,  m.u16[i]);
        TEST_PUSH(tc, uint32_n,  m.u32[i]);
        TEST_PUSH(tc, uint64_n,  m.u64[i]);
        TEST_PUSH(tc, float32_n, m.f32[i]);
        TEST_PUSH(tc, float64_n, m.f64[i]);
        TEST_PUSH(tc, uint8_n,   s.u8[i]);
        TEST_PUSH(tc, uint16_n,  s.u16[i]);
        TEST_PUSH(tc, uint32_n,  s.u32[i]);
        TEST_PUSH(tc, uint64_n,  s.u64[i]);
        TEST_PUSH(tc, float32_n, s.f32[i]);
        TEST_PUSH(tc, float64_n, s.f64[i]);
    }
}

void test_test_utils(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("test_utils");
    test_test_utils_n<16>(tc);
    test_test_utils_n<32>(tc);
    test_test_utils_n<64>(tc);
}


} // namespace SIMDPP_ARCH_NAMESPACE
