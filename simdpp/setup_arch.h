/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_SETUP_ARCH_H
#define LIBSIMDPP_SIMD_SETUP_ARCH_H

#include <simdpp/detail/preprocessor.h>

// Set up macros for current architecture. Note that this file may be included
// multiple times, more information on the caveats are within the file.
#include <simdpp/detail/preprocess_single_arch.h>

// Set up main feature macros
#if SIMDPP_ARCH_PP_USE_NULL
#define SIMDPP_USE_NULL 1
#else
#define SIMDPP_USE_NULL 0
#endif
#if SIMDPP_ARCH_PP_USE_SSE2
#define SIMDPP_USE_SSE2 1
#else
#define SIMDPP_USE_SSE2 0
#endif
#if SIMDPP_ARCH_PP_USE_SSE3
#define SIMDPP_USE_SSE3 1
#else
#define SIMDPP_USE_SSE3 0
#endif
#if SIMDPP_ARCH_PP_USE_SSSE3
#define SIMDPP_USE_SSSE3 1
#else
#define SIMDPP_USE_SSSE3 0
#endif
#if SIMDPP_ARCH_PP_USE_SSE4_1
#define SIMDPP_USE_SSE4_1 1
#else
#define SIMDPP_USE_SSE4_1 0
#endif
#if SIMDPP_ARCH_PP_USE_AVX
#define SIMDPP_USE_AVX 1
#else
#define SIMDPP_USE_AVX 0
#endif
#if SIMDPP_ARCH_PP_USE_AVX2
#define SIMDPP_USE_AVX2 1
#else
#define SIMDPP_USE_AVX2 0
#endif
#if SIMDPP_ARCH_PP_USE_FMA3
#define SIMDPP_USE_FMA3 1
#else
#define SIMDPP_USE_FMA3 0
#endif
#if SIMDPP_ARCH_PP_USE_FMA4
#define SIMDPP_USE_FMA4 1
#else
#define SIMDPP_USE_FMA4 0
#endif
#if SIMDPP_ARCH_PP_USE_XOP
#define SIMDPP_USE_XOP 1
#else
#define SIMDPP_USE_XOP 0
#endif
#if SIMDPP_ARCH_PP_USE_AVX512F
#define SIMDPP_USE_AVX512F 1
#else
#define SIMDPP_USE_AVX512F 0
#endif
#if SIMDPP_ARCH_PP_USE_NEON
#define SIMDPP_USE_NEON 1
#else
#define SIMDPP_USE_NEON 0
#endif
#if SIMDPP_ARCH_PP_USE_NEON_FLT_SP
#define SIMDPP_USE_NEON_FLT_SP 1
#else
#define SIMDPP_USE_NEON_FLT_SP 0
#endif
#if SIMDPP_ARCH_PP_USE_ALTIVEC
#define SIMDPP_USE_ALTIVEC 1
#else
#define SIMDPP_USE_ALTIVEC 0
#endif

// Generate SIMDPP_ARCH_NAMESPACE. It's a human-readable identifier depending
// on the enabled instruction sets
#if SIMDPP_ARCH_PP_NS_USE_NULL
#define SIMDPP_NS_ID_NULL SIMDPP_INSN_ID_NULL
#else
#define SIMDPP_NS_ID_NULL
#endif
#if SIMDPP_ARCH_PP_NS_USE_SSE2
#define SIMDPP_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
#else
#define SIMDPP_NS_ID_SSE2
#endif
#if SIMDPP_ARCH_PP_NS_USE_SSE3
#define SIMDPP_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
#else
#define SIMDPP_NS_ID_SSE3
#endif
#if SIMDPP_ARCH_PP_NS_USE_SSSE3
#define SIMDPP_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
#else
#define SIMDPP_NS_ID_SSSE3
#endif
#if SIMDPP_ARCH_PP_NS_USE_SSE4_1
#define SIMDPP_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
#else
#define SIMDPP_NS_ID_SSE4_1
#endif
#if SIMDPP_ARCH_PP_NS_USE_AVX
#define SIMDPP_NS_ID_AVX SIMDPP_INSN_ID_AVX
#else
#define SIMDPP_NS_ID_AVX
#endif
#if SIMDPP_ARCH_PP_NS_USE_AVX2
#define SIMDPP_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
#else
#define SIMDPP_NS_ID_AVX2
#endif
#if SIMDPP_ARCH_PP_NS_USE_FMA3
#define SIMDPP_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
#else
#define SIMDPP_NS_ID_FMA3
#endif
#if SIMDPP_ARCH_PP_NS_USE_FMA4
#define SIMDPP_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
#else
#define SIMDPP_NS_ID_FMA4
#endif
#if SIMDPP_ARCH_PP_NS_USE_XOP
#define SIMDPP_NS_ID_XOP SIMDPP_INSN_ID_XOP
#else
#define SIMDPP_NS_ID_XOP
#endif
#if SIMDPP_ARCH_PP_NS_USE_AVX512F
#define SIMDPP_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
#else
#define SIMDPP_NS_ID_AVX512F
#endif
#if SIMDPP_ARCH_PP_NS_USE_NEON
#define SIMDPP_NS_ID_NEON SIMDPP_INSN_ID_NEON
#else
#define SIMDPP_NS_ID_NEON
#endif
#if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
#define SIMDPP_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
#else
#define SIMDPP_NS_ID_NEON_FLT_SP
#endif
#if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
#define SIMDPP_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
#else
#define SIMDPP_NS_ID_ALTIVEC
#endif

#define SIMDPP_ARCH_NAMESPACE SIMDPP_PP_PASTE15(arch, \
	SIMDPP_NS_ID_NULL, SIMDPP_NS_ID_SSE2, SIMDPP_NS_ID_SSE3,                \
    SIMDPP_NS_ID_SSSE3, SIMDPP_NS_ID_SSE4_1, SIMDPP_NS_ID_AVX,              \
    SIMDPP_NS_ID_AVX2, SIMDPP_NS_ID_AVX512F, SIMDPP_NS_ID_FMA3,             \
    SIMDPP_NS_ID_FMA4, SIMDPP_NS_ID_XOP, SIMDPP_NS_ID_NEON,                 \
    SIMDPP_NS_ID_NEON_FLT_SP, SIMDPP_NS_ID_ALTIVEC)

// Include headers relevant for the enabled instruction sets.
#if SIMDPP_USE_SSE2
    #include <xmmintrin.h>
    #include <emmintrin.h>
#endif

#if SIMDPP_USE_SSE3
    #include <pmmintrin.h>
#endif

#if SIMDPP_USE_SSSE3
    #include <tmmintrin.h>
#endif

#if SIMDPP_USE_SSE4_1
    #include <smmintrin.h>
#endif

#if SIMDPP_USE_AVX
    #include <immintrin.h>
#endif

#if SIMDPP_USE_AVX2
    #include <immintrin.h>
#endif

#if SIMDPP_USE_FMA3
    #include <immintrin.h>
#endif

#if SIMDPP_USE_FMA4
    #include <x86intrin.h>
    #if SIMDPP_USE_FMA3
        #error "X86_FMA3 and X86_FMA4 can't be used together"
    #endif
#endif

#if SIMDPP_USE_XOP
    #include <x86intrin.h>
#endif

#if SIMDPP_USE_AVX512F
    #include <immintrin.h>
#endif

#if SIMDPP_USE_NEON || SIMDPP_USE_NEON_FLT_SP
    #include <arm_neon.h>
#endif

#if SIMDPP_USE_ALTIVEC
    #include <altivec.h>
    #undef vector
    #undef pixel
    #undef bool
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
#undef SIMDPP_USE_NEON_FLT_SP
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

/** @def SIMDPP_ARCH_NAME
    Usable in contexts where a string is required
*/
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
