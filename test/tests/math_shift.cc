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

template<class V, unsigned i>
struct Test_shift_l {
    static constexpr unsigned limit = V::num_bits;
    static void test(TestCase& tc, V a)
    {
        V b = simdpp::shift_l<i>(a);
        V c = simdpp::shift_l(a, i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);
    }
};

template<class V, unsigned i>
struct Test_shift_r {
    static constexpr unsigned limit = V::num_bits;
    static void test(TestCase& tc, V a)
    {
        V b = simdpp::shift_r<i>(a);
        V c = simdpp::shift_r(a, i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);
    }
};

void test_math_shift(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "math_shift");

    using namespace simdpp;

    unsigned vnum = 8;
    Vectors<16*16> v;

    // Vectors with 8-bit integer elements
    TemplateTestArrayHelper<Test_shift_l, uint8x32>::run(tc, v.du8, vnum);
    TemplateTestArrayHelper<Test_shift_l, int8x32>::run(tc, v.di8, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint8x32>::run(tc, v.du8, vnum);
    TemplateTestArrayHelper<Test_shift_r, int8x32>::run(tc, v.di8, vnum);

    // Vectors with 16-bit integer elements
    TemplateTestArrayHelper<Test_shift_l, uint16x16>::run(tc, v.du16, vnum);
    TemplateTestArrayHelper<Test_shift_l, int16x16>::run(tc, v.di16, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint16x16>::run(tc, v.du16, vnum);
    TemplateTestArrayHelper<Test_shift_r, int16x16>::run(tc, v.di16, vnum);

    // Vectors with 32-bit integer elements
    TemplateTestArrayHelper<Test_shift_l, uint32x8>::run(tc, v.du32, vnum);
    TemplateTestArrayHelper<Test_shift_l, int32x8>::run(tc, v.di32, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint32x8>::run(tc, v.du32, vnum);
    TemplateTestArrayHelper<Test_shift_r, int32x8>::run(tc, v.di32, vnum);

#if !(SIMDPP_USE_ALTIVEC)
    // Vectors with 64-bit integer elements
    TemplateTestArrayHelper<Test_shift_l, uint64x4>::run(tc, v.du64, vnum);
    TemplateTestArrayHelper<Test_shift_l, int64x4>::run(tc, v.di64, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint64x4>::run(tc, v.du64, vnum);
    TemplateTestArrayHelper<Test_shift_r, int64x4>::run(tc, v.di64, vnum);
#endif
}

} // namespace SIMDPP_ARCH_NAMESPACE
