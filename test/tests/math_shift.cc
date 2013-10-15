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

#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned i>
struct Test_shift_l {
    static constexpr unsigned limit = traits<V>::num_bits;
    static void test(TestCase& tc, V a)
    {
        V b = simdpp::shift_l<i>(a);
        V c = simdpp::shift_l(a,i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);
    }
};

template<class V, unsigned i>
struct Test_shift_r {
    static constexpr unsigned limit = traits<V>::num_bits;
    static void test(TestCase& tc, V a)
    {
        V b = simdpp::shift_r<i>(a);
        V c = simdpp::shift_r(a,i);
        TEST_PUSH(tc, V, b);
        TEST_PUSH(tc, V, c);
    }
};

void test_math_shift(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "math_shift");

    using namespace simdpp;

    unsigned vnum = 16;
    union {
        uint8_t c[256];
        uint8x16 u8[16];
        int8x16 s8[16];
        uint16x8 u16[16];
        int16x8 s16[16];
        uint32x4 u32[16];
        int32x4 s32[16];
        uint64x2 u64[16];
        int64x2 s64[16];
    };

    for (unsigned z = 0; z < 128; z++) {
        c[z] = z*2;
    }
    for (unsigned z = 0; z < 128; z++) {
        c[128+z] = 256-(z*2);
    }

    //int8x16
    TemplateTestArrayHelper<Test_shift_l, uint8x16>::run(tc, u8, vnum);
    TemplateTestArrayHelper<Test_shift_l, int8x16>::run(tc, s8, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint8x16>::run(tc, u8, vnum);
    TemplateTestArrayHelper<Test_shift_r, int8x16>::run(tc, s8, vnum);

    //int16x8
    TemplateTestArrayHelper<Test_shift_l, uint16x8>::run(tc, u16, vnum);
    TemplateTestArrayHelper<Test_shift_l, int16x8>::run(tc, s16, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint16x8>::run(tc, u16, vnum);
    TemplateTestArrayHelper<Test_shift_r, int16x8>::run(tc, s16, vnum);

    // int32x4
    TemplateTestArrayHelper<Test_shift_l, uint32x4>::run(tc, u32, vnum);
    TemplateTestArrayHelper<Test_shift_l, int32x4>::run(tc, s32, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint32x4>::run(tc, u32, vnum);
    TemplateTestArrayHelper<Test_shift_r, int32x4>::run(tc, s32, vnum);

    // int64x2
    TemplateTestArrayHelper<Test_shift_l, uint64x2>::run(tc, u64, vnum);
    TemplateTestArrayHelper<Test_shift_l, int64x2>::run(tc, s64, vnum);
    TemplateTestArrayHelper<Test_shift_r, uint64x2>::run(tc, u64, vnum);
    TemplateTestArrayHelper<Test_shift_r, int64x2>::run(tc, s64, vnum);
}

} // namespace SIMDPP_ARCH_NAMESPACE
