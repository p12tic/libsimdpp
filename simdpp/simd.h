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

    - @c X86_FMA3:

        The Intel x86/x86_64 FMA3 instruction set is used. The SSE, SSE2, SSE3
        instruction set support is required implicitly (no need to define the
        macros for these instruction sets). This instruction set must not be
        combined with X86_FMA4.

        Macro: @c SIMDPP_ARCH_X86_FMA3.

    - @c X86_FMA4:

        The AMD x86/x86_64 FMA4 instruction set is used. The SSE, SSE2, SSE3
        instruction set support is required implicitly (no need to define the
        macros for these instruction sets). This instruction set must not be
        combined with X86_FMA3.

        Macro: @c SIMDPP_ARCH_X86_FMA4.

    - @c X86_XOP:

        The AMD x86/x86_64 XOP instruction set is used. The SSE, SSE2, SSE3
        instruction set support is required implicitly (no need to define
        the macros for these instruction sets).

        Macro: @c SIMDPP_ARCH_X86_XOP.

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

    - @c POWER_ALTIVEC:

        The POWER Altivec instruction set. 64-bit floating point operations
        are not vectorized.

        Macro @c SIMDPP_ARCH_POWER_ALTIVEC.

    Instruction counts
    ------------------

    In this documentation all functions that map to more than one instruction
    are marked as such by listing the number of instructions that are used to
    implement a function. The instructions are counted as follows:

     - Any register-register moves and copies that do not cross the processor
        domains are ignored;
     - Non-vector domain instructions are ignored except when they move data
        to or from memory or vector domain.
     - If the implementation of a function is dependent on template arguments
        (for example, element selector), then the instruction count is defined
        as a range with both lower and upper bounds
     - If the function loads or computes static data, then the instruction
        count is defined as a range. The lower count calculated as if the loads
        from memory or computation didn't happen (for example, if the function
        was used in a small loop and there were enough registers to cache the
        data). The upper count is calculated the other way round.

    If instruction count is not listed for specific architecture, then the
    function directly maps to one instruction. This rule does not apply to the
    following architectures:

    @c X86_FMA3, @c X86_FMA4 and @c X86_XOP.

    For these, if instruction count is not listed, the instruction counts
    should be interpreted as if the architecture is not supported.

    Note, that instruction count is very, very imprecise way to measure
    performance. It is provided just as a quick way to estimate how well
    specific functionality maps to target architecture.

    Dynamic dispatch
    ----------------

    If the user wants to include several versions of the same code, compiled
    for different architectures sets into the same executable, then all such
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

/* The following file sets up the preprocessor variables and includes the
   required system headers for the specific architecture
*/
#include <simdpp/setup_arch.h>

#include <cstdlib>


#include <simdpp/adv/transpose.h>
#include <simdpp/altivec/load1.h>
#include <simdpp/core/align.h>
#include <simdpp/core/aligned_allocator.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_not.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/broadcast.h>
#include <simdpp/core/broadcast_w.h>
#include <simdpp/core/cache.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/cmp_eq.h>
#include <simdpp/core/cmp_ge.h>
#include <simdpp/core/cmp_gt.h>
#include <simdpp/core/cmp_le.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/cmp_neq.h>
#include <simdpp/core/extract.h>
#include <simdpp/core/f_abs.h>
#include <simdpp/core/f_add.h>
#include <simdpp/core/f_ceil.h>
#include <simdpp/core/f_div.h>
#include <simdpp/core/f_floor.h>
#include <simdpp/core/f_fmadd.h>
#include <simdpp/core/f_fmsub.h>
#include <simdpp/core/f_isnan.h>
#include <simdpp/core/f_isnan2.h>
#include <simdpp/core/f_max.h>
#include <simdpp/core/f_min.h>
#include <simdpp/core/f_mul.h>
#include <simdpp/core/f_neg.h>
#include <simdpp/core/f_rcp_e.h>
#include <simdpp/core/f_rcp_rh.h>
#include <simdpp/core/f_rsqrt_e.h>
#include <simdpp/core/f_rsqrt_rh.h>
#include <simdpp/core/f_sign.h>
#include <simdpp/core/f_sqrt.h>
#include <simdpp/core/f_sub.h>
#include <simdpp/core/f_trunc.h>
#include <simdpp/core/i_abs.h>
#include <simdpp/core/i_add.h>
#include <simdpp/core/i_adds.h>
#include <simdpp/core/i_avg.h>
#include <simdpp/core/i_avg_trunc.h>
#include <simdpp/core/i_div_p.h>
#include <simdpp/core/i_max.h>
#include <simdpp/core/i_min.h>
#include <simdpp/core/i_mul.h>
#include <simdpp/core/i_mull.h>
#include <simdpp/core/i_neg.h>
#include <simdpp/core/i_shift_l.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/core/i_subs.h>
#include <simdpp/core/insert.h>
#include <simdpp/core/load.h>
#include <simdpp/core/load_packed2.h>
#include <simdpp/core/load_packed3.h>
#include <simdpp/core/load_packed4.h>
#include <simdpp/core/load_u.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/move_r.h>
#include <simdpp/core/permute2.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/permute_bytes16.h>
#include <simdpp/core/permute_zbytes16.h>
#include <simdpp/core/shuffle1.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/shuffle_bytes16.h>
#include <simdpp/core/shuffle_zbytes16.h>
#include <simdpp/core/store.h>
#include <simdpp/core/store_first.h>
#include <simdpp/core/store_last.h>
#include <simdpp/core/store_packed2.h>
#include <simdpp/core/store_packed3.h>
#include <simdpp/core/store_packed4.h>
#include <simdpp/core/stream.h>
#include <simdpp/core/to_float32.h>
#include <simdpp/core/to_float64.h>
#include <simdpp/core/to_int16.h>
#include <simdpp/core/to_int32.h>
#include <simdpp/core/to_int64.h>
#include <simdpp/core/to_int8.h>
#include <simdpp/core/unzip_hi.h>
#include <simdpp/core/unzip_lo.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/detail/cast.h>
#include <simdpp/core/detail/cast.inl>

#include <simdpp/neon/math_int.h>
#include <simdpp/neon/memory_store.h>
#include <simdpp/neon/shuffle.h>

#include <simdpp/null/bitwise.h>
#include <simdpp/null/compare.h>
#include <simdpp/null/foreach.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/math.h>
#include <simdpp/null/memory.h>
#include <simdpp/null/set.h>
#include <simdpp/null/shuffle.h>
#include <simdpp/null/transpose.h>

#include <simdpp/sse/cache.h>
#include <simdpp/sse/compare.h>
#include <simdpp/sse/convert.h>
#include <simdpp/sse/extract_half.h>
#include <simdpp/sse/math_fp.h>
#include <simdpp/sse/math_int.h>
#include <simdpp/sse/memory_load.h>
#include <simdpp/sse/memory_store.h>
#include <simdpp/sse/shuffle.h>

#include <simdpp/types.h>
#include <simdpp/types/float32.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/types/float32x4.inl>
#include <simdpp/types/float32x8.h>
#include <simdpp/types/float32x8.inl>
#include <simdpp/types/float64.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/float64x2.inl>
#include <simdpp/types/float64x4.h>
#include <simdpp/types/float64x4.inl>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int16.h>
#include <simdpp/types/int16.inl>
#include <simdpp/types/int16x16.h>
#include <simdpp/types/int16x16.inl>
#include <simdpp/types/int16x8.h>
#include <simdpp/types/int16x8.inl>
#include <simdpp/types/int32.h>
#include <simdpp/types/int32.inl>
#include <simdpp/types/int32x4.h>
#include <simdpp/types/int32x4.inl>
#include <simdpp/types/int32x8.h>
#include <simdpp/types/int32x8.inl>
#include <simdpp/types/int64.h>
#include <simdpp/types/int64.inl>
#include <simdpp/types/int64x2.h>
#include <simdpp/types/int64x2.inl>
#include <simdpp/types/int64x4.h>
#include <simdpp/types/int64x4.inl>
#include <simdpp/types/int8.h>
#include <simdpp/types/int8.inl>
#include <simdpp/types/int8x16.h>
#include <simdpp/types/int8x16.inl>
#include <simdpp/types/int8x32.h>
#include <simdpp/types/int8x32.inl>
#include <simdpp/types/traits.h>

/** @def SIMDPP_NO_DISPATCHER
    Disables internal dispatching functionality. If the internal dispathcher
    mechanism is not needed, the user can define the @c SIMDPP_NO_DISPATCHER.
    On cxx98 branch, this results in the library not depending on boost.
*/
#ifndef SIMDPP_NO_DISPATCHER
#include <simdpp/this_compile_arch.h>
#include <simdpp/dispatch/dispatcher.h>
#endif

namespace simdpp {
using namespace SIMDPP_ARCH_NAMESPACE;
namespace detail {
using namespace ::simdpp::SIMDPP_ARCH_NAMESPACE::detail;
} // namespace detail
} // namespace simdpp

#endif
