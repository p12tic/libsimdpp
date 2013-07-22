/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_NEON_VFP_SP_H
#define LIBSIMDPP_NEON_VFP_SP_H

#if SIMDPP_ARCH_FILE_INCLUDED
    #error "You must not include more than one architecture files."
#endif

#define SIMDPP_ARCH_FILE_INCLUDED

// Double and single precision floating point numbers use VFP, the rest use NEON
#define SIMDPP_USE_NEON 1
#define SIMDPP_USE_NEON_VFP_SP 1
#define SIMDPP_USE_NEON_VFP_DP 1
#define SIMDPP_ARCH neon_vfp_sp

#include <arm_neon.h>

#include <simdpp/simd.h>

#endif
