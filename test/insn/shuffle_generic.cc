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

template<class V, unsigned i>
struct Test_shuffle21 {
    static const unsigned limit = 4;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const unsigned s0 = i / 2 % 2;
        const unsigned s1 = i % 2;

        V r = simdpp::shuffle1<s0,s1>(a, b);
        TEST_PUSH(tc, V, r);
    }
};

template<class V, unsigned i>
struct Test_shuffle42 {
    static const unsigned limit = 256;
    static void test(TestResultsSet& tc, const V& a, const V& b)
    {
        const unsigned s0 = i / 64 % 4;
        const unsigned s1 = i / 16 % 4;
        const unsigned s2 = i / 4 % 4;
        const unsigned s3 = i % 4;

        V r = simdpp::shuffle2<s0,s1,s2,s3>(a, b);
        TEST_PUSH(tc, V, r);
    }
};

template<unsigned B>
void test_shuffle_generic_n(TestResultsSet& tc)
{
    using namespace simdpp;

    Vectors<B,2> v;

    // int32
    TemplateTestHelper<Test_shuffle42, uint32<B/4>>::run(tc, v.u32[0], v.u32[1]);

    // int64
    TemplateTestHelper<Test_shuffle21, uint64<B/8>>::run(tc, v.u64[0], v.u64[1]);

    // float32
    TemplateTestHelper<Test_shuffle42, float32<B/4>>::run(tc, v.f32[0], v.f32[1]);

    // float64
    TemplateTestHelper<Test_shuffle21, float64<B/8>>::run(tc, v.f64[0], v.f64[1]);
}

void test_shuffle_generic(TestResults& res)
{
    TestResultsSet& tc = res.new_results_set("shuffle_generic");

    test_shuffle_generic_n<16>(tc);
    test_shuffle_generic_n<32>(tc);
    test_shuffle_generic_n<64>(tc);
}

} // namespace SIMDPP_ARCH_NAMESPACE
