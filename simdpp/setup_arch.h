/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_SETUP_ARCH_H
#define LIBSIMDPP_SIMD_SETUP_ARCH_H

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

#ifdef SIMDPP_ARCH_X86_FMA3
    #ifndef SIMDPP_USE_FMA3
        #define SIMDPP_USE_FMA3 1
    #endif
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

#ifdef SIMDPP_ARCH_X86_FMA4
    #ifndef SIMDPP_USE_FMA4
        #define SIMDPP_USE_FMA4 1
    #endif
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

#ifdef SIMDPP_ARCH_X86_XOP
    #ifndef SIMDPP_USE_XOP
        #define SIMDPP_USE_XOP 1
    #endif
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

#ifdef SIMDPP_ARCH_X86_AVX512F
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
    #ifndef SIMDPP_USE_FMA3
        #define SIMDPP_USE_FMA3 1
    #endif
    #ifndef SIMDPP_USE_AVX512
        #define SIMDPP_USE_AVX512 1
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

#ifdef SIMDPP_ARCH_POWER_ALTIVEC
    #ifndef SIMDPP_USE_ALTIVEC
        #define SIMDPP_USE_ALTIVEC 1
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

#ifdef SIMDPP_USE_FMA3
    #define SIMDPP_PP_FMA3 _fma3
    #include <immintrin.h>
#else
    #define SIMDPP_PP_FMA3
#endif

#ifdef SIMDPP_USE_FMA4
    #define SIMDPP_PP_FMA4 _fma4
    #include <x86intrin.h>
    #ifdef SIMDPP_USE_FMA3
        #error "X86_FMA3 and X86_FMA4 can't be used together"
    #endif
#else
    #define SIMDPP_PP_FMA4
#endif

#ifdef SIMDPP_USE_XOP
    #define SIMDPP_PP_XOP _xop
    #include <x86intrin.h>
#else
    #define SIMDPP_PP_XOP
#endif

#ifdef SIMDPP_USE_AVX512
    #define SIMDPP_PP_AVX512 _avx512
    #include <immintrin.h>
#else
    #define SIMDPP_PP_AVX512
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

#ifdef SIMDPP_USE_ALTIVEC
    #define SIMDPP_PP_ALTIVEC _altivec
    #include <altivec.h>
    #undef vector
    #undef pixel
    #undef bool
#else
    #define SIMDPP_PP_ALTIVEC
#endif

// helper macros
#if __amd64__ || __x86_64__ || _M_AMD64 || __aarch64__ || __powerpc64__
#define SIMDPP_64_BITS 1
#define SIMDPP_32_BITS 0
#else
#define SIMDPP_32_BITS 1
#define SIMDPP_64_BITS 0
#endif

#if SIMDPP_USE_NEON && SIMDPP_64_BITS
#define SIMDPP_USE_NEON_FLT_SP 1
#endif

#define SIMDPP_USE_NEON32 (SIMDPP_USE_NEON && SIMDPP_32_BITS)
#define SIMDPP_USE_NEON64 (SIMDPP_USE_NEON && SIMDPP_64_BITS)
#define SIMDPP_USE_NEON32_FLT_SP (SIMDPP_USE_NEON_FLT_SP && SIMDPP_32_BITS)
#define SIMDPP_USE_NEON_NO_FLT_SP (SIMDPP_USE_NEON && !SIMDPP_USE_NEON_FLT_SP)

#if __i386__ || __i386 || _M_IX86 || __amd64__ || __x64_64__ || _M_AMD64 || _M_X64
#define SIMDPP_X86 1
#elif _M_ARM || __arm__ || __aarch64__
#define SIMDPP_ARM 1
#elif __powerpc__ || __powerpc64__
#define SIMDPP_PPC 1
#endif

/** @def SIMDPP_ARCH_NAMESPACE
    Put all functions to a namespace that depends on the instruction set that
    the library is compiled for. This is needed to avoid violating the One
    Definition Rule.
*/
#define SIMDPP_CONCAT2(a, ...) a ## __VA_ARGS__
#define SIMDPP_CONCAT(a, b) SIMDPP_CONCAT2(a, b)

#define SIMDPP_PP_ARCH_CONCAT0  SIMDPP_CONCAT(arch, SIMDPP_PP_NULL)
#define SIMDPP_PP_ARCH_CONCAT1  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT0, SIMDPP_PP_SSE2)
#define SIMDPP_PP_ARCH_CONCAT2  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT1, SIMDPP_PP_SSE3)
#define SIMDPP_PP_ARCH_CONCAT3  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT2, SIMDPP_PP_SSSE3)
#define SIMDPP_PP_ARCH_CONCAT4  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT3, SIMDPP_PP_SSE4_1)
#define SIMDPP_PP_ARCH_CONCAT5  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT4, SIMDPP_PP_AVX)
#define SIMDPP_PP_ARCH_CONCAT6  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT5, SIMDPP_PP_AVX2)
#define SIMDPP_PP_ARCH_CONCAT7  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT6, SIMDPP_PP_FMA3)
#define SIMDPP_PP_ARCH_CONCAT8  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT7, SIMDPP_PP_FMA4)
#define SIMDPP_PP_ARCH_CONCAT9  SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT8, SIMDPP_PP_XOP)
#define SIMDPP_PP_ARCH_CONCAT10 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT9, SIMDPP_PP_AVX512)
#define SIMDPP_PP_ARCH_CONCAT11 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT10, SIMDPP_PP_NEON)
#define SIMDPP_PP_ARCH_CONCAT12 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT11, SIMDPP_PP_NEON_FLT_SP)
#define SIMDPP_PP_ARCH_CONCAT13 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT12, SIMDPP_PP_ALTIVEC)

#define SIMDPP_ARCH_NAMESPACE SIMDPP_PP_ARCH_CONCAT13



/** @def SIMDPP_ARCH_NAME
    Usable in contexts where a string is required
*/

#define SIMDPP_STRINGIFY2(x) #x
#define SIMDPP_STRINGIFY(x) SIMDPP_STRINGIFY2(x)
#define SIMDPP_ARCH_NAME SIMDPP_STRINGIFY(SIMDPP_ARCH_NAMESPACE)

// workarounds
#if __GNUC__
#define SIMDPP_INL __attribute__((__always_inline__)) inline
#else
#define SIMDPP_INL inline
#endif

#if __GNUC__
#define SIMDPP_ALIGN(X) __attribute__((__aligned__(X)))
#elif _MSC_VER
#define SIMDPP_ALIGN(X) __declspec(align(X))
#else
#error "Unsupported compiler"
#endif

#include <simdpp/detail/workarounds.h>

// #define SIMDPP_EXPR_DEBUG 1

// FIXME: unused (workarounds for AMD CPUs)
// #define SIMDPP_USE_AMD

#endif
