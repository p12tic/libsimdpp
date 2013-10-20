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

#ifndef LIBSIMDPP_TEST_TEST_HELPERS_H
#define LIBSIMDPP_TEST_TEST_HELPERS_H

#include <simdpp/simd.h>
#include "test_case.h"
#include "traits.h"

namespace SIMDPP_ARCH_NAMESPACE {

/*  A bunch of overloads that wrap the TestCase::push() method. The push()
    method accepts a type enum plus a pointer; the wrapper overloads determine
    the type enum from the type of the supplied argument.
    @{
*/
inline void test_push_internal(TestCase& t, std::uint16_t data, unsigned line)
{
    t.push(TestCase::TYPE_UINT16, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int8x16 data, unsigned line)
{
    t.push(TestCase::TYPE_INT8x16, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint8x16 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT8x16, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int16x8 data, unsigned line)
{
    t.push(TestCase::TYPE_INT16x8, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint16x8 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT16x8, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int32x4 data, unsigned line)
{
    t.push(TestCase::TYPE_INT32x4, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint32x4 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT32x4, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int64x2 data, unsigned line)
{
    t.push(TestCase::TYPE_INT64x2, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint64x2 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT64x2, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::float32x4 data, unsigned line)
{
    t.push(TestCase::TYPE_FLOAT32x4, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::float64x2 data, unsigned line)
{
    t.push(TestCase::TYPE_FLOAT64x2, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int8x32 data, unsigned line)
{
    t.push(TestCase::TYPE_INT8x32, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint8x32 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT8x32, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int16x16 data, unsigned line)
{
    t.push(TestCase::TYPE_INT16x16, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint16x16 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT16x16, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int32x8 data, unsigned line)
{
    t.push(TestCase::TYPE_INT32x8, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint32x8 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT32x8, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::int64x4 data, unsigned line)
{
    t.push(TestCase::TYPE_INT64x4, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::uint64x4 data, unsigned line)
{
    t.push(TestCase::TYPE_UINT64x4, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::float32x8 data, unsigned line)
{
    t.push(TestCase::TYPE_FLOAT32x8, &data, line);
}

inline void test_push_internal(TestCase& t, simdpp::float64x4 data, unsigned line)
{
    t.push(TestCase::TYPE_FLOAT64x4, &data, line);
}
// @}

/* Extracts the lower half of a vector.
    @{
*/
template<class R, class T>
inline R tst_ext_half_avx_impl(T x)
{
#ifdef SIMDPP_USE_AVX
    return simdpp::sse::extract_lo(x);
#else
    return x[0];
#endif
}

template<class R, class T>
inline R tst_ext_half_avx2_impl(T x)
{
#ifdef SIMDPP_USE_AVX2
    return simdpp::sse::extract_lo(x);
#else
    return x[0];
#endif
}

inline simdpp::basic_int8x16 tst_ext_half(simdpp::basic_int8x32 x)
{
    return tst_ext_half_avx2_impl<simdpp::basic_int8x16>(x);
}
inline simdpp::int8x16 tst_ext_half(simdpp::int8x32 x)
{
    return tst_ext_half_avx2_impl<simdpp::int8x16>(x);
}
inline simdpp::uint8x16 tst_ext_half(simdpp::uint8x32 x)
{
    return tst_ext_half_avx2_impl<simdpp::uint8x16>(x);
}

inline simdpp::basic_int16x8 tst_ext_half(simdpp::basic_int16x16 x)
{
    return tst_ext_half_avx2_impl<simdpp::basic_int16x8>(x);
}
inline simdpp::int16x8 tst_ext_half(simdpp::int16x16 x)
{
    return tst_ext_half_avx2_impl<simdpp::int16x8>(x);
}
inline simdpp::uint16x8 tst_ext_half(simdpp::uint16x16 x)
{
    return tst_ext_half_avx2_impl<simdpp::uint16x8>(x);
}

inline simdpp::basic_int32x4 tst_ext_half(simdpp::basic_int32x8 x)
{
    return tst_ext_half_avx2_impl<simdpp::basic_int32x4>(x);
}
inline simdpp::int32x4 tst_ext_half(simdpp::int32x8 x)
{
    return tst_ext_half_avx2_impl<simdpp::int32x4>(x);
}
inline simdpp::uint32x4 tst_ext_half(simdpp::uint32x8 x)
{
    return tst_ext_half_avx2_impl<simdpp::uint32x4>(x);
}

inline simdpp::basic_int64x2 tst_ext_half(simdpp::basic_int64x4 x)
{
    return tst_ext_half_avx2_impl<simdpp::basic_int64x2>(x);
}
inline simdpp::int64x2 tst_ext_half(simdpp::int64x4 x)
{
    return tst_ext_half_avx2_impl<simdpp::int64x2>(x);
}
inline simdpp::uint64x2 tst_ext_half(simdpp::uint64x4 x)
{
    return tst_ext_half_avx2_impl<simdpp::uint64x2>(x);
}

inline simdpp::float32x4 tst_ext_half(simdpp::float32x8 x)
{
    return tst_ext_half_avx_impl<simdpp::float32x4>(x);
}

inline simdpp::float64x2 tst_ext_half(simdpp::float64x4 x)
{
    return tst_ext_half_avx_impl<simdpp::float64x2>(x);
}
// @}

} // namespace SIMDPP_ARCH_NAMESPACE

// we are supposed to call this from within the test function which is in
// SIMDPP_ARCH_NAMESPACE namespace

/*
    T - type
    D - an object of type T to push
    A - array of objects to push
    O1, Q2 - arguments to apply OP to
    OP - operation to apply to the array or arguments
    R - type to cast the object to be pushed to
*/
#define TEST_PUSH(TC,T,D)   { test_push_internal((TC), (T)(D), __LINE__); }

// applies the same operation to 32-byte and 16-byte vectors
// Single argument version
#define TEST_PUSH16X2_1(TC,T,OP,Q1)                                     \
{                                                                       \
    test_push_internal((TC), (T)(OP)((Q1)), __LINE__);                  \
    using H = typename traits<T>::half_vector_type;                     \
    test_push_internal((TC), (H)((OP)(tst_ext_half((Q1)))), __LINE__);  \
}

// Two argument version
#define TEST_PUSH16X2_2(TC,T,OP,Q1,Q2)                                  \
{                                                                       \
    test_push_internal((TC), (T)(OP)((Q1), (Q2)), __LINE__);            \
    using H = typename traits<T>::half_vector_type;                     \
    test_push_internal((TC), (H)((OP)(tst_ext_half((Q1)),               \
                                      tst_ext_half((Q2)))), __LINE__);  \
}

#define NEW_TEST_CASE(R, NAME) ((R).new_test_case((NAME), __FILE__))

#define TEST_ARRAY_PUSH(TC, T, A)                                       \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        TEST_PUSH(TC, T, *lp);                                          \
    }                                                                   \
}

#define TEST_ARRAY_HELPER1(TC, T, OP, A)                                \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        TEST_PUSH(TC, T, OP(*lp));                                      \
    }                                                                   \
}

#define TEST_ARRAY_HELPER1_T(TC, R, T, OP, A)                           \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        TEST_PUSH(TC, R, OP(*lp));                                      \
    }                                                                   \
}

#define TEST_ARRAY_HELPER2(TC, T, OP, A, B)                             \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        const T* rp = reinterpret_cast<const T*>((B) + i);              \
        TEST_PUSH(TC, T, OP(*lp, *rp));                                 \
    }                                                                   \
}

#define TEST_ARRAY_HELPER16X2_1(TC, T, OP, A)                           \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        TEST_PUSH16X2_1(TC, T, OP, *lp);                                \
    }                                                                   \
}

#define TEST_ARRAY_HELPER16X2_1T(TC, R, T, OP, A)                       \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        TEST_PUSH16X2_1(TC, R, OP, *lp);                                \
    }                                                                   \
}

#define TEST_ARRAY_HELPER16X2_2(TC, T, OP, A, B)                        \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        const T* lp = reinterpret_cast<const T*>((A) + i);              \
        const T* rp = reinterpret_cast<const T*>((B) + i);              \
        TEST_PUSH16X2_2(TC, T, OP, *lp, *rp);                           \
    }                                                                   \
}

// tests OP on all pairs of elements within array A
#define TEST_ALL_COMB_HELPER(TC, T, OP, A, EL_SIZE)                     \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        for (unsigned j = 0; j < sizeof(A) / sizeof(T); j++) {          \
            const T* lp = reinterpret_cast<const T*>((A) + i);          \
            const T* rp = reinterpret_cast<const T*>((A) + j);          \
            T l = *lp; T r = *rp;                                       \
            for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {    \
                TEST_PUSH(TC, T, OP(l, r));                             \
                l = simdpp::align<1>(l, l);                             \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER_T(TC, R, T, OP, A, EL_SIZE)                \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        for (unsigned j = 0; j < sizeof(A) / sizeof(T); j++) {          \
            const T* lp = reinterpret_cast<const T*>((A) + i);          \
            const T* rp = reinterpret_cast<const T*>((A) + j);          \
            T l = *lp; T r = *rp;                                       \
            for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {    \
                TEST_PUSH(TC, R, OP(l, r));                             \
                l = simdpp::align<1>(l, l);                             \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER16X2_2(TC, T, OP, A, EL_SIZE)               \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        for (unsigned j = 0; j < sizeof(A) / sizeof(T); j++) {          \
            const T* lp = reinterpret_cast<const T*>((A) + i);          \
            const T* rp = reinterpret_cast<const T*>((A) + j);          \
            T l = *lp; T r = *rp;                                       \
            for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {    \
                TEST_PUSH16X2_2(TC, T, OP, l, r);                       \
                l = simdpp::align<1>(l, l);                             \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_ALL_COMB_HELPER16X2_2T(TC, R, T, OP, A, EL_SIZE)           \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof(T); i++) {              \
        for (unsigned j = 0; j < sizeof(A) / sizeof(T); j++) {          \
            const T* lp = reinterpret_cast<const T*>((A) + i);          \
            const T* rp = reinterpret_cast<const T*>((A) + j);          \
            T l = *lp; T r = *rp;                                       \
            for (unsigned rot = 0; rot < sizeof(T)/EL_SIZE; rot++) {    \
                TEST_PUSH16X2_2(TC, R, OP, l, r);                       \
                l = simdpp::align<1>(l, l);                             \
            }                                                           \
        }                                                               \
    }                                                                   \
}

/**
    Used to test functions that depend on a template parameter. Essentially
    implements a for loop realised in templates.

    The template calls F<V, i>::test(tc, a) for each i from 0 to F<V, 0>::limit.
*/
template<template<class, unsigned> class F, class V, bool large, unsigned i, unsigned limit>
struct TemplateTestHelperImpl;

template<template<class, unsigned> class F, class V, unsigned i, unsigned limit>
struct TemplateTestHelperImpl<F, V, false, i, limit> {

    static void run(TestCase& tc, V a)
    {
        F<V, i>::test(tc, a);
        const bool is_large = i + 30 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+1, limit>::run(tc, a);
    }

    static void run(TestCase& tc, V a, V b)
    {
        F<V, i>::test(tc, a, b);
        const bool is_large = i + 30 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+1, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V, unsigned i, unsigned limit>
struct TemplateTestHelperImpl<F, V, true, i, limit> {

    static void run(TestCase& tc, V a)
    {
        F<V, i>::test(tc, a);
        F<V, i+1>::test(tc, a);
        F<V, i+2>::test(tc, a);
        F<V, i+3>::test(tc, a);
        F<V, i+4>::test(tc, a);
        F<V, i+5>::test(tc, a);
        F<V, i+6>::test(tc, a);
        F<V, i+7>::test(tc, a);
        F<V, i+8>::test(tc, a);
        F<V, i+9>::test(tc, a);
        F<V, i+10>::test(tc, a);
        F<V, i+11>::test(tc, a);
        F<V, i+12>::test(tc, a);
        F<V, i+13>::test(tc, a);
        F<V, i+14>::test(tc, a);
        F<V, i+15>::test(tc, a);
        F<V, i+16>::test(tc, a);
        F<V, i+17>::test(tc, a);
        F<V, i+18>::test(tc, a);
        F<V, i+19>::test(tc, a);
        F<V, i+20>::test(tc, a);
        F<V, i+20>::test(tc, a);
        F<V, i+21>::test(tc, a);
        F<V, i+22>::test(tc, a);
        F<V, i+23>::test(tc, a);
        F<V, i+24>::test(tc, a);
        F<V, i+25>::test(tc, a);
        F<V, i+26>::test(tc, a);
        F<V, i+27>::test(tc, a);
        F<V, i+28>::test(tc, a);
        F<V, i+29>::test(tc, a);
        const bool is_large = i + 60 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+30, limit>::run(tc, a);
    }

    static void run(TestCase& tc, V a, V b)
    {
        F<V, i>::test(tc, a, b);
        F<V, i+1>::test(tc, a, b);
        F<V, i+2>::test(tc, a, b);
        F<V, i+3>::test(tc, a, b);
        F<V, i+4>::test(tc, a, b);
        F<V, i+5>::test(tc, a, b);
        F<V, i+6>::test(tc, a, b);
        F<V, i+7>::test(tc, a, b);
        F<V, i+8>::test(tc, a, b);
        F<V, i+9>::test(tc, a, b);
        F<V, i+10>::test(tc, a, b);
        F<V, i+11>::test(tc, a, b);
        F<V, i+12>::test(tc, a, b);
        F<V, i+13>::test(tc, a, b);
        F<V, i+14>::test(tc, a, b);
        F<V, i+15>::test(tc, a, b);
        F<V, i+16>::test(tc, a, b);
        F<V, i+17>::test(tc, a, b);
        F<V, i+18>::test(tc, a, b);
        F<V, i+19>::test(tc, a, b);
        F<V, i+20>::test(tc, a, b);
        F<V, i+20>::test(tc, a, b);
        F<V, i+21>::test(tc, a, b);
        F<V, i+22>::test(tc, a, b);
        F<V, i+23>::test(tc, a, b);
        F<V, i+24>::test(tc, a, b);
        F<V, i+25>::test(tc, a, b);
        F<V, i+26>::test(tc, a, b);
        F<V, i+27>::test(tc, a, b);
        F<V, i+28>::test(tc, a, b);
        F<V, i+29>::test(tc, a, b);
        const bool is_large = i + 60 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+30, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V, unsigned i>
struct TemplateTestHelperImpl<F, V, true, i, i> {
    static void run(TestCase, V) {}
    static void run(TestCase, V, V) {}
};

template<template<class, unsigned> class F, class V, unsigned i>
struct TemplateTestHelperImpl<F, V, false, i, i> {
    static void run(TestCase, V) {}
    static void run(TestCase, V, V) {}
};

template<template<class, unsigned> class F, class V>
struct TemplateTestHelper {
    static void run(TestCase& tc, V a)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, a);
    }

    static void run(TestCase& tc, V a, V b)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V>
struct TemplateTestArrayHelper {
    static void run(TestCase& tc, V* a, unsigned n)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        for (unsigned i = 0; i < n; i++) {
            TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, *(a+i));
        }
    }

    static void run(TestCase& tc, V* a, V* b, unsigned n)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        for (unsigned i = 0; i < n; i++) {
            TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, *(a+i), *(b+i));
        }
    }
};

#endif
