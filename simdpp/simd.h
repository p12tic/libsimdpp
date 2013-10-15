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

#ifndef SIMDPP_ARCH_FILE_INCLUDED
    #error "You must not include this file directly. Include the architecture-specific headers"
#endif

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
    #include <avxintrin.h>
#else
    #define SIMDPP_PP_AVX
#endif

#ifdef SIMDPP_USE_AVX2
    #define SIMDPP_PP_AVX2 _avx2
    #include <avx2intrin.h>
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

/** Put all functions to a namespace that depends on the instruction set that
    the library is compiled for. This is needed to avoid violating the One
    Definition Rule.
*/
#define SIMDPP_CONCAT2(a, ...) a ## __VA_ARGS__
#define SIMDPP_CONCAT(a, b) SIMDPP_CONCAT2(a, b)

#define SIMDPP_PP_ARCH_CONCAT0 SIMDPP_PP_NULL
#define SIMDPP_PP_ARCH_CONCAT1 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT0, SIMDPP_PP_SSE2)
#define SIMDPP_PP_ARCH_CONCAT2 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT1, SIMDPP_PP_SSE3)
#define SIMDPP_PP_ARCH_CONCAT3 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT2, SIMDPP_PP_SSSE3)
#define SIMDPP_PP_ARCH_CONCAT4 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT3, SIMDPP_PP_SSE4_1)
#define SIMDPP_PP_ARCH_CONCAT5 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT4, SIMDPP_PP_AVX)
#define SIMDPP_PP_ARCH_CONCAT6 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT5, SIMDPP_PP_AVX2)
#define SIMDPP_PP_ARCH_CONCAT7 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT6, SIMDPP_PP_NEON)
#define SIMDPP_PP_ARCH_CONCAT8 SIMDPP_CONCAT(SIMDPP_PP_ARCH_CONCAT7, SIMDPP_PP_NEON_FLT_SP)

#define SIMDPP_ARCH_NAMESPACE SIMDPP_PP_ARCH_CONCAT8

/** Usable in contexts where a string is required
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

#include <simdpp/simd/detail/traits.h>

namespace simdpp {
using namespace SIMDPP_ARCH_NAMESPACE;
} // namespace simdpp

#endif
