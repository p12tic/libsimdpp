/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <numeric>
#include <simdpp/simd.h>


namespace SIMDPP_ARCH_NAMESPACE {

    template<typename T>
    void test_fill_type(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
        { //test prologue
            vector_t ivect = { (T)0,(T)1 };
            vector_t expected = { (T)42,(T)42 };

            fill(ivect.data(), ivect.data() + ivect.size(), (T)42);
            for (auto i = 0; i < expected.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
            {
                TEST_EQUAL(tr, expected[i], ivect[i]);
            }
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(150, (T)0);
            vector_t expected(150, (T)42);

            fill(ivect.data(), ivect.data() + ivect.size(), (T)42);
            for (auto i = 0; i < expected.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
            {
                TEST_EQUAL(tr, expected[i], ivect[i]);
            }
        }
        { //test main loop and epilogue on range
            vector_aligned_t ivect(150, (T)0);
            vector_t expected(150, (T)42);

            fill(ivect.data() + 10u, ivect.data() + ivect.size() - 10u, (T)42);
            for (auto i = 10; i < expected.size() - 10u; ++i) //TODO make TEST_EQUAL_COLECTIONS
            {
                TEST_EQUAL(tr, expected[i], ivect[i]);
            }
        }
    }

    void test_fill(TestResults& res, TestReporter& tr)
    {
        using namespace simdpp;
        TestResultsSet& ts = res.new_results_set("fill");
        test_fill_type<double>(ts, tr);
        test_fill_type<float>(ts, tr);
        test_fill_type<uint64_t>(ts, tr);
        test_fill_type<int64_t>(ts, tr);
        test_fill_type<uint32_t>(ts, tr);
        test_fill_type<int32_t>(ts, tr);
        test_fill_type<uint16_t>(ts, tr);
        test_fill_type<int16_t>(ts, tr);
        test_fill_type<uint8_t>(ts, tr);
        test_fill_type<int8_t>(ts, tr);
    }

} // namespace SIMDPP_ARCH_NAMESPACE