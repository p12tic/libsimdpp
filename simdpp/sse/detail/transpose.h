/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_DETAIL_TRANSPOSE_H
#define LIBSIMDPP_SSE_DETAIL_TRANSPOSE_H

#include <simdpp/sse/shuffle.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace sse {
namespace detail {

/// @{
/** Helper function.

    @code
    r = [a0,a4,a8,a12,a1,a5,a9,a13,a2,a6,a10,a14,a3,a7,a11,a15]
    @endcode

    The 256-bit version applies the 128 bit operation to the two halves.

    Needs SSSE3
*/
inline basic_int8x16 transpose_inplace(basic_int8x16 a)
{
#if SIMDPP_USE_SSSE3
    // the compiler will take this out of any loops automatically
    uint8x16 idx = uint8x16::make_const(0, 4, 8, 12, 1, 5, 9, 13,
                                        2, 6, 10,14, 3, 7, 11,15);
    return _mm_shuffle_epi8(a, idx);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

inline basic_int8x32 transpose_inplace(basic_int8x32 a)
{
#if SIMDPP_USE_AVX2
    uint8x32 idx = uint8x32::make_const(0, 4, 8, 12, 1, 5, 9, 13,
                                        2, 6, 10,14, 3, 7, 11,15);
    return _mm256_shuffle_epi8(a, idx);
#elif SIMDPP_USE_SSSE3
    return {transpose_inplace(a[0]), transpose_inplace(a[1])};
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}
/// @}

/// @{
/** Partially transposes two 8x8 8-bit matrices within eight int8x16 vectors

    @code
    r0 = [ a0_0; ...; a7_0 ; a0_1; ...; a7_1 ]
    r1 = [ a0_2; ...; a7_2 ; a0_3; ...; a7_3 ]
    ...
    r7 = [ a0_14; ...; a7_14 ; a0_15; ...; a7_15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 24}

    @par 256-bit version:
    @icost{AVX2, 24}
*/
inline void partial_transpose8(basic_int8x16& a0, basic_int8x16& a1,
                               basic_int8x16& a2, basic_int8x16& a3,
                               basic_int8x16& a4, basic_int8x16& a5,
                               basic_int8x16& a6, basic_int8x16& a7)
{
    /*
    [a0;a1;a2;a3;a4;a5;a6;a7;...]
    [b0;b1;b2;b3;b4;b5;b6;b7;...]
    [c0;c1;c2;c3;c4;c5;c6;c7;...]
    [d0;d1;d2;d3;d4;d5;d6;d7;...]
    [e0;e1;e2;e3;e4;e5;e6;e7;...]
    [f0;f1;f2;f3;f4;f5;f6;f7;...]
    [g0;g1;g2;g3;g4;g5;g6;g7;...]
    [h0;h1;h2;h3;h4;h5;h6;h7;...]
    */
    basic_int16x8 b0, b1, b2, b3, b4, b5, b6, b7;
    b0 = zip_lo(a0, a1);
    b1 = zip_lo(a2, a3);
    b2 = zip_lo(a4, a5);
    b3 = zip_lo(a6, a7);
    b4 = zip_hi(a0, a1);
    b5 = zip_hi(a2, a3);
    b6 = zip_hi(a4, a5);
    b7 = zip_hi(a6, a7);
    /*
    [a0;b0;a1;b1;...;a7;b7]
    [c0;d0;c1;d1;...;c7;d7]
    [e0;f0;e1;f1;...;e7;f7]
    [g0;h0;g1;h1;...;g7;h7]
    [a8;b8;a9;b9;...;a15;b15]
    [c8;d9;c8;d9;...;c15;d15]
    [e8;f8;e9;f9;...;e15;f15]
    [g8;h8;g9;h9;...;g15;t15]
    */
    basic_int32x4 c0, c1, c2, c3, c4, c5, c6, c7;

    c0 = zip_lo(b0, b1);
    c1 = zip_lo(b2, b3);
    c2 = zip_hi(b0, b1);
    c3 = zip_hi(b2, b3);
    c4 = zip_lo(b4, b5);
    c5 = zip_lo(b6, b7);
    c6 = zip_hi(b4, b5);
    c7 = zip_hi(b6, b7);
    /*
    [a0;b0;c0;d0;...;a3;b3;c3;d3]
    [e0;f0;g0;h0;...;e3;f3;g3;h3]
    [a4;b4;c4;d4;...;a7;b7;c7;d7]
    [e4;f4;g4;h4;...;e7;f7;g7;h7]
    [a8;b8;c8;d8;...;a11;b11;c11;d11]
    [e8;f8;g8;h8;...;e11;f11;g11;h11]
    [a12;b12;c12;d12;...;a15;b15;c15;d15]
    [e12;f12;g12;h12;...;e15;f15;g15;h15]
    */
    a0 = zip_lo(c0, c1);
    a1 = zip_hi(c0, c1);
    a2 = zip_lo(c2, c3);
    a3 = zip_hi(c2, c3);
    a4 = zip_lo(c4, c5);
    a5 = zip_hi(c4, c5);
    a6 = zip_lo(c6, c7);
    a7 = zip_hi(c6, c7);
}
inline void partial_transpose8(basic_int8x32& a0, basic_int8x32& a1,
                               basic_int8x32& a2, basic_int8x32& a3,
                               basic_int8x32& a4, basic_int8x32& a5,
                               basic_int8x32& a6, basic_int8x32& a7)
{
    basic_int16x16 b0, b1, b2, b3, b4, b5, b6, b7;
    b0 = zip_lo(a0, a1);
    b1 = zip_lo(a2, a3);
    b2 = zip_lo(a4, a5);
    b3 = zip_lo(a6, a7);
    b4 = zip_hi(a0, a1);
    b5 = zip_hi(a2, a3);
    b6 = zip_hi(a4, a5);
    b7 = zip_hi(a6, a7);

    basic_int32x8 c0, c1, c2, c3, c4, c5, c6, c7;

    c0 = zip_lo(b0, b1);
    c1 = zip_lo(b2, b3);
    c2 = zip_hi(b0, b1);
    c3 = zip_hi(b2, b3);
    c4 = zip_lo(b4, b5);
    c5 = zip_lo(b6, b7);
    c6 = zip_hi(b4, b5);
    c7 = zip_hi(b6, b7);

    a0 = zip_lo(c0, c1);
    a1 = zip_hi(c0, c1);
    a2 = zip_lo(c2, c3);
    a3 = zip_hi(c2, c3);
    a4 = zip_lo(c4, c5);
    a5 = zip_hi(c4, c5);
    a6 = zip_lo(c6, c7);
    a7 = zip_hi(c6, c7);
}
/// @}

} // namespace detail
} // namespace sse
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
