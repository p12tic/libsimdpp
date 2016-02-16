/*  Copyright (C) 2015  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ID_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ID_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

// This file contains definitions of instruction set ids from which
// architecture id is constructed. Architecture id is used to define
// SIMDPP_ARCH_NAMESPACE

#define SIMDPP_INSN_ID_NULL _null
#define SIMDPP_INSN_ID_SSE2 _sse2
#define SIMDPP_INSN_ID_SSE3 _sse3
#define SIMDPP_INSN_ID_SSSE3 _ssse3
#define SIMDPP_INSN_ID_SSE4_1 _sse4p1
#define SIMDPP_INSN_ID_AVX _avx
#define SIMDPP_INSN_ID_AVX2 _avx2
#define SIMDPP_INSN_ID_FMA3 _fma3
#define SIMDPP_INSN_ID_FMA4 _fma4
#define SIMDPP_INSN_ID_XOP _xop
#define SIMDPP_INSN_ID_AVX512F _avx512f
#define SIMDPP_INSN_ID_NEON _neon
#define SIMDPP_INSN_ID_NEON_FLT_SP _neonfltsp
#define SIMDPP_INSN_ID_ALTIVEC _altivec

#endif

