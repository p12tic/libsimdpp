/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef SIMDPP_TEST_INSN_TESTS_H
#define SIMDPP_TEST_INSN_TESTS_H

#include "../utils/test_helpers.h"
#include "../utils/test_results.h"

#include <cstdint>
#include <iostream>

namespace SIMDPP_ARCH_NAMESPACE {

void main_test_function(TestResults& res, TestReporter& tr, const TestOptions& opts);
 void test_all_of(TestResults& res, TestReporter& tr);
 void test_any_of(TestResults& res, TestReporter& tr);
 void test_bitwise(TestResults& res, TestReporter& tr);
 void test_blend(TestResults& res);
 void test_compare(TestResults& res);
 void test_convert(TestResults& res);
 void test_construct(TestResults& res);
 void test_copy(TestResults& res, TestReporter& tr);
 void test_copy_n(TestResults& res, TestReporter& tr);
 void test_count(TestResults& res, TestReporter& tr);
 void test_count_if(TestResults& res, TestReporter& tr);
 void test_equal(TestResults& res, TestReporter& tr);
 void test_for_each(TestResults& res, TestReporter& tr);
 void test_fill(TestResults& res, TestReporter& tr);
 void test_find(TestResults& res, TestReporter& tr);
 void test_find_if(TestResults& res, TestReporter& tr);
 void test_find_if_not(TestResults& res, TestReporter& tr);
 void test_lexicographical_compare(TestResults& res, TestReporter& tr);   
 void test_math_fp(TestResults& res, const TestOptions& opts);
 void test_math_int(TestResults& res);
 void test_math_shift(TestResults& res);
 void test_max(TestResults& res, TestReporter& tr);
 void test_max_element(TestResults& res, TestReporter& tr);
 void test_memory_load(TestResults& res, TestReporter& tr);
 void test_memory_store(TestResults& res, TestReporter& tr);
 void test_min(TestResults& res, TestReporter& tr);
 void test_min_element(TestResults& res, TestReporter& tr);
 void test_none_of(TestResults& res, TestReporter& tr);
 void test_replace(TestResults& res, TestReporter& tr);
 void test_replace_if(TestResults& res, TestReporter& tr);
 void test_set(TestResults& res);
 void test_shuffle(TestResults& res);
 void test_shuffle_bytes(TestResults& res, TestReporter& tr);
 void test_shuffle_generic(TestResults& res);
 void test_permute_generic(TestResults& res);
 void test_reduce(TestResults& res, TestReporter& tr);
 void test_shuffle_transpose(TestResults& res);
 void test_test_utils(TestResults& res);
 void test_transpose(TestResults& res);
 void test_transform(TestResults& res, TestReporter& tr);
 void test_transform_reduce(TestResults& res, TestReporter& tr);  

} // namespace SIMDPP_ARCH_NAMESPACE

std::vector<simdpp::detail::FnVersion> get_test_archs();

#endif
