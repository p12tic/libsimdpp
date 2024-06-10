/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <simdpp/simd.h>
#include <simdpp/algorithm/lexicographical_compare.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
struct LexicographicalCompareFuzzingTest
{
    LexicographicalCompareFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator1(0), m_generator2(1) {}
    void operator()(TestReporter& tr)
    {

        for (auto size : m_sizes)
        {           
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorIota<T>>(size, m_generator1));
                auto input2(DataGeneratorAligned<T, GeneratorIota<T>>(size, m_generator2));
                auto res_std = std::lexicographical_compare(input.cbegin(), input.cend(), input2.cbegin(), input2.cend());
                auto res_simd = simdpp::lexicographical_compare(input.data(), input.data() + input.size(), input2.data(), input2.data() + input2.size() );
                TEST_EQUAL(tr, res_std, res_simd);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorIota<T>>(size, m_generator1));
                auto input2(DataGenerator<T, GeneratorIota<T>>(size, m_generator2));
                auto res_std = std::lexicographical_compare(input.cbegin(), input.cend(), input2.cbegin(), input2.cend());
                auto res_simd = simdpp::lexicographical_compare(input.data(), input.data() + input.size(), input2.data(), input2.data() + input2.size());
                TEST_EQUAL(tr, res_std, res_simd);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorIota<T> m_generator1;
    GeneratorIota<T> m_generator2;
};

template<typename T>
    void test_lexicograpical_compare_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
    vector_aligned_t ivect = {(T)0,(T)1};
    vector_aligned_t ivect2={(T)1,(T)2};
    auto res = lexicographical_compare(ivect.data(),ivect.data()+ivect.size(),ivect2.data(),ivect2.data()+ivect2.size());
    auto resstd = std::lexicographical_compare(begin(ivect), end(ivect),begin(ivect2), end(ivect2));
    TEST_EQUAL(tr, res, resstd);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(50);
        vector_aligned_t ivect2(50);
        std::iota(begin(ivect),end(ivect),(T)0);
        std::iota(begin(ivect2),end(ivect2),(T)1);
        auto res = lexicographical_compare(ivect.data(),ivect.data()+ivect.size(),ivect2.data(),ivect2.data()+ivect2.size());
        auto resstd = std::lexicographical_compare(begin(ivect), end(ivect),begin(ivect2), end(ivect2));
        TEST_EQUAL(tr, res, resstd);
        auto resinv = lexicographical_compare(ivect2.data(),ivect2.data()+ivect2.size(),ivect.data(),ivect.data()+ivect.size());
        auto resstdinv = std::lexicographical_compare(begin(ivect2), end(ivect2),begin(ivect), end(ivect));
        TEST_EQUAL(tr, resinv, resstdinv);
        auto ressame = lexicographical_compare(ivect.data(),ivect.data()+ivect.size(),ivect.data(),ivect.data()+ivect.size());
        auto resstdsame = std::lexicographical_compare(begin(ivect), end(ivect),begin(ivect), end(ivect));
        TEST_EQUAL(tr, ressame, resstdsame);
    }
    LexicographicalCompareFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_lexicographical_compare(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("lexicographical_compare");
    //test_lexicograpical_compare_type<double>(ts, tr); //FIXME
    //test_lexicograpical_compare_type<float>(ts, tr);  //FIXME
    //test_lexicograpical_compare_type<uint64_t>(ts, tr); //FIXME
    //test_lexicograpical_compare_type<int64_t>(ts, tr); //FIXME
    test_lexicograpical_compare_type<uint32_t>(ts, tr);
    test_lexicograpical_compare_type<int32_t>(ts, tr);
    test_lexicograpical_compare_type<uint16_t>(ts, tr);
    test_lexicograpical_compare_type<int16_t>(ts, tr);
    test_lexicograpical_compare_type<uint8_t>(ts, tr);
    test_lexicograpical_compare_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE  
