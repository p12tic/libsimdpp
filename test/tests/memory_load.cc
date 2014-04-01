/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../test_helpers.h"
#include "../test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned vnum>
void test_load_helper(TestCase& tc, void* sv_p)
{
    using E = typename V::element_type;
    auto sdata = reinterpret_cast<E*>(sv_p);

    V rv[vnum];

    auto rzero = [&]()
    {
        for (unsigned i = 0; i < vnum; i++) {
            rv[i] = V::zero();
        }
    };

    // calls constructor that accepts expr_construct
    for (unsigned i = 0; i < vnum; i++) {
        V r = simdpp::load(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = simdpp::load_u(sdata+i);
        TEST_PUSH(tc, V, r);
    }

    // calls operator= that accepts expr_construct
    for (unsigned i = 0; i < vnum; i++) {
        V r;
        r = simdpp::load(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r;
        r = simdpp::load_u(sdata+i);
        TEST_PUSH(tc, V, r);
    }

    // initializes the vector directly
    for (unsigned i = 0; i < vnum; i++) {
        V r = simdpp::load<V>(sdata + i*V::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*V::length; i++) {
        V r = simdpp::load_u<V>(sdata+i);
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

    constexpr unsigned vnum = 4;
    constexpr unsigned size = 32*vnum;

    union {
        uint8_t sdata[size];
        uint8x32 align1;
        float32x8 align2;
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
