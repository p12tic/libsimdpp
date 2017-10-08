/*  Copyright (C) 2011-2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_WORKAROUNDS_H
#define LIBSIMDPP_SIMDPP_DETAIL_WORKAROUNDS_H

// this file contains workarounds for common compiler problems

// the implementation of XOP's com instruction is buggy in clang 3.5 and 3.4.
// clang 3.3 doesn't support the corresponding intrinsic at all
#if defined(__clang__)
#define SIMDPP_WORKAROUND_XOP_COM 1
#endif

#if SIMDPP_USE_NEON64
#if (__GNUC__ == 4) && (__GNUC_MINOR__ <= 8) && !defined(__INTEL_COMPILER) && !defined(__clang__)
#define vreinterpretq_f64_u64(x) ((float64x2_t) (uint64x2_t) (x))
#define vreinterpretq_u64_f64(x) ((uint64x2_t) (float64x2_t) (x))
#endif

#if (__GNUC__ == 4) && (__GNUC_MINOR__ <= 9) && !defined(__INTEL_COMPILER) && !defined(__clang__)
#define vmul_f64(x, y) ((float64x1_t)( ((float64x1_t)(x)) * ((float64x1_t)(y)) ))
#endif
#endif

#if SIMDPP_USE_AVX512F
#if (__GNUC__ == 4) && !defined(__INTEL_COMPILER) && !defined(__clang__)
/*  See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70059.
    _mm512_inserti64x4(x, y, 0) and related intrinsics result in wrong code.
    _mm512_castsi256_si512 is not available in GCC 4.9, thus there's no way
    to convert between 256-bit and 512-bit vectors.
*/
#error "The first supported GCC version for AVX512F is 5.0"
#endif
#endif

#if SIMDPP_USE_AVX || SIMDPP_USE_AVX2
#if (__clang_major__ == 3) && (__clang_minor__ == 6)
/*  See https://llvm.org/bugs/show_bug.cgi?id=23441. Clang does not generate
    correct floating-point code for basic 256-bit floating-point operations,
    such as those resulting from _mm256_set_ps, _mm256_load_ps. Due to the
    nature of affected operations, the bug is almost impossible to work around
    reliably.
*/
#error AVX and AVX2 are not supported on clang 3.6 due to compiler bugs
#endif
#endif

#if SIMDPP_USE_AVX
#if (__GNUC__ == 4) && (__GNUC_MINOR__ == 4) && !defined(__INTEL_COMPILER) && !defined(__clang__)
/*  GCC emits "Error: operand size mismatch for `vmovq'" when compiling
    256-bit shuffling intrinsics. No workaround has been found yet
*/
#error AVX is not supported in GCC 4.4 due to compiler bugs
#endif
#endif

#if (__clang_major__ == 3) && (__clang_minor__ <= 4)
#define SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS 1
/*  Clang 3.4 and older may crash when the following intrinsics are used with
    arguments that are known at compile time: _mm256_sll_epi{16,32,64},
    _mm256_srl_epi{16,32,64}, _mm256_sra_epi{16,32}
*/
#endif

#if SIMDPP_USE_ALTIVEC
#if defined(__GNUC__) && (__GNUC__ < 6) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ && \
    !defined(__INTEL_COMPILER) && !defined(__clang__)
// Internal compiler errors or wrong behaviour on various SIMD memory operations
#error GCC 5.x and older not supported on PPC little-endian due to compiler bugs.
#endif
#endif

#if SIMDPP_USE_VSX_206
#if defined(__GNUC__) && (__GNUC__ < 6) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ && \
    !defined(__INTEL_COMPILER) && !defined(__clang__)
// Internal compiler errors or wrong behaviour on various SIMD memory operations
#error GCC 5.x and older not supported on VSX big-endian due to compiler bugs.
#endif
#endif

#if SIMDPP_USE_AVX512F && (__clang_major__ == 3)
// Clang does not have _MM_CMPINT_* definitions up to Clang 4.0.
#ifndef _MM_CMPINT_EQ
#define _MM_CMPINT_EQ 0
#endif
#ifndef _MM_CMPINT_LT
#define _MM_CMPINT_LT 1
#endif
#ifndef _MM_CMPINT_LE
#define _MM_CMPINT_LE 2
#endif
#ifndef _MM_CMPINT_FALSE
#define _MM_CMPINT_FALSE 3
#endif
#ifndef _MM_CMPINT_NEQ
#define _MM_CMPINT_NEQ 4
#endif
#ifndef _MM_CMPINT_NLT
#define _MM_CMPINT_NLT 5
#endif
#ifndef _MM_CMPINT_NLE
#define _MM_CMPINT_NLE 6
#endif
#ifndef _MM_CMPINT_TRUE
#define _MM_CMPINT_TRUE 7
#endif
#endif

#if SIMDPP_USE_AVX512BW
#if (__clang_major__ == 4) && (__clang_minor__ == 0)
// Internal compiler errors when trying to select wrong instruction for specific
// combination of shuffles. Not possible to work around as shuffle detection is
// quite clever.
#error Clang 4.0 is not supported on AVX512BW due to compiler bugs.
#endif
#endif

/*  Clang supports a native vector extension that defines operators between
    vector types. SSE types such as __m128 and __m128i are implemented on top
    of this extension, which causes code like this being possible:

__m128i a, b; a = a + b;

    Previously, all libsimdpp types had an implicit conversion operator to
    native vector type. For example, both uint8<16> and uint16<8> could be
    implicitly converted to __m128i. This leads to code like this being
    accepted on clang.

uint8<16> a;
uint16<8> b;
a = a + b;

    Here, both a and b are implicitly converted to __m128i values and they are
    added using an operator provided by the clang vector extension.
    Unexpectedly, the result is paddq instruction (64-bit integer addition).

    Because of this, the implicit native vector type conversion operators are
    deprecated and a native() method is provided as a replacement in libsimdpp
    vector types. This change only affects code that interacts with native
    intrinsics. Altivec/VSX and MSA are affected only slightly, because
    intrinsics of those instruction sets never accepted implicit conversions
    from libsimdpp types.
*/
#ifndef SIMDPP_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    #define SIMDPP_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES 1
#endif
#if SIMDPP_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    #define SIMDPP_IMPLICIT_CONVERSION_DEPRECATION_MSG                          \
        SIMDPP_DEPRECATED(                                                      \
            "Implicit conversion operators may lead to wrong code being "       \
            "accepted without a compile error on Clang. Use the native() "      \
            "method as a replacement.")
#endif

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<unsigned V> struct make_constexpr { static const unsigned value = V; };

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#if __GNUC__
#define SIMDPP_WORKAROUND_MAKE_CONSTEXPR(X) detail::make_constexpr<(X)>::value
#else
#define SIMDPP_WORKAROUND_MAKE_CONSTEXPR(X) (X)
#endif

#endif
