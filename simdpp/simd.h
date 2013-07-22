/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_H
#define LIBSIMDPP_SIMD_H

#ifndef SIMDPP_ARCH_FILE_INCLUDED
    #error "You must not include this file directly. Include the architecture specific headers"
#endif

#include <cstdlib>

// Put all functions to a namespace that depends on the architecture that the
// library is compiled for. This is needed to avoid violating the One
// Definition Rule

#define SIMDPP_ARCH_NAMESPACE_HELPER2(x) simdpp_arch_ ## x
#define SIMDPP_ARCH_NAMESPACE_HELPER(x) SIMDPP_ARCH_NAMESPACE_HELPER2(x)
#define SIMDPP_ARCH_NAMESPACE SIMDPP_ARCH_NAMESPACE_HELPER(SIMDPP_ARCH)

// Hide the namespace defined above from doxygen.s
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    #define SIMDPP_ARCH_NAMESPACE_BEGIN namespace SIMDPP_ARCH_NAMESPACE {
    #define SIMDPP_ARCH_NAMESPACE_END }
#else
    #define SIMDPP_ARCH_NAMESPACE_BEGIN
    #define SIMDPP_ARCH_NAMESPACE_END
#endif

#include <simdpp/simd/fwd.h>

#include <simdpp/simd/int128.h>
#include <simdpp/simd/int8x16.h>
#include <simdpp/simd/int16x8.h>
#include <simdpp/simd/int32x4.h>
#include <simdpp/simd/int64x2.h>
#include <simdpp/simd/float64x2.h>
#include <simdpp/simd/float32x4.h>

#include <simdpp/simd/detail/not_implemented.h>

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
