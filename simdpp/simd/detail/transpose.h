/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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
#ifndef LIBSIMDPP_SIMD_DETAIL_TRANSPOSE_H
#define LIBSIMDPP_SIMD_DETAIL_TRANSPOSE_H

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle_bytes.h>

#if SIMDPP_USE_NULL
    #include <simdpp/null/transpose.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
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
inline void transpose2(basic_int8x16& a0, basic_int8x16& a1)
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
inline basic_int8x16 transpose_inplace(basic_int8x16 a)
{
#if SIMDPP_USE_SSSE3 || SIMDPP_USE_ALTIVEC
    // the compiler will take this out of any loops automatically
    uint8x16 idx = uint8x16::make_const(0, 4, 8, 12, 1, 5, 9, 13,
                                        2, 6, 10,14, 3, 7, 11,15);
    return permute_bytes16(a, idx);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

inline basic_int8x32 transpose_inplace(basic_int8x32 a)
{
#if SIMDPP_USE_AVX2 || SIMDPP_USE_ALTIVEC
    uint8x32 idx = uint8x32::make_const(0, 4, 8, 12, 1, 5, 9, 13,
                                        2, 6, 10,14, 3, 7, 11,15);
    return permute_bytes16(a, idx);
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
