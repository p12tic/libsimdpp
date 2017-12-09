/*  Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<class E, class Sum>
class SumClosure {
public:
    SumClosure(Sum& sum) : sum_(sum) {}

    void operator()(E el) { sum_ += (Sum) el; }

private:
    Sum& sum_;
};

template<class V>
void test_for_each_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    typedef typename V::element_type E;

    TestData<V> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0, 0, 0, 0));
    s.add(make_uint(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));

    for (unsigned i = 0; i < s.size(); ++i) {
        V v = s[i];
        uint64_t sum = 0;
        for_each(v, SumClosure<E,uint64_t>(sum));
        TEST_PUSH(ts, uint64_t, sum);
    }

    V v1234 = make_uint(1, 2, 3, 4);
    uint64_t expected;
    switch (V::length) {
    case 1: expected = 1; break;
    case 2: expected = 3; break;
    case 4: expected = 10; break;
    default:
        expected = 10 * V::length / 4;
    }
    E sum = 0;
    for_each(v1234, SumClosure<E, E>(sum));

    TEST_EQUAL(tr, expected, (uint64_t)sum);
}

template<unsigned B>
void test_for_each_n(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;

    typedef uint8<B> int8_n;
    typedef uint16<B/2> int16_n;
    typedef uint32<B/4> int32_n;
    typedef uint64<B/8> int64_n;
    typedef uint8<B> uint8_n;
    typedef uint16<B/2> uint16_n;
    typedef uint32<B/4> uint32_n;
    typedef uint64<B/8> uint64_n;
    typedef float32<B/4> float32_n;
    typedef float64<B/8> float64_n;

    test_for_each_type<int8_n>(ts, tr);
    test_for_each_type<int16_n>(ts, tr);
    test_for_each_type<int32_n>(ts, tr);
    test_for_each_type<int64_n>(ts, tr);
    test_for_each_type<uint8_n>(ts, tr);
    test_for_each_type<uint16_n>(ts, tr);
    test_for_each_type<uint32_n>(ts, tr);
    test_for_each_type<uint64_n>(ts, tr);
    test_for_each_type<float32_n>(ts, tr);
    test_for_each_type<float64_n>(ts, tr);
}

void test_for_each(TestResults& res, TestReporter& tr)
{
    TestResultsSet& ts = res.new_results_set("foreach");
    test_for_each_n<16>(ts, tr);
    test_for_each_n<32>(ts, tr);
    test_for_each_n<64>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
