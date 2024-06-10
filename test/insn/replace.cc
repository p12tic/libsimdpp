/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
    Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <simdpp/simd.h>
#include <simdpp/algorithm/transform.h>
#include <simdpp/algorithm/replace.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
struct ReplaceFuzzingTest
{
    ReplaceFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generatorFive(5),m_generatorTen(10) {}
    void operator()(TestReporter& tr)
    {
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generatorFive));
                auto expected(DataGeneratorAligned<T, GeneratorConstant<T>>(size, m_generatorTen));
                simdpp::replace(input.data(),input.data()+input.size(),(T)5,(T)10);
                TEST_EQUAL_COLLECTIONS(tr, input, expected);
            }
            {//non aligned input/ouput
                auto input(DataGenerator<T, GeneratorConstant<T>>(size, m_generatorFive));
                auto expected(DataGenerator<T, GeneratorConstant<T>>(size, m_generatorTen));
                simdpp::replace(input.data(), input.data() + input.size(),(T)5, (T)10);
                TEST_EQUAL_COLLECTIONS(tr, input, expected);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorConstant<T> m_generatorFive;
    GeneratorConstant<T> m_generatorTen;
};

template<typename T>
    void test_replace_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect = { (T)42,(T)42 };
        vector_t expected = { (T)0,(T)0 };

        replace(ivect.data(),ivect.data()+ivect.size(),(T)42,(T)0 );
        TEST_EQUAL_COLLECTIONS(tr, ivect, expected);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(50);
        std::iota(begin(ivect),end(ivect),(T)0);
        vector_aligned_t expected(50);
        std::copy(begin(ivect),end(ivect),begin(expected));
        expected[39]=42;
        replace(ivect.data(),ivect.data()+ivect.size(),(T)39,(T)42 );
        TEST_EQUAL_COLLECTIONS(tr, ivect, expected);
    }
    ReplaceFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_replace(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("replace");
    test_replace_type<double>(ts, tr);
    test_replace_type<float>(ts, tr);
    test_replace_type<uint64_t>(ts, tr);
    test_replace_type<int64_t>(ts, tr);
    test_replace_type<uint32_t>(ts, tr);
    test_replace_type<int32_t>(ts, tr);
    test_replace_type<uint16_t>(ts, tr);
    test_replace_type<int16_t>(ts, tr);
    test_replace_type<uint8_t>(ts, tr);
    test_replace_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
