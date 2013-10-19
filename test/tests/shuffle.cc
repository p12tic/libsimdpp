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
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

// shuffles within 256-bit vectors are limited to 128-bit halves
template<class V>
struct Shuffle_width {
    static const bool is_256 = (traits<V>::length * traits<V>::num_bits) == 256 ? true : false;
    static const unsigned value = is_256 ? traits<V>::length / 2 : traits<V>::length;
};

template<class V, unsigned i>
struct Test_move_r {
    static const unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::move_r<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_move_l {
    static const unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::move_l<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_broadcast {
    static const unsigned limit = Shuffle_width<V>::value;
    static void test(TestCase& tc, V a)
    {
        a = simdpp::broadcast<i>(a);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_align {
    static const unsigned limit = Shuffle_width<V>::value + 1;
    static void test(TestCase& tc, V a, V b)
    {
        a = simdpp::align<i>(a, b);
        TEST_PUSH(tc, V, a);
    }
};

template<class V, unsigned i>
struct Test_insert_extract {
    static const unsigned limit = traits<V>::length;
    static void test(TestCase& tc, V a, V b)
    {
        a = simdpp::insert<i>(a, simdpp::extract<i>(b));
        TEST_PUSH(tc, V, a);
    }
};

template<class V>
void test_shuffle_type128(TestCase &tc, V v1, V v2)
{
    TEST_PUSH(tc, V, zip_lo(v1, v2));
    TEST_PUSH(tc, V, zip_hi(v1, v2));
    TEST_PUSH(tc, V, unzip_lo(v1, v2));
    TEST_PUSH(tc, V, unzip_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_broadcast, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
    TemplateTestHelper<Test_insert_extract, V>::run(tc, v1, v2);
}

template<class V>
void test_shuffle_type256(TestCase &tc, V v1, V v2)
{
    TEST_PUSH(tc, V, zip_lo(v1, v2));
    TEST_PUSH(tc, V, zip_hi(v1, v2));
    TEST_PUSH(tc, V, unzip_lo(v1, v2));
    TEST_PUSH(tc, V, unzip_hi(v1, v2));

    TemplateTestHelper<Test_move_r, V>::run(tc, v1);
    TemplateTestHelper<Test_move_l, V>::run(tc, v1);
    TemplateTestHelper<Test_broadcast, V>::run(tc, v1);
    TemplateTestHelper<Test_align, V>::run(tc, v1, v2);
}

void test_shuffle(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "shuffle");

    using namespace simdpp;

    union {
        uint8_t c[64];
        uint8x16 u8[4];
        uint16x8 u16[4];
        uint32x4 u32[4];
        uint64x2 u64[4];
        float32x4 f32[4];
        float64x2 f64[4];

        uint8x32 du8[4];
        uint16x16 du16[4];
        uint32x8 du32[4];
        uint64x4 du64[4];
        float32x8 df32[4];
        float64x4 df64[4];
    };

    for (unsigned i = 0; i < 64; i++) {
        c[i] = i;
    }

    // TODO blend

    test_shuffle_type128<uint8x16>(tc, u8[0], u8[1]);
    test_shuffle_type128<uint16x8>(tc, u16[0], u16[1]);
    test_shuffle_type128<uint32x4>(tc, u32[0], u32[1]);
    test_shuffle_type128<uint64x2>(tc, u64[0], u64[1]);
    test_shuffle_type128<float32x4>(tc, f32[0], f32[1]);
    test_shuffle_type128<float64x2>(tc, f64[0], f64[1]);

    test_shuffle_type256<uint8x32>(tc, du8[0], du8[1]);
    test_shuffle_type256<uint16x16>(tc, du16[0], du16[1]);
    test_shuffle_type256<uint32x8>(tc, du32[0], du32[1]);
    test_shuffle_type256<uint64x4>(tc, du64[0], du64[1]);
    test_shuffle_type256<float32x8>(tc, df32[0], df32[1]);
    test_shuffle_type256<float64x4>(tc, df64[0], df64[1]);

    // extract bits
    union {
        uint8_t ec[16];
        uint8x16 eu8;
    };
    for (unsigned el = 0; el < 16; el++) {
        for (auto& ic : ec) {
            ic = 0;
        }
        ec[el] = 0xff;
        TEST_PUSH(tc, uint16_t, extract_bits<>(eu8));
        ec[el] = 1 << 0;
        TEST_PUSH(tc, uint16_t, extract_bits<0>(eu8));
        ec[el] = 1 << 1;
        TEST_PUSH(tc, uint16_t, extract_bits<1>(eu8));
        ec[el] = 1 << 2;
        TEST_PUSH(tc, uint16_t, extract_bits<2>(eu8));
        ec[el] = 1 << 3;
        TEST_PUSH(tc, uint16_t, extract_bits<3>(eu8));
        ec[el] = 1 << 4;
        TEST_PUSH(tc, uint16_t, extract_bits<4>(eu8));
        ec[el] = 1 << 5;
        TEST_PUSH(tc, uint16_t, extract_bits<5>(eu8));
        ec[el] = 1 << 6;
        TEST_PUSH(tc, uint16_t, extract_bits<6>(eu8));
        ec[el] = 1 << 7;
        TEST_PUSH(tc, uint16_t, extract_bits<7>(eu8));
    }

}

} // namespace SIMDPP_ARCH_NAMESPACE
