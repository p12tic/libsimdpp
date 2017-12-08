/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_TEST_UTILS_TEST_HELPERS_H
#define LIBSIMDPP_TEST_UTILS_TEST_HELPERS_H

#include <simdpp/simd.h>
#include <simdpp/detail/align_v128.h>
#include <simdpp/detail/mem_block.h>
#include <iostream>
#include "test_results_set.h"
#include "test_reporter.h"
#include <cfenv>
#include <float.h>


inline void set_round_to_zero()
{
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996) // disable security warning
    _controlfp(_MCW_RC, _RC_CHOP);
#pragma warning(pop)
#else
    std::fesetround(FE_TOWARDZERO);
#endif
#if SIMDPP_USE_SSE2
    _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
#endif
}

inline void set_round_to_nearest()
{
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996) // disable security warning
    _controlfp(_MCW_RC, _RC_NEAR);
#pragma warning(pop)
#else
    std::fesetround(FE_TONEAREST);
#endif
#if SIMDPP_USE_SSE2
    _MM_SET_ROUNDING_MODE(_MM_ROUND_NEAREST);
#endif
}

inline void prevent_optimization_impl(const void* ptr)
{
    std::cout << ptr;
}

// Some compilers are really clever figuring out ways to access to data that
// would allow them to optimize things. Storing and reading a pointer from
// volatile location seems to work around this.
template<class T>
T* prevent_optimization(T* ptr)
{
    volatile bool never = false;
    if (never) {
        prevent_optimization_impl(ptr);
    }
    T* volatile* volatile opaque;
    opaque = &ptr;
    return *opaque;
}

namespace SIMDPP_ARCH_NAMESPACE {


/*  Certain compilers deduce that we perform tests on constant data and
    precompute the results. We want actual instructions to execute though. This
    class solves the issue by accessing the test data through a volatile
    pointer.
*/
template<class T>
class TestData {
public:

    TestData() {}

    TestData(const TestData& other)
    {
        data_ = other.data_;
    }

    TestData& operator=(const TestData& other)
    {
        data_ = other.data_;
    }

    template<class U>
    void add(const U& u)
    {
        T t = (T) u;
        data_.push_back(t);
    }

    void add(const TestData& other)
    {
        data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    }

    size_t size() const { return data_.size(); }

    const T& operator[](unsigned i) const
    {
        return *(prevent_optimization(&data_.front()) + i);
    }

private:
    std::vector<T, simdpp::aligned_allocator<T, sizeof(T)>> data_;
};


/*  A bunch of overloads that wrap the TestSuite::push() method. The push()
    method accepts a type enum plus a pointer; the wrapper overloads determine
    the type enum from the type of the supplied argument.
*/
inline void test_push_internal(TestResultsSet& t, std::int8_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_INT8, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::uint8_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_UINT8, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::int16_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_INT16, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::uint16_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_UINT16, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::int32_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_INT32, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::uint32_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_UINT32, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::int64_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_INT64, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, std::uint64_t data,
                               const char* file, unsigned line)
{
    t.push(TYPE_UINT64, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, float data,
                               const char* file, unsigned line)
{
    t.push(TYPE_FLOAT32, 1, file, line).set(0, &data);
}

inline void test_push_internal(TestResultsSet& t, double data,
                               const char* file, unsigned line)
{
    t.push(TYPE_FLOAT64, 1, file, line).set(0, &data);
}

template<class V>
void test_push_internal_vec(TestResultsSet::Result& res, const V& data)
{
    static_assert(sizeof(data) == V::length_bytes,
                  "Vector uses unsupported data layout");
    for (unsigned i = 0; i < data.vec_length; ++i) {
        using Base = typename V::base_vector_type;
        std::memcpy(res.data.data() + i * Base::length_bytes,
                    &data.vec(i), Base::length_bytes);
    }
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int8<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT8, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint8<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT8, N, file, line), data);
}
template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int16<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT16, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint16<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT16, N, file, line), data);
}
template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int32<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT32, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint32<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT32, N, file, line), data);
}
template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::int64<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_INT64, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::uint64<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_UINT64, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::float32<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_FLOAT32, N, file, line), data);
}

template<unsigned N>
void test_push_internal(TestResultsSet& t, const simdpp::float64<N>& data,
                        const char* file, unsigned line)
{
    test_push_internal_vec(t.push(TYPE_FLOAT64, N, file, line), data);
}

template<class V>
void test_push_stored(TestResultsSet& t, const typename V::element_type* data,
                      unsigned count, const char* file, unsigned line)
{
    ElementType type = GetElementType<V>::value;
    TestResultsSet::Result& res = t.push(type, count, file, line);
    std::memcpy(res.data.data(), data, count * sizeof(data[0]));
}

template<class V>
void print_vector_hex(std::ostream& out, const V& v)
{
    simdpp::detail::mem_block<V> block(v);
    print_vector_hex(out, GetElementType<V>::value, v.length, block.data());
}

template<class V>
void print_vector_numeric(std::ostream& out, const V& v)
{
    simdpp::detail::mem_block<V> block(v);
    print_vector_numeric(out, GetElementType<V>::value, v.length, block.data());
}

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
#define TEST_PUSH(TC,T,D)                                                       \
    { test_push_internal((TC), (T)(D), __FILE__, __LINE__); }

// The following macro is the same as TEST_PUSH, except that D is a pointer to
// data of COUNT vectors of type T stored to memory. D must be V::element_type.
#define TEST_PUSH_STORED(TC, T, D, COUNT)                                       \
{ test_push_stored<V>((TC), (D), COUNT, __FILE__, __LINE__); }

#define TEST_PUSH_ARRAY(TC, T, A)                                       \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < sizeof(A) / sizeof((A)[0]); i++) {                 \
        T l = (T) (A)[i];                                                       \
        TEST_PUSH(TC, T, l);                                                    \
    }                                                                   \
}

#define TEST_PUSH_ARRAY_OP1(TC, T, OP, A)                               \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        T l = (T) (A)[i];                                                       \
        TEST_PUSH(TC, T, OP(l));                                                \
    }                                                                   \
}

#define TEST_PUSH_ARRAY_OP1_T(TC, R, T, OP, A)                          \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        T l = (T) (A)[i];                                                       \
        TEST_PUSH(TC, R, OP(l));                                                \
    }                                                                   \
}

#define TEST_PUSH_ARRAY_OP2(TC, T, OP, A, B)                            \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        T l = (T) (A)[i];                                                       \
        T r = (T) (B)[i];                                                       \
        TEST_PUSH(TC, T, OP(l, r));                                             \
    }                                                                   \
}

// tests OP on all pairs of elements within array A
#define TEST_PUSH_ALL_COMB_OP1(TC, T, OP, A)                            \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        T l = (T) (A)[i];                                                       \
        for (unsigned rot = 0; rot < 128 / T::num_bits; rot++) {        \
            TEST_PUSH(TC, T, OP(l));                                    \
            l = simdpp::detail::align_v128<1>(l, l);                    \
        }                                                               \
    }                                                                   \
}

#define TEST_PUSH_ALL_COMB_OP1_T(TC, R, T, OP, A)                       \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        T l = (T) (A)[i];                                                       \
        for (unsigned rot = 0; rot < 128 / T::num_bits; rot++) {        \
            TEST_PUSH(TC, R, OP(l));                                    \
            l = simdpp::detail::align_v128<1>(l, l);                    \
        }                                                               \
    }                                                                   \
}

#define TEST_PUSH_ALL_COMB_OP2(TC, T, OP, A)                            \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        for (unsigned j = 0; j < (A).size(); j++) {                     \
            T l = (T) (A)[i];                                                   \
            T r = (T) (A)[j];                                                   \
            for (unsigned rot = 0; rot < 128 / T::num_bits; rot++) {    \
                TEST_PUSH(TC, T, OP(l, r));                             \
                l = simdpp::detail::align_v128<1>(l, l);                \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_PUSH_ALL_COMB_OP2_T(TC, R, T, OP, A)                       \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i = 0; i < (A).size(); i++) {                         \
        for (unsigned j = 0; j < (A).size(); j++) {                     \
            T l = (T) (A)[i];                                                   \
            T r = (T) (A)[j];                                                   \
            for (unsigned rot = 0; rot < 128 / T::num_bits; rot++) {    \
                TEST_PUSH(TC, R, OP(l, r));                             \
                l = simdpp::detail::align_v128<1>(l, l);                \
            }                                                           \
        }                                                               \
    }                                                                   \
}

#define TEST_PUSH_ALL_COMB_OP2_SEPARATE_T(TC, R, T1, T2, OP, A1, A2)            \
{                                                                               \
    (TC).reset_seq();                                                           \
    for (unsigned i = 0; i < (A1).size(); i++) {                                \
        for (unsigned j = 0; j < (A2).size(); j++) {                            \
            T1 l = (T1) (A1)[i];                                                \
            T2 r = (T2) (A2)[j];                                                \
            for (unsigned rot = 0; rot < 128 / T1::num_bits; rot++) {           \
                TEST_PUSH(TC, R, OP(l, r));                                     \
                l = simdpp::detail::align_v128<1>(l, l);                        \
            }                                                                   \
        }                                                                       \
    }                                                                           \
}

#define TEST_EQUAL_ALL_COMB_OP2_EXPLICIT(TR, T, OP1, OP2, A)                    \
{                                                                               \
    for (unsigned i = 0; i < (A).size(); i++) {                                 \
        for (unsigned j = 0; j < (A).size(); j++) {                             \
            T ARG1 = (T) (A)[i];                                                \
            T ARG2 = (T) (A)[j];                                                \
            for (unsigned rot = 0; rot < 128 / T::num_bits; rot++) {            \
                TEST_EQUAL(TR, (OP1), (OP2));                                   \
                ARG1 = simdpp::detail::align_v128<1>(ARG1, ARG1);               \
            }                                                                   \
        }                                                                       \
    }                                                                           \
}

#define TEST_PUSH_ALL_COMB_OP3(TC, T, OP, A)                            \
{                                                                       \
    (TC).reset_seq();                                                   \
    for (unsigned i0 = 0; i0 < (A).size(); i0++) {                      \
    for (unsigned i1 = 0; i1 < (A).size(); i1++) {                      \
    for (unsigned i2 = 0; i2 < (A).size(); i2++) {                      \
        T v0 = (T) (A)[i0];                                                     \
        T v1 = (T) (A)[i1];                                                     \
        T v2 = (T) (A)[i2];                                                     \
        for (unsigned rot0 = 0; rot0 < 128 / T::num_bits; rot0++) {     \
            for (unsigned rot1 = 0; rot1 < 128 / T::num_bits; rot1++) { \
                TEST_PUSH(TC, T, OP(v0, v1, v2));                       \
                v0 = simdpp::detail::align_v128<1>(v0, v0);             \
            }                                                           \
            v1 = simdpp::detail::align_v128<1>(v1, v1);                 \
        }                                                               \
    }}}                                                                 \
}


// Implements TemplateTestHelper functionality. Template recursion is optimized
// by potentially putting a large number of test template instantiations into a
// single instantiation of TemplateTestHelperImpl.
enum {
    TemplateTestHelperImpl_InstBatchSize = 30
};

template<template<class, unsigned> class F,
         class V, bool large, unsigned i, unsigned limit>
struct TemplateTestHelperImpl;

template<template<class, unsigned> class F,
         class V, unsigned i, unsigned limit>
struct TemplateTestHelperImpl<F, V, false, i, limit> {

    static void run(TestResultsSet& tc, const V& a)
    {
        F<V, i>::test(tc, a);
        const unsigned batch_size = TemplateTestHelperImpl_InstBatchSize;
        const bool is_large = i + batch_size < limit;
        TemplateTestHelperImpl<F, V, is_large, i+1, limit>::run(tc, a);
    }

    static void run(TestResultsSet& tc, const V& a, const V& b)
    {
        F<V, i>::test(tc, a, b);
        const unsigned batch_size = TemplateTestHelperImpl_InstBatchSize;
        const bool is_large = i + batch_size < limit;
        TemplateTestHelperImpl<F, V, is_large, i+1, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V, unsigned i, unsigned limit>
struct TemplateTestHelperImpl<F, V, true, i, limit> {

    static void run(TestResultsSet& tc, const V& a)
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
        const unsigned batch_size = TemplateTestHelperImpl_InstBatchSize;
        const bool is_large = i + batch_size*2 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+batch_size, limit>::run(tc, a);
    }

    static void run(TestResultsSet& tc, const V& a, const V& b)
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
        const unsigned batch_size = TemplateTestHelperImpl_InstBatchSize;
        const bool is_large = i + batch_size*2 < limit;
        TemplateTestHelperImpl<F, V, is_large, i+batch_size, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V, unsigned i>
struct TemplateTestHelperImpl<F, V, true, i, i> {
    static void run(TestResultsSet&, const V&) {}
    static void run(TestResultsSet&, const V&, const V&) {}
};

template<template<class, unsigned> class F, class V, unsigned i>
struct TemplateTestHelperImpl<F, V, false, i, i> {
    static void run(TestResultsSet&, const V&) {}
    static void run(TestResultsSet&, const V&, const V&) {}
};

/**
    Used to test functions that depend on a template parameter. Essentially
    implements a for loop realised in templates.

    The template calls F<V, i>::test(tc, a) for each i from 0 to F<V, 0>::limit.
*/
template<template<class, unsigned> class F, class V>
struct TemplateTestHelper {
    static void run(TestResultsSet& tc, const V& a)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, a);
    }

    static void run(TestResultsSet& tc, const V& a, const V& b)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, a, b);
    }
};

template<template<class, unsigned> class F, class V>
struct TemplateTestArrayHelper {
    static void run(TestResultsSet& tc, V* a, unsigned n)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        for (unsigned i = 0; i < n; i++) {
            TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, *(a+i));
        }
    }

    static void run(TestResultsSet& tc, V* a, V* b, unsigned n)
    {
        const unsigned limit = F<V,0>::limit;

        tc.reset_seq();
        for (unsigned i = 0; i < n; i++) {
            TemplateTestHelperImpl<F, V, false, 0, limit>::run(tc, *(a+i), *(b+i));
        }
    }
};

template<class E>
void test_cmp_memory(TestReporter& tr, const E* e1, const E* e2, unsigned count,
                     bool expected_equal, unsigned line, const char* file)
{
    if (count == 0) {
        tr.add_result(true);
        return;
    }

    int memcmp_result = std::memcmp(e1, e2, sizeof(E) * count);
    bool success = expected_equal ? memcmp_result == 0 : memcmp_result != 0;
    tr.add_result(success);

    if (!success) {
        print_separator(tr.out());
        print_file_info(tr.out(), file, line);
        tr.out() << (expected_equal ? "Memory not equal:\n"
                                    : "Memory equal:\n");
        print_data_diff(tr.out(), GetElementType<E>::value, count, e1, e2);
    }
}

template<class V1, class V2>
void test_cmp_equal_impl(std::true_type /*is_V1_vector*/, TestReporter& tr,
                         const V1& q1, const V2& q2,
                         bool expected_equal, unsigned line, const char* file)
{
    using V = typename simdpp::detail::get_expr_nomask<V1>::type;
    V v1, v2;
    v1 = q1.eval(); v2 = q2.eval();

    int memcmp_result = std::memcmp(&v1, &v2, V::length_bytes);
    bool success = expected_equal ? memcmp_result == 0 : memcmp_result != 0;
    tr.add_result(success);

    if (!success) {
        print_separator(tr.out());
        print_file_info(tr.out(), file, line);
        tr.out() << (expected_equal ? "Vectors not equal:\n" : "Vectors equal:\n");
        print_data_diff(tr.out(), GetElementType<V>::value, V::length, &v1, &v2);
    }
}

template<class T1, class T2>
void test_cmp_equal_impl(std::false_type /*is_T1_vector*/, TestReporter& tr,
                         const T1& a1, const T2& a2,
                         bool expected_equal, unsigned line, const char* file)
{
    static_assert(sizeof(T1) == sizeof(T2), "Data type sizes must be equal");
    bool success = expected_equal ? std::memcmp(&a1, &a2, sizeof(a1)) == 0 :
                                    std::memcmp(&a1, &a2, sizeof(a1)) != 0;
    tr.add_result(success);

    if (!success) {
        print_separator(tr.out());
        print_file_info(tr.out(), file, line);
        tr.out() << (expected_equal ? "Data not equal:\n" : "Data equal:\n");
        print_data_diff(tr.out(), GetElementType<T1>::value, 1, &a1, &a2);
    }
}

template<class T1, class T2>
void test_cmp_equal(TestReporter& tr, const T1& a1, const T2& a2,
                    bool expected_equal, unsigned line, const char* file)
{
    static_assert(simdpp::is_vector<T1>::value == simdpp::is_vector<T2>::value,
                  "Invalid types for comparison");
    test_cmp_equal_impl(simdpp::is_vector<T1>(), tr, a1, a2, expected_equal,
                        line, file);
}

#define TEST_EQUAL(TR, V1, V2)                                                  \
    do { test_cmp_equal(TR, V1, V2, true, __LINE__, __FILE__); } while(0)

#define TEST_NOT_EQUAL(TR, V1, V2)                                              \
    do { test_cmp_equal(TR, V1, V2, false, __LINE__, __FILE__); } while(0)

#define TEST_EQUAL_MEMORY(TR, E1, E2, COUNT)                                    \
    do { test_cmp_memory((TR), (E1), (E2), (COUNT), true, __LINE__, __FILE__); } while(0)

#define TEST_NOT_EQUAL_MEMORY(TR, E1, E2, COUNT)                                \
    do { test_cmp_memory((TR), (E1), (E2), (COUNT), false, __LINE__, __FILE__); } while(0)

#endif
