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

template<class V, unsigned vnum>
void test_load_helper(TestCase& tc, void* sv_p)
{
    typedef typename V::element_type E;
    auto sdata = reinterpret_cast<E*>(sv_p);

    V rv[vnum];

    auto rzero = [&]()
    {
        for (unsigned i = 0; i < vnum; i++) {
            rv[i] = V::zero();
        }
    };

    for (unsigned i = 0; i < vnum; i++) {
        V r = load(r, sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = load_u(r, sdata+i);
        TEST_PUSH(tc, V, r);
    }

    rzero();
    load_packed2(rv[0], rv[1], sdata);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero();
    load_packed3(rv[0], rv[1], rv[2], sdata);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero();
    load_packed4(rv[0], rv[1], rv[2], rv[3], sdata);
    TEST_ARRAY_PUSH(tc, V, rv);
}


void test_memory_load(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "memory_load");

    using namespace simdpp;

    const unsigned vnum = 4;
    const unsigned size = 32*vnum;

    union {
        uint8_t sdata[size];
        simdpp::detail::align_type align;
    };

    for (unsigned i = 0; i < size; i++) {
        sdata[i] = i;
    }

    // 16-byte vectors
    test_load_helper<uint8x16, 4>(tc, sdata);
    test_load_helper<uint16x8, 4>(tc, sdata);
    test_load_helper<uint32x4, 4>(tc, sdata);
    test_load_helper<uint64x2, 4>(tc, sdata);
    test_load_helper<float32x4, 4>(tc, sdata);
    test_load_helper<float64x2, 4>(tc, sdata);

    // 32-byte vectors
    test_load_helper<uint8x32, 4>(tc, sdata);
    test_load_helper<uint16x16, 4>(tc, sdata);
    test_load_helper<uint32x8, 4>(tc, sdata);
    test_load_helper<uint64x4, 4>(tc, sdata);
    test_load_helper<float32x8, 4>(tc, sdata);
    test_load_helper<float64x4, 4>(tc, sdata);
}

} // namespace SIMDPP_ARCH_NAMESPACE
