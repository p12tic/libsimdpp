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

#ifndef LIBSIMDPP_DISPATCH_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS_H
#define LIBSIMDPP_DISPATCH_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS_H

#include <simdpp/dispatch/arch.h>

namespace simdpp {

/** Retrieves supported architecture using GCC __builtin_cpu_supports function.
    Works only on x86.
*/
inline Arch get_arch_gcc_builtin_cpu_supports()
{
    Arch arch_info;
#if (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 8)
#if __i386__ || __amd64__
    if (__builtin_cpu_supports("avx2")) {
        arch_info |= Arch::X86_SSE2;
        arch_info |= Arch::X86_SSE3;
        arch_info |= Arch::X86_SSSE3;
        arch_info |= Arch::X86_SSE4_1;
        arch_info |= Arch::X86_AVX;
        arch_info |= Arch::X86_AVX2;
    } else if (__builtin_cpu_supports("avx")) {
        arch_info |= Arch::X86_SSE2;
        arch_info |= Arch::X86_SSE3;
        arch_info |= Arch::X86_SSSE3;
        arch_info |= Arch::X86_SSE4_1;
        arch_info |= Arch::X86_AVX;
    } else if (__builtin_cpu_supports("sse4.1")) {
        arch_info |= Arch::X86_SSE2;
        arch_info |= Arch::X86_SSE3;
        arch_info |= Arch::X86_SSSE3;
        arch_info |= Arch::X86_SSE4_1;
    } else if (__builtin_cpu_supports("ssse3")) {
        arch_info |= Arch::X86_SSE2;
        arch_info |= Arch::X86_SSE3;
        arch_info |= Arch::X86_SSSE3;
    } else if (__builtin_cpu_supports("sse3")) {
        arch_info |= Arch::X86_SSE3;
        arch_info |= Arch::X86_SSE2;
    } else if (__builtin_cpu_supports("sse2")) {
        arch_info |= Arch::X86_SSE2;
    }
#endif
#endif
    return arch_info;
}
} // namespace simdpp

#endif
