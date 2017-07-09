/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include "insn/dispatcher.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>

// Check whether all available getters of supported architecture compiles
// on all compilers
#include <simdpp/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_string_list.h>

static simdpp::Arch g_supported_arch;

simdpp::Arch get_supported_arch()
{
    return g_supported_arch;
}

/*  We test the dispatcher by compiling a
*/
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
    } else if (arch_name == "ARM_NEON") {
        g_supported_arch = Arch::ARM_NEON;
    } else if (arch_name == "ARM_NEON_FLT_SP") {
        g_supported_arch = Arch::ARM_NEON | Arch::ARM_NEON_FLT_SP;
    } else {
        std::cerr << "Invalid architecture specified: " << arch_name << "\n";
        return EXIT_FAILURE;
    }

    Arch selected = test_dispatcher();
    if (selected != g_supported_arch) {
        std::cerr << "Wrong architecture selected: \n"
                  << "  Supported: "
                  << std::hex << static_cast<unsigned>(g_supported_arch)
                  << "\n  Selected: "
                  << std::hex << static_cast<unsigned>(selected) << "\n";
        return EXIT_FAILURE;
    }

    unsigned err = 0;
    if (test_dispatcher1(1) != 1) {
        err |= 1;
    }
    if (test_dispatcher2(1, 2) != 1+2) {
        err |= 2;
    }
    if (test_dispatcher3(1, 2, 3) != 1+2+3) {
        err |= 4;
    }
    if (test_dispatcher4(1, 2, 3, 4) != 1+2+3+4) {
        err |= 8;
    }
    if (err != 0) {
        std::cout << "ERR: " << err << "\n";
        return EXIT_FAILURE;
    }
}
