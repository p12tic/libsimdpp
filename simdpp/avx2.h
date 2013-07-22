/*  libsimdpp
    Copyright (C) 2012 Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_AVX_H
#define LIBSIMDPP_AVX_H

#ifdef SIMDPP_ARCH_FILE_INCLUDED
    #error "You must not include more than one architecture files."
#endif

#define SIMDPP_ARCH_FILE_INCLUDED

#define SIMDPP_USE_SSE2 1
#define SIMDPP_USE_SSE3 1
#define SIMDPP_USE_SSSE3 1
#define SIMDPP_USE_SSE4_1 1
#define SIMDPP_USE_AVX 1
#define SIMDPP_USE_AVX2 1
#define SIMDPP_ARCH avx2

#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <immintrin.h>

#include <simdpp/simd.h>

#endif

