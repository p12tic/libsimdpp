/*  Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

#if (__clang_major__ == 3) && (__clang_minor__ == 5)
// clang 3.5 crashes when compiling lambda in the test
template<class E, class Sum>
class SumClosure {
public:
    SumClosure(Sum& sum) : sum_(sum) {}

    void operator()(E el) { sum_ += (Sum) el; }

private:
    Sum& sum_;
};
#endif

template<class V>
void test_for_each_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using E = typename V::element_type;

    TestData<V> s;
    s.add(make_uint(0, 1, 2, 3));
    s.add(make_uint(0, 0, 0, 0));
    s.add(make_uint(0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));

    for (unsigned i = 0; i < s.size(); ++i) {
        V v = s[i];
        uint64_t sum = 0;
#if (__clang_major__ == 3) && (__clang_minor__ == 5)
        for_each(v, SumClosure<E,uint64_t>(sum));
#else
        for_each(v, [&](E el) { sum += (uint64_t) el; });
#endif
        TEST_PUSH(ts, uint64_t, sum);
    }

    V v1234 = make_uint(1, 2, 3, 4);
    E expected;
    switch (V::length) {
    case 1: expected = 1; break;
    case 2: expected = 3; break;
    case 4: expected = 10; break;
    default:
        expected = 10 * V::length / 4;
    }
    E sum = 0;
#if (__clang_major__ == 3) && (__clang_minor__ == 5)
    for_each(v1234, SumClosure<E, E>(sum));
#else
    for_each(v1234, [&](E el) { sum += (uint64_t) el; });
#endif

    TEST_EQUAL(tr, expected, sum);
}

template<unsigned B>
void test_for_each_n(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;

    using int8_n = uint8<B>;
    using int16_n = uint16<B/2>;
    using int32_n = uint32<B/4>;
    using int64_n = uint64<B/8>;
    using uint8_n = uint8<B>;
    using uint16_n = uint16<B/2>;
    using uint32_n = uint32<B/4>;
    using uint64_n = uint64<B/8>;
    using float32_n = float32<B/4>;
    using float64_n = float64<B/8>;

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
