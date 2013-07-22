/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NULL_H
#define LIBSIMDPP_NULL_H

#if SIMDPP_ARCH_FILE_INCLUDED
    #error "You must not include more than one architecture files."
#endif

#define SIMDPP_ARCH_FILE_INCLUDED

#define SIMDPP_USE_NULL 1
#define SIMDPP_ARCH null

#include <simdpp/simd.h>

#endif
