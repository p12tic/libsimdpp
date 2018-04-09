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
#include <simdpp/algorithm/equal.h>

namespace SIMDPP_ARCH_NAMESPACE {

template<typename T>
struct EqualFuzzingTest
{
    EqualFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator(0) {}
    void operator()(TestReporter& tr)
    {
        for (auto size : m_sizes)
        {
            {//aligned input/ouput 
                auto input(DataGeneratorAligned<T, GeneratorIota<T>>(size, m_generator));
                auto input2(DataGeneratorAligned<T, GeneratorIota<T>>(size, m_generator));
                auto res_std = std::equal(input.cbegin(), input.cend(), input2.cbegin());
                auto res_simd = simdpp::equal(input.data(), input.data() + input.size(), input2.data());
                TEST_EQUAL(tr, res_std, res_simd);
            }
            {//unaligned input/ouput 
                auto input(DataGenerator<T, GeneratorIota<T>>(size, m_generator));
                auto input2(DataGenerator<T, GeneratorIota<T>>(size, m_generator));
                auto res_std = std::equal(input.cbegin(), input.cend(),input2.cbegin());
                auto res_simd = simdpp::equal(input.data(), input.data() + input.size(), input2.data());
                TEST_EQUAL(tr, res_std, res_simd);

            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorIota<T> m_generator;
};

template<typename T>
void test_equal_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect1 = { (T)42,(T)42 };
        vector_t ivect2 = { (T)0,(T)0 };

        auto res=equal(ivect1.data(), ivect1.data() + ivect1.size(), ivect2.data());
        TEST_EQUAL(tr,res,false);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect1(50);
        std::iota(begin(ivect1),end(ivect1),(T)1);            
        vector_aligned_t ivect2(50);
        std::copy(begin(ivect1),end(ivect1),begin(ivect2));
        auto res=equal(ivect1.data(), ivect1.data() + ivect1.size(), ivect2.data());
        TEST_EQUAL(tr,res,true);
        ivect2[25]=0;
        auto res2=equal(ivect1.data(), ivect1.data() + ivect1.size(), ivect2.data());
        TEST_EQUAL(tr,res2,false);
    }
    EqualFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_equal(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("copy");
    // test_equal_type<double>(ts, tr);   //FIXME
    // test_equal_type<float>(ts, tr);    //FIXME
    test_equal_type<uint64_t>(ts, tr);
    test_equal_type<int64_t>(ts, tr);
    test_equal_type<uint32_t>(ts, tr);
    test_equal_type<int32_t>(ts, tr);
    test_equal_type<uint16_t>(ts, tr);
    test_equal_type<int16_t>(ts, tr);
    test_equal_type<uint8_t>(ts, tr);
    test_equal_type<int8_t>(ts, tr);
}

} // namespace SIMDPP_ARCH_NAMESPACE
