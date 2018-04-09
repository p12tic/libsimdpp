/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <numeric>
#include <simdpp/simd.h>
#include <simdpp/algorithm/fill.h>

namespace SIMDPP_ARCH_NAMESPACE {


template<typename T>
struct FillFuzzingTest
{
    FillFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator(42) {}
    void operator()(TestReporter& tr)
    {
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto expected(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generator));
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> output(size);               
                simdpp::fill(output.data(), output.data() + output.size(),(T)42);
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
            {//unaligned input/ouput 
                auto expected(DataGenerator<T, GeneratorConstant<T>>(size, m_generator));
                std::vector<T> output(size);
                simdpp::fill(output.data(), output.data() + output.size(), (T)42);
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorConstant<T> m_generator;
};


template<typename T>
void test_fill_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect = { (T)0,(T)1 };
        vector_t expected = { (T)42,(T)42 };

        fill(ivect.data(), ivect.data() + ivect.size(), (T)42);
        TEST_EQUAL_COLLECTIONS(tr, ivect, expected);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(150, (T)0);
        vector_t expected(150, (T)42);

        fill(ivect.data(), ivect.data() + ivect.size(), (T)42);
        TEST_EQUAL_COLLECTIONS(tr, ivect, expected);
    }
    { //test main loop and epilogue on range
        vector_aligned_t ivect(150, (T)0);
        vector_t expected(150, (T)42);

        fill(ivect.data() + 10u, ivect.data() + ivect.size() - 10u, (T)42);
        for (auto i = 10; i < expected.size() - 10u; ++i) 
        {
            TEST_EQUAL(tr, expected[i], ivect[i]);
        }
    }
    FillFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
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