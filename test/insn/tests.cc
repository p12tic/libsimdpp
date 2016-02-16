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

namespace SIMDPP_ARCH_NAMESPACE {

void main_test_function(TestResults& res)
{
    test_test_utils(res);

    test_construct(res);
    test_convert(res);
    test_blend(res);
    test_bitwise(res);
    test_math_fp(res);
    test_math_int(res);
    test_compare(res);
    test_math_shift(res);
    test_permute_generic(res);
    test_shuffle_generic(res);
    test_shuffle(res);
    test_shuffle_bytes(res);
    test_memory_load(res);
    test_memory_store(res);
    test_transpose(res);
}

} // namespace SIMDPP_ARCH_NAMESPACE
/* TODO: here we use dispatcher only to register the available functions, not
    to dispatch them. To simplify, use a dummy function for SIMDPP_USER_ARCH_INFO
*/
inline simdpp::Arch get_arch()
{
    return simdpp::Arch();
}

#define SIMDPP_USER_ARCH_INFO get_arch

SIMDPP_MAKE_DISPATCHER_VOID1(main_test_function, TestResults&)

#if SIMDPP_EMIT_DISPATCHER
std::vector<simdpp::detail::FnVersion> get_test_archs()
{
    simdpp::detail::FnVersion versions[SIMDPP_DISPATCH_MAX_ARCHS] = {};
    SIMDPP_DISPATCH_COLLECT_FUNCTIONS(versions, main_test_function, void(*)(TestResults&))
    std::vector<simdpp::detail::FnVersion> result;
    result.assign(versions, versions+SIMDPP_DISPATCH_MAX_ARCHS);
    return result;
}
#endif

