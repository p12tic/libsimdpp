/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_TRANSPOSE_H
#define LIBSIMDPP_TRANSPOSE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/fwd.h>
#include <simdpp/simd/make_shuffle_bytes_mask.h>
#include <simdpp/simd/detail/transpose.h>
#include <simdpp/null/transpose.h>

#if SIMDPP_USE_SSE2
    #include <simdpp/sse/shuffle.h>
#elif SIMDPP_USE_NEON
    #include <simdpp/neon/shuffle.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** @defgroup simd_transpose Operations: transpose matrices consisting of
    several vectors
    @{
*/

/// @{
/** Transposes four 2x2 16-bit matrices within two int16x8 vectors

    @code
    r0 = [ a0_0; a1_0 ; ... ; a0_6; a1_6 ]
    r1 = [ a0_1; a1_1 ; ... ; a0_7; a0_7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{ALTIVEC, 2-4}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, 2}
    @icost{ALTIVEC, 4-6}
*/
inline void transpose2(basic_int16x8& a0, basic_int16x8& a1)
{
#if SIMDPP_USE_NULL
    null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    basic_int32x4 b0, b1;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    a0 = shuffle2<0,2,0,2>(b0, b1);
    a1 = shuffle2<1,3,1,3>(b0, b1);
#elif SIMDPP_USE_NEON
    auto r = vtrnq_u16(a0, a1);
    a0 = r.val[0];
    a1 = r.val[1];
#elif SIMDPP_USE_ALTIVEC
    uint16x8 m0 = make_shuffle_bytes16_mask<0,8+0, 2,8+2, 4,8+4, 6,8+6>(m0);
    uint16x8 m1 = make_shuffle_bytes16_mask<1,8+1, 3,8+3, 5,8+5, 7,8+7>(m1);
    uint16x8 b0, b1;
    b0 = shuffle_bytes16(a0, a1, m0);
    b1 = shuffle_bytes16(a0, a1, m1);
    a0 = b0;  a1 = b1;
#endif
}

inline void transpose2(basic_int16x16& a0, basic_int16x16& a1)
{
#if SIMDPP_USE_AVX2
    basic_int32x8 b0, b1;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    a0 = shuffle2<0,2,0,2>(b0, b1);
    a1 = shuffle2<1,3,1,3>(b0, b1);
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}
/// @}

/// @{
/** Transposes two 2x2 32-bit matrices within two int32x4 vectors

    @code
    r0 = [ a0_0; a1_0 ; a0_2; a1_2 ]
    r1 = [ a0_1; a1_1 ; a0_3; a0_3 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{ALTIVEC, 2-4}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 8}
    @icost{AVX2, 4}
    @icost{NEON, 2}
    @icost{ALTIVEC, 4-6}
*/
inline void transpose2(basic_int32x4& a0, basic_int32x4& a1)
{
#if SIMDPP_USE_NULL
    null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    basic_int64x2 b0, b1;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    a0 = zip_lo(b0, b1);
    a1 = zip_hi(b0, b1);
#elif SIMDPP_USE_NEON
    auto r = vtrnq_u32(a0, a1);
    a0 = r.val[0];
    a1 = r.val[1];
#elif SIMDPP_USE_ALTIVEC
    uint32x4 m0 = make_shuffle_bytes16_mask<0,4+0, 2,4+2>(m0);
    uint32x4 m1 = make_shuffle_bytes16_mask<1,4+1, 3,4+3>(m1);
    uint32x4 b0, b1;
    b0 = shuffle_bytes16(a0, a1, m0);
    b1 = shuffle_bytes16(a0, a1, m1);
    a0 = b0;  a1 = b1;
#endif
}

inline void transpose2(basic_int32x8& a0, basic_int32x8& a1)
{
#if SIMDPP_USE_AVX2
    basic_int64x4 b0, b1;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    a0 = zip_lo(b0, b1);
    a1 = zip_hi(b0, b1);
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}
/// @}

/// @{
/** Transposes a 2x2 64-bit matrix within two int64x2 vectors

    @code
    r0 = [ a0_0; a1_0 ]
    r1 = [ a0_1; a1_1 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 2}
    @icost{ALTIVEC, 2-4}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 4}
    @icost{AVX2, 2}
    @icost{NEON, 2}
    @icost{ALTIVEC, 4-6}
*/
inline void transpose2(basic_int64x2& a0, basic_int64x2& a1)
{
#if SIMDPP_USE_NULL
    null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    basic_int64x2 b0;
    b0 = zip_lo(a0, a1);
    a1 = zip_hi(a0, a1);
    a0 = b0;
#elif SIMDPP_USE_NEON
    neon::transpose2(a0, a1);
#elif SIMDPP_USE_ALTIVEC
    uint64x2 m0 = make_shuffle_bytes16_mask<0,2+0>(m0);
    uint64x2 m1 = make_shuffle_bytes16_mask<1,2+1>(m1);
    uint32x4 b0, b1;
    b0 = shuffle_bytes16(a0, a1, m0);
    b1 = shuffle_bytes16(a0, a1, m1);
    a0 = b0;  a1 = b1;
#endif
}

inline void transpose2(basic_int64x4& a0, basic_int64x4& a1)
{
#if SIMDPP_USE_AVX2
    basic_int64x4 b0;
    b0 = zip_lo(a0, a1);
    a1 = zip_hi(a0, a1);
    a0 = b0;
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}
/// @}

/// @{
/** Transposes two 2x2 32-bit matrices within two float32x4 vectors

    @code
    r0 = [ a0_0; a1_0 ; a0_2; a1_2 ]
    r1 = [ a0_1; a1_1 ; a0_3; a0_3 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4}
    @icost{ALTIVEC, 2-4}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE4.1, 8}
    @icost{AVX-AVX2, 4}
    @icost{ALTIVEC, 4-6}
    @icost{NEON, 2}
*/
inline void transpose2(float32x4& a0, float32x4& a1)
{
#if SIMDPP_USE_NULL
    null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    float64x2 b0, b1;
    b0 = bit_cast<float64x2>(zip_lo(a0, a1));
    b1 = bit_cast<float64x2>(zip_hi(a0, a1));
    a0 = bit_cast<float32x4>(zip_lo(b0, b1));
    a1 = bit_cast<float32x4>(zip_hi(b0, b1));
#elif SIMDPP_USE_NEON
    auto r = vtrnq_f32(a0, a1);
    a0 = r.val[0];
    a1 = r.val[1];
#elif SIMDPP_USE_ALTIVEC
    uint32x4 m0 = make_shuffle_bytes16_mask<0,4+0, 2,4+2>(m0);
    uint32x4 m1 = make_shuffle_bytes16_mask<1,4+1, 3,4+3>(m1);
    float32x4 b0, b1;
    b0 = shuffle_bytes16(a0, a1, m0);
    b1 = shuffle_bytes16(a0, a1, m1);
    a0 = b0;  a1 = b1;
#endif
}

inline void transpose2(float32x8& a0, float32x8& a1)
{
#if SIMDPP_USE_AVX
    float64x4 b0, b1;
    b0 = bit_cast<float64x4>(zip_lo(a0, a1));
    b1 = bit_cast<float64x4>(zip_hi(a0, a1));
    a0 = bit_cast<float32x8>(zip_lo(b0, b1));
    a1 = bit_cast<float32x8>(zip_hi(b0, b1));
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}
/// @}

/// @{
/** Transposes a 2x2 64-bit matrix within two int64x2 vectors

    @code
    r0 = [ a0_0; a1_0 ]
    r1 = [ a0_1; a1_1 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 2}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-SSE4.1, 4}
    @icost{AVX-AVX2, 2}
    @novec{NEON, ALTIVEC}
*/
inline void transpose2(float64x2& a0, float64x2& a1)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_ALTIVEC
    null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    float64x2 b0;
    b0 = zip_lo(a0, a1);
    a1 = zip_hi(a0, a1);
    a0 = b0;
#elif SIMDPP_USE_NEON
    int64x2 b0, b1;
    b0 = a0;  b1 = a1;
    transpose2(b0, b1);
    a0 = b0;  a1 = b1;
#endif
}

inline void transpose2(float64x4& a0, float64x4& a1)
{
#if SIMDPP_USE_AVX
    float64x4 b0;
    b0 = zip_lo(a0, a1);
    a1 = zip_hi(a0, a1);
    a0 = b0;
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}
/// @}

void transpose4(basic_int32x4& a0, basic_int32x4& a1,
                basic_int32x4& a2, basic_int32x4& a3);
/// @{
/** Transposes four 4x4 8-bit matrix within four int8x16 vectors

    @code
    r0 = [ a0_0; a1_0; a2_0; a3_0 ; a0_4; a1_4; a2_4; a3_4 ...]
    r1 = [ a0_1; a1_1; a2_1; a3_1 ; a0_5; a1_5; a2_5; a3_5 ...]
    r2 = [ a0_2; a1_2; a2_2; a3_2 ; a0_6; a1_6; a2_6; a3_6 ...]
    r3 = [ a0_3; a1_3; a2_3; a3_3 ; a0_7; a1_7; a2_7; a3_7 ...]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 16}
    @icost{NEON, 4}
    @icost{ALTIVEC, 8-12}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 32}
    @icost{AVX2, 16}
    @icost{NEON, 8}
    @icost{ALTIVEC, 16-20}
*/
inline void transpose4(basic_int8x16& a0, basic_int8x16& a1,
                       basic_int8x16& a2, basic_int8x16& a3)
{
    // [a0,a1,a2,a3 ... ]
    // [b0,b1,b2,b3 ... ]
    // [c0,c1,c2,c3 ... ]
    // [d0,d1,d2,d3 ... ]
#if SIMDPP_USE_NULL
    null::transpose4(a0, a1, a2, a3);
#elif SIMDPP_USE_SSE2
    basic_int16x8 b0, b1, b2, b3;
    b0 = zip_lo(a0, a1);
    b1 = zip_lo(a2, a3);
    b2 = zip_hi(a0, a1);
    b3 = zip_hi(a2, a3);
    // [a0,b0,a1,b1,a2,b2,a3,b3 ... b7]
    // [c0,d0,c1,d1,c2,d2,c3,d3 ... d7]
    // [a8 ... b15]
    // [c8 ... d15]
    basic_int32x4 c0, c1, c2, c3;
    c0 = zip_lo(b0, b1);
    c1 = zip_hi(b0, b1);
    c2 = zip_lo(b2, b3);
    c3 = zip_hi(b2, b3);
    // [a0,b0,c0,d0,[a..d]1, [a..d]2,  [a..d]3]
    // [[a..d]4,    [a..d]5, [a..d]6,  [a..d]7]
    // [[a..d]8,    [a..d]9, [a..d]10, [a..d]11]
    // [[a..d]12,   [a..d]13,[a..d]14, [a..d]15]
    transpose4(c0, c1, c2, c3);
    a0 = c0;
    a1 = c1;
    a2 = c2;
    a3 = c3;
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    basic_int16x8 b0, b1, b2, b3;
    detail::transpose2(a0, a1);  // 8-bit transpose
    detail::transpose2(a2, a3);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose2(b0, b2);  // 16-bit transpose
    transpose2(b1, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(basic_int32x8& a0, basic_int32x8& a1,
                       basic_int32x8& a2, basic_int32x8& a3);

inline void transpose4(basic_int8x32& a0, basic_int8x32& a1,
                       basic_int8x32& a2, basic_int8x32& a3)
{
#if SIMDPP_USE_AVX2
    basic_int16x16 b0, b1, b2, b3;
    b0 = zip_lo(a0, a1);
    b1 = zip_lo(a2, a3);
    b2 = zip_hi(a0, a1);
    b3 = zip_hi(a2, a3);
    basic_int32x8 c0, c1, c2, c3;
    c0 = zip_lo(b0, b1);
    c1 = zip_hi(b0, b1);
    c2 = zip_lo(b2, b3);
    c3 = zip_hi(b2, b3);
    transpose4(c0, c1, c2, c3);
    a0 = c0;
    a1 = c1;
    a2 = c2;
    a3 = c3;
#else
    transpose4(a0[0], a1[0], a2[0], a3[0]);
    transpose4(a0[1], a1[1], a2[1], a3[1]);
#endif
}
/// @}

/// @{
/** Transposes two 4x4 16-bit matrices within four int16x8 vectors

    @code
    r0 = [ a0_0; a1_0; a2_0; a3_0 ; a0_4; a1_4; a2_4; a3_4 ]
    r1 = [ a0_1; a1_1; a2_1; a3_1 ; a0_5; a1_5; a2_5; a3_5 ]
    r2 = [ a0_2; a1_2; a2_2; a3_2 ; a0_6; a1_6; a2_6; a3_6 ]
    r3 = [ a0_3; a1_3; a2_3; a3_3 ; a0_7; a1_7; a2_7; a3_7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 12}
    @icost{NEON, 4}
    @icost{ALTIVEC, 8-12}

    @par 256-bit version:
    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.

    @icost{SSE2-AVX, 24}
    @icost{AVX2, 12}
    @icost{NEON, 8}
    @icost{ALTIVEC, 16-20}
*/
inline void transpose4(basic_int16x8& a0, basic_int16x8& a1,
                       basic_int16x8& a2, basic_int16x8& a3)
{
#if SIMDPP_USE_NULL
    null::transpose4(a0, a1, a2, a3);
#elif SIMDPP_USE_SSE2
    basic_int32x4 b0, b1, b2, b3;
    basic_int64x2 c0, c1, c2, c3;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    b2 = zip_lo(a2, a3);
    b3 = zip_hi(a2, a3);
    // [a0,b0,a1,b1,a2,b2,a3,b3]
    // [a4,b4,a5,b5,a6,b6,a7,b7]
    // [c0,d0,c1,d1,c2,d2,c3,d3]
    // [c4,d4,c5,d5,c6,d6,c7,d7]
    c0 = zip_lo(b0, b2);
    c1 = zip_hi(b0, b2);
    c2 = zip_lo(b1, b3);
    c3 = zip_hi(b1, b3);
    // [a0,b0,c0,d0,a1,b1,c1,d1]
    // [a2,b2,c2,d2,a3,b3,c3,d3]
    // [a4,b4,c4,d4,a5,b5,c5,d5]
    // [a6,b6,c6,d6,a7,b7,c7,d7]
    a0 = zip_lo(c0, c2);
    a1 = zip_hi(c0, c2);
    a2 = zip_lo(c1, c3);
    a3 = zip_hi(c1, c3);
    // [a0,b0,c0,d0,a4,b4,c4,d4]
    // [a1,b1,c1,d1,a5,b5,c5,d5]
    // [a2,b2,c2,d2,a6,b6,c6,d6]
    // [a3,b3,c3,d3,a7,b7,c7,d7]
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    basic_int32x4 b0, b1, b2, b3;
    transpose2(a0, a1);  // 16-bit transpose
    transpose2(a2, a3);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose2(b0, b2);  // 32-bit transpose
    transpose2(b1, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(basic_int16x16& a0, basic_int16x16& a1,
                       basic_int16x16& a2, basic_int16x16& a3)
{
#if SIMDPP_USE_AVX2
    basic_int32x8 b0, b1, b2, b3;
    basic_int64x4 c0, c1, c2, c3;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    b2 = zip_lo(a2, a3);
    b3 = zip_hi(a2, a3);

    c0 = zip_lo(b0, b2);
    c1 = zip_hi(b0, b2);
    c2 = zip_lo(b1, b3);
    c3 = zip_hi(b1, b3);

    a0 = zip_lo(c0, c2);
    a1 = zip_hi(c0, c2);
    a2 = zip_lo(c1, c3);
    a3 = zip_hi(c1, c3);
#else
    transpose4(a0[0], a1[0], a2[0], a3[0]);
    transpose4(a0[1], a1[1], a2[1], a3[1]);
#endif
}
/// @}


namespace detail {

template<class V> struct dbl_length_vector;
template<> struct dbl_length_vector<basic_int32x4> { using type = basic_int64x2; };
template<> struct dbl_length_vector<basic_int32x8> { using type = basic_int64x4; };
template<> struct dbl_length_vector<float32x4> { using type = float64x2; };
template<> struct dbl_length_vector<float32x8> { using type = float64x4; };

template<class V>
void sse_transpose4x32_impl(V& a0, V& a1, V& a2, V& a3)
{
    using Z = typename dbl_length_vector<V>::type;
    Z b0, b1, b2, b3;
    // [a0,a1,a2,a3]
    // [b0,b1,b2,b3]
    // [c0,c1,c2,c3]
    // [d0,d1,d2,d3]
    // bit_cast needed for float versions
    b0 = bit_cast<Z>(zip_lo(a0, a1));
    b1 = bit_cast<Z>(zip_hi(a0, a1));
    b2 = bit_cast<Z>(zip_lo(a2, a3));
    b3 = bit_cast<Z>(zip_hi(a2, a3));
    // [a0,b0,a1,b1]
    // [a2,b2,a3,b3]
    // [c0,d0,c1,d1]
    // [c2,d2,c3,d3]
    a0 = bit_cast<V>(zip_lo(b0, b2));
    a1 = bit_cast<V>(zip_hi(b0, b2));
    a2 = bit_cast<V>(zip_lo(b1, b3));
    a3 = bit_cast<V>(zip_hi(b1, b3));
}
} // namespace detail

/// @{
/** Transposes a 4x4 32-bit matrix within four int32x4 vectors

    @code
    r0 = [ a0_0; a1_0; a2_0; a3_0 ]
    r1 = [ a0_1; a1_1; a2_1; a3_1 ]
    r2 = [ a0_2; a1_2; a2_2; a3_2 ]
    r3 = [ a0_3; a1_3; a2_3; a3_3 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 12}
    @icost{NEON, 4}
    @icost{ALTIVEC, 8-12}

    @par 256-bit version:
    @icost{SSE2-AVX, 24}
    @icost{AVX2, 12}
    @icost{NEON, 8}
    @icost{ALTIVEC, 16-20}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline void transpose4(basic_int32x4& a0, basic_int32x4& a1,
                       basic_int32x4& a2, basic_int32x4& a3)
{
#if SIMDPP_USE_NULL
    null::transpose4(a0, a1, a2, a3);
#elif SIMDPP_USE_SSE2
    detail::sse_transpose4x32_impl(a0, a1, a2, a3);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    basic_int64x2 b0, b1, b2, b3;
    transpose2(a0, a1);  // 32-bit transpose
    transpose2(a2, a3);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose2(b0, b2);  // 64-bit transpose
    transpose2(b1, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(basic_int32x8& a0, basic_int32x8& a1,
                       basic_int32x8& a2, basic_int32x8& a3)
{
#if SIMDPP_USE_AVX2
    detail::sse_transpose4x32_impl(a0, a1, a2, a3);
#else
    transpose4(a0[0], a1[0], a2[0], a3[0]);
    transpose4(a0[1], a1[1], a2[1], a3[1]);
#endif
}
/// @}

/// @{
/** Transposes 4x4 32-bit matrix within four float32x4 vectors

    @code
    r0 = [ a0_0; a1_0; a2_0; a3_0 ]
    r1 = [ a0_1; a1_1; a2_1; a3_1 ]
    r2 = [ a0_2; a1_2; a2_2; a3_2 ]
    r3 = [ a0_3; a1_3; a2_3; a3_3 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 12}
    @icost{NEON, 4}
    @icost{ALTIVEC, 8-12}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 24}
    @icost{AVX-AVX2, 12}
    @icost{NEON, 8}
    @icost{ALTIVEC, 16-20}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline void transpose4(float32x4& a0, float32x4& a1,
                       float32x4& a2, float32x4& a3)
{
#if SIMDPP_USE_SSE2
    detail::sse_transpose4x32_impl(a0, a1, a2, a3);
#else
    basic_int32x4 b0, b1, b2, b3;
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(float32x8& a0, float32x8& a1,
                       float32x8& a2, float32x8& a3)
{
#if SIMDPP_USE_AVX
    detail::sse_transpose4x32_impl(a0, a1, a2, a3);
#else
    transpose4(a0[0], a1[0], a2[0], a3[0]);
    transpose4(a0[1], a1[1], a2[1], a3[1]);
#endif
}
/// @}

/** Transposes two 8x8 8-bit matrices within eight int8x16 vectors

    @code
    r0 = [ a0_0; ...; a7_0 ; a0_8; ...; a7_8 ]
    r1 = [ a0_1; ...; a7_1 ; a0_9; ...; a7_9 ]
    ...
    r7 = [ a0_7; ...; a7_7 ; a0_15; ...; a7_15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 32}
    @icost{NEON, 12}
    @icost{ALTIVEC, 24-30}

    @par 256-bit version:
    @icost{SSE2-AVX, 64}
    @icost{AVX2, 32}
    @icost{NEON, 24}
    @icost{ALTIVEC, 48-54}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline void transpose8(basic_int8x16& a0, basic_int8x16& a1,
                       basic_int8x16& a2, basic_int8x16& a3,
                       basic_int8x16& a4, basic_int8x16& a5,
                       basic_int8x16& a6, basic_int8x16& a7)
{
#if SIMDPP_USE_NULL
    null::transpose8(a0, a1, a2, a3, a4, a5, a6, a7);
#elif SIMDPP_USE_SSE2

    detail::partial_transpose8(a0, a1, a2, a3, a4, a5, a6, a7);

    basic_int64x2 d0, d1, d2, d3, d4, d5, d6, d7;
    d0 = a0;  d1 = a1;  d2 = a2;  d3 = a3;
    d4 = a4;  d5 = a5;  d6 = a6;  d7 = a7;
    /*
    [a0,...,h0,a1,...,h1]
    [a2,...,h2,a3,...,h3]
    [a4,...,h4,a5,...,h5]
    [a6,...,h6,a7,...,h7]
    [a8,...,h8,a9,...,h9]
    [a10,...,h10,a11,...,h11]
    [a12,...,h12,a13,...,h13]
    [a14,...,h14,a15,...,h15]
    */
    a0 = zip_lo(d0, d4);
    a1 = zip_hi(d0, d4);
    a2 = zip_lo(d1, d5);
    a3 = zip_hi(d1, d5);
    a4 = zip_lo(d2, d6);
    a5 = zip_hi(d2, d6);
    a6 = zip_lo(d3, d7);
    a7 = zip_hi(d3, d7);

#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    basic_int16x8 b0, b1, b2, b3, b4, b5, b6, b7;
    detail::transpose2(a0, a1); // 8-bit transpose
    detail::transpose2(a2, a3);
    detail::transpose2(a4, a5);
    detail::transpose2(a6, a7);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    b4 = a4;  b5 = a5;  b6 = a6;  b7 = a7;

    /*
    [a0,b0,a2,b2,...,a14,b14]
    [a1,b1,a3,b3,...,a15,b15]
    [c0,d0,c2,d2,...,c14,d14]
    [c1,d1,c3,d3,...,c15,d15]
    [e0,f0,e2,f2,...,e14,f14]
    [e1,f1,e3,f3,...,e15,f15]
    [g0,h0,g2,h2,...,g14,h14]
    [g1,h1,g3,h3,...,g15,h15]
    */
    basic_int32x4 c0, c1, c2, c3, c4, c5, c6, c7;
    transpose2(b0, b2); // 16-bit transpose
    transpose2(b1, b3);
    transpose2(b4, b6);
    transpose2(b5, b7);
    c0 = b0;  c1 = b1;  c2 = b2;  c3 = b3;
    c4 = b4;  c5 = b5;  c6 = b6;  c7 = b7;

    /*
    [a0,...,d0,a4,...,d4,a8 ,...,d8 ,a12,...,d12]
    [a1,...,d1,a5,...,d5,a9 ,...,d9 ,a13,...,d13]
    [a2,...,d2,a6,...,d6,a10,...,d10,a14,...,d14]
    [a3,...,d3,a7,...,d7,a11,...,d11,a15,...,d15]
    [e0,...,h0,e4,...,h4,e8 ,...,h8 ,e12,...,h12]
    [e1,...,h1,e5,...,h5,e9 ,...,h9 ,e13,...,h13]
    [e2,...,h2,e6,...,h6,e10,...,h10,e14,...,h14]
    [e3,...,h3,e7,...,h7,e11,...,h11,e15,...,h15]
    */
    transpose2(c0, c4); // 32-bit transpose
    transpose2(c1, c5);
    transpose2(c2, c6);
    transpose2(c3, c7);
    a0 = c0;  a1 = c1;  a2 = c2;  a3 = c3;
    a4 = c4;  a5 = c5;  a6 = c6;  a7 = c7;
#endif
    /*
    [a0,...,h0,a8,...,h8]
    [a1,...,h1,a9,...,h9]
    [a2,...,h2,a10,...,h10]
    [a3,...,h3,a11,...,h11]
    [a4,...,h4,a12,...,h12]
    [a5,...,h5,a13,...,h13]
    [a6,...,h6,a14,...,h14]
    [a7,...,h7,a15,...,h15]
    */
}

inline void transpose8(basic_int8x32& a0, basic_int8x32& a1,
                       basic_int8x32& a2, basic_int8x32& a3,
                       basic_int8x32& a4, basic_int8x32& a5,
                       basic_int8x32& a6, basic_int8x32& a7)
{
#if SIMDPP_USE_AVX2
    detail::partial_transpose8(a0, a1, a2, a3, a4, a5, a6, a7);

    basic_int64x4 d0, d1, d2, d3, d4, d5, d6, d7;
    d0 = a0;  d1 = a1;  d2 = a2;  d3 = a3;
    d4 = a4;  d5 = a5;  d6 = a6;  d7 = a7;

    a0 = zip_lo(d0, d4);
    a1 = zip_hi(d0, d4);
    a2 = zip_lo(d1, d5);
    a3 = zip_hi(d1, d5);
    a4 = zip_lo(d2, d6);
    a5 = zip_hi(d2, d6);
    a6 = zip_lo(d3, d7);
    a7 = zip_hi(d3, d7);
#else
    transpose8(a0[0], a1[0], a2[0], a3[0], a4[0], a5[0], a6[0], a7[0]);
    transpose8(a0[1], a1[1], a2[1], a3[1], a4[1], a5[1], a6[1], a7[1]);
#endif
}
/// @}

/** Transposes a 8x8 16-bit matrix within eight int16x8 vectors

    @code
    r0 = [ a0_0; a1_0; a2_0; a3_0 ...; a7_0 ]
    r1 = [ a0_1; a1_1; a2_1; a3_1 ...; a7_1 ]
    ...
    r7 = [ a0_7; a1_7; a2_7; a3_7 ...; a7_7 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 24}
    @icost{NEON, 12}

    @par 256-bit version:
    @icost{SSE2-AVX, 48}
    @icost{AVX2, 24}
    @icost{NEON, 24}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline void transpose8(basic_int16x8& a0, basic_int16x8& a1,
                       basic_int16x8& a2, basic_int16x8& a3,
                       basic_int16x8& a4, basic_int16x8& a5,
                       basic_int16x8& a6, basic_int16x8& a7)
{
    /*
    [a0,a1,a2,a3,a4,a5,a6,a7]
    [b0,b1,b2,b3,b4,b5,b6,b7]
    [c0,c1,c2,c3,c4,c5,c6,c7]
    [d0,d1,d2,d3,d4,d5,d6,d7]
    [e0,e1,e2,e3,e4,e5,e6,e7]
    [f0,f1,f2,f3,f4,f5,f6,f7]
    [g0,g1,g2,g3,g4,g5,g6,g7]
    [h0,h1,h2,h3,h4,h5,h6,h7]
    */
#if SIMDPP_USE_NULL
    null::transpose8(a0, a1, a2, a3, a4, a5, a6, a7);
#elif SIMDPP_USE_SSE2
    basic_int32x4 b0, b1, b2, b3, b4, b5, b6, b7;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    b2 = zip_lo(a2, a3);
    b3 = zip_hi(a2, a3);
    b4 = zip_lo(a4, a5);
    b5 = zip_hi(a4, a5);
    b6 = zip_lo(a6, a7);
    b7 = zip_hi(a6, a7);
    /*
    [a0,b0,a1,b1,a2,b2,a3,b3]
    [a4,b4,a5,b5,a6,b6,a7,b7]
    [c0,d0,c1,d1,c2,d2,c3,d3]
    [c4,d4,c5,d5,c6,d6,c7,d7]
    [e0,f0,e1,f1,e2,f2,e3,f3]
    [e4,f4,e5,f5,e6,f6,e7,f7]
    [g0,h0,g1,h1,g2,h2,g3,h3]
    [g4,h4,g5,h5,g6,h6,g7,h7]
    */
    basic_int64x2 c0, c1, c2, c3, c4, c5, c6, c7;
    c0 = zip_lo(b0, b2);
    c1 = zip_lo(b4, b6);
    c2 = zip_hi(b0, b2);
    c3 = zip_hi(b4, b6);
    c4 = zip_lo(b1, b3);
    c5 = zip_lo(b5, b7);
    c6 = zip_hi(b1, b3);
    c7 = zip_hi(b5, b7);
    /*
    [a0,b0,c0,d0,a1,b1,c1,d1]
    [e0,f0,g0,h0,e1,f1,g1,h1]
    [a2,b2,c2,d2,a3,b3,c3,d3]
    [e2,f2,g2,h2,e3,f3,g3,h3]
    [a4,b4,c4,d4,a5,b5,c5,d5]
    [e4,f4,g4,h4,e5,f5,g5,h5]
    [a6,b6,c6,d6,a7,b7,c7,d7]
    [e6,f6,g6,h6,e7,f7,g7,h7]
    */
    a0 = zip_lo(c0, c1);
    a1 = zip_hi(c0, c1);
    a2 = zip_lo(c2, c3);
    a3 = zip_hi(c2, c3);
    a4 = zip_lo(c4, c5);
    a5 = zip_hi(c4, c5);
    a6 = zip_lo(c6, c7);
    a7 = zip_hi(c6, c7);

#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC

    transpose4(a0, a1, a2, a3);
    transpose4(a4, a5, a6, a7);

    basic_int64x2 b0, b1, b2, b3, b4, b5, b6, b7;
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    b4 = a4;  b5 = a5;  b6 = a6;  b7 = a7;
    /*
    [a0,b0,c0,d0,a4,b4,c4,d4]
    [a1,b1,c1,d1,a5,b5,c5,d5]
    [a2,b2,c2,d2,a6,b6,c6,d6]
    [a3,b3,c3,d3,a7,b7,c7,d7]
    [e0,f0,g0,h0,e4,f4,g4,h4]
    [e1,f1,g1,h1,e5,f5,g5,h5]
    [e2,f2,g2,h2,e6,f6,g6,h6]
    [e3,f3,g3,h3,e7,f7,g7,h7]
    */
    transpose2(b0, b4); // 64-bit transpose
    transpose2(b1, b5);
    transpose2(b2, b6);
    transpose2(b3, b7);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
    a4 = b4;  a5 = b5;  a6 = b6;  a7 = b7;

#endif
    /*
    [a0,b0,c0,d0,e0,f0,g0,h0]
    [a1,b1,c1,d1,e1,f1,g1,h1]
    [a2,b2,c2,d2,e2,f2,g2,h2]
    [a3,b3,c3,d3,e3,f3,g3,h3]
    [a4,b4,c4,d4,e4,f4,g4,h4]
    [a5,b5,c5,d5,e5,f5,g5,h5]
    [a6,b6,c6,d6,e6,f6,g6,h6]
    [a7,b7,c7,d7,e7,f7,g7,h7]
    */
}

inline void transpose8(basic_int16x16& a0, basic_int16x16& a1,
                       basic_int16x16& a2, basic_int16x16& a3,
                       basic_int16x16& a4, basic_int16x16& a5,
                       basic_int16x16& a6, basic_int16x16& a7)
{
#if SIMDPP_USE_AVX2
    basic_int32x8 b0, b1, b2, b3, b4, b5, b6, b7;
    b0 = zip_lo(a0, a1);
    b1 = zip_hi(a0, a1);
    b2 = zip_lo(a2, a3);
    b3 = zip_hi(a2, a3);
    b4 = zip_lo(a4, a5);
    b5 = zip_hi(a4, a5);
    b6 = zip_lo(a6, a7);
    b7 = zip_hi(a6, a7);

    basic_int64x4 c0, c1, c2, c3, c4, c5, c6, c7;
    c0 = zip_lo(b0, b2);
    c1 = zip_lo(b4, b6);
    c2 = zip_hi(b0, b2);
    c3 = zip_hi(b4, b6);
    c4 = zip_lo(b1, b3);
    c5 = zip_lo(b5, b7);
    c6 = zip_hi(b1, b3);
    c7 = zip_hi(b5, b7);

    a0 = zip_lo(c0, c1);
    a1 = zip_hi(c0, c1);
    a2 = zip_lo(c2, c3);
    a3 = zip_hi(c2, c3);
    a4 = zip_lo(c4, c5);
    a5 = zip_hi(c4, c5);
    a6 = zip_lo(c6, c7);
    a7 = zip_hi(c6, c7);

#else
    transpose8(a0[0], a1[0], a2[0], a3[0], a4[0], a5[0], a6[0], a7[0]);
    transpose8(a0[1], a1[1], a2[1], a3[1], a4[1], a5[1], a6[1], a7[1]);
#endif
}

/** Transposes a 16x16 8-bit matrix within sixteen int8x16 vectors

    @code
    r0 =  [ a0_0; ...; a15_0 ]
    r1 =  [ a0_1; ...; a15_1 ]
    ...
    r15 = [ a0_15; ...; a15_15 ]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, NEON, 32}

    @par 256-bit version:
    @icost{SSE2-AVX, 64}
    @icost{AVX2, 32}
    @icost{NEON, 64}

    The lower and higher 128-bit halves are processed as if 128-bit instruction
    was applied to each of them separately.
*/
inline void transpose16(basic_int8x16& a0, basic_int8x16& a1,
                        basic_int8x16& a2, basic_int8x16& a3,
                        basic_int8x16& a4, basic_int8x16& a5,
                        basic_int8x16& a6, basic_int8x16& a7,
                        basic_int8x16& a8, basic_int8x16& a9,
                        basic_int8x16& a10, basic_int8x16& a11,
                        basic_int8x16& a12, basic_int8x16& a13,
                        basic_int8x16& a14, basic_int8x16& a15)
{
#if SIMDPP_USE_NULL
    null::transpose16(a0, a1, a2,  a3,  a4,  a5,  a6,  a7,
                      a8, a9, a10, a11, a12, a13, a14, a15);
#elif SIMDPP_USE_SSE2
    detail::partial_transpose8(a0, a1, a2, a3, a4, a5, a6, a7);
    detail::partial_transpose8(a8, a9, a10, a11, a12, a13, a14, a15);
    /*
    [a0,...,h0,a1,...,h1]
    [a2,...,h2,a3,...,h3]
    [a4,...,h4,a5,...,h5]
    [a6,...,h6,a7,...,h7]
    [a8,...,h8,a9,...,h9]
    [a10,...,h10,a11,...,h11]
    [a12,...,h12,a13,...,h13]
    [a14,...,h14,a15,...,h15]
    [i0,...,p0,i1,...,p1]
    [i2,...,p2,i3,...,p3]
    [i4,...,p4,i5,...,p5]
    [i6,...,p6,i7,...,p7]
    [i8,...,p8,i9,...,p9]
    [i10,...,p10,i11,...,p11]
    [i12,...,p12,i13,...,p13]
    [i14,...,p14,i15,...,p15]
    */
    basic_int64x2 d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;
    d0 = a0;  d1 = a1;  d2 = a2;  d3 = a3;
    d4 = a4;  d5 = a5;  d6 = a6;  d7 = a7;
    d8 = a8;  d9 = a9;  d10 = a10;  d11 = a11;
    d12 = a12;  d13 = a13;  d14 = a14;  d15 = a15;

    a0 = zip_lo(d0, d8);
    a1 = zip_hi(d0, d8);
    a2 = zip_lo(d1, d9);
    a3 = zip_hi(d1, d9);
    a4 = zip_lo(d2, d10);
    a5 = zip_hi(d2, d10);
    a6 = zip_lo(d3, d11);
    a7 = zip_hi(d3, d11);
    a8 = zip_lo(d4, d12);
    a9 = zip_hi(d4, d12);
    a10 = zip_lo(d5, d13);
    a11 = zip_hi(d5, d13);
    a12 = zip_lo(d6, d14);
    a13 = zip_hi(d6, d14);
    a14 = zip_lo(d7, d15);
    a15 = zip_hi(d7, d15);

#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC

    transpose8(a0, a1, a2, a3, a4, a5, a6, a7);
    transpose8(a8, a9, a10, a11, a12, a13, a14, a15);

    /*
    [a0,...,h0,a8,...,h8]
    [a1,...,h1,a9,...,h9]
    [a2,...,h2,a10,...,h10]
    [a3,...,h3,a11,...,h11]
    [a4,...,h4,a12,...,h12]
    [a5,...,h5,a13,...,h13]
    [a6,...,h6,a14,...,h14]
    [a7,...,h7,a15,...,h15]
    [i0,...,p0,i8,...,p8]
    [i1,...,p1,i9,...,p9]
    [i2,...,p2,i10,...,p10]
    [i3,...,p3,i11,...,p11]
    [i4,...,p4,i12,...,p12]
    [i5,...,p5,i13,...,p13]
    [i6,...,p6,i14,...,p14]
    [i7,...,p7,i15,...,p15]
    */

    basic_int64x2 d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;
    d0 = a0;  d1 = a1;  d2 = a2;  d3 = a3;
    d4 = a4;  d5 = a5;  d6 = a6;  d7 = a7;
    d8 = a8;  d9 = a9;  d10 = a10;  d11 = a11;
    d12 = a12;  d13 = a13;  d14 = a14;  d15 = a15;

    transpose2(d0, d8); // 64-bit transpose
    transpose2(d1, d9);
    transpose2(d2, d10);
    transpose2(d3, d11);
    transpose2(d4, d12);
    transpose2(d5, d13);
    transpose2(d6, d14);
    transpose2(d7, d15);

    a0 = d0;  a1 = d1;  a2 = d2;  a3 = d3;
    a4 = d4;  a5 = d5;  a6 = d6;  a7 = d7;
    a8 = d8;  a9 = d9;  a10 = d10;  a11 = d11;
    a12 = d12;  a13 = d13;  a14 = d14;  a15 = d15;
#endif
}

inline void transpose16(basic_int8x32& a0, basic_int8x32& a1,
                        basic_int8x32& a2, basic_int8x32& a3,
                        basic_int8x32& a4, basic_int8x32& a5,
                        basic_int8x32& a6, basic_int8x32& a7,
                        basic_int8x32& a8, basic_int8x32& a9,
                        basic_int8x32& a10, basic_int8x32& a11,
                        basic_int8x32& a12, basic_int8x32& a13,
                        basic_int8x32& a14, basic_int8x32& a15)
{
#if SIMDPP_USE_AVX2
    detail::partial_transpose8(a0, a1, a2, a3, a4, a5, a6, a7);
    detail::partial_transpose8(a8, a9, a10, a11, a12, a13, a14, a15);

    basic_int64x4 d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15;
    d0 = a0;  d1 = a1;  d2 = a2;  d3 = a3;
    d4 = a4;  d5 = a5;  d6 = a6;  d7 = a7;
    d8 = a8;  d9 = a9;  d10 = a10;  d11 = a11;
    d12 = a12;  d13 = a13;  d14 = a14;  d15 = a15;

    a0 = zip_lo(d0, d8);
    a1 = zip_hi(d0, d8);
    a2 = zip_lo(d1, d9);
    a3 = zip_hi(d1, d9);
    a4 = zip_lo(d2, d10);
    a5 = zip_hi(d2, d10);
    a6 = zip_lo(d3, d11);
    a7 = zip_hi(d3, d11);
    a8 = zip_lo(d4, d12);
    a9 = zip_hi(d4, d12);
    a10 = zip_lo(d5, d13);
    a11 = zip_hi(d5, d13);
    a12 = zip_lo(d6, d14);
    a13 = zip_hi(d6, d14);
    a14 = zip_lo(d7, d15);
    a15 = zip_hi(d7, d15);
#else
    transpose16(a0[0], a1[0], a2[0],  a3[0],  a4[0],  a5[0],  a6[0],  a7[0],
                a8[0], a9[0], a10[0], a11[0], a12[0], a13[0], a14[0], a15[0]);
    transpose16(a0[1], a1[1], a2[1],  a3[1],  a4[1],  a5[1],  a6[1],  a7[1],
                a8[1], a9[1], a10[1], a11[1], a12[1], a13[1], a14[1], a15[1]);
#endif
}

/// @} -- end defgroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

