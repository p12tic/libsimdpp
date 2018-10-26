/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>
Copyright (C) 2018  Thomas Retornaz <thomas.retornaz@mines-paris.org>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <simdpp/simd.h>
#include <simdpp/algorithm/transform.h>

namespace SIMDPP_ARCH_NAMESPACE {


template< typename T>
struct UnaryOpAddValue
{
    T m_val;
public:
    UnaryOpAddValue(T val) :m_val(val) {}
    SIMDPP_INL T operator()(T const &a) const  SIMDPP_NOEXCEPT
    {
        return m_val + a;
    }

    template<typename U>
    SIMDPP_INL U operator()(U const &a) const  SIMDPP_NOEXCEPT
    {
        return m_val + a;
    }
};

template< typename T>
struct BinaryOpAdd
{
public:
    BinaryOpAdd() {}
    SIMDPP_INL T operator()(T const &a0, T const &a1) const  SIMDPP_NOEXCEPT
    {
        return a0 + a1;
    }

    template<typename U>
    SIMDPP_INL U operator()(U const &a0, U const &a1) const  SIMDPP_NOEXCEPT
    {
        using namespace simdpp;
        return a0 + a1;
    }
};

    
template<typename T>
struct TransformUnaryFuzzingTest
{
    TransformUnaryFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        auto opPlusOne = UnaryOpAddValue<T>(1);
        for (auto size : m_sizes)
        {
            {//aligned input/ouput
                const auto input(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> expected(size);
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> output(size);
                std::transform(input.cbegin(), input.cend(),expected.begin(), opPlusOne);
                simdpp::transform(input.data(), input.data() + input.size(), output.data(), opPlusOne);
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
            {//non aligned input/ouput
                const auto input(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                std::vector<T> expected(size);
                std::vector<T> output(size);
                std::transform(input.cbegin(), input.cend(),expected.begin(), opPlusOne);
                simdpp::transform(input.data(), input.data() + input.size(), output.data(), opPlusOne);
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};

template<typename T>
struct TransformBinaryFuzzingTest
{
    TransformBinaryFuzzingTest(std::initializer_list<std::size_t> sizes = {}) :m_sizes(sizes), m_generator() {}
    void operator()(TestReporter& tr)
    {
        auto opPlus = BinaryOpAdd<T>();
        for (auto size : m_sizes)
        {
            {//aligned input/ouput
                const auto input1(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                const auto input2(DataGeneratorAligned<T, GeneratorRandom<T>>(size, m_generator));
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> expected(size);
                std::vector<T, simdpp::aligned_allocator<T, simdpp::simd_traits<T>::alignment>> output(size);
                std::transform(input1.cbegin(), input1.cend(), input2.cbegin(), expected.begin(), opPlus);
                simdpp::transform(input1.data(), input1.data() + input1.size(), input2.data(), output.data(), opPlus);
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
            {//non aligned input/ouput
                const auto input1(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                const auto input2(DataGenerator<T, GeneratorRandom<T>>(size, m_generator));
                std::vector<T> expected(size);
                std::vector<T> output(size);
                std::transform(input1.cbegin(), input1.cend(), input2.cbegin(), expected.begin(), opPlus);
                simdpp::transform(input1.data(), input1.data() + input1.size(), input2.data(), output.data(), opPlus);
                TEST_EQUAL_COLLECTIONS(tr, output, expected);
            }
        }
    }
    std::vector<std::size_t> m_sizes;
    GeneratorRandom<T> m_generator;
};
template<typename T>
void test_transform_type_unary(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    auto opPlusOne = UnaryOpAddValue<T>(1);
    { //test prologue
        vector_t ivect = { 0,1 };
        vector_t ovect(2);
        vector_t expected = { 1,2 };

        transform(ivect.data(), ivect.data() + ivect.size(), ovect.data(), opPlusOne);
        TEST_EQUAL_COLLECTIONS(tr, ovect, expected);
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect(150, 0);
        vector_aligned_t ovect(150);
        vector_t expected(150, 1);

        transform(ivect.data(), ivect.data() + ivect.size(), ovect.data(), opPlusOne);
        TEST_EQUAL_COLLECTIONS(tr, ovect, expected);
    }
    TransformUnaryFuzzingTest<T> fuzzing({1,3,5,8,21,55,89,144});//0 generate null ptr inputs/ouput
    fuzzing(tr);


}
template<typename T, typename U>
void test_transform_type_binary(TestResultsSet& ts, TestReporter& tr)
{
    using namespace simdpp;
    using vector_t = std::vector<T>;
    using vector_u = std::vector<U>;
    using vector_aligned_t = std::vector<T, aligned_allocator<T, simd_traits<T>::alignment>>;
    using vector_aligned_u = std::vector<U, aligned_allocator<U, simd_traits<U>::alignment>>;
    auto opPlus = BinaryOpAdd<T>();
    { //test prologue
        vector_t ivect1 = { 0,1 };
        vector_u ivect2 = { 1,2 };
        vector_t ovect(2);
        vector_t expected = { 1,3 };

        transform(ivect1.data(), ivect1.data() + ivect1.size(), ivect2.data(), ovect.data(), opPlus);
        for (auto i = 0u; i < ovect.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
        {
            TEST_EQUAL(tr, expected[i], ovect[i]);
        }
    }
    { //test main loop and epilogue on aligned vector
        vector_aligned_t ivect1(150, 0);
        vector_aligned_t ivect2(150, 1);
        vector_aligned_t ovect(150);
        vector_t expected(150, 1);

        transform(ivect1.data(), ivect1.data() + ivect1.size(), ivect2.data(), ovect.data(), opPlus);
        for (auto i = 0u; i < ovect.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
        {
            TEST_EQUAL(tr, expected[i], ovect[i]);
        }
    }
    { //test main loop and epilogue on range
        vector_aligned_t ivect1(150, 0);
        vector_aligned_t ivect2(150, 1);
        vector_aligned_t ovect(150);
        vector_t expected(150, 1);

        transform(ivect1.data() + 10u, ivect1.data() + ivect1.size() - 10u, ivect2.data() + 10u, ovect.data() + 10u, opPlus);
        for (auto i = 10u; i < ovect.size() - 10u; ++i) //TODO make TEST_EQUAL_COLECTIONS
        {
            TEST_EQUAL(tr, expected[i], ovect[i]);
        }
    }
    TransformBinaryFuzzingTest<T> fuzzing({1,3,5,8,21,55,89,144 }); //0 generate null ptr inputs/ouput
    fuzzing(tr);
}

void test_transform(TestResults& res, TestReporter& tr)
{
    using namespace simdpp;
    TestResultsSet& ts = res.new_results_set("transform");
    test_transform_type_unary<double>(ts, tr);
    test_transform_type_unary<float>(ts, tr);
    test_transform_type_unary<uint64_t>(ts, tr);
    test_transform_type_unary<int64_t>(ts, tr);
    test_transform_type_unary<uint32_t>(ts, tr);
    test_transform_type_unary<int32_t>(ts, tr);
    test_transform_type_unary<uint16_t>(ts, tr);
    test_transform_type_unary<int16_t>(ts, tr);
    test_transform_type_unary<uint8_t>(ts, tr);
    test_transform_type_unary<int8_t>(ts, tr);

    test_transform_type_binary<double, double>(ts, tr);
    test_transform_type_binary<float, float>(ts, tr);
    test_transform_type_binary<uint64_t, uint64_t>(ts, tr);
    test_transform_type_binary<int64_t, int64_t>(ts, tr);
    test_transform_type_binary<uint32_t, uint32_t>(ts, tr);
    test_transform_type_binary<int32_t, int32_t>(ts, tr);
    test_transform_type_binary<uint16_t, uint16_t>(ts, tr);
    test_transform_type_binary<int16_t, int16_t>(ts, tr);
    test_transform_type_binary<uint8_t, uint8_t>(ts, tr);
    test_transform_type_binary<int8_t, int8_t>(ts, tr);

}

} // namespace SIMDPP_ARCH_NAMESPACE
