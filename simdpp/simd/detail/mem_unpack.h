/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMD_DETAIL_MEM_UNPACK_H
#define LIBSIMDPP_SIMD_DETAIL_MEM_UNPACK_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/make_shuffle_bytes_mask.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/shuffle_generic.h>
#include <simdpp/simd/transpose.h>
#include <simdpp/simd/detail/width.h>
#include <simdpp/simd/detail/shuffle128.h>
#include <simdpp/simd/detail/transpose.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class T>
void mem_unpack2_impl(T& a, T& b)
{
    T c1, c2;
    c1 = a;
    c2 = b;
    a = unzip_lo(c1, c2);
    b = unzip_hi(c1, c2);
}

template<class T>
void mem_unpack2_256_impl(T& a, T& b)
{
    T c1, c2;
    c1 = shuffle128<0,2>(a, b);
    c2 = shuffle128<1,3>(a, b);
    a = unzip_lo(c1, c2);
    b = unzip_hi(c1, c2);
}

/// @{
/** Concatenates @a a and @a b and stores the elements of the resulting array
    as follows:
     * every (2n)-th element is stored to @a a
     * every (2n+1)-th element is stored to @a b

    n = [0, <number of elements in vector> - 1]
*/
inline void mem_unpack2(basic_int8x16& a, basic_int8x16& b) { mem_unpack2_impl(a, b); }
inline void mem_unpack2(basic_int16x8& a, basic_int16x8& b) { mem_unpack2_impl(a, b); }
inline void mem_unpack2(basic_int32x4& a, basic_int32x4& b) { mem_unpack2_impl(a, b); }
inline void mem_unpack2(basic_int64x2& a, basic_int64x2& b) { mem_unpack2_impl(a, b); }
inline void mem_unpack2(float32x4& a, float32x4& b)         { mem_unpack2_impl(a, b); }
inline void mem_unpack2(float64x2& a, float64x2& b)         { mem_unpack2_impl(a, b); }

inline void mem_unpack2(basic_int8x32& a, basic_int8x32& b) { mem_unpack2_256_impl(a, b); }
inline void mem_unpack2(basic_int16x16& a, basic_int16x16& b){mem_unpack2_256_impl(a, b); }
inline void mem_unpack2(basic_int32x8& a, basic_int32x8& b) { mem_unpack2_256_impl(a, b); }
inline void mem_unpack2(basic_int64x4& a, basic_int64x4& b) { mem_unpack2_256_impl(a, b); }
inline void mem_unpack2(float32x8& a, float32x8& b)         { mem_unpack2_256_impl(a, b); }
inline void mem_unpack2(float64x4& a, float64x4& b)         { mem_unpack2_256_impl(a, b); }
/// @}

/// @{
/** Generic implementation of mem_unpack3. The 256-bit version applies 128-bit
    operations to each half of each vector separately.
*/
template<class T> void mem_unpack3_impl8(T& a, T& b, T& c)
{
#if SIMDPP_USE_ALTIVEC
    using U = typename T::uint_vector_type;

    // [a0, b0, c0, a1, b1, c1, a2, b2, c2, a3, b3, c3, a4, b4, c4, a5 ]
    // [b5, c5, a6, b6, c6, a7, b7, c7, a8, b8, c8, a9, b9, c9, a10,b10]
    // [c10,a11,b11,c11,a12,b12,c12,a13,b13,c13,a14,b14,c14,a15,b15,c15]
    T mask1 = make_shuffle_bytes16_mask<   1,    4,    7, 10, 13,16+0,16+3,16+6,
                                        16+9,16+12,16+15,  3,  6,   9,  12,  15>(mask1);
    T a1, b1, c1;
    a1 = shuffle_bytes16(c, a, mask1);
    b1 = shuffle_bytes16(a, b, mask1);
    c1 = shuffle_bytes16(b, c, mask1);
    // [a11,a12,a13,a14,a15,a0, a1, a2, a3, a4, a5, b11,b12,b13,b14,b15]
    // [b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10,c0, c1, c2, c3, c4 ]
    // [c5, c6, c7, c8, c9, c10,c11,c12,c13,c14,c15,a6, a7, a8, a9, a10]
    T a2, b2, c2;
    T mask2 = U::make_const(0xff);
    mask2 = move_l<5>(mask2);

    a2 = blend(a1, c1, mask2);
    b2 = blend(b1, a1, mask2);
    c2 = blend(c1, b1, mask2);
    // [a11..a15,a0..a10]
    // [b0..b15]
    // [c5..c15,c0..c5]
    a = align<5>(a2, a2);
    b = b2;
    c = align<11>(c2, c2);
#else
    typename same_width<T>::b8 t0, t1, t2, t3;
    t0 = a;
    t1 = align<12>(a, b);
    t2 = align<8>(b, c);
    t3 = move_l<4>(c);
    // [a0, b0, c0, a1, b1, c1, a2, b2, c2, a3, b3, c3, ...]
    // [a4, b4, c4, a5, b5, c5, a6, b6, c6, a7, b7, c7, ...]
    // [a8, b8, c8, a9, b9, c9, a10,b10,c10,a11,b11,c11, ...]
    // [a12,b12,c12,a13,b13,c13,a14,b14,c14,a15,b15,c15, ...]
    typename same_width<T>::b16 b0, b1, b2, b3;
    b0 = zip_lo(t0, t1);
    b1 = zip_lo(t2, t3);
    b2 = zip_hi(t0, t1);
    b3 = zip_hi(t2, t3);
    // [a0, a4, b0, b4, c0, c4, a1, a5, b1, b5, c1, c5, a2, a6, b2, b6 ]
    // [a8, a12,b8, b12,c9, c13,a9, a13,b9, b13,c9, c13,a10,a14,b10,b14,]
    // [c2, c6, a3, a7, b3, b7, c3, c7, ... ]
    // [c10,c14,a11,a15,b11,b15,c11,c15,... ]
    typename same_width<T>::b8 u0, u1, u2;
    u0 = zip_lo(b0, b1);
    u1 = zip_hi(b0, b1);
    u2 = zip_lo(b2, b3);
    // [a0, a4, a8, a12,b0, b4, b8, b12, c0, c4, c8, c12, a1, a5, a9, a13 ]
    // [b1, b5, b9, b13,c1, c5, c9, c13, a2, a6, a10,a14, b2, b6, b10,b14 ]
    // [c2, c6, c10,c14,a3, a7, a11,a15, b3, b7, b11,b15, c3, c7, c11,c15 ]
    t0 = u0;
    t1 = align<12>(u0, u1);
    t2 = align<8>(u1, u2);
    t3 = move_l<4>(u2);
    // [a0, a4, a8, a12,b0, b4, b8, b12, c0, c4, c8, c12, ...]
    // [a1, a5, a9, a13,b1, b5, b9, b13, c1, c5, c9, c13, ...]
    // [a2, a6, a10,a14,b2, b6, b10,b13, c2, c6, c10,c14, ...]
    // [a3, a7, a11,a15,b3, b7, b11,b13, c3, c7, c11,c15, ...]
    b0 = zip_lo(t0, t1);
    b1 = zip_lo(t2, t3);
    b2 = zip_hi(t0, t1);
    b3 = zip_hi(t2, t3);
    // [a0, a1, a4, a5, a8, a9, a12,a13,b0, b1, b4, b5, b8, b9, b12,b13 ]
    // [a2, a3, a6, a7, a10,a11,a14,a15,b2, b3, b6, b7, b10,b11,b14,b15 ]
    // [c0, c1, c4, c5, c8, c9, c12,c13, ... ]
    // [c2, c3, c6, c7, c10,c11,c14,c15, ... ]
    a = zip_lo(b0, b1);
    b = zip_hi(b0, b1);
    c = zip_lo(b2, b3);
#endif
}

template<class T> void mem_unpack3_impl16(T& a, T& b, T& c)
{
#if SIMDPP_USE_ALTIVEC
    using U = typename T::uint_vector_type;

    // [a0,b0,c0,a1,b1,c1,a2,b2]
    // [c2,a3,b3,c3,a4,b4,c4,a5]
    // [b5,c5,a6,b6,c6,a7,b7,c7]
    T mask1 = make_shuffle_bytes16_mask<0,3,6,8+1,8+4,8+7,8+2,8+5>(mask1);
    T a1, b1, c1;
    a1 = shuffle_bytes16(a, b, mask1);
    c1 = shuffle_bytes16(b, c, mask1);
    b1 = shuffle_bytes16(c, a, mask1);
    // [a0,a1,a2,a3,a4,a5,b3,b4]
    // [c2,c3,c4,c5,c6,c7,a6,a7]
    // [b5,b6,b7,b0,b1,b2,c0,c1]
    T a2, b2, c2;
    T mask2 = U::make_const(0xffff);
    mask2 = move_l<2>(mask2);

    a2 = blend(a1, c1, mask2);
    b2 = blend(b1, a1, mask2);
    c2 = blend(c1, b1, mask2);
    // [a0..a7]
    // [b5..b7,b0..b4]
    // [c2..c7,c0,c1]
    a = a2;
    b = align<3>(b2, b2);
    c = align<6>(c2, c2);
#else
    T t0, t1, t2, t3;
    t0 = a;
    t1 = align<6>(a, b);
    t2 = align<4>(b, c);
    t3 = move_l<2>(c);
    // [a0,b0,c0,a1,b1,c1, ... ]
    // [a2,b2,c2,a3,b3,c3, ... ]
    // [a4,b4,c4,a5,b5,c5, ... ]
    // [a6,b6,c6,a7,b7,c7, ... ]
    typename same_width<T>::b32 b0, b1, b2, b3;
    b0 = zip_lo(t0, t1);
    b1 = zip_lo(t2, t3);
    b2 = zip_hi(t0, t1);
    b3 = zip_hi(t2, t3);
    // [a0,a2,b0,b2,c0,c2,a1,a3]
    // [a4,a6,b4,b6,c4,c6,a5,a7]
    // [b1,b3,c1,c3, ... ]
    // [b5,b7,c5,c7, ... ]
    typename same_width<T>::b64 c0, c1, c2;
    c0 = zip_lo(b0, b1);
    c1 = zip_hi(b0, b1);
    c2 = zip_lo(b2, b3);
    // [a0,a2,a4,a6,b0,b2,b4,b6]
    // [c0,c2,c4,c6,a1,a3,a5,a7]
    // [b1,b3,b5,b7,c1,c3,c5,c7]
    t0 = c0;
    t1 = shuffle1<1,0>(c0, c1);
    t2 = broadcast<1>(c1);
    t3 = c2;
    // [a0,a2,a4,a6,b0,b2,b4,b6]
    // [b0,b2,b4,b6,c0,c2,c4,c6]
    // [a1,a3,a5,a7,a1,a3,a5,a7]
    // [b1,b3,b5,b7,c1,c3,c5,c7]
    a = zip_lo(t0, t2);
    b = zip_lo(t1, t3);
    c = zip_hi(t1, t3);
#endif
}

template<class T> void mem_unpack3_impl32(T& a, T& b, T& c)
{
#if SIMDPP_USE_ALTIVEC
    using U = typename T::uint_vector_type;

    // [a0,b0,c0,a1]
    // [b1,c1,a2,b2]
    // [c2,a3,b3,c3]
    U mask1 = make_shuffle_bytes16_mask<0,3,4+2,4+1>(mask1);
    T a1, b1, c1;
    a1 = shuffle_bytes16(a, b, mask1);
    b1 = shuffle_bytes16(b, c, mask1);
    c1 = shuffle_bytes16(c, a, mask1);
    // [a0,a1,a2,c1]
    // [b1,b2,b3,a3]
    // [c2,c3,c0,b0]
    T a2, b2, c2;
    U mask2 = U::make_const(0xffffffff);
    mask2 = move_l<1>(mask2);

    a2 = blend(a1, b1, mask2);
    b2 = blend(b1, c1, mask2);
    c2 = blend(c1, a1, mask2);
    // [a0,a1,a2,a3]
    // [b1,b2,b3,b0]
    // [c2,c3,c0,c1]
    a = a2;
    b = align<3>(b2, b2);
    c = align<2>(c2, c2);
#else
    T t11, t12, t21, t22, t31, t32;
    // [a0,b0,c0,a1]
    // [b1,c1,a2,b2]
    // [c2,a3,b3,c3]
    t11 = a;
    t12 = shuffle2<0,1,2,3>(c, b);
    t21 = shuffle2<0,1,0,1>(a, b);
    t22 = shuffle2<2,3,2,3>(b, c);
    t31 = shuffle2<2,3,0,1>(a, b);
    t32 = c;
    // [a0,b0,c0,a1]
    // [c2,a3,a2,b2]
    // [a0,b0,b1,c1]
    // [a2,b2,b3,c3]
    // [c0,a1,b1,c1]
    // [c2,a3,b3,c3]
    a = shuffle2<0,3,2,1>(t11, t12);
    b = shuffle2<1,2,1,2>(t21, t22);
    c = shuffle2<0,3,0,3>(t31, t32);
#endif
}

template<class T> void mem_unpack3_impl64(T& a, T& b, T& c)
{
    T d0, d1, d2;
    d0 = shuffle1<0,1>(a, b);
    d1 = shuffle1<1,0>(a, c);
    d2 = shuffle1<0,1>(b, c);
    a = d0; b = d1; c = d2;
}
/// @}

template<class T>
void mem_unpack3_256_shuffle(T& a, T& b, T& c)
{
    // shuffle the vectors so that the lower halves contain the first 3 128-bit
    // items (a and lower half of b) and the higher halves contain the rest
    T t0, t1, t2;
    t0 = a;  t1 = b;  t2 = c;
    a = shuffle128<0,3>(t0, t1);
    b = shuffle128<1,2>(t0, t2);
    c = shuffle128<0,3>(t1, t2);
}
/// @{
/** Concatenates @a a, @a b and @a c and stores the elements of the resulting
    array as follows:
     * every (3n)-th element is stored to @a a
     * every (3n+1)-th element is stored to @a b
     * every (3n+2)-th element is stored to @a c

    n = [0, <number of elements in vector> - 1]
*/
inline void mem_unpack3(basic_int8x16& a, basic_int8x16& b, basic_int8x16& c)
{
    mem_unpack3_impl8(a, b, c);
}
inline void mem_unpack3(basic_int8x32& a, basic_int8x32& b, basic_int8x32& c)
{
    mem_unpack3_256_shuffle(a, b, c);
    mem_unpack3_impl8(a, b, c);
}

inline void mem_unpack3(basic_int16x8& a, basic_int16x8& b, basic_int16x8& c)
{
    mem_unpack3_impl16(a, b, c);
}
inline void mem_unpack3(basic_int16x16& a, basic_int16x16& b, basic_int16x16& c)
{
    mem_unpack3_256_shuffle(a, b, c);
    mem_unpack3_impl16(a, b, c);
}

inline void mem_unpack3(basic_int32x4& a, basic_int32x4& b, basic_int32x4& c)
{
    mem_unpack3_impl32(a, b, c);
}
inline void mem_unpack3(basic_int32x8& a, basic_int32x8& b, basic_int32x8& c)
{
    mem_unpack3_256_shuffle(a, b, c);
    mem_unpack3_impl32(a, b, c);
}

inline void mem_unpack3(basic_int64x2& a, basic_int64x2& b, basic_int64x2& c)
{
    mem_unpack3_impl64(a, b, c);
}
inline void mem_unpack3(basic_int64x4& a, basic_int64x4& b, basic_int64x4& c)
{
    mem_unpack3_256_shuffle(a, b, c);
    mem_unpack3_impl64(a, b, c);
}

inline void mem_unpack3(float32x4& a, float32x4& b, float32x4& c)
{
    mem_unpack3_impl32(a, b, c);
}
inline void mem_unpack3(float32x8& a, float32x8& b, float32x8& c)
{
    mem_unpack3_256_shuffle(a, b, c);
    mem_unpack3_impl32(a, b, c);
}

inline void mem_unpack3(float64x2& a, float64x2& b, float64x2& c)
{
    mem_unpack3_impl64(a, b, c);
}
inline void mem_unpack3(float64x4& a, float64x4& b, float64x4& c)
{
    mem_unpack3_256_shuffle(a, b, c);
    mem_unpack3_impl64(a, b, c);
}
/// @}

/// @{
/** Generic implementation of mem_unpack4. The 256-bit version applies 128-bit
    operations to each half of each vector separately.
*/
template<class T> void mem_unpack4_impl8(T& a, T& b, T& c, T& d)
{
#if SIMDPP_USE_SSSE3 || SIMDPP_USE_ALTIVEC
    // TODO: optimize for altivec
    typename same_width<T>::b32 b0, b1, b2, b3;
    b0 = transpose_inplace(a);
    b1 = transpose_inplace(b);
    b2 = transpose_inplace(c);
    b3 = transpose_inplace(d);

    transpose4(b0, b1, b2, b3);
    a = b0;  b = b1;  c = b2;  d = b3;
#else
    // [a0, b0, c0, d0, a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3 ]
    // [a4, b4, c4, d4, a5, b5, c5, d5, a6, b6, c6, d6, a7, b7, c7, d7 ]
    // [a8, b8, c8, d8, a9, b9, c9, d9, a10,b10,c10,d10,a11,b11,c11,d11]
    // [a12,b12,c12,d12,a13,b13,c13,d13,a14,b14,c14,d14,a15,b15,c15,d15]
    T b0, b1, b2, b3, c0, c1, c2, c3;
    b0 = zip_lo(a, b);
    b1 = zip_hi(a, b);
    b2 = zip_lo(c, d);
    b3 = zip_hi(c, d);
    // [a0, a4, b0, b4, c0, c4, d0, d4, a1, a5, b1, b5, c1, c5, d1, d5 ]
    // [a2, a6, b2, b6, c2, c6, d2, d6, a3, a7, b3, b7, c3, c7, d3, d7 ]
    // [a8, a12,b8, b12,c8, c12,d8, d12,a9, a13,b9, b13,c9, c13,d9, d13]
    // [a10,a14,b10,b14,c10,c14,d10,d14,a11,a15,b11,b15,c11,c15,d11,d15]
    c0 = zip_lo(b0, b1);
    c1 = zip_hi(b0, b1);
    c2 = zip_lo(b2, b3);
    c3 = zip_hi(b2, b3);
    // [a0, a2, a4, a6, b0, b2, b4, b6, c0, c2, c4, c6, d0, d2, d4, d6 ]
    // [a1, a3, a5, a7, b1, b3, b5, b7, c1, c3, c5, c7, d1, d3, d5, d7 ]
    // [a8, a10,a12,a14,b8, b10,b12,b14,c8, c10,c12,c14,d8, d10,d12,d14]
    // [a9, a11,a13,a15,b9, b11,b13,b15,c9, c11,c13,c15,d9, d11,d13,d15]
    typename same_width<T>::b64 d0, d1, d2, d3;
    d0 = zip_lo(c0, c1);
    d1 = zip_hi(c0, c1);
    d2 = zip_lo(c2, c3);
    d3 = zip_hi(c2, c3);
    // [a0 .. a7, b0 .. b7 ]
    // [c0 .. c7, d0 .. d7 ]
    // [a8 .. a15, b8 .. b15 ]
    // [b8 .. b15, d8 .. d15 ]
    a = zip_lo(d0, d2);
    b = zip_hi(d0, d2);
    c = zip_lo(d1, d3);
    d = zip_hi(d1, d3);
#endif
}

template<class T> void mem_unpack4_impl16(T& a, T& b, T& c, T& d)
{
    // [a0,b0,c0,d0,a1,b1,c1,d1]
    // [a2,b2,c2,d2,a3,b3,c3,d3]
    // [a4,b4,c4,d4,a5,b5,c5,d5]
    // [a6,b6,c6,d6,a7,b7,c7,d7]
    typename same_width<T>::b16 t0, t1, t2, t3;
    t0 = zip_lo(a, b);
    t1 = zip_hi(a, b);
    t2 = zip_lo(c, d);
    t3 = zip_hi(c, d);
    // [a0,a2,b0,b2,c0,c2,d0,d2]
    // [a1,a3,b1,b3,c1,c3,d1,d3]
    // [a4,a6,b4,b6,c4,c6,d4,d6]
    // [a5,a7,b5,b7,c5,c7,d5,d7]
    typename same_width<T>::b64 u0, u1, u2, u3;
    u0 = zip_lo(t0, t1);
    u1 = zip_hi(t0, t1);
    u2 = zip_lo(t2, t3);
    u3 = zip_hi(t2, t3);
    // [a0,a1,a2,a3,b0,b1,b2,b3]
    // [c0,c1,c2,c3,d0,d1,d2,d3]
    // [a4,a5,a6,a7,b4,b5,b6,b7]
    // [c4,c5,c6,c7,d4,d5,d6,d7]
    a = zip_lo(u0, u2);
    b = zip_hi(u0, u2);
    c = zip_lo(u1, u3);
    d = zip_hi(u1, u3);
}

template<class T> void mem_unpack4_impl64(T& a, T& b, T& c, T& d)
{
    transpose2(a, c);
    transpose2(b, d);
    T t;
    t = b;
    b = c;
    c = t;
}
/// @}


template<class T>
void mem_unpack4_256_shuffle(T& a, T& b, T& c, T& d)
{
    // shuffle the vectors so that the lower halves contain the first 3 128-bit
    // items (a and lower half of b) and the higher halves contain the rest
    T t0, t1, t2, t3;
    t0 = a;  t1 = b;  t2 = c;  t3 = d;
    a = shuffle128<0,2>(t0, t2);
    b = shuffle128<1,3>(t0, t2);
    c = shuffle128<0,2>(t1, t3);
    d = shuffle128<1,3>(t1, t3);
}

/// @{
/** Concatenates @a a, @a b, @a c and @a d and stores the elements of the
    resulting array as follows:
     * every (4n)-th element is stored to @a a
     * every (4n+1)-th element is stored to @a b
     * every (4n+2)-th element is stored to @a c
     * every (4n+3)-th element is stored to @a d

    n = [0, <number of elements in vector> - 1]
*/
// @icost{SSE2, SSE3, 16}
// @icost{SSSE3, SSE4.1, 12}
inline void mem_unpack4(basic_int8x16& a, basic_int8x16& b,
                       basic_int8x16& c, basic_int8x16& d)
{
    mem_unpack4_impl8(a, b, c, d);
}

inline void mem_unpack4(basic_int8x32& a, basic_int8x32& b,
                       basic_int8x32& c, basic_int8x32& d)
{
    mem_unpack4_256_shuffle(a, b, c, d);
    mem_unpack4_impl8(a, b, c, d);
}

inline void mem_unpack4(basic_int16x8& a, basic_int16x8& b,
                       basic_int16x8& c, basic_int16x8& d)
{
    mem_unpack4_impl16(a, b, c, d);
}

inline void mem_unpack4(basic_int16x16& a, basic_int16x16& b,
                       basic_int16x16& c, basic_int16x16& d)
{
    mem_unpack4_256_shuffle(a, b, c, d);
    mem_unpack4_impl16(a, b, c, d);
}

inline void mem_unpack4(basic_int32x4& a, basic_int32x4& b,
                       basic_int32x4& c, basic_int32x4& d)
{
    transpose4(a, b, c, d);
}

inline void mem_unpack4(basic_int32x8& a, basic_int32x8& b,
                       basic_int32x8& c, basic_int32x8& d)
{
    mem_unpack4_256_shuffle(a, b, c, d);
    transpose4(a, b, c, d);
}

inline void mem_unpack4(basic_int64x2& a, basic_int64x2& b,
                       basic_int64x2& c, basic_int64x2& d)
{
    mem_unpack4_impl64(a, b, c, d);
}

inline void mem_unpack4(basic_int64x4& a, basic_int64x4& b,
                       basic_int64x4& c, basic_int64x4& d)
{
    mem_unpack4_256_shuffle(a, b, c, d);
    mem_unpack4_impl64(a, b, c, d);
}

inline void mem_unpack4(float32x4& a, float32x4& b, float32x4& c, float32x4& d)
{
    transpose4(a, b, c, d);
}

inline void mem_unpack4(float32x8& a, float32x8& b, float32x8& c, float32x8& d)
{
    mem_unpack4_256_shuffle(a, b, c, d);
    transpose4(a, b, c, d);
}

inline void mem_unpack4(float64x2& a, float64x2& b, float64x2& c, float64x2& d)
{
    mem_unpack4_impl64(a, b, c, d);
}

inline void mem_unpack4(float64x4& a, float64x4& b, float64x4& c, float64x4& d)
{
    mem_unpack4_256_shuffle(a, b, c, d);
    mem_unpack4_impl64(a, b, c, d);
}
/// @}

/// @{
/** Concatenates the given vectors and stores the elements of the resulting
    array as follows:
     * every (3n)-th element of the first 48 elements is stored to @a a
     * every (3n+1)-th element of the first 48 elements is stored to @a b
     * every (3n+2)-th element of the first 48 elements is stored to @a c
     * every (3n)-th element of the last 48 elements is stored to @a d
     * every (3n+1)-th element of the last 48 elements is stored to @a e
     * every (3n+2)-th element of the lasd 48 elements is stored to @a f

    n = [0, <number of elements in vector> - 1]
*/
inline void mem_unpack6(basic_int8x16& a, basic_int8x16& b, basic_int8x16& c,
                        basic_int8x16& d, basic_int8x16& e, basic_int8x16& f)
{
    basic_int8x16 t0, t1, t2, t3, t4, t5;
    t0 = zip_lo(a, d);
    t1 = zip_hi(a, d);
    t2 = zip_lo(b, e);
    t3 = zip_hi(b, e);
    t4 = zip_lo(c, f);
    t5 = zip_hi(c, f);

    basic_int8x16 u0, u1, u2, u3, u4, u5;
    u0 = zip_lo(t0, t3);
    u1 = zip_hi(t0, t3);
    u2 = zip_lo(t1, t4);
    u3 = zip_hi(t1, t4);
    u4 = zip_lo(t2, t5);
    u5 = zip_hi(t2, t5);

    t0 = zip_lo(u0, u3);
    t1 = zip_hi(u0, u3);
    t2 = zip_lo(u1, u4);
    t3 = zip_hi(u1, u4);
    t4 = zip_lo(u2, u5);
    t5 = zip_hi(u2, u5);

    u0 = zip_lo(t0, t3);
    u1 = zip_hi(t0, t3);
    u2 = zip_lo(t1, t4);
    u3 = zip_hi(t1, t4);
    u4 = zip_lo(t2, t5);
    u5 = zip_hi(t2, t5);

    t0 = zip_lo(u0, u3);
    t1 = zip_hi(u0, u3);
    t2 = zip_lo(u1, u4);
    t3 = zip_hi(u1, u4);
    t4 = zip_lo(u2, u5);
    t5 = zip_hi(u2, u5);

    a = zip_lo(t0, t3);
    b = zip_hi(t0, t3);
    c = zip_lo(t1, t4);
    d = zip_hi(t1, t4);
    e = zip_lo(t2, t5);
    f = zip_hi(t2, t5);
}

inline void mem_unpack6(basic_int16x8& a, basic_int16x8& b, basic_int16x8& c,
                       basic_int16x8& d, basic_int16x8& e, basic_int16x8& f)
{
    basic_int16x8 t0, t1, t2, t3, t4, t5;
    t0 = zip_lo(a, d);
    t1 = zip_hi(a, d);
    t2 = zip_lo(b, e);
    t3 = zip_hi(b, e);
    t4 = zip_lo(c, f);
    t5 = zip_hi(c, f);

    basic_int16x8 u0, u1, u2, u3, u4, u5;
    u0 = zip_lo(t0, t3);
    u1 = zip_hi(t0, t3);
    u2 = zip_lo(t1, t4);
    u3 = zip_hi(t1, t4);
    u4 = zip_lo(t2, t5);
    u5 = zip_hi(t2, t5);

    a = zip_lo(u0, u3);
    b = zip_hi(u0, u3);
    c = zip_lo(u1, u4);
    d = zip_hi(u1, u4);
    e = zip_lo(u2, u5);
    f = zip_hi(u2, u5);
}
/// @}

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

