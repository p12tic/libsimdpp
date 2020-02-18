/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"
#include "tests.h"
#include <simdpp/simd.h>
#include <vector>

static_assert(sizeof(simdpp::uint8<16>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::int8<16>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::uint16<8>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::int16<8>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::uint32<4>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::int32<4>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::uint64<2>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::int64<2>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::float32<4>) == 16, "Incorrect vector size");
static_assert(sizeof(simdpp::float64<2>) == 16, "Incorrect vector size");

static_assert(sizeof(simdpp::uint8<32>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::int8<32>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::uint16<16>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::int16<16>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::uint32<8>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::int32<8>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::uint64<4>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::int64<4>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::float32<8>) == 32, "Incorrect vector size");
static_assert(sizeof(simdpp::float64<4>) == 32, "Incorrect vector size");

static_assert(sizeof(simdpp::uint8<64>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::int8<64>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::uint16<32>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::int16<32>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::uint32<16>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::int32<16>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::uint64<8>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::int64<8>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::float32<16>) == 64, "Incorrect vector size");
static_assert(sizeof(simdpp::float64<8>) == 64, "Incorrect vector size");

namespace SIMDPP_ARCH_NAMESPACE {

    void main_test_function(TestResults& res, TestReporter& tr, const TestOptions& opts)
    {
        test_test_utils(res);

        // Tests are ordered in such a way so that base functionality that other
        // tests depend on is tested first.
        test_construct(res);
        test_memory_load(res, tr);
        test_memory_store(res, tr);

        test_blend(res);
        test_bitwise(res, tr);
        test_permute_generic(res);
        test_shuffle_generic(res);
        test_shuffle(res);
        test_shuffle_bytes(res, tr);

        test_convert(res);
        test_math_fp(res, opts);
        test_math_int(res);
        test_compare(res);
        test_math_shift(res);
        test_transpose(res);

        test_for_each(res, tr);

        //algorithm
        test_all_of(res,tr);
        test_any_of(res,tr);         
        test_copy(res,tr);
        test_copy_n(res,tr);
        test_count(res,tr);
        test_count_if(res,tr);
        test_equal(res,tr);        
        test_fill(res,tr);
        test_find(res, tr);
        test_find_if(res, tr);
        test_find_if_not(res, tr);
        test_lexicographical_compare(res,tr);
        test_max(res,tr);
        test_max_element(res, tr);
        test_min(res,tr);
        test_min_element(res, tr);
        test_none_of(res,tr);
        test_replace(res,tr);
        test_replace_if(res,tr);        
        test_reduce(res, tr);
        test_transform(res, tr);
        test_transform_reduce(res, tr);

    }

} // namespace SIMDPP_ARCH_NAMESPACE
/* TODO: here we use dispatcher only to register the available functions, not
    to dispatch them. To simplify, use a dummy function for SIMDPP_USER_ARCH_INFO
*/
inline simdpp::Arch get_arch()
{
    return simdpp::Arch();
}

#define SIMDPP_USER_ARCH_INFO get_arch()

SIMDPP_MAKE_DISPATCHER_VOID3(main_test_function, TestResults&, TestReporter&, const TestOptions&)

#if SIMDPP_EMIT_DISPATCHER
std::vector<simdpp::detail::FnVersion> get_test_archs()
{
    simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {};
    using FunPtr = void(*)(TestResults&, TestReporter&, const TestOptions&);
    SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, main_test_function, FunPtr)
    std::vector<simdpp::detail::FnVersion> result;
    result.assign(versions, versions + SIMDPP_DISPATCH_MAX_ARCHS);
    return result;
}
#endif

