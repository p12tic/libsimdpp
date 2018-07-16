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
#include <simdpp/algorithm/reduce.h>

namespace SIMDPP_ARCH_NAMESPACE {

template< typename T>
struct BinaryOpPlus
{
public:
    BinaryOpPlus() {}
    SIMDPP_INL T operator()(T const &a0, T const &a1) const  SIMDPP_NOEXCEPT
    {
        return a0 + a1;
    }

    template<typename U>
    SIMDPP_INL U operator()(U const &a0, U const &a1) const  SIMDPP_NOEXCEPT
    {
        return a0 + a1;
    }
};

//from https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
template<typename T>
bool approximatelyEqual(T a, T b, T epsilon)
{
    return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

template<typename T>
struct ReduceFuzzingTest
{
    ReduceFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        T init = (T)0;
        for (auto size : m_sizes)
        {
            {//aligned input/ouput
                const auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::accumulate(input.cbegin(), input.cend(), init);
                //auto res_std=std::reduce(cbegin(input), cend(input),init);
                auto res_simd = simdpp::reduce(input.data(), input.data() + input.size(), init);
                TEST_EQUAL(tr, approximatelyEqual(res_std, res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
            {//non aligned input/ouput
                const auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                auto res_std = std::accumulate(input.cbegin(), input.cend(), init);
                //auto res_std = std::reduce(cbegin(input), cend(input), init);
                auto res_simd = simdpp::reduce(input.data(), input.data() + input.size(), init);
                TEST_EQUAL(tr, approximatelyEqual(res_std, res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
struct ReduceBinaryFuzzingTest
{
    ReduceBinaryFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        T init = (T)0;
        auto opPlus = BinaryOpPlus<T>();
        T neutral = (T)0;
        for (auto size : m_sizes)
        {
            {//aligned input/ouput
                const auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                //auto res_std = std::reduce(cbegin(input), cend(input),init, opPlus);
                auto res_std = std::accumulate(input.cbegin(), input.cend(), init, opPlus);
                auto res_simd = simdpp::reduce(input.data(), input.data() + input.size(), init, neutral, opPlus);
                TEST_EQUAL(tr, approximatelyEqual(res_std, res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
            {//non aligned input/ouput
                const auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                //auto res_std = std::reduce(cbegin(input), cend(input), init, opPlus);
                auto res_std = std::accumulate(input.cbegin(), input.cend(), init, opPlus);
                auto res_simd = simdpp::reduce(input.data(), input.data() + input.size(), init, neutral, opPlus);
                TEST_EQUAL(tr, approximatelyEqual(res_std, res_simd, 10 * std::numeric_limits<T>::epsilon()), true);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
void test_reduce_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    { //test prologue
        vector_t ivect = { 0,41 };
        T expected = { 42 };
        T init = { 1 };
        T res = reduce(ivect.data(), ivect.data() + ivect.size(), init);
        TEST_EQUAL(tr, expected, res);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(42, 1);
        T expected = { 42 };
        T init = { 0 };
        T res = reduce(ivect.data(), ivect.data() + ivect.size(), init);
        TEST_EQUAL(tr, expected, res);
    }
    { //test main loop and epilogue on range
        vector_aligned_t ivect(150, 1);
        T expected = { 42 };
        T init = { 0 };
        T res = reduce(ivect.data() + 8u, ivect.data() + ivect.size() - 100u, init);
        TEST_EQUAL(tr, expected, res);
    }
    ReduceFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

template<typename T>
void test_reducebinop_type(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    auto opPlus = BinaryOpPlus<T>();

    { //test prologue
        vector_t ivect = { 1,42 };
        T expected = { 43 };
        T init = { 0 };
        T neutral = { 0 };
        T res = reduce(ivect.data(), ivect.data() + ivect.size(), init, neutral, opPlus);
        TEST_EQUAL(tr, expected, res);
    }
    { //test main loop and epilogue on unaligned vector
        vector_t ivect(125, 1);
        T expected = { 125 };
        T init = { 0 };
        T neutral = { 0 };
        T res = reduce(ivect.data(), ivect.data() + ivect.size(), init, neutral, opPlus);
        TEST_EQUAL(tr, expected, res);
    }
    ReduceBinaryFuzzingTest<T> fuzzing({ 1,3,5,8,21,55,89,144 });//0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_reduce(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("reduce");
    test_reduce_type<double>(ts, tr);
    test_reduce_type<float>(ts, tr);
    /* test_reduce_type<uint64_t>(ts, tr);
    test_reduce_type<int64_t>(ts, tr);
    test_reduce_type<uint32_t>(ts, tr);
    test_reduce_type<int32_t>(ts, tr);
    test_reduce_type<uint16_t>(ts, tr);
    test_reduce_type<int16_t>(ts, tr);
    test_reduce_type<uint8_t>(ts, tr);
    test_reduce_type<int8_t>(ts, tr);*/

    test_reducebinop_type<double>(ts, tr);
    test_reducebinop_type<float>(ts, tr);
    /*test_reducebinop_type<uint64_t>(ts, tr);
    test_reducebinop_type<int64_t>(ts, tr);
    test_reducebinop_type<uint32_t>(ts, tr);
    test_reducebinop_type<int32_t>(ts, tr);
    test_reducebinop_type<uint16_t>(ts, tr);
    test_reducebinop_type<int16_t>(ts, tr);
    test_reducebinop_type<uint8_t>(ts, tr);
    test_reducebinop_type<int8_t>(ts, tr);*/

}
}
