/*  Copyright (C) 2018  Povilas Kanapickas <povilas@radix.lt>

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

    template<typename T>
    struct UnaryPredicateEqualValue
    {
    public:
        UnaryPredicateEqualValue(T val) :m_val(val), m_val_simd(simdpp::splat(val)) {}
        using simd_mask_T = typename simdpp::typetraits<T>::simd_mask_type;
        using simd_type_T = typename simdpp::typetraits<T>::simd_type;

        bool                  operator()(T a)           const { return a == m_val; }
        simd_mask_T operator()(const simd_type_T& a) const { return cmp_eq(a, m_val_simd); }

        T m_val;
        simd_type_T m_val_simd;
    };

    template<typename T>
    void test_count_if_type(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        const auto pred = UnaryPredicateEqualValue<T>((T)42);
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
        { //test prologue
            vector_t ivect = { (T)42,(T)42 };
            auto res = count_if(ivect.data(), ivect.data() + ivect.size(), pred);
            auto resstd = std::count_if(begin(ivect), end(ivect), pred);
            TEST_EQUAL(tr, res, resstd);
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(50, (T)42);
            ivect[25] = (T)0;
            ivect[49] = (T)0;
            auto res = count_if(ivect.data(), ivect.data() + ivect.size(), pred);
            auto resstd = std::count_if(begin(ivect), end(ivect), pred);
            TEST_EQUAL(tr, res, resstd);
        }
    }

    void test_count_if(TestResults& res, TestReporter& tr)
    {
        using namespace simdpp;
        TestResultsSet& ts = res.new_results_set("count_if");
        test_count_if_type<double>(ts, tr);
        test_count_if_type<float>(ts, tr);
        test_count_if_type<uint64_t>(ts, tr);
        test_count_if_type<int64_t>(ts, tr);
        test_count_if_type<uint32_t>(ts, tr);
        test_count_if_type<int32_t>(ts, tr);
        test_count_if_type<uint16_t>(ts, tr);
        test_count_if_type<int16_t>(ts, tr);
        test_count_if_type<uint8_t>(ts, tr);
        test_count_if_type<int8_t>(ts, tr);
    }

} // namespace SIMDPP_ARCH_NAMESPACE  