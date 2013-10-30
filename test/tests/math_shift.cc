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

template<class V, unsigned i>
struct Test_shift_l {
    static const unsigned limit = V::num_bits;
    static void test(TestCase& tc, V a)
    {
        V b = simdpp::shift_l<i>(a);
        V c = simdpp::shift_l(a, i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);

        typedef typename V::half_vector_type H;
        H ah = tst_ext_half(a);
        H bh = simdpp::shift_l<i>(ah);
        H ch = simdpp::shift_l(ah, i);
        TEST_PUSH(tc, H, bh);
        TEST_PUSH(tc, H, ch);
    }
};

template<class V, unsigned i>
struct Test_shift_r {
    static const unsigned limit = V::num_bits;
    static void test(TestCase& tc, V a)
    {
        V b = simdpp::shift_r<i>(a);
        V c = simdpp::shift_r(a, i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);

        typedef typename V::half_vector_type H;
        H ah = tst_ext_half(a);
        H bh = simdpp::shift_r<i>(ah);
        H ch = simdpp::shift_r(ah, i);
        TEST_PUSH(tc, H, bh);
        TEST_PUSH(tc, H, ch);
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
