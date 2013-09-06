/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompaing
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_DETAIL_WORD_SIZE_H
#define LIBSIMDPP_SIMD_DETAIL_WORD_SIZE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#if __i386__ || __i386 || _M_IX86
#define SIMDPP_SSE_32_BITS 1
#endif

#endif

