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
#include <cstring>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned vnum>
void test_store_helper(TestCase& tc, V* sv)
{
    using E = typename V::element_type;

    union {
        E rdata[V::length * vnum];
        V rv[vnum];
    };

    auto rzero = [&]()
    {
        for (unsigned i = 0; i < vnum; i++) {
            rv[i] = V::zero();
        }
    };

    for (unsigned i = 0; i < vnum; i++) {
        rzero();
        store(rdata+i*V::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero();
        stream(rdata+i*V::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero();
        store_first(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero();
        store_last(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    rzero();
    store_packed2(rdata, sv[0], sv[1]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero();
    store_packed3(rdata, sv[0], sv[1], sv[2]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero();
    store_packed4(rdata, sv[0], sv[1], sv[2], sv[3]);
    TEST_ARRAY_PUSH(tc, V, rv);
}

void test_memory_store(TestResults& res)
{
    TestCase& tc = NEW_TEST_CASE(res, "memory_store");

    using namespace simdpp;

    constexpr unsigned vnum = 4;
    constexpr unsigned size = 32*vnum;

    Vectors<size> v;

    // 16-byte vectors
    test_store_helper<uint8x16, 4>(tc, v.u8);
    test_store_helper<uint16x8, 4>(tc, v.u16);
    test_store_helper<uint32x4, 4>(tc, v.u32);
    test_store_helper<uint64x2, 4>(tc, v.u64);
    test_store_helper<float32x4, 4>(tc, v.f32);
    test_store_helper<float64x2, 4>(tc, v.f64);

    // 32-byte vectors
    test_store_helper<uint8x32, 4>(tc, v.du8);
    test_store_helper<uint16x16, 4>(tc, v.du16);
    test_store_helper<uint32x8, 4>(tc, v.du32);
    test_store_helper<uint64x4, 4>(tc, v.du64);
    test_store_helper<float32x8, 4>(tc, v.df32);
    test_store_helper<float64x4, 4>(tc, v.df64);
}

} // namespace SIMDPP_ARCH_NAMESPACE
