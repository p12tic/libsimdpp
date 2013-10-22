/*  libsimdpp
    Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_H
#define LIBSIMDPP_SIMD_H

/** @mainpage

    libsimdpp is a header-only zero-overhead C++ wrapper around SIMD intrinsics.
    It supports multiple instruction sets via single interface. The same source
    code may be compiled for different instruction sets and linked to the same
    resulting binary. The library provides a convenient dynamic dispatch
    mechanism to select the fastest version of a function for the target
    processor.

    To use the library, define one or more macros that specify the instruction
    set (architecture) of the target processor and then include @c
    simdpp/simd.h. The following instruction sets are supported:

    - @c NONE_NULL:

        The instructions are not vectorized and use standard C++.
        This instruction set is used if no SIMD instruction set is selected.
        (no macro defined).

    - @c X86_SSE2:

        The x86/x86_64 SSE and SSE2 instruction sets are used.

        Macro: @c SIMDPP_ARCH_X86_SSE2.

    - @c X86_SSE3:

        The x86/x86_64 SSE3 instruction set is used. The SSE and SSE2
        instruction set support is required implicitly (no need to define the
        macros for these instruction sets).

        Macro: @c SIMDPP_ARCH_X86_SSE3.

    - @c X86_SSSE3:

        The x86/x86_64 SSSE3 instruction set is used. The SSE, SSE2 and SSE3
        instruction set support is required implicitly (no need to define the
        macros for these instruction sets).

        Macro: @c SIMDPP_ARCH_X86_SSSE3.

    - @c X86_SSE4.1:

        The x86/x86_64 SSE4.1 instruction set is used. The SSE, SSE2 and SSE3
        instruction set support is required implicitly (no need to define the
        macros for these instruction sets).

        Macro: @c SIMDPP_ARCH_X86_SSE4_1.

    - @c X86_AVX:

        The x86/x86_64 AVX instruction set is used. The SSE, SSE2, SSE3 and
        SSSE3 instruction set support is required implicitly (no need to define
        the macros for these instruction sets).

        Macro: @c SIMDPP_ARCH_X86_AVX.

    - @c X86_AVX2:

        The x86/x86_64 AVX2 instruction set is used. The SSE, SSE2, SSE3, SSSE3
        and AVX instruction set support is required implicitly (no need to
        define the macros for these instruction sets).

        Macro: @c SIMDPP_ARCH_X86_AVX2.

    - @c ARM_NEON:

        The ARM NEON instruction set. The VFP co-processor is used for any
        floating-point functionality (NEON does not require the implementation
        to be IEEE-754 compliant, whereas VFP does).

        Macro @c SIMDPP_ARCH_ARM_NEON

    - @c ARM_NEON_FLT_SP:

        Performs 32-bit floating-point computations on the NEON vector unit.
        The NEON instruction set support is required implicitly (no need to
        define the macro for that instruction set).

        Macro @c SIMDPP_ARCH_ARM_NEON_FLT_SP.

    If the user wants to include several versions of the same code, compiled
    for different architectures sets, into the same executable, then all such
    code @a must be put into @c SIMDPP_ARCH_NAMESPACE namespace. This macro
    evaluates to an identifier which is unique for each architecture.

    In addition to the above, the source file must not define any of the
    architecture select macros; they must be supplied via the compiler options.
    The code for @c NONE_NULL architecture must be linked to the resulting
    executable.

    To use dynamic dispatch mechanism, declare the function within an
    @c SIMDPP_ARCH_NAMESPACE and then use one of @c SIMDPP_MAKE_DISPATCHER_***
    macros.

    Dynamic dispatch example
    ------------------------

    The following example demonstrates the simpliest usage of dynamic dispatch:

    @code
    // test.h
    void print_arch();
    @endcode

    @code
    // test.cc
    #include "test.h"
    #include <simdpp/simd.h>
    #include <iostream>

    namespace SIMDPP_ARCH_NAMESPACE {

    void print_arch()
    {
        std::cout << static_cast<unsigned>(simdpp::this_compile_arch()) << '\n';
    }

    } // namespace SIMDPP_ARCH_NAMESPACE

    SIMDPP_MAKE_DISPATCHER_VOID0(print_arch);
    @endcode

    @code
    // main.cc
    #include "test.h"

    int main()
    {
        print_arch();
    }
    @endcode

    @code
    #Makefile

    CXXFLAGS="-std=c++11"

    test: main.o test_sse2.o test_sse3.o test_sse4_1.o test_null.o
        g++ $^ -lpthread -o test

    main.o: main.cc
        g++ main.cc $(CXXFLAGS) -c -o main.o

    # inclusion of NONE_NULL is mandatory
    test_null.o: test.cc
        g++ test.cc -c $(CXXFLAGS) -o test_sse2.o

    test_sse2.o: test.cc
        g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE2 -msse2 -o test_sse2.o

    test_sse3.o: test.cc
        g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE3 -msse3 -o test_sse3.o

    test_sse4_1.o: test.cc
        g++ test.cc -c $(CXXFLAGS) -DSIMDPP_ARCH_X86_SSE4_1 -msse4.1 -o test_sse3.o
    @endcode

    If compiled, the above example selects the "fastest" of SSE2, SSE3 or SSE4.1
    instruction sets, whichever is available on the target processor and
    outputs an integer that identifiers that instruction set.

    Note, that the object files must be linked directly to the executable. If
    static libraries are used, the linker may throw out static dispatcher
    registration code and break the mechanism. Do prevent this behavior,
    @c -Wl,--whole-archive or an equivalent flag must be used.

    CMake
    -----

    For CMake users, @c cmake/SimdppMultiarch.cmake contains several useful
    functions:
     - @c simdpp_get_compilable_archs: checks what architectures are
        supported by the compiler.
     - @c simdpp_get_runnable_archs: checks what architectures are supported by
        both the compiler and the current processor.
     - @c simdpp_multiversion: given a list of architectures (possibly
        generated by @c simdpp_get_compilable_archs or
        @c simdpp_get_runnable_archs), automatically configures compilation of
        additional objects. The user only needs to add the returned list of
        source files to @c add_library or @c add_executable.

    The above example may be build with @c CMakeLists.txt as simple as follows:
    @code
    cmake_minimum_required(VERSION 2.8.0)
    project(test)

    include(SimdppMultiarch)

    simdpp_get_runnable_archs(RUNNABLE_ARCHS)
    simdpp_multiarch(GEN_ARCH_FILES test.cc ${RUNNABLE_ARCHS})
    add_executable(test main.cc ${GEN_ARCH_FILES})
    target_link_libraries(test pthread)
    set_target_properties(test PROPERTIES COMPILE_FLAGS "-std=c++11")
    @endcode
*/

#ifdef SIMDPP_ARCH_X86_SSE2
    #ifndef SIMDPP_USE_SSE2
        #define SIMDPP_USE_SSE2 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_X86_SSE3
    #ifndef SIMDPP_USE_SSE2
        #define SIMDPP_USE_SSE2 1
    #endif
    #ifndef SIMDPP_USE_SSE3
        #define SIMDPP_USE_SSE3 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_X86_SSSE3
    #ifndef SIMDPP_USE_SSE2
        #define SIMDPP_USE_SSE2 1
    #endif
    #ifndef SIMDPP_USE_SSE3
        #define SIMDPP_USE_SSE3 1
    #endif
    #ifndef SIMDPP_USE_SSSE3
        #define SIMDPP_USE_SSSE3 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_X86_SSE4_1
    #ifndef SIMDPP_USE_SSE2
        #define SIMDPP_USE_SSE2 1
    #endif
    #ifndef SIMDPP_USE_SSE3
        #define SIMDPP_USE_SSE3 1
    #endif
    #ifndef SIMDPP_USE_SSSE3
        #define SIMDPP_USE_SSSE3 1
    #endif
    #ifndef SIMDPP_USE_SSE4_1
        #define SIMDPP_USE_SSE4_1 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_X86_AVX
    #ifndef SIMDPP_USE_SSE2
        #define SIMDPP_USE_SSE2 1
    #endif
    #ifndef SIMDPP_USE_SSE3
        #define SIMDPP_USE_SSE3 1
    #endif
    #ifndef SIMDPP_USE_SSSE3
        #define SIMDPP_USE_SSSE3 1
    #endif
    #ifndef SIMDPP_USE_SSE4_1
        #define SIMDPP_USE_SSE4_1 1
    #endif
    #ifndef SIMDPP_USE_AVX
        #define SIMDPP_USE_AVX 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_X86_AVX2
    #ifndef SIMDPP_USE_SSE2
        #define SIMDPP_USE_SSE2 1
    #endif
    #ifndef SIMDPP_USE_SSE3
        #define SIMDPP_USE_SSE3 1
    #endif
    #ifndef SIMDPP_USE_SSSE3
        #define SIMDPP_USE_SSSE3 1
    #endif
    #ifndef SIMDPP_USE_SSE4_1
        #define SIMDPP_USE_SSE4_1 1
    #endif
    #ifndef SIMDPP_USE_AVX
        #define SIMDPP_USE_AVX 1
    #endif
    #ifndef SIMDPP_USE_AVX2
        #define SIMDPP_USE_AVX2 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_ARM_NEON
    #ifndef SIMDPP_USE_NEON
        #define SIMDPP_USE_NEON 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifdef SIMDPP_ARCH_ARM_NEON_FLT_SP
    #ifndef SIMDPP_USE_NEON
        #define SIMDPP_USE_NEON 1
    #endif
    #ifndef SIMDPP_USE_NEON_FLT_SP
        #define SIMDPP_USE_NEON_FLT_SP 1
    #endif
    #ifndef SIMDPP_ARCH_NOT_NULL
        #define SIMDPP_ARCH_NOT_NULL
    #endif
#endif

#ifndef SIMDPP_ARCH_NOT_NULL
    #define SIMDPP_USE_NULL 1
    #define SIMDPP_PP_NULL _null
#else
    #define SIMDPP_PP_NULL
#endif

#ifdef SIMDPP_USE_SSE2
    #define SIMDPP_PP_SSE2 _sse2
    #include <xmmintrin.h>
    #include <emmintrin.h>
#else
    #define SIMDPP_PP_SSE2
#endif

#ifdef SIMDPP_USE_SSE3
    #define SIMDPP_PP_SSE3 _sse3
    #include <pmmintrin.h>
#else
    #define SIMDPP_PP_SSE3
#endif

#ifdef SIMDPP_USE_SSSE3
    #define SIMDPP_PP_SSSE3 _ssse3
    #include <tmmintrin.h>
#else
    #define SIMDPP_PP_SSSE3
#endif

#ifdef SIMDPP_USE_SSE4_1
    #define SIMDPP_PP_SSE4_1 _sse4p1
    #include <smmintrin.h>
#else
    #define SIMDPP_PP_SSE4_1
#endif

#ifdef SIMDPP_USE_AVX
    #define SIMDPP_PP_AVX _avx
    #include <immintrin.h>
#else
    #define SIMDPP_PP_AVX
#endif

#ifdef SIMDPP_USE_AVX2
    #define SIMDPP_PP_AVX2 _avx2
    #include <immintrin.h>
#else
    #define SIMDPP_PP_AVX2
#endif
#ifdef SIMDPP_USE_NEON
    #define SIMDPP_PP_NEON _neon
    #include <arm_neon.h>
#else
    #define SIMDPP_PP_NEON
#endif

#ifdef SIMDPP_USE_NEON_FLT_SP
    #define SIMDPP_PP_NEON_FLT_SP _neonfltsp
#else
    #define SIMDPP_PP_NEON_FLT_SP
#endif

/** @def SIMDPP_ARCH_NAMESPACE
    Put all functions to a namespace that depends on the instruction set that
    the library is compiled for. This is needed to avoid violating the One
    Definition Rule.
*/
#define SIMDPP_CONCAT2(a, ...) a ## __VA_ARGS__
#define SIMDPP_CONCAT(a, b) SIMDPP_CONCAT2(a, b)

#define SIMDPP_PP_ARCH_CONCAT0 SIMDPP_CONCAT(arch, SIMDPP_PP_NULL)
#define SIMDPP_PP_ARCH_CONCAT1 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT0, SIMDPP_PP_SSE2)
#define SIMDPP_PP_ARCH_CONCAT2 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT1, SIMDPP_PP_SSE3)
#define SIMDPP_PP_ARCH_CONCAT3 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT2, SIMDPP_PP_SSSE3)
#define SIMDPP_PP_ARCH_CONCAT4 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT3, SIMDPP_PP_SSE4_1)
#define SIMDPP_PP_ARCH_CONCAT5 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT4, SIMDPP_PP_AVX)
#define SIMDPP_PP_ARCH_CONCAT6 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT5, SIMDPP_PP_AVX2)
#define SIMDPP_PP_ARCH_CONCAT7 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT6, SIMDPP_PP_NEON)
#define SIMDPP_PP_ARCH_CONCAT8 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT7, SIMDPP_PP_NEON_FLT_SP)

#define SIMDPP_ARCH_NAMESPACE SIMDPP_PP_ARCH_CONCAT8

/** @def SIMDPP_ARCH_NAME
    Usable in contexts where a string is required
*/

#define SIMDPP_STRINGIFY2(x) #x
#define SIMDPP_STRINGIFY(x) SIMDPP_STRINGIFY2(x)
#define SIMDPP_ARCH_NAME SIMDPP_STRINGIFY(SIMDPP_ARCH_NAMESPACE)

#include <cstdlib>

#include <simdpp/simd/fwd.h>

#include <simdpp/simd/int128.h>
#include <simdpp/simd/int8x16.h>
#include <simdpp/simd/int16x8.h>
#include <simdpp/simd/int32x4.h>
#include <simdpp/simd/int64x2.h>
#include <simdpp/simd/float64x2.h>
#include <simdpp/simd/float32x4.h>

#include <simdpp/simd/detail/not_implemented.h>

#include <simdpp/simd/cache.h>
#include <simdpp/simd/bitwise.h>
#include <simdpp/simd/math_shift.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/make_shuffle_bytes_mask.h>
#include <simdpp/simd/shuffle_bytes.h>
#include <simdpp/simd/shuffle_generic.h>
#include <simdpp/simd/memory_load.h>
#include <simdpp/simd/memory_store.h>

#include <simdpp/simd/compare.h>
#include <simdpp/simd/math_int_basic.h>
#include <simdpp/simd/math_int_adv.h>
#include <simdpp/simd/convert.h>
#include <simdpp/simd/math_fp_basic.h>
#include <simdpp/simd/math_fp_adv.h>

#include <simdpp/simd/insert.h>
#include <simdpp/simd/extract.h>

#include <simdpp/simd/int128.inl>
#include <simdpp/simd/int8x16.inl>
#include <simdpp/simd/int16x8.inl>
#include <simdpp/simd/int32x4.inl>
#include <simdpp/simd/int64x2.inl>
#include <simdpp/simd/float32x4.inl>
#include <simdpp/simd/float64x2.inl>

#include <simdpp/simd/int256.inl>
#include <simdpp/simd/int8x32.inl>
#include <simdpp/simd/int16x16.inl>
#include <simdpp/simd/int32x8.inl>
#include <simdpp/simd/int64x4.inl>
#include <simdpp/simd/float32x8.inl>
#include <simdpp/simd/float64x4.inl>

#include <simdpp/simd/this_compile_arch.h>

#include <simdpp/dispatcher.h>
#include <simdpp/simd/detail/traits.h>

namespace simdpp {
using namespace SIMDPP_ARCH_NAMESPACE;
} // namespace simdpp

#endif
