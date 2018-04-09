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
//algorithm
#include <simdpp/algorithm/copy.h>
#include <algorithm>

namespace SIMDPP_ARCH_NAMESPACE {


template<typename T>
struct CopyFuzzingTest
{
    CopyFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> expected(size);
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> output(size);
                std::copy(input.cbegin(), input.cend(),begin(expected));
                simdpp::copy(input.data(), input.data()+input.size(), output.data());
                TEST_EQUAL_COLLECTIONS(tr,output,expected);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                std::vector<T> expected(size);
                std::vector<T> output(size);
                std::copy(input.cbegin(), input.cend(), begin(expected));
                simdpp::copy(input.data(), input.data() + input.size(), output.data());
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
void test_copy_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect = { (T)42,(T)42 };
        vector_t ovect = { (T)0,(T)0 };

        copy(ivect.data(), ivect.data() + ivect.size(), ovect.data());
        TEST_EQUAL_COLLECTIONS(tr, ivect, ovect);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(150, (T)42);
        vector_t ovect(150, (T)0);

        copy(ivect.data(), ivect.data() + ivect.size(), ovect.data());
        TEST_EQUAL_COLLECTIONS(tr, ivect, ovect);
    }
    { //test main loop and epilogue on range
        vector_aligned_t ivect(150, (T)42);
        vector_t ovect(150, (T)0);

        copy(ivect.data() + 10u, ivect.data() + ivect.size() - 10u, ovect.data()+10u);
        for (auto i = 0u; i < 10u; ++i) 
        {
            TEST_EQUAL(tr, ovect[i], (T)0);
        }
        for (auto i = 10; i < ovect.size() - 10u; ++i) 
        {
            TEST_EQUAL(tr, ovect[i], ivect[i]);
        }
        for (auto i = ovect.size() - 10u; i < ovect.size(); ++i)
        {
            TEST_EQUAL(tr, ovect[i], (T)0);
        }
    }
    CopyFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_copy(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("copy");
    test_copy_type<double>(ts, tr);
    test_copy_type<float>(ts, tr);
    test_copy_type<uint64_t>(ts, tr);
    test_copy_type<int64_t>(ts, tr);
    test_copy_type<uint32_t>(ts, tr);
    test_copy_type<int32_t>(ts, tr);
    test_copy_type<uint16_t>(ts, tr);
    test_copy_type<int16_t>(ts, tr);
    test_copy_type<uint8_t>(ts, tr);
    test_copy_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
