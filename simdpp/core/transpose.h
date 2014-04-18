/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_TRANSPOSE_H
#define LIBSIMDPP_SIMDPP_CORE_TRANSPOSE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/detail/insn/transpose.h>
#include <simdpp/neon/shuffle.h>
#include <simdpp/detail/null/transpose.h>
#include <simdpp/sse/shuffle.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
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
inline void transpose2(uint16x8& a0, uint16x8& a1)
{
#if SIMDPP_USE_NULL
    detail::null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    uint32x4 b0, b1;
    b0 = zip8_lo(a0, a1);
    b1 = zip8_hi(a0, a1);
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

inline void transpose2(int16x8& a0, int16x8& a1)
{
    uint16x8 b0, b1;
    b0 = a0; b1 = a1;
    transpose2(b0, b1);
    a0 = b0; a1 = b1;
}

inline void transpose2(uint16x16& a0, uint16x16& a1)
{
#if SIMDPP_USE_AVX2
    uint32x8 b0, b1;
    b0 = zip8_lo(a0, a1);
    b1 = zip8_hi(a0, a1);
    a0 = shuffle2<0,2,0,2>(b0, b1);
    a1 = shuffle2<1,3,1,3>(b0, b1);
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}

inline void transpose2(int16x16& a0, int16x16& a1)
{
    uint16x16 b0, b1;
    b0 = a0; b1 = a1;
    transpose2(b0, b1);
    a0 = b0; a1 = b1;
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
inline void transpose2(uint32x4& a0, uint32x4& a1)
{
#if SIMDPP_USE_NULL
    detail::null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    uint64x2 b0, b1;
    b0 = zip4_lo(a0, a1);
    b1 = zip4_hi(a0, a1);
    a0 = zip2_lo(b0, b1);
    a1 = zip2_hi(b0, b1);
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

inline void transpose2(int32x4& a0, int32x4& a1)
{
    uint32x4 b0, b1;
    b0 = a0; b1 = a1;
    transpose2(b0, b1);
    a0 = b0; a1 = b1;
}

inline void transpose2(uint32x8& a0, uint32x8& a1)
{
#if SIMDPP_USE_AVX2
    uint64x4 b0, b1;
    b0 = zip4_lo(a0, a1);
    b1 = zip4_hi(a0, a1);
    a0 = zip2_lo(b0, b1);
    a1 = zip2_hi(b0, b1);
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}

inline void transpose2(int32x8& a0, int32x8& a1)
{
    uint32x8 b0, b1;
    b0 = a0; b1 = a1;
    transpose2(b0, b1);
    a0 = b0; a1 = b1;
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
inline void transpose2(uint64x2& a0, uint64x2& a1)
{
#if SIMDPP_USE_NULL
    detail::null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    uint64x2 b0;
    b0 = zip2_lo(a0, a1);
    a1 = zip2_hi(a0, a1);
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

inline void transpose2(int64x2& a0, int64x2& a1)
{
    uint64x2 b0, b1;
    b0 = a0; b1 = a1;
    transpose2(b0, b1);
    a0 = b0; a1 = b1;
}

inline void transpose2(uint64x4& a0, uint64x4& a1)
{
#if SIMDPP_USE_AVX2
    uint64x4 b0;
    b0 = zip2_lo(a0, a1);
    a1 = zip2_hi(a0, a1);
    a0 = b0;
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}

inline void transpose2(int64x4& a0, int64x4& a1)
{
    uint64x4 b0, b1;
    b0 = a0; b1 = a1;
    transpose2(b0, b1);
    a0 = b0; a1 = b1;
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
    detail::null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    float64x2 b0, b1;
    b0 = bit_cast<float64x2>(zip4_lo(a0, a1));
    b1 = bit_cast<float64x2>(zip4_hi(a0, a1));
    a0 = bit_cast<float32x4>(zip2_lo(b0, b1));
    a1 = bit_cast<float32x4>(zip2_hi(b0, b1));
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
    b0 = bit_cast<float64x4>(zip4_lo(a0, a1));
    b1 = bit_cast<float64x4>(zip4_hi(a0, a1));
    a0 = bit_cast<float32x8>(zip2_lo(b0, b1));
    a1 = bit_cast<float32x8>(zip2_hi(b0, b1));
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
    detail::null::transpose2(a0, a1);
#elif SIMDPP_USE_SSE2
    float64x2 b0;
    b0 = zip2_lo(a0, a1);
    a1 = zip2_hi(a0, a1);
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
    b0 = zip2_lo(a0, a1);
    a1 = zip2_hi(a0, a1);
    a0 = b0;
#else
    transpose2(a0[0], a1[0]);
    transpose2(a0[1], a1[1]);
#endif
}
/// @}

void transpose4(uint32x4& a0, uint32x4& a1,
                uint32x4& a2, uint32x4& a3);
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
inline void transpose4(uint8x16& a0, uint8x16& a1,
                       uint8x16& a2, uint8x16& a3)
{
    // [a0,a1,a2,a3 ... ]
    // [b0,b1,b2,b3 ... ]
    // [c0,c1,c2,c3 ... ]
    // [d0,d1,d2,d3 ... ]
#if SIMDPP_USE_NULL
    detail::null::transpose4(a0, a1, a2, a3);
#elif SIMDPP_USE_SSE2
    uint16x8 b0, b1, b2, b3;
    b0 = zip16_lo(a0, a1);
    b1 = zip16_lo(a2, a3);
    b2 = zip16_hi(a0, a1);
    b3 = zip16_hi(a2, a3);
    // [a0,b0,a1,b1,a2,b2,a3,b3 ... b7]
    // [c0,d0,c1,d1,c2,d2,c3,d3 ... d7]
    // [a8 ... b15]
    // [c8 ... d15]
    uint32x4 c0, c1, c2, c3;
    c0 = zip8_lo(b0, b1);
    c1 = zip8_hi(b0, b1);
    c2 = zip8_lo(b2, b3);
    c3 = zip8_hi(b2, b3);
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
    uint16x8 b0, b1, b2, b3;
    detail::transpose2(a0, a1);  // 8-bit transpose
    detail::transpose2(a2, a3);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose2(b0, b2);  // 16-bit transpose
    transpose2(b1, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(int8x16& a0, int8x16& a1,
                       int8x16& a2, int8x16& a3)
{
    uint8x16 b0, b1, b2, b3;
    b0 = a0; b1 = a1; b2 = a2; b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0; a1 = b1; a2 = b2; a3 = b3;
}

inline void transpose4(uint32x8& a0, uint32x8& a1,
                       uint32x8& a2, uint32x8& a3);

inline void transpose4(uint8x32& a0, uint8x32& a1,
                       uint8x32& a2, uint8x32& a3)
{
#if SIMDPP_USE_AVX2
    uint16x16 b0, b1, b2, b3;
    b0 = zip16_lo(a0, a1);
    b1 = zip16_lo(a2, a3);
    b2 = zip16_hi(a0, a1);
    b3 = zip16_hi(a2, a3);
    uint32x8 c0, c1, c2, c3;
    c0 = zip8_lo(b0, b1);
    c1 = zip8_hi(b0, b1);
    c2 = zip8_lo(b2, b3);
    c3 = zip8_hi(b2, b3);
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

inline void transpose4(int8x32& a0, int8x32& a1,
                       int8x32& a2, int8x32& a3)
{
    uint8x32 b0, b1, b2, b3;
    b0 = a0; b1 = a1; b2 = a2; b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0; a1 = b1; a2 = b2; a3 = b3;
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
inline void transpose4(uint16x8& a0, uint16x8& a1,
                       uint16x8& a2, uint16x8& a3)
{
#if SIMDPP_USE_NULL
    detail::null::transpose4(a0, a1, a2, a3);
#elif SIMDPP_USE_SSE2
    uint32x4 b0, b1, b2, b3;
    uint64x2 c0, c1, c2, c3;
    b0 = zip8_lo(a0, a1);
    b1 = zip8_hi(a0, a1);
    b2 = zip8_lo(a2, a3);
    b3 = zip8_hi(a2, a3);
    // [a0,b0,a1,b1,a2,b2,a3,b3]
    // [a4,b4,a5,b5,a6,b6,a7,b7]
    // [c0,d0,c1,d1,c2,d2,c3,d3]
    // [c4,d4,c5,d5,c6,d6,c7,d7]
    c0 = zip4_lo(b0, b2);
    c1 = zip4_hi(b0, b2);
    c2 = zip4_lo(b1, b3);
    c3 = zip4_hi(b1, b3);
    // [a0,b0,c0,d0,a1,b1,c1,d1]
    // [a2,b2,c2,d2,a3,b3,c3,d3]
    // [a4,b4,c4,d4,a5,b5,c5,d5]
    // [a6,b6,c6,d6,a7,b7,c7,d7]
    a0 = zip2_lo(c0, c2);
    a1 = zip2_hi(c0, c2);
    a2 = zip2_lo(c1, c3);
    a3 = zip2_hi(c1, c3);
    // [a0,b0,c0,d0,a4,b4,c4,d4]
    // [a1,b1,c1,d1,a5,b5,c5,d5]
    // [a2,b2,c2,d2,a6,b6,c6,d6]
    // [a3,b3,c3,d3,a7,b7,c7,d7]
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    uint32x4 b0, b1, b2, b3;
    transpose2(a0, a1);  // 16-bit transpose
    transpose2(a2, a3);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose2(b0, b2);  // 32-bit transpose
    transpose2(b1, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(int16x8& a0, int16x8& a1,
                       int16x8& a2, int16x8& a3)
{
    uint16x8 b0, b1, b2, b3;
    b0 = a0; b1 = a1; b2 = a2; b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0; a1 = b1; a2 = b2; a3 = b3;
}


inline void transpose4(uint16x16& a0, uint16x16& a1,
                       uint16x16& a2, uint16x16& a3)
{
#if SIMDPP_USE_AVX2
    uint32x8 b0, b1, b2, b3;
    uint64x4 c0, c1, c2, c3;
    b0 = zip8_lo(a0, a1);
    b1 = zip8_hi(a0, a1);
    b2 = zip8_lo(a2, a3);
    b3 = zip8_hi(a2, a3);

    c0 = zip4_lo(b0, b2);
    c1 = zip4_hi(b0, b2);
    c2 = zip4_lo(b1, b3);
    c3 = zip4_hi(b1, b3);

    a0 = zip2_lo(c0, c2);
    a1 = zip2_hi(c0, c2);
    a2 = zip2_lo(c1, c3);
    a3 = zip2_hi(c1, c3);
#else
    transpose4(a0[0], a1[0], a2[0], a3[0]);
    transpose4(a0[1], a1[1], a2[1], a3[1]);
#endif
}

inline void transpose4(int16x16& a0, int16x16& a1,
                       int16x16& a2, int16x16& a3)
{
    uint16x16 b0, b1, b2, b3;
    b0 = a0; b1 = a1; b2 = a2; b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0; a1 = b1; a2 = b2; a3 = b3;
}
/// @}


namespace detail {

template<class V> struct dbl_length_vector;
template<> struct dbl_length_vector<uint32x4> { using type = uint64x2; };
template<> struct dbl_length_vector<uint32x8> { using type = uint64x4; };
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
    b0 = bit_cast<Z>(zip4_lo(a0, a1));
    b1 = bit_cast<Z>(zip4_hi(a0, a1));
    b2 = bit_cast<Z>(zip4_lo(a2, a3));
    b3 = bit_cast<Z>(zip4_hi(a2, a3));
    // [a0,b0,a1,b1]
    // [a2,b2,a3,b3]
    // [c0,d0,c1,d1]
    // [c2,d2,c3,d3]
    a0 = bit_cast<V>(zip2_lo(b0, b2));
    a1 = bit_cast<V>(zip2_hi(b0, b2));
    a2 = bit_cast<V>(zip2_lo(b1, b3));
    a3 = bit_cast<V>(zip2_hi(b1, b3));
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
inline void transpose4(uint32x4& a0, uint32x4& a1,
                       uint32x4& a2, uint32x4& a3)
{
#if SIMDPP_USE_NULL
    detail::null::transpose4(a0, a1, a2, a3);
#elif SIMDPP_USE_SSE2
    detail::sse_transpose4x32_impl(a0, a1, a2, a3);
#elif SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    uint64x2 b0, b1, b2, b3;
    transpose2(a0, a1);  // 32-bit transpose
    transpose2(a2, a3);
    b0 = a0;  b1 = a1;  b2 = a2;  b3 = a3;
    transpose2(b0, b2);  // 64-bit transpose
    transpose2(b1, b3);
    a0 = b0;  a1 = b1;  a2 = b2;  a3 = b3;
#endif
}

inline void transpose4(int32x4& a0, int32x4& a1,
                       int32x4& a2, int32x4& a3)
{
    uint32x4 b0, b1, b2, b3;
    b0 = a0; b1 = a1; b2 = a2; b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0; a1 = b1; a2 = b2; a3 = b3;
}

inline void transpose4(uint32x8& a0, uint32x8& a1,
                       uint32x8& a2, uint32x8& a3)
{
#if SIMDPP_USE_AVX2
    detail::sse_transpose4x32_impl(a0, a1, a2, a3);
#else
    transpose4(a0[0], a1[0], a2[0], a3[0]);
    transpose4(a0[1], a1[1], a2[1], a3[1]);
#endif
}

inline void transpose4(int32x8& a0, int32x8& a1,
                       int32x8& a2, int32x8& a3)
{
    uint32x8 b0, b1, b2, b3;
    b0 = a0; b1 = a1; b2 = a2; b3 = a3;
    transpose4(b0, b1, b2, b3);
    a0 = b0; a1 = b1; a2 = b2; a3 = b3;
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
    uint32x4 b0, b1, b2, b3;
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

/// @} -- end defgroup

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

