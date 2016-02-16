#!/usr/bin/env python3

#   Copyright (C) 2015  Povilas Kanapickas <povilas@radix.lt>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

# Generates the simdpp/dispatch/collect_macros_generated.h file
# Use as $ ./tools/gen_dispatcher_collect_macros.py > simdpp/dispatch/collect_macros_generated.h

from gen_common import output_template

num_archs = 15

single_arch_template = '''
#ifdef SIMDPP_DISPATCH_ARCH$num$
    #define SIMDPP_ARCH_PP_LIST SIMDPP_DISPATCH_ARCH$num$
    #include <simdpp/detail/preprocess_single_arch.h>

    // Use the results of preprocess_single_arch.h to define
    // SIMDPP_DISPATCH_$num$_NAMESPACE

    #if SIMDPP_ARCH_PP_NS_USE_NULL
    #define SIMDPP_DISPATCH_$num$_NS_ID_NULL SIMDPP_INSN_ID_NULL
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_NULL
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE2
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSE2 SIMDPP_INSN_ID_SSE2
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSE2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE3
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSE3 SIMDPP_INSN_ID_SSE3
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSSE3
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSSE3 SIMDPP_INSN_ID_SSSE3
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSSE3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_SSE4_1
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSE4_1 SIMDPP_INSN_ID_SSE4_1
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_SSE4_1
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX
    #define SIMDPP_DISPATCH_$num$_NS_ID_AVX SIMDPP_INSN_ID_AVX
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_AVX
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX2
    #define SIMDPP_DISPATCH_$num$_NS_ID_AVX2 SIMDPP_INSN_ID_AVX2
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_AVX2
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA3
    #define SIMDPP_DISPATCH_$num$_NS_ID_FMA3 SIMDPP_INSN_ID_FMA3
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_FMA3
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_FMA4
    #define SIMDPP_DISPATCH_$num$_NS_ID_FMA4 SIMDPP_INSN_ID_FMA4
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_FMA4
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_XOP
    #define SIMDPP_DISPATCH_$num$_NS_ID_XOP SIMDPP_INSN_ID_XOP
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_XOP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_AVX512F
    #define SIMDPP_DISPATCH_$num$_NS_ID_AVX512F SIMDPP_INSN_ID_AVX512F
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_AVX512F
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON
    #define SIMDPP_DISPATCH_$num$_NS_ID_NEON SIMDPP_INSN_ID_NEON
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_NEON
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_NEON_FLT_SP
    #define SIMDPP_DISPATCH_$num$_NS_ID_NEON_FLT_SP SIMDPP_INSN_ID_NEON_FLT_SP
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_NEON_FLT_SP
    #endif
    #if SIMDPP_ARCH_PP_NS_USE_ALTIVEC
    #define SIMDPP_DISPATCH_$num$_NS_ID_ALTIVEC SIMDPP_INSN_ID_ALTIVEC
    #else
    #define SIMDPP_DISPATCH_$num$_NS_ID_ALTIVEC
    #endif

    #define SIMDPP_DISPATCH_$num$_NAMESPACE SIMDPP_PP_PASTE15(arch,         $n$
        SIMDPP_DISPATCH_$num$_NS_ID_NULL,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_SSE2,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_SSE3,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_SSSE3,                                  $n$
        SIMDPP_DISPATCH_$num$_NS_ID_SSE4_1,                                 $n$
        SIMDPP_DISPATCH_$num$_NS_ID_AVX,                                    $n$
        SIMDPP_DISPATCH_$num$_NS_ID_AVX2,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_AVX512F,                                $n$
        SIMDPP_DISPATCH_$num$_NS_ID_FMA3,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_FMA4,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_XOP,                                    $n$
        SIMDPP_DISPATCH_$num$_NS_ID_NEON,                                   $n$
        SIMDPP_DISPATCH_$num$_NS_ID_NEON_FLT_SP,                            $n$
        SIMDPP_DISPATCH_$num$_NS_ID_ALTIVEC)

    #define SIMDPP_DISPATCH_$num$_FN_REGISTER(ARRAY,NAME,FUN_TYPE)          $n$
        ARRAY[$num$-1] = SIMDPP_DISPATCH_$num$_NAMESPACE::register_fn_##NAME((FUN_TYPE)(NULL));
    #define SIMDPP_DISPATCH_$num$_FN_DECLARE(NAME,FUN_TYPE)                 $n$
        namespace SIMDPP_DISPATCH_$num$_NAMESPACE {                         $n$
            ::simdpp::detail::FnVersion register_fn_##NAME(FUN_TYPE); }
    #undef SIMDPP_ARCH_PP_LIST
#else
    #define SIMDPP_DISPATCH_$num$_FN_REGISTER(ARRAY,NAME,FUN_TYPE)
    #define SIMDPP_DISPATCH_$num$_FN_DECLARE(NAME,FUN_TYPE)
#endif'''

single_fn_register_template = '    SIMDPP_DISPATCH_$num$_FN_REGISTER(ARRAY,NAME,FUN_TYPE)   $n$'
single_fn_declare_template = '    SIMDPP_DISPATCH_$num$_FN_DECLARE(NAME,FUN_TYPE)   $n$'

# print the actual file

print('''/*  Copyright (C) 2015  Povilas Kanapickas <povilas@radix.lt>

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
''')

print('#define SIMDPP_DISPATCH_MAX_ARCHS ' + str(num_archs) + '\n')

for i in range(1, num_archs+1):
    vars = { 'num' : str(i) }
    output_template(single_arch_template, vars)

print('''

#define SIMDPP_DISPATCH_DECLARE_FUNCTIONS(NAME,FUN_TYPE)                    \\''')
for i in range(1, num_archs+1):
    vars = { 'num' : str(i) }
    output_template(single_fn_declare_template, vars)

print('''

#define SIMDPP_DISPATCH_COLLECT_FUNCTIONS(ARRAY,NAME,FUN_TYPE)              \\''')
for i in range(1, num_archs+1):
    vars = { 'num' : str(i) }
    output_template(single_fn_register_template, vars)

print('''

#endif // SIMDPP_EMIT_DISPATCHER
#endif
''')
