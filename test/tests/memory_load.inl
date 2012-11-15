/*  libsimdpp
    Copyright (C) 2011-2012  p12 tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_TESTS_MEMORY_LOAD_H
#define LIBSIMDPP_TEST_TESTS_MEMORY_LOAD_H

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned vnum>
void test_load_helper(TestCase& tc, void* sv_p)
{
    using E = typename traits<V>::element_type;
    auto sdata = reinterpret_cast<E*>(sv_p);

    V rv[vnum];

    auto rzero = [&]()
    {
        for (unsigned i = 0; i < vnum; i++) {
            rv[i] = V::zero();
        }
    };

    for (unsigned i = 0; i < vnum; i++) {
        V r = load(r, sdata + i*traits<V>::length);
        TEST_PUSH(tc, V, r);
    }

    for (unsigned i = 0; i < (vnum-1)*traits<V>::length; i++) {
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

    constexpr unsigned vnum = 4;
    constexpr unsigned size = 16*vnum;

    union {
        uint8_t sdata[size];
        uint8x16 align;
    };

    for (unsigned i = 0; i < size; i++) {
        sdata[i] = i;
    }

    test_load_helper<uint8x16, 4>(tc, sdata);
    test_load_helper<uint16x8, 4>(tc, sdata);
    test_load_helper<uint32x4, 4>(tc, sdata);
    test_load_helper<uint64x2, 4>(tc, sdata);
    test_load_helper<float32x4, 4>(tc, sdata);
    test_load_helper<float64x2, 4>(tc, sdata);
}

SIMDPP_ARCH_NAMESPACE_END

#endif
