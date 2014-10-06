/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "../arch_registration.h"
#include "../test_helpers.h"
#include "../test_results.h"
#include "../tests.h"
#include <simdpp/simd.h>

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
    test_shuffle_generic(res);
    test_shuffle(res);
    test_shuffle_bytes(res);
    test_memory_load(res);
    test_memory_store(res);
    test_transpose(res);
}

static ArchRegistration tester(main_test_function,
                               SIMDPP_ARCH_NAME,
                               simdpp::this_compile_arch());

} // namespace SIMDPP_ARCH_NAMESPACE
