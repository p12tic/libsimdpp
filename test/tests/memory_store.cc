/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
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

    auto rzero = [&](V* r)
    {
        for (unsigned i = 0; i < vnum; i++) {
            r[i] = V::zero();
        }
    };

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        store(rdata+i*V::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    for (unsigned i = 0; i < vnum; i++) {
        rzero(rv);
        stream(rdata+i*V::length, sv[0]);
        TEST_ARRAY_PUSH(tc, V, rv);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv);
        store_first(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    tc.reset_seq();
    for (unsigned i = 0; i < V::length; i++) {
        rzero(rv);
        store_last(rdata, sv[0], i);
        TEST_PUSH(tc, V, rv[0]);
    }

    rzero(rv);
    store_packed2(rdata, sv[0], sv[1]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero(rv);
    store_packed3(rdata, sv[0], sv[1], sv[2]);
    TEST_ARRAY_PUSH(tc, V, rv);

    rzero(rv);
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
