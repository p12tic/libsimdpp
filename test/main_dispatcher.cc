/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "dispatcher/dispatcher.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include "utils/test_helpers.h"

// Check whether all available getters of supported architecture compiles
// on all compilers
#include <simdpp/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_string_list.h>

static simdpp::Arch g_supported_arch;

int g_test_dispatcher_val;

simdpp::Arch get_supported_arch()
{
    return g_supported_arch;
}

template<class T>
void test_dispatcher_template_pair_for_type(TestReporter& tr)
{
    g_test_dispatcher_val = 0;
    test_dispatcher_void_template_pair(std::pair<T, T>(1, 2));
    TEST_EQUAL(tr, 1+2, g_test_dispatcher_val);


    g_test_dispatcher_val = 0;
    test_dispatcher_void_template_pair2(std::pair<T, T>(1, 2),
                                        std::pair<T, T>(3, 4));
    TEST_EQUAL(tr, 1+2+3+4, g_test_dispatcher_val);

    std::pair<T, T> pair;
    pair = test_dispatcher_ret_template_pair(std::pair<T, T>(1, 2));
    TEST_EQUAL(tr, (T)1, pair.first);
    TEST_EQUAL(tr, (T)2, pair.second);

    pair = test_dispatcher_ret_template_pair2(std::pair<T, T>(1, 2),
                                              std::pair<T, T>(3, 4));
    TEST_EQUAL(tr, (T)(1+3), pair.first);
    TEST_EQUAL(tr, (T)(2+4), pair.second);

    g_test_dispatcher_val = 0;
    test_dispatcher_void_template_nondeductible<T>();
    TEST_EQUAL(tr, (int)sizeof(T), g_test_dispatcher_val);

    pair = test_dispatcher_ret_template_nondeductible<T>();
    TEST_EQUAL(tr, (T)(sizeof(T)), pair.first);
    TEST_EQUAL(tr, (T)(sizeof(T)), pair.second);
}

template<class T, class U>
void test_dispatcher_template2_pair_for_type(TestReporter& tr)
{
    g_test_dispatcher_val = 0;
    test_dispatcher_void_template2_pair(std::pair<T, U>(1, 2));
    TEST_EQUAL(tr, 1+2, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_void_template2_pair2(std::pair<T, U>(1, 2),
                                        std::pair<T, U>(3, 4));
    TEST_EQUAL(tr, 1+2+3+4, g_test_dispatcher_val);

    std::pair<T, U> pair;
    pair = test_dispatcher_ret_template2_pair(std::pair<T, U>(1, 2));
    TEST_EQUAL(tr, (T)1, pair.first);
    TEST_EQUAL(tr, (U)2, pair.second);

    pair = test_dispatcher_ret_template2_pair2(std::pair<T, U>(1, 2),
                                              std::pair<T, U>(3, 4));
    TEST_EQUAL(tr, (T)(1+3), pair.first);
    TEST_EQUAL(tr, (U)(2+4), pair.second);

    g_test_dispatcher_val = 0;
    test_dispatcher_void_template2_nondeductible<T, U>();
    TEST_EQUAL(tr, (int)(sizeof(T) + sizeof(U)), g_test_dispatcher_val);

    pair = test_dispatcher_ret_template2_nondeductible<T, U>();
    TEST_EQUAL(tr, (T)(sizeof(T)), pair.first);
    TEST_EQUAL(tr, (U)(sizeof(U)), pair.second);
}

int main(int argc, char** argv)
{
    using simdpp::Arch;

    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Please supply the name of \n"
                     "the architecture as the first argument.";
        return EXIT_FAILURE;
    }

    std::string arch_name = argv[1];
    if (arch_name == "NONE_NULL") {
        g_supported_arch = Arch::NONE_NULL;
    } else if (arch_name == "X86_SSE2") {
        g_supported_arch = Arch::X86_SSE2;
    } else if (arch_name == "X86_SSE3") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3;
    } else if (arch_name == "X86_SSSE3") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3;
    } else if (arch_name == "X86_SSE4_1") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                           Arch::X86_SSE4_1;
    } else if (arch_name == "X86_AVX") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                Arch::X86_SSE4_1 | Arch::X86_AVX;
    } else if (arch_name == "X86_AVX2") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                Arch::X86_SSE4_1 | Arch::X86_AVX | Arch::X86_AVX2;
    } else if (arch_name == "X86_AVX512F") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                Arch::X86_SSE4_1 | Arch::X86_AVX | Arch::X86_AVX2 |
                Arch::X86_AVX512F;
    } else if (arch_name == "X86_AVX512BW") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                Arch::X86_SSE4_1 | Arch::X86_AVX | Arch::X86_AVX2 |
                Arch::X86_AVX512F | Arch::X86_AVX512BW;
    } else if (arch_name == "X86_AVX512DQ") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                Arch::X86_SSE4_1 | Arch::X86_AVX | Arch::X86_AVX2 |
                Arch::X86_AVX512F | Arch::X86_AVX512DQ;
    } else if (arch_name == "X86_AVX512VL") {
        g_supported_arch = Arch::X86_SSE2 | Arch::X86_SSE3 | Arch::X86_SSSE3 |
                Arch::X86_SSE4_1 | Arch::X86_AVX | Arch::X86_AVX2 |
                Arch::X86_AVX512F | Arch::X86_AVX512VL;
    } else if (arch_name == "ARM_NEON") {
        g_supported_arch = Arch::ARM_NEON;
    } else if (arch_name == "ARM_NEON_FLT_SP") {
        g_supported_arch = Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP;
    } else {
        std::cerr << "Invalid architecture specified: " << arch_name << "\n";
        return EXIT_FAILURE;
    }

    TestReporter tr(std::cerr);

    Arch selected = test_dispatcher_get_arch();
    if (selected != g_supported_arch) {
        tr.out() << "Wrong architecture selected: \n"
                 << "  Supported: "
                 << std::hex << static_cast<unsigned>(g_supported_arch)
                 << "\n  Selected: "
                 << std::hex << static_cast<unsigned>(selected) << "\n";
        tr.add_result(false);
        return EXIT_FAILURE;
    }
    tr.add_result(true);

    TEST_EQUAL(tr, 42, test_dispatcher_old_ret0());
    TEST_EQUAL(tr, 1, test_dispatcher_old_ret1(1));
    TEST_EQUAL(tr, 1+2, test_dispatcher_old_ret2(1, 2));
    TEST_EQUAL(tr, 1+2+3, test_dispatcher_old_ret3(1, 2, 3));
    TEST_EQUAL(tr, 1+2+3+4, test_dispatcher_old_ret4(1, 2, 3, 4));

    g_test_dispatcher_val = 0;
    test_dispatcher_old_void0();
    TEST_EQUAL(tr, 42, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_old_void1(1);
    TEST_EQUAL(tr, 1, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_old_void2(1, 2);
    TEST_EQUAL(tr, 1+2, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_old_void3(1, 2, 3);
    TEST_EQUAL(tr, 1+2+3, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_old_void4(1, 2, 3, 4);
    TEST_EQUAL(tr, 1+2+3+4, g_test_dispatcher_val);

    TEST_EQUAL(tr, 42, test_dispatcher_ret0());
    TEST_EQUAL(tr, 1, test_dispatcher_ret1(1));
    TEST_EQUAL(tr, 1+2, test_dispatcher_ret2(1, 2));
    TEST_EQUAL(tr, 1+2+3, test_dispatcher_ret3(1, 2, 3));
    TEST_EQUAL(tr, 1+2+3+4, test_dispatcher_ret4(1, 2, 3, 4));

    g_test_dispatcher_val = 0;
    test_dispatcher_void0();
    TEST_EQUAL(tr, 42, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_void1(1);
    TEST_EQUAL(tr, 1, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_void2(1, 2);
    TEST_EQUAL(tr, 1+2, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_void3(1, 2, 3);
    TEST_EQUAL(tr, 1+2+3, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_void4(1, 2, 3, 4);
    TEST_EQUAL(tr, 1+2+3+4, g_test_dispatcher_val);

    void* voidptr = reinterpret_cast<void*>(uintptr_t(1234));
    void* voidptr2 = test_dispatcher_ret_voidptr(voidptr);
    TEST_EQUAL(tr, voidptr, voidptr2);

    g_test_dispatcher_val = 0;
    test_dispatcher_void_pair(std::pair<int, int>(1, 2));
    TEST_EQUAL(tr, 1+2, g_test_dispatcher_val);

    g_test_dispatcher_val = 0;
    test_dispatcher_void_pair2(std::pair<int, int>(1, 2),
                               std::pair<int, int>(3, 4));
    TEST_EQUAL(tr, 1+2+3+4, g_test_dispatcher_val);

    std::pair<int, int> intpair;
    intpair = test_dispatcher_ret_pair(std::pair<int, int>(1, 2));
    TEST_EQUAL(tr, 1, intpair.first);
    TEST_EQUAL(tr, 2, intpair.second);

    intpair = test_dispatcher_ret_pair2(std::pair<int, int>(1, 2),
                                        std::pair<int, int>(3, 4));
    TEST_EQUAL(tr, 1+3, intpair.first);
    TEST_EQUAL(tr, 2+4, intpair.second);

    test_dispatcher_template_pair_for_type<int>(tr);
    test_dispatcher_template_pair_for_type<char>(tr);
    test_dispatcher_template2_pair_for_type<int, int>(tr);
    test_dispatcher_template2_pair_for_type<char, int>(tr);
    test_dispatcher_template2_pair_for_type<int, char>(tr);
    test_dispatcher_template2_pair_for_type<char, char>(tr);

    tr.report_summary();
    return tr.success() ? EXIT_SUCCESS : EXIT_FAILURE;
}
