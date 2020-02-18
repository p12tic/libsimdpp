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
#include <simdpp/algorithm/find.h>

namespace SIMDPP_ARCH_NAMESPACE {


template<typename T>
struct FindFuzzingTest
{
    FindFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator(0) {}
    void operator()(TestReporter& tr)
    {
        for (auto size : m_sizes)
        {
            const auto val = ((size - 1) / 2)+1;
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorIota<T>>(size, m_generator));
                auto res_std = std::find(input.cbegin(), input.cend(), val);
                auto res_simd = simdpp::find(input.data(), input.data() + input.size(),val);
                TEST_EQUAL(tr, *res_std, *res_simd);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorIota<T>>(size, m_generator));
                auto res_std = std::find(input.cbegin(), input.cend(), val);
                auto res_simd = simdpp::find(input.data(), input.data() + input.size(), val);
                TEST_EQUAL(tr, *res_std, *res_simd);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorIota<T> m_generator;
};

template<typename T>
void test_find_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    {//test prologue
        vector_aligned_t ivect(5);
        std::iota(begin(ivect), end(ivect), T(1));
        auto resstd = std::find(begin(ivect), end(ivect),(T)3);
        auto res = find(ivect.data(), ivect.data() + ivect.size(), (T)3);
        TEST_EQUAL(tr, *resstd, *res);
    }
    { //test main loop and epilogue
        vector_aligned_t ivect(100);
        std::iota(begin(ivect), end(ivect), T(1));
        auto resstd = std::find(begin(ivect), end(ivect),(T)98);
        auto res = find(ivect.data(), ivect.data() + ivect.size(), (T)98);
        TEST_EQUAL(tr, *resstd, *res);
    }
    { //test main loop
        vector_aligned_t ivect(100);
        std::iota(begin(ivect), end(ivect), T(1));
        auto resstd = std::find(begin(ivect), end(ivect),(T)50);
        auto res = find(ivect.data(), ivect.data() + ivect.size(), (T)50);
        TEST_EQUAL(tr, *resstd, *res);
    }
    FindFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_find(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("find");
    test_find_type<double>(ts, tr);
    test_find_type<float>(ts, tr);
    // test_find_type<uint64_t>(ts, tr); //FIXME
    // test_find_type<int64_t>(ts, tr); //FIXME
    test_find_type<uint32_t>(ts, tr);
    test_find_type<int32_t>(ts, tr);
    test_find_type<uint16_t>(ts, tr);
    test_find_type<int16_t>(ts, tr);
    test_find_type<uint8_t>(ts, tr);
    test_find_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
