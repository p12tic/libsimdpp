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

void test_math_fp(TestResults& res)
{
    // TODO sqrt_e sqrt_rh rcp_e rcp_rh

    TestCase& tc = NEW_TEST_CASE(res, "math_fp");

    using namespace simdpp;

    float nanf = std::numeric_limits<float>::quiet_NaN();
    double nan = std::numeric_limits<double>::quiet_NaN();
    float inff = std::numeric_limits<float>::infinity();
    double inf = std::numeric_limits<double>::infinity();

    // Vectors with 32-bit floating-point elements
    {
        float32x8 s[] = {
            (float32<8>) make_float(0.0f, -0.0f, 0.0f, -0.0f),
            (float32<8>) make_float(1.0f, 2.0f, 3.0f, 4.0f),
            (float32<8>) make_float(-1.0f, -2.0f, -3.0f, -4.0f),
            (float32<8>) make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            (float32<8>) make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            (float32<8>) make_float(nanf, nanf, nanf, nanf),
            (float32<8>) make_float(inff, inff, inff, inff),
            (float32<8>) make_float(-inff, -inff, -inff, -inff),
        };

        TEST_ALL_COMB_HELPER2(tc, float32x8, add, s, 4);
        TEST_ALL_COMB_HELPER2(tc, float32x8, sub, s, 4);
        TEST_ALL_COMB_HELPER2(tc, float32x8, mul, s, 4);
        tc.set_precision(1);
        TEST_ALL_COMB_HELPER2(tc, float32x8, div, s, 4);
        tc.unset_precision();

        TEST_ARRAY_HELPER1(tc, float32x8, abs, s);
        TEST_ARRAY_HELPER1(tc, float32x8, sign, s);
        TEST_ARRAY_HELPER1(tc, float32x8, neg, s);

#if SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4
        TEST_ALL_COMB_HELPER16X2_3(tc, float32x8, fmadd, s, 4);
        TEST_ALL_COMB_HELPER16X2_3(tc, float32x8, fmsub, s, 4);
#endif
        float32x8 snan[] = {
            (float32<8>) make_float(1.0f, 2.0f, 3.0f, 4.0f),
            (float32<8>) make_float(-1.0f, -2.0f, -3.0f, -4.0f),
            (float32<8>) make_float(67500000.0f, 67500001.0f, 67500002.0f, 67500003.0f),
            (float32<8>) make_float(-67500000.0f, -67500001.0f, -67500002.0f, -67500003.0f),
            (float32<8>) make_float(inff, inff, inff, inff),
            (float32<8>) make_float(-inff, -inff, -inff, -inff),
        };
        TEST_ALL_COMB_HELPER2(tc, float32x8, min, snan, 4);
        TEST_ALL_COMB_HELPER2(tc, float32x8, max, snan, 4);


    }

    // Vectors with 64-bit floating-point elements
    {
        float64x4 s[] = {
            (float64<4>) make_float(0.0, -0.0),
            (float64<4>) make_float(1.0, 2.0),
            (float64<4>) make_float(3.0, 4.0),
            (float64<4>) make_float(-1.0, -2.0),
            (float64<4>) make_float(-3.0, -4.0),
            (float64<4>) make_float(63100000000000000.0, 63100000000000004.0),
            (float64<4>) make_float(63100000000000008.0, 63100000000000012.0),
            (float64<4>) make_float(-63100000000000000.0, -63100000000000004.0),
            (float64<4>) make_float(-63100000000000008.0, -63100000000000012.0),
            (float64<4>) make_float(nan, nan),
            (float64<4>) make_float(inf, inf),
            (float64<4>) make_float(-inf, -inf),
        };

        TEST_ALL_COMB_HELPER2(tc, float64x4, add, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64x4, sub, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64x4, mul, s, 8);
        TEST_ALL_COMB_HELPER2(tc, float64x4, div, s, 8);

        TEST_ARRAY_HELPER1(tc, float64x4, abs, s);
        TEST_ARRAY_HELPER1(tc, float64x4, sign, s);
        TEST_ARRAY_HELPER1(tc, float64x4, neg, s);

#if SIMDPP_USE_FMA3 || SIMDPP_USE_FMA4
        TEST_ALL_COMB_HELPER16X2_3(tc, float64x4, fmadd, s, 8);
        TEST_ALL_COMB_HELPER16X2_3(tc, float64x4, fmsub, s, 8);
#endif

        float64x4 snan[] = {
            (float64<4>) make_float(1.0, 2.0),
            (float64<4>) make_float(3.0, 4.0),
            (float64<4>) make_float(-1.0, -2.0),
            (float64<4>) make_float(-3.0, -4.0),
            (float64<4>) make_float(63100000000000000.0, 63100000000000004.0),
            (float64<4>) make_float(63100000000000008.0, 63100000000000012.0),
            (float64<4>) make_float(-63100000000000000.0, -63100000000000004.0),
            (float64<4>) make_float(-63100000000000008.0, -63100000000000012.0),
            (float64<4>) make_float(inf, inf),
            (float64<4>) make_float(-inf, -inf),
        };
        TEST_ALL_COMB_HELPER2(tc, float64x4, min, snan, 8);
        TEST_ALL_COMB_HELPER2(tc, float64x4, max, snan, 8);
    }
}

} // namespace SIMDPP_ARCH_NAMESPACE
