/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#include "tests/dispatcher.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

static simdpp::Arch g_supported_arch;

simdpp::ArchUserInfo get_supported_arch()
{
    simdpp::ArchUserInfo res;
    res.supported = g_supported_arch;
    res.not_supported = ~res.supported;
    return res;
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
}
