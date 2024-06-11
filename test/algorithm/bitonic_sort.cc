/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/simd.h>
#include <simdpp/algorithm/bitonic_sort.h>
#include "../insn/tests.h"
#include "../utils/test_helpers.h"
#include <algorithm>
#include <array>
#include <random>

namespace SIMDPP_ARCH_NAMESPACE {

template<class V, unsigned N, bool Ascending>
struct TestDataPreparer
{
    using E = typename V::element_type;

    TestDataPreparer()
    {
        for (std::uint32_t i = 0; i < data.size(); ++i)
        {
            data[i] = static_cast<E>(i);
        }
        expected_data = data;
        std::sort(expected_data.begin(), expected_data.end(), [](auto l, auto r)
        {
            if (Ascending) {
                return l < r;
            } else {
                return l > r;
            };
        });
    }

    void next()
    {
        std::shuffle(data.begin(), data.end(), rng);
    }

    std::minstd_rand rng = std::minstd_rand{123};
    std::array<E, N> data;
    std::array<E, N> expected_data;
};

template<class V, bool Ascending>
void test_bitonic_sort_impl1_v(TestReporter& tr)
{
    TestDataPreparer<V, 8, Ascending> data_preparer;

    for (std::uint32_t i = 0; i < 1000; ++i)
    {
        data_preparer.next();

        V sorted = simdpp::load_u(&data_preparer.data[0]);
        if (Ascending) {
            simdpp::bitonic_sort_asc(sorted);
        } else {
            simdpp::bitonic_sort_dec(sorted);
        }
        V expected = simdpp::load_u(&data_preparer.expected_data[0]);
        TEST_EQUAL(tr, sorted, expected);
    }
}

template<class V, bool Ascending>
void test_bitonic_sort_impl2_v(TestReporter& tr)
{
    TestDataPreparer<V, 16, Ascending> data_preparer;

    for (std::uint32_t i = 0; i < 1000; ++i)
    {
        data_preparer.next();

        V sorted1 = simdpp::load_u(&data_preparer.data[0]);
        V sorted2 = simdpp::load_u(&data_preparer.data[8]);
        if (Ascending) {
            simdpp::bitonic_sort_asc(sorted1, sorted2);
        } else {
            simdpp::bitonic_sort_dec(sorted1, sorted2);
        }
        V expected1 = simdpp::load_u(&data_preparer.expected_data[0]);
        V expected2 = simdpp::load_u(&data_preparer.expected_data[8]);
        TEST_EQUAL(tr, sorted1, expected1);
        TEST_EQUAL(tr, sorted2, expected2);
    }
}

void test_algorithm_bitonic_sort(TestReporter& tr)
{
    test_bitonic_sort_impl1_v<simdpp::float32<8>, true>(tr);
    test_bitonic_sort_impl1_v<simdpp::uint32<8>, true>(tr);
    test_bitonic_sort_impl1_v<simdpp::int32<8>, true>(tr);
    test_bitonic_sort_impl1_v<simdpp::float32<8>, false>(tr);
    test_bitonic_sort_impl1_v<simdpp::uint32<8>, false>(tr);
    test_bitonic_sort_impl1_v<simdpp::int32<8>, false>(tr);
    test_bitonic_sort_impl2_v<simdpp::float32<8>, true>(tr);
    test_bitonic_sort_impl2_v<simdpp::uint32<8>, true>(tr);
    test_bitonic_sort_impl2_v<simdpp::int32<8>, true>(tr);
    test_bitonic_sort_impl2_v<simdpp::float32<8>, false>(tr);
    test_bitonic_sort_impl2_v<simdpp::uint32<8>, false>(tr);
    test_bitonic_sort_impl2_v<simdpp::int32<8>, false>(tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
