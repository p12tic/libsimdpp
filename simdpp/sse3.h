/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE3_H
#define LIBSIMDPP_SSE3_H

#ifdef SIMDPP_ARCH_FILE_INCLUDED
    #error "You must not include more than one architecture files."
#endif

#define SIMDPP_ARCH_FILE_INCLUDED

#define SIMDPP_USE_SSE2 1
#define SIMDPP_USE_SSE3 1
#define SIMDPP_ARCH sse3


#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>

#include <simdpp/simd.h>

#endif
