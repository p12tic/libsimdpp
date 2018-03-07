#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include <vector>
#include <iterator>
#include <simdpp/simd.h>

namespace SIMDPP_ARCH_NAMESPACE {

    template<typename T>
    void test_count_type(TestResultsSet& ts, TestReporter& tr)
    {
        using namespace simdpp;
        using vector_t = std::vector<T>;
        using vector_aligned_t = std::vector<T, aligned_allocator<T, typetraits<T>::alignment>>;
        { //test prologue
            vector_t ivect = { (T)42,(T)42 };
            auto res = count(ivect.data(), ivect.data() + ivect.size(), (T)42);
            auto resstd = std::count(begin(ivect), end(ivect), (T)42);
            TEST_EQUAL(tr, res, resstd);
        }
        { //test main loop and epilogue on aligned vector
            vector_aligned_t ivect(50, (T)42);
            ivect[25] = (T)0;
            ivect[49] = (T)0;
            auto res = count(ivect.data(), ivect.data() + ivect.size(), (T)42);
            auto resstd = std::count(begin(ivect), end(ivect), (T)42);
            TEST_EQUAL(tr, res, resstd);
        }
    }

    void test_count(TestResults& res, TestReporter& tr)
    {
        using namespace simdpp;
        TestResultsSet& ts = res.new_results_set("count");
        test_count_type<double>(ts, tr);
        test_count_type<float>(ts, tr);
        test_count_type<uint64_t>(ts, tr);
        test_count_type<int64_t>(ts, tr);
        test_count_type<uint32_t>(ts, tr);
        test_count_type<int32_t>(ts, tr);
        test_count_type<uint16_t>(ts, tr);
        test_count_type<int16_t>(ts, tr);
        test_count_type<uint8_t>(ts, tr);
        test_count_type<int8_t>(ts, tr);
    }

} // namespace SIMDPP_ARCH_NAMESPACE      