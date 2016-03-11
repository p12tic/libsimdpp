/*  Copyright (C) 2015  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/


// This file is generated automatically. See tools/gen_dispatcher_collect_macros.py

#ifndef LIBSIMDPP_DISPATCH_COLLECT_MACROS_GENERATED_H
#define LIBSIMDPP_DISPATCH_COLLECT_MACROS_GENERATED_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#if SIMDPP_EMIT_DISPATCHER

#define SIMDPP_DISPATCH_MAX_ARCHS 15


#ifdef SIMDPP_DISPATCH_ARCH1
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH1
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_1_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_1_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_1_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_1_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_1_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_1_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_1_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_1_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_1_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_1_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_1_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_1_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_1_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_1_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_1_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_1_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_1_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_1_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_1_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_1_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_1_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_1_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_1_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_1_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_1_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_1_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_1_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_1_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_1_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_1_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_1_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_1_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[1-1] = SIMDPP_DISPATCH_1_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_1_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_1_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_1_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_1_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH2
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH2
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_2_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_2_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_2_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_2_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_2_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_2_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_2_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_2_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_2_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_2_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_2_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_2_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_2_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_2_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_2_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_2_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_2_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_2_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_2_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_2_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_2_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_2_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_2_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_2_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_2_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_2_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_2_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_2_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_2_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_2_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_2_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_2_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[2-1] = SIMDPP_DISPATCH_2_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_2_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_2_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_2_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_2_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH3
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH3
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_3_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_3_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_3_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_3_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_3_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_3_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_3_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_3_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_3_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_3_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_3_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_3_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_3_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_3_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_3_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_3_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_3_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_3_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_3_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_3_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_3_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_3_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_3_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_3_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_3_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_3_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_3_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_3_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_3_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_3_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_3_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_3_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[3-1] = SIMDPP_DISPATCH_3_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_3_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_3_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_3_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_3_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH4
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH4
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_4_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_4_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_4_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_4_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_4_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_4_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_4_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_4_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_4_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_4_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_4_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_4_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_4_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_4_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_4_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_4_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_4_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_4_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_4_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_4_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_4_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_4_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_4_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_4_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_4_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_4_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_4_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_4_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_4_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_4_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_4_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_4_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[4-1] = SIMDPP_DISPATCH_4_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_4_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_4_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_4_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_4_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH5
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH5
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_5_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_5_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_5_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_5_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_5_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_5_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_5_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_5_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_5_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_5_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_5_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_5_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_5_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_5_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_5_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_5_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_5_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_5_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_5_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_5_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_5_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_5_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_5_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_5_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_5_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_5_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_5_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_5_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_5_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_5_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_5_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_5_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[5-1] = SIMDPP_DISPATCH_5_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_5_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_5_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_5_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_5_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH6
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH6
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_6_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_6_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_6_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_6_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_6_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_6_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_6_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_6_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_6_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_6_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_6_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_6_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_6_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_6_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_6_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_6_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_6_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_6_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_6_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_6_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_6_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_6_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_6_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_6_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_6_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_6_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_6_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_6_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_6_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_6_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_6_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_6_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[6-1] = SIMDPP_DISPATCH_6_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_6_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_6_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_6_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_6_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH7
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH7
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_7_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_7_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_7_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_7_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_7_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_7_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_7_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_7_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_7_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_7_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_7_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_7_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_7_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_7_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_7_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_7_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_7_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_7_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_7_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_7_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_7_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_7_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_7_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_7_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_7_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_7_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_7_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_7_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_7_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_7_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_7_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_7_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[7-1] = SIMDPP_DISPATCH_7_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_7_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_7_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_7_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_7_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH8
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH8
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_8_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_8_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_8_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_8_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_8_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_8_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_8_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_8_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_8_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_8_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_8_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_8_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_8_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_8_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_8_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_8_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_8_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_8_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_8_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_8_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_8_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_8_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_8_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_8_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_8_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_8_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_8_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_8_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_8_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_8_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_8_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_8_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[8-1] = SIMDPP_DISPATCH_8_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_8_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_8_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_8_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_8_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH9
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH9
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_9_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_9_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_9_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_9_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_9_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_9_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_9_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_9_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_9_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_9_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_9_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_9_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_9_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_9_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_9_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_9_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_9_NAMESPACE SIMDPP_PP_PASTE15(arch,               \
        SIMDPP_DISPATCH_9_NS_ID_NULL,                                         \
        SIMDPP_DISPATCH_9_NS_ID_SSE2,                                         \
        SIMDPP_DISPATCH_9_NS_ID_SSE3,                                         \
        SIMDPP_DISPATCH_9_NS_ID_SSSE3,                                        \
        SIMDPP_DISPATCH_9_NS_ID_SSE4_1,                                       \
        SIMDPP_DISPATCH_9_NS_ID_AVX,                                          \
        SIMDPP_DISPATCH_9_NS_ID_AVX2,                                         \
        SIMDPP_DISPATCH_9_NS_ID_AVX512F,                                      \
        SIMDPP_DISPATCH_9_NS_ID_FMA3,                                         \
        SIMDPP_DISPATCH_9_NS_ID_FMA4,                                         \
        SIMDPP_DISPATCH_9_NS_ID_XOP,                                          \
        SIMDPP_DISPATCH_9_NS_ID_NEON,                                         \
        SIMDPP_DISPATCH_9_NS_ID_NEON_FLT_SP,                                  \
        SIMDPP_DISPATCH_9_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_9_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                \
        ARRAY[9-1] = SIMDPP_DISPATCH_9_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_9_FN_DECLARE(NAME,FUN_TYPE)                       \
        namespace SIMDPP_DISPATCH_9_NAMESPACE {                               \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_9_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_9_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH10
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH10
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_10_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_10_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_10_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_10_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_10_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_10_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_10_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_10_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_10_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_10_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_10_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_10_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_10_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_10_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_10_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_10_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_10_NAMESPACE SIMDPP_PP_PASTE15(arch,              \
        SIMDPP_DISPATCH_10_NS_ID_NULL,                                        \
        SIMDPP_DISPATCH_10_NS_ID_SSE2,                                        \
        SIMDPP_DISPATCH_10_NS_ID_SSE3,                                        \
        SIMDPP_DISPATCH_10_NS_ID_SSSE3,                                       \
        SIMDPP_DISPATCH_10_NS_ID_SSE4_1,                                      \
        SIMDPP_DISPATCH_10_NS_ID_AVX,                                         \
        SIMDPP_DISPATCH_10_NS_ID_AVX2,                                        \
        SIMDPP_DISPATCH_10_NS_ID_AVX512F,                                     \
        SIMDPP_DISPATCH_10_NS_ID_FMA3,                                        \
        SIMDPP_DISPATCH_10_NS_ID_FMA4,                                        \
        SIMDPP_DISPATCH_10_NS_ID_XOP,                                         \
        SIMDPP_DISPATCH_10_NS_ID_NEON,                                        \
        SIMDPP_DISPATCH_10_NS_ID_NEON_FLT_SP,                                 \
        SIMDPP_DISPATCH_10_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_10_FN_REGISTER(ARRAY,NAME,FUN_TYPE)               \
        ARRAY[10-1] = SIMDPP_DISPATCH_10_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_10_FN_DECLARE(NAME,FUN_TYPE)                      \
        namespace SIMDPP_DISPATCH_10_NAMESPACE {                              \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_10_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_10_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH11
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH11
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_11_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_11_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_11_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_11_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_11_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_11_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_11_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_11_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_11_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_11_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_11_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_11_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_11_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_11_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_11_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_11_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_11_NAMESPACE SIMDPP_PP_PASTE15(arch,              \
        SIMDPP_DISPATCH_11_NS_ID_NULL,                                        \
        SIMDPP_DISPATCH_11_NS_ID_SSE2,                                        \
        SIMDPP_DISPATCH_11_NS_ID_SSE3,                                        \
        SIMDPP_DISPATCH_11_NS_ID_SSSE3,                                       \
        SIMDPP_DISPATCH_11_NS_ID_SSE4_1,                                      \
        SIMDPP_DISPATCH_11_NS_ID_AVX,                                         \
        SIMDPP_DISPATCH_11_NS_ID_AVX2,                                        \
        SIMDPP_DISPATCH_11_NS_ID_AVX512F,                                     \
        SIMDPP_DISPATCH_11_NS_ID_FMA3,                                        \
        SIMDPP_DISPATCH_11_NS_ID_FMA4,                                        \
        SIMDPP_DISPATCH_11_NS_ID_XOP,                                         \
        SIMDPP_DISPATCH_11_NS_ID_NEON,                                        \
        SIMDPP_DISPATCH_11_NS_ID_NEON_FLT_SP,                                 \
        SIMDPP_DISPATCH_11_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_11_FN_REGISTER(ARRAY,NAME,FUN_TYPE)               \
        ARRAY[11-1] = SIMDPP_DISPATCH_11_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_11_FN_DECLARE(NAME,FUN_TYPE)                      \
        namespace SIMDPP_DISPATCH_11_NAMESPACE {                              \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_11_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_11_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH12
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH12
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_12_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_12_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_12_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_12_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_12_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_12_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_12_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_12_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_12_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_12_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_12_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_12_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_12_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_12_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_12_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_12_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_12_NAMESPACE SIMDPP_PP_PASTE15(arch,              \
        SIMDPP_DISPATCH_12_NS_ID_NULL,                                        \
        SIMDPP_DISPATCH_12_NS_ID_SSE2,                                        \
        SIMDPP_DISPATCH_12_NS_ID_SSE3,                                        \
        SIMDPP_DISPATCH_12_NS_ID_SSSE3,                                       \
        SIMDPP_DISPATCH_12_NS_ID_SSE4_1,                                      \
        SIMDPP_DISPATCH_12_NS_ID_AVX,                                         \
        SIMDPP_DISPATCH_12_NS_ID_AVX2,                                        \
        SIMDPP_DISPATCH_12_NS_ID_AVX512F,                                     \
        SIMDPP_DISPATCH_12_NS_ID_FMA3,                                        \
        SIMDPP_DISPATCH_12_NS_ID_FMA4,                                        \
        SIMDPP_DISPATCH_12_NS_ID_XOP,                                         \
        SIMDPP_DISPATCH_12_NS_ID_NEON,                                        \
        SIMDPP_DISPATCH_12_NS_ID_NEON_FLT_SP,                                 \
        SIMDPP_DISPATCH_12_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_12_FN_REGISTER(ARRAY,NAME,FUN_TYPE)               \
        ARRAY[12-1] = SIMDPP_DISPATCH_12_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_12_FN_DECLARE(NAME,FUN_TYPE)                      \
        namespace SIMDPP_DISPATCH_12_NAMESPACE {                              \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_12_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_12_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH13
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH13
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_13_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_13_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_13_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_13_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_13_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_13_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_13_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_13_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_13_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_13_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_13_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_13_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_13_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_13_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_13_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_13_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_13_NAMESPACE SIMDPP_PP_PASTE15(arch,              \
        SIMDPP_DISPATCH_13_NS_ID_NULL,                                        \
        SIMDPP_DISPATCH_13_NS_ID_SSE2,                                        \
        SIMDPP_DISPATCH_13_NS_ID_SSE3,                                        \
        SIMDPP_DISPATCH_13_NS_ID_SSSE3,                                       \
        SIMDPP_DISPATCH_13_NS_ID_SSE4_1,                                      \
        SIMDPP_DISPATCH_13_NS_ID_AVX,                                         \
        SIMDPP_DISPATCH_13_NS_ID_AVX2,                                        \
        SIMDPP_DISPATCH_13_NS_ID_AVX512F,                                     \
        SIMDPP_DISPATCH_13_NS_ID_FMA3,                                        \
        SIMDPP_DISPATCH_13_NS_ID_FMA4,                                        \
        SIMDPP_DISPATCH_13_NS_ID_XOP,                                         \
        SIMDPP_DISPATCH_13_NS_ID_NEON,                                        \
        SIMDPP_DISPATCH_13_NS_ID_NEON_FLT_SP,                                 \
        SIMDPP_DISPATCH_13_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_13_FN_REGISTER(ARRAY,NAME,FUN_TYPE)               \
        ARRAY[13-1] = SIMDPP_DISPATCH_13_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_13_FN_DECLARE(NAME,FUN_TYPE)                      \
        namespace SIMDPP_DISPATCH_13_NAMESPACE {                              \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_13_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_13_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH14
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH14
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_14_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_14_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_14_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_14_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_14_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_14_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_14_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_14_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_14_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_14_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_14_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_14_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_14_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_14_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_14_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_14_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_14_NAMESPACE SIMDPP_PP_PASTE15(arch,              \
        SIMDPP_DISPATCH_14_NS_ID_NULL,                                        \
        SIMDPP_DISPATCH_14_NS_ID_SSE2,                                        \
        SIMDPP_DISPATCH_14_NS_ID_SSE3,                                        \
        SIMDPP_DISPATCH_14_NS_ID_SSSE3,                                       \
        SIMDPP_DISPATCH_14_NS_ID_SSE4_1,                                      \
        SIMDPP_DISPATCH_14_NS_ID_AVX,                                         \
        SIMDPP_DISPATCH_14_NS_ID_AVX2,                                        \
        SIMDPP_DISPATCH_14_NS_ID_AVX512F,                                     \
        SIMDPP_DISPATCH_14_NS_ID_FMA3,                                        \
        SIMDPP_DISPATCH_14_NS_ID_FMA4,                                        \
        SIMDPP_DISPATCH_14_NS_ID_XOP,                                         \
        SIMDPP_DISPATCH_14_NS_ID_NEON,                                        \
        SIMDPP_DISPATCH_14_NS_ID_NEON_FLT_SP,                                 \
        SIMDPP_DISPATCH_14_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_14_FN_REGISTER(ARRAY,NAME,FUN_TYPE)               \
        ARRAY[14-1] = SIMDPP_DISPATCH_14_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_14_FN_DECLARE(NAME,FUN_TYPE)                      \
        namespace SIMDPP_DISPATCH_14_NAMESPACE {                              \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_14_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_14_FN_DECLARE(NAME,FUN_TYPE)
#endif

#ifdef SIMDPP_DISPATCH_ARCH15
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH15
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_15_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_15_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_15_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_15_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_15_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_15_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_15_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_15_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_15_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_15_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_15_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_15_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_15_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_15_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_15_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_15_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_15_NAMESPACE SIMDPP_PP_PASTE15(arch,              \
        SIMDPP_DISPATCH_15_NS_ID_NULL,                                        \
        SIMDPP_DISPATCH_15_NS_ID_SSE2,                                        \
        SIMDPP_DISPATCH_15_NS_ID_SSE3,                                        \
        SIMDPP_DISPATCH_15_NS_ID_SSSE3,                                       \
        SIMDPP_DISPATCH_15_NS_ID_SSE4_1,                                      \
        SIMDPP_DISPATCH_15_NS_ID_AVX,                                         \
        SIMDPP_DISPATCH_15_NS_ID_AVX2,                                        \
        SIMDPP_DISPATCH_15_NS_ID_AVX512F,                                     \
        SIMDPP_DISPATCH_15_NS_ID_FMA3,                                        \
        SIMDPP_DISPATCH_15_NS_ID_FMA4,                                        \
        SIMDPP_DISPATCH_15_NS_ID_XOP,                                         \
        SIMDPP_DISPATCH_15_NS_ID_NEON,                                        \
        SIMDPP_DISPATCH_15_NS_ID_NEON_FLT_SP,                                 \
        SIMDPP_DISPATCH_15_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_15_FN_REGISTER(ARRAY,NAME,FUN_TYPE)               \
        ARRAY[15-1] = SIMDPP_DISPATCH_15_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_15_FN_DECLARE(NAME,FUN_TYPE)                      \
        namespace SIMDPP_DISPATCH_15_NAMESPACE {                              \
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_15_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_15_FN_DECLARE(NAME,FUN_TYPE)
#endif


#define SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME,FUN_TYPE)                    \
    SIMDPP_DISPATCH_1_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_2_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_3_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_4_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_5_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_6_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_7_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_8_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_9_FN_DECLARE(NAME,FUN_TYPE)                               \
    SIMDPP_DISPATCH_10_FN_DECLARE(NAME,FUN_TYPE)                              \
    SIMDPP_DISPATCH_11_FN_DECLARE(NAME,FUN_TYPE)                              \
    SIMDPP_DISPATCH_12_FN_DECLARE(NAME,FUN_TYPE)                              \
    SIMDPP_DISPATCH_13_FN_DECLARE(NAME,FUN_TYPE)                              \
    SIMDPP_DISPATCH_14_FN_DECLARE(NAME,FUN_TYPE)                              \
    SIMDPP_DISPATCH_15_FN_DECLARE(NAME,FUN_TYPE)                              \


#define SIMDPP_DISPATCH_COLLECT_FUNCTIONS(ARRAY,NAME,FUN_TYPE)              \
    SIMDPP_DISPATCH_1_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_2_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_3_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_4_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_5_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_6_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_7_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_8_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_9_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                        \
    SIMDPP_DISPATCH_10_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                       \
    SIMDPP_DISPATCH_11_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                       \
    SIMDPP_DISPATCH_12_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                       \
    SIMDPP_DISPATCH_13_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                       \
    SIMDPP_DISPATCH_14_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                       \
    SIMDPP_DISPATCH_15_FN_REGISTER(ARRAY,NAME,FUN_TYPE)                       \


#endif // SIMDPP_EMIT_DISPATCHER
#endif

