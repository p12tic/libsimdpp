/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {
    template< typename T>
    struct UnaryOpAddValue
    {
        T m_val;
    public:
        UnaryOpAddValue(T val) :m_val(val) {}
        SIMDPP_INL T operator()(T const &a) const  noexcept
        {
            return m_val + a;
        }

        template<typename U>
        SIMDPP_INL U operator()(U const &a) const  noexcept
        {
            return m_val + a;
        }
    };

    template< typename T>
    struct BinaryOpAdd
    {
    public:
        BinaryOpAdd() {}
        SIMDPP_INL T operator()(T const &a0, T const &a1) const  noexcept
        {
            return a0 + a1;
        }

        template<typename U>
        SIMDPP_INL U operator()(U const &a0, U const &a1) const  noexcept
        {
            using namespace simdpp;
            return a0 + a1;
        }
    };


    template<typename T>
    void test_transform_type_unary(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
        auto opPlusOne = UnaryOpAddValue<T>(1);
        { //test prologue
            vector_t ivect = { 0,1 };
            vector_t ovect(2);
            vector_t expected = { 1,2 };

            transform(ivect.data(), ivect.data() + ivect.size(), ovect.data(), opPlusOne);
            for (auto i = 0; i < ovect.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
            {
                TEST_EQUAL(tr, expected[i], ovect[i]);
            }
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(150, 0);
            vector_aligned_t ovect(150);
            vector_t expected(150, 1);

            transform(ivect.data(), ivect.data() + ivect.size(), ovect.data(), opPlusOne);
            for (auto i = 0; i < ovect.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
            {
                TEST_EQUAL(tr, expected[i], ovect[i]);
            }
        }
        { //test main loop and epilogue on range
            vector_aligned_t ivect(150, 0);
            vector_aligned_t  ovect(150);
            vector_t expected(150, 1);

            transform(ivect.data() + 10u, ivect.data() + ivect.size() - 10u, ovect.data() + 10u, opPlusOne);
            for (auto i = 10; i < ovect.size() - 10u; ++i) //TODO make TEST_EQUAL_COLECTIONS
            {
                TEST_EQUAL(tr, expected[i], ovect[i]);
            }
        }



    }
    template<typename T, typename U>
    void test_transform_type_binary(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_u = std::vector<U>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
        using vector_aligned_u = std::vector<U, aligned_allocator<U, typetraits<U>::alignment>>;
        auto opPlus = BinaryOpAdd<T>();
        { //test prologue
            vector_t ivect1 = { 0,1 };
            vector_u ivect2 = { 1,2 };
            vector_t ovect(2);
            vector_t expected = { 1,3 };

            transform(ivect1.data(), ivect1.data() + ivect1.size(), ivect2.data(), ovect.data(), opPlus);
            for (auto i = 0; i < ovect.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
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
            for (auto i = 0; i < ovect.size(); ++i) //TODO make TEST_EQUAL_COLECTIONS
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
