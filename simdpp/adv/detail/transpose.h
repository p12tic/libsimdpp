/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ADV_DETAIL_TRANSPOSE_H
#define LIBSIMDPP_SIMDPP_ADV_DETAIL_TRANSPOSE_H

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/detail/width.h>
#include <simdpp/core/permute_bytes16.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/detail/null/transpose.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

/// @{
/** Transposes eight 2x2 8-bit matrices within two int8x16 vectors

    @code
    r0 = [ a0_0; a1_0 ; ... ; a0_14; a1_14 ]
    r1 = [ a1_1; a1_1 ; ... ; a0_15; a0_15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{ALTIVEC, 2-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{ALTIVEC, 4-6}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline void transpose2(uint8x16& a0, uint8x16& a1)
{
#if SIMDPP_USE_NULL
    null::transpose2(a0, a1);
#elif SIMDPP_USE_NEON
    auto r = vtrnq_u8(a0, a1);
    a0 = r.val[0];
    a1 = r.val[1];
#elif SIMDPP_USE_ALTIVEC
    uint8x16 m0 = make_shuffle_bytes16_mask<0,16+0, 2,16+2, 4,16+4, 6,16+6,
                                            8,16+8, 10,16+10, 12,16+12, 14,16+14>(m0);
    uint8x16 m1 = make_shuffle_bytes16_mask<1,16+1, 3,16+3, 5,16+5, 7,16+7,
                                            9,16+9, 11,16+11, 13,16+13, 15,16+15>(m1);
    uint16x8 b0, b1;
    b0 = shuffle_bytes16(a0, a1, m0);
    b1 = shuffle_bytes16(a0, a1, m1);
    a0 = b0;  a1 = b1;
#else
    SIMDPP_NOT_IMPLEMENTED2(a0, a1);
#endif
}

/// @{
/** Helper function.

    @code
    r = [a0,a4,a8,a12,a1,a5,a9,a13,a2,a6,a10,a14,a3,a7,a11,a15]
    @endcode

    The 256-bit version applies the 128 bit operation to the two halves.

    Needs SSSE3
*/
inline uint8x16 transpose_inplace(uint8x16 a)
{
#if SIMDPP_USE_SSSE3 || SIMDPP_USE_ALTIVEC
    // the compiler will take this out of any loops automatically
    uint8x16 idx = make_uint(0, 4, 8, 12, 1, 5, 9, 13,
                            2, 6, 10,14, 3, 7, 11,15);
    return permute_bytes16(a, idx);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

inline uint8x32 transpose_inplace(uint8x32 a)
{
#if SIMDPP_USE_AVX2 || SIMDPP_USE_ALTIVEC
    uint8x32 idx = make_uint(0, 4, 8, 12, 1, 5, 9, 13,
                             2, 6, 10,14, 3, 7, 11,15);
    return permute_bytes16(a, idx);
#elif SIMDPP_USE_SSSE3
    SIMDPP_VEC_ARRAY_IMPL1(uint8x32, transpose_inplace, a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}
/// @}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
