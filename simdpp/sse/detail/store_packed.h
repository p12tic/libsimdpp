/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SSE_DETAIL_STORE_PACKED_H
#define LIBSIMDPP_SSE_DETAIL_STORE_PACKED_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>
#include <simdpp/simd/shuffle.h>
#include <simdpp/simd/math_shift.h>
#include <simdpp/simd/transpose.h>
#include <simdpp/simd/detail/width.h>
#include <simdpp/sse/detail/shuffle128.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN
namespace sse {
namespace detail {

template<class T>
inline void st_pack2_impl(T& a, T& b)
{
    T c1, c2;
    c1 = a;
    c2 = b;
    a = zip_lo(c1, c2);
    b = zip_hi(c1, c2);
}

template<class T>
inline void st_pack2_256_impl(T& a, T& b)
{
    T c1, c2;
    c1 = zip_lo(a, b);
    c2 = zip_hi(a, b);
    a = shuffle128<0,0>(c1, c2);
    b = shuffle128<1,1>(c1, c2);
}

/// @{
/** Interleaves the elements of @a a and @a b in such way that:
     * every (2n)-th element comes from @a a
     * every (2n+1)-th element comes from @a b

    n = [0, <number of elements in vector> - 1]
*/
inline void st_pack2(basic_int8x16& a, basic_int8x16& b) { st_pack2_impl(a, b); }
inline void st_pack2(basic_int16x8& a, basic_int16x8& b) { st_pack2_impl(a, b); }
inline void st_pack2(basic_int32x4& a, basic_int32x4& b) { st_pack2_impl(a, b); }
inline void st_pack2(basic_int64x2& a, basic_int64x2& b) { st_pack2_impl(a, b); }
inline void st_pack2(float32x4& a, float32x4& b)         { st_pack2_impl(a, b); }
inline void st_pack2(float64x2& a, float64x2& b)         { st_pack2_impl(a, b); }

inline void st_pack2(basic_int8x32& a, basic_int8x32& b) { st_pack2_256_impl(a, b); }
inline void st_pack2(basic_int16x16& a, basic_int16x16& b){st_pack2_256_impl(a, b); }
inline void st_pack2(basic_int32x8& a, basic_int32x8& b) { st_pack2_256_impl(a, b); }
inline void st_pack2(basic_int64x4& a, basic_int64x4& b) { st_pack2_256_impl(a, b); }
inline void st_pack2(float32x8& a, float32x8& b)         { st_pack2_256_impl(a, b); }
inline void st_pack2(float64x4& a, float64x4& b)         { st_pack2_256_impl(a, b); }
/// @}

#if SIMDPP_USE_SSSE3
inline basic_int8x16 shuffle_epi8_wrapper(basic_int8x16 x, basic_int8x16 idx)
{
    return _mm_shuffle_epi8(x, idx);
}

inline basic_int8x32 shuffle_epi8_wrapper(basic_int8x32 x, basic_int8x32 idx)
{
#if SIMDPP_USE_AVX2
    return _mm256_shuffle_epi8(x, idx);
#else
    return {_mm_shuffle_epi8(x[0], idx[0]), _mm_shuffle_epi8(x[1], idx[1])};
#endif
}
#endif

/// @{
/** Generic implementation of st_pack3. The 256-bit version applies 128-bit
    operations to each half of each vector separately.
*/
template<class T> void st_pack3_impl8(T& a, T& b, T& c)
{
    // either basic_int16x8 or basic_int16x16, other entries likewise
    using w_b16 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b16;
    using w_b32 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b32;
    using w_u8 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::u8;
    using w_b8 = T;

    w_b16 t0, t1, t2, t3;
    t0 = zip_lo(a, b);
    t1 = zip_hi(a, b);
    t2 = zip_lo(c, w_b8::zero());
    t3 = zip_hi(c, w_b8::zero());

    w_b8 u0, u1, u2, u3;
    u0 = zip_lo(t0, t2);
    u1 = zip_hi(t0, t2);
    u2 = zip_lo(t1, t3);
    u3 = zip_hi(t1, t3);

    // [a0, b0, c0, 0, a1, b1, c1, 0, a2, b2, c2, 0, a3, b3, c3, 0]
    // [a4, b4, c4, 0, a5, b5, c5, 0, a6, b6, c6, 0, a7, b7, c7, 0]
    // [a8, b8, c8, 0, a9, b9, c9, 0, a10,b10,c10,0, a11,b11,c11,0]
    // [a12,b12,c12,0, a13,b13,c13,0, a14,b14,c14,0, a15,b15,c15,0]
#if SIMDPP_USE_SSSE3
    // it's not worth to use 4 different index vectors to shuffle the vectors
    // properly and use only bit_or later
    w_b8 idx = w_u8::make_const(0,   1,  2,  4,    5,    6,    8,    9,
                               10, 12, 13, 14, 0xff, 0xff, 0xff, 0xff);
    u0 = shuffle_epi8_wrapper(u0, idx);
    u1 = shuffle_epi8_wrapper(u1, idx);
    u2 = shuffle_epi8_wrapper(u2, idx);
    u3 = shuffle_epi8_wrapper(u3, idx);
#else
    using w_u64 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::u64;

    // the following is still faster than non-SIMD implementation
    w_b8 mask1 = w_u8::make_const(0xff, 0xff, 0xff, 0, 0, 0, 0, 0,
                                  0xff, 0xff, 0xff, 0, 0, 0, 0, 0);
    w_u64 w0, w1, w2, w3;
    w0 = u0;  w1 = u1;  w2 = u2;  w3 = u3;
    w0 = shift_r(w0, 8);
    w1 = shift_r(w1, 8);
    w2 = shift_r(w2, 8);
    w3 = shift_r(w3, 8);

    u0 = bit_and(u0, mask1);
    u1 = bit_and(u1, mask1);
    u2 = bit_and(u2, mask1);
    u3 = bit_and(u3, mask1);

    w0 = bit_andnot(w0, mask1);
    w1 = bit_andnot(w1, mask1);
    w2 = bit_andnot(w2, mask1);
    w3 = bit_andnot(w3, mask1);

    u0 = bit_or(u0, w0);
    u1 = bit_or(u1, w1);
    u2 = bit_or(u2, w2);
    u3 = bit_or(u3, w3);

    w_b8 mask2 = w_u8::make_const(0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0);
    w_b8 x0, x1, x2, x3;
    x0 = move_l<2>(u0);
    x1 = move_l<2>(u1);
    x2 = move_l<2>(u2);
    x3 = move_l<2>(u3);

    u0 = bit_and(u0, mask2);
    u1 = bit_and(u1, mask2);
    u2 = bit_and(u2, mask2);
    u3 = bit_and(u3, mask2);

    x0 = bit_andnot(x0, mask2);
    x1 = bit_andnot(x1, mask2);
    x2 = bit_andnot(x2, mask2);
    x3 = bit_andnot(x3, mask2);

    u0 = bit_or(u0, x0);
    u1 = bit_or(u1, x1);
    u2 = bit_or(u2, x2);
    u3 = bit_or(u3, x3);
#endif
    // [a0, b0, c0, a1, b1, c1, a2, b2, c2, a3, b3, c3, 0,0,0,0]
    // [a4, b4, c4, a5, b5, c5, a6, b6, c6, a7, b7, c7, 0,0,0,0]
    // [a8, b8, c8, a9, b9, c9, a10,b10,c10,a11,b11,c11,0,0,0,0]
    // [a12,b12,c12,a13,b13,c13,a14,b14,c14,a15,b15,c15,0,0,0,0]
    w_b32 k0, k1, k2, k3, l0, l3;
    k0 = u0;
    k1 = u1;
    k2 = u2;
    k3 = u3;
    l0 = move_r<3>(k1);
    l3 = move_l<2>(k2);
    k3 = move_r<1>(k3);
    a = bit_or(k0, l0);
    b = shuffle2<1,2,0,1>(k1, k2);
    c = bit_or(k3, l3);
}

template<class T> void st_pack3_impl16(T& a, T& b, T& c)
{
    // either basic_int8x16 or basic_int8x32, other entries likewise
    using w_b16 = T;
    using w_b32 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b32;

    w_b32 t0, t1, t2, t3;
    t0 = zip_lo(a, b);
    t1 = zip_hi(a, b);
    t2 = zip_lo(c, w_b32::zero());
    t3 = zip_hi(c, w_b32::zero());

    w_b16 u0, u1, u2, u3;
    u0 = zip_lo(t0, t2);
    u1 = zip_hi(t0, t2);
    u2 = zip_lo(t1, t3);
    u3 = zip_hi(t1, t3);

    // [a0, b0, c0, 0, a1, b1, c1, 0 ]
    // [a2, b2, c2, 0, a3, b3, c3, 0 ]
    // [a4, b4, c4, 0, a5, b5, c5, 0 ]
    // [a6, b6, c6, 0, a7, b7, c7, 0 ]

#if SIMDPP_USE_SSSE3
    using w_b8 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b8;
    using w_u8 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::u8;

    // it's not worth to use 4 different index vectors to shuffle the vectors
    // properly and use only bit_or later
    w_b8 idx = w_u8::make_const(0,   1,  2,  3,    4,    5,    8,    9,
                                10, 11, 12, 13, 0xff, 0xff, 0xff, 0xff);
    u0 = shuffle_epi8_wrapper(u0, idx);
    u1 = shuffle_epi8_wrapper(u1, idx);
    u2 = shuffle_epi8_wrapper(u2, idx);
    u3 = shuffle_epi8_wrapper(u3, idx);

#else
    using w_u16 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::u16;

    // the following is still faster than non-SIMD implementation
    w_b16 mask2 = w_u16::make_const(0xffff, 0xffff, 0xffff, 0,
                                    0, 0, 0, 0);
    w_b16 x0, x1, x2, x3;
    x0 = move_l<1>(u0);
    x1 = move_l<1>(u1);
    x2 = move_l<1>(u2);
    x3 = move_l<1>(u3);

    u0 = bit_and(u0, mask2);
    u1 = bit_and(u1, mask2);
    u2 = bit_and(u2, mask2);
    u3 = bit_and(u3, mask2);

    x0 = bit_andnot(x0, mask2);
    x1 = bit_andnot(x1, mask2);
    x2 = bit_andnot(x2, mask2);
    x3 = bit_andnot(x3, mask2);

    u0 = bit_or(u0, x0);
    u1 = bit_or(u1, x1);
    u2 = bit_or(u2, x2);
    u3 = bit_or(u3, x3);
#endif
    // [a0, b0, c0, a1, b1, c1, 0, 0]
    // [a2, b2, c2, a3, b3, c3, 0, 0]
    // [a4, b4, c4, a5, b5, c5, 0, 0]
    // [a6, b6, c6, a7, b7, c7, 0, 0]
    w_b32 k0, k1, k2, k3, l0, l3;
    k0 = u0;
    k1 = u1;
    k2 = u2;
    k3 = u3;
    l0 = move_r<3>(k1);
    l3 = move_l<2>(k2);
    k3 = move_r<1>(k3);
    a = bit_or(k0, l0);
    b = shuffle2<1,2,0,1>(k1, k2);
    c = bit_or(k3, l3);
}

template<class T> void st_pack3_impl32(T& a, T& b, T& c)
{
    T t0, t1, t2;
    t0 = shuffle2<0,2,0,2>(a, b);
    t1 = shuffle2<0,2,1,3>(c, a);
    t2 = shuffle2<1,3,1,3>(b, c);
    // [a0,a2,b0,b2]
    // [c0,c2,a1,a3]
    // [b1,b3,c1,c3]
    t0 = permute<0,2,1,3>(t0);
    t1 = permute<0,2,1,3>(t1);
    t2 = permute<0,2,1,3>(t2);
    // [a0,b0,a2,b2]
    // [c0,a1,c2,a3]
    // [b1,c1,b3,c3]
    a = shuffle2<0,1,0,1>(t0, t1);
    b = shuffle2<0,1,2,3>(t2, t0);
    c = shuffle2<2,3,2,3>(t1, t2);
}

template<class T> void st_pack3_impl64(T& a, T& b, T& c)
{
    T d0, d1, d2;
    d0 = shuffle1<0,0>(a, b);
    d1 = shuffle1<0,1>(c, a);
    d2 = shuffle1<1,1>(b, c);
    a = d0;  b = d1;  c = d2;
}
/// @}

template<class T>
void st_pack3_256_shuffle(T& a, T& b, T& c)
{
    // shuffle the vectors with the lower halves containing the first 3 128-bit
    // items and the higher halves contain the rest
    T t0, t1, t2;
    t0 = a;  t1 = b;  t2 = c;
    a = shuffle128<0,0>(t0, t1);
    b = shuffle128<0,1>(t2, t0);
    c = shuffle128<1,1>(t1, t2);
}

/// @{
/** Interleaves the elements of @a a, @a b and @a c in such way that:
     * every (3n)-th element comes from @a a
     * every (3n+1)-th element comes from @a b
     * every (3n+2)-th element comes from @a c

    n = [0, <number of elements in vector> - 1]
*/
inline void st_pack3(basic_int8x16& a, basic_int8x16& b, basic_int8x16& c)
{
    st_pack3_impl8(a, b, c);
}
inline void st_pack3(basic_int8x32& a, basic_int8x32& b, basic_int8x32& c)
{
    st_pack3_impl8(a, b, c);
    st_pack3_256_shuffle(a, b, c);
}

inline void st_pack3(basic_int16x8& a, basic_int16x8& b, basic_int16x8& c)
{
    st_pack3_impl16(a, b, c);
}
inline void st_pack3(basic_int16x16& a, basic_int16x16& b, basic_int16x16& c)
{
    st_pack3_impl16(a, b, c);
    st_pack3_256_shuffle(a, b, c);
}

inline void st_pack3(basic_int32x4& a, basic_int32x4& b, basic_int32x4& c)
{
    st_pack3_impl32(a, b, c);
}
inline void st_pack3(basic_int32x8& a, basic_int32x8& b, basic_int32x8& c)
{
    st_pack3_impl32(a, b, c);
    st_pack3_256_shuffle(a, b, c);
}

inline void st_pack3(basic_int64x2& a, basic_int64x2& b, basic_int64x2& c)
{
    st_pack3_impl64(a, b, c);
}
inline void st_pack3(basic_int64x4& a, basic_int64x4& b, basic_int64x4& c)
{
    st_pack3_impl64(a, b, c);
    st_pack3_256_shuffle(a, b, c);
}

inline void st_pack3(float32x4& a, float32x4& b, float32x4& c)
{
    st_pack3_impl32(a, b, c);
}
inline void st_pack3(float32x8& a, float32x8& b, float32x8& c)
{
    st_pack3_impl32(a, b, c);
    st_pack3_256_shuffle(a, b, c);
}

inline void st_pack3(float64x2& a, float64x2& b, float64x2& c)
{
    st_pack3_impl64(a, b, c);
}
inline void st_pack3(float64x4& a, float64x4& b, float64x4& c)
{
    st_pack3_impl64(a, b, c);
    st_pack3_256_shuffle(a, b, c);
}
/// @}

/// @{
/** Generic implementation of st_pack4. The 256-bit version applies 128-bit
    operations to each half of each vector separately.
*/
template<class T> void st_pack4_impl8(T& a, T& b, T& c, T& d)
{
    // either basic_int16x8 or basic_int16x16, other entries likewise

#if SIMDPP_USE_SSSE3
    using w_b32 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b32;

    w_b32 b0, b1, b2, b3;
    b0 = a;  b1 = b;  b2 = c;  b3 = d;
    transpose4(b0, b1, b2, b3);
    a = b0;  b = b1;  c = b2;  d = b3;

    a = transpose_inplace(a);
    b = transpose_inplace(b);
    c = transpose_inplace(c);
    d = transpose_inplace(d);
#else
    using w_b8 = T;
    using w_b16 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b16;
    using w_b64 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b64;

    w_b8 e0, e1, e2, e3;
    w_b64 d0, d1, d2, d3;
    d0 = a;  d1 = b;  d2 = c;  d3 = d;
    e0 = zip_lo(d0, d2);
    e1 = zip_lo(d1, d3);
    e2 = zip_hi(d0, d2);
    e3 = zip_hi(d1, d3);
    // [a0 .. a7,  c0 .. c7  ]
    // [b0 .. b7,  d0 .. d7  ]
    // [a8 .. a15, c8 .. c15 ]
    // [b8 .. b15, d8 .. d15 ]
    w_b16 f0, f1, f2, f3;
    f0 = zip_lo(e0, e1);
    f1 = zip_hi(e0, e1);
    f2 = zip_lo(e2, e3);
    f3 = zip_hi(e2, e3);
    // [a0, b0, a1, b1, a2, b2, a3, b3, a4, b4, a5, b5, a6, b6, a7, b7 ]
    // [c0, d0, c1, d1, c2, d2, c3, d3, c4, d4, c5, d5, c6, d6, c7, d7 ]
    // [a8, b8, a9, b9, a10,b10,a11,b11,a12,b12,a13,b13,a14,b14,a15,b15]
    // [c8, d8, c9, d9, c10,d10,c11,d11,c12,d12,c13,d13,c14,d14,c15,d15]
    a = zip_lo(f0, f1);
    b = zip_hi(f0, f1);
    c = zip_lo(f2, f3);
    d = zip_hi(f2, f3);
#endif
}

template<class T> void st_pack4_impl16(T& a, T& b, T& c, T& d)
{
    using w_b16 = T;
    using w_b32 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b32;
    using w_b64 = typename ::simdpp::SIMDPP_ARCH_NAMESPACE::detail::same_width<T>::b64;

    w_b16 e0, e1, e2, e3;
    w_b64 d0, d1, d2, d3;
    d0 = a;  d1 = b;  d2 = c;  d3 = d;
    e0 = zip_lo(d0, d2);
    e1 = zip_lo(d1, d3);
    e2 = zip_hi(d0, d2);
    e3 = zip_hi(d1, d3);
    // [a0,a1,a2,a3,c0,c1,c2,c3]
    // [b0,b1,b2,b3,d0,d1,d2,d3]
    // [a4,a5,a6,a7,c4,c5,c6,c7]
    // [b4,b5,b6,b7,d4,d5,d6,d7]
    w_b32 f0, f1, f2, f3;
    f0 = zip_lo(e0, e1);
    f1 = zip_hi(e0, e1);
    f2 = zip_lo(e2, e3);
    f3 = zip_hi(e2, e3);
    // [a0,b0,a1,b1,a2,b2,a3,b3]
    // [c0,d0,c1,d1,c2,d2,c3,d3]
    // [a4,b4,a5,b5,a6,b6,a7,b7]
    // [c4,d4,c5,d5,c6,d6,c7,d7]
    a = zip_lo(f0, f1);
    b = zip_hi(f0, f1);
    c = zip_lo(f2, f3);
    d = zip_hi(f2, f3);
}

template<class T> void st_pack4_impl64(T& a, T& b, T& c, T& d)
{
    transpose2(a, b);
    transpose2(c, d);
    T t;
    t = b;
    b = c;
    c = t;
}

/// @}

template<class T>
void st_pack4_256_shuffle(T& a, T& b, T& c, T& d)
{
    // shuffle the vectors with the lower halves containing the first 4 128-bit
    // items and the higher halves contain the rest
    T t0, t1, t2, t3;
    t0 = a;  t1 = b;  t2 = c;  t3 = d;
    a = shuffle128<0,0>(t0, t1);
    b = shuffle128<0,0>(t2, t3);
    c = shuffle128<1,1>(t0, t1);
    d = shuffle128<1,1>(t2, t3);
}

/// @{
/** Interleaves the elements of @a a, @a b, @a c and @a d in such way that:
     * every (4n)-th element comes from @a a
     * every (4n+1)-th element comes from @a b
     * every (4n+2)-th element comes from @a c
     * every (4n+3)-th element comes from @a d

    n = [0, <number of elements in vector> - 1]
*/
inline void st_pack4(basic_int8x16& a, basic_int8x16& b,
                     basic_int8x16& c, basic_int8x16& d)
{
    st_pack4_impl8(a, b, c, d);
}
inline void st_pack4(basic_int8x32& a, basic_int8x32& b,
                     basic_int8x32& c, basic_int8x32& d)
{
    st_pack4_impl8(a, b, c, d);
    st_pack4_256_shuffle(a, b, c, d);
}

inline void st_pack4(basic_int16x8& a, basic_int16x8& b,
                     basic_int16x8& c, basic_int16x8& d)
{
    st_pack4_impl16(a, b, c, d);
}
inline void st_pack4(basic_int16x16& a, basic_int16x16& b,
                     basic_int16x16& c, basic_int16x16& d)
{
    st_pack4_impl16(a, b, c, d);
    st_pack4_256_shuffle(a, b, c, d);
}

inline void st_pack4(basic_int32x4& a, basic_int32x4& b,
                     basic_int32x4& c, basic_int32x4& d)
{
    transpose4(a, b, c, d);
}
inline void st_pack4(basic_int32x8& a, basic_int32x8& b,
                     basic_int32x8& c, basic_int32x8& d)
{
    transpose4(a, b, c, d);
    st_pack4_256_shuffle(a, b, c, d);
}

inline void st_pack4(basic_int64x2& a, basic_int64x2& b,
                     basic_int64x2& c, basic_int64x2& d)
{
    st_pack4_impl64(a, b, c, d);
}
inline void st_pack4(basic_int64x4& a, basic_int64x4& b,
                     basic_int64x4& c, basic_int64x4& d)
{
    st_pack4_impl64(a, b, c, d);
    st_pack4_256_shuffle(a, b, c, d);
}

inline void st_pack4(float32x4& a, float32x4& b, float32x4& c, float32x4& d)
{
    transpose4(a, b, c, d);
}
inline void st_pack4(float32x8& a, float32x8& b, float32x8& c, float32x8& d)
{
    transpose4(a, b, c, d);
    st_pack4_256_shuffle(a, b, c, d);
}

inline void st_pack4(float64x2& a, float64x2& b, float64x2& c, float64x2& d)
{
    st_pack4_impl64(a, b, c, d);
}
inline void st_pack4(float64x4& a, float64x4& b, float64x4& c, float64x4& d)
{
    st_pack4_impl64(a, b, c, d);
    st_pack4_256_shuffle(a, b, c, d);
}
/// @}

} // namespace detail
} // namespace sse
SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif

