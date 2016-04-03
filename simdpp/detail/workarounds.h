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
#if (__GNUC__ == 4) && (__GNUC_MINOR__ <= 8)
#define vreinterpretq_f64_u64(x) ((float64x2_t) (uint64x2_t) (x))
#define vreinterpretq_u64_f64(x) ((uint64x2_t) (float64x2_t) (x))
#endif

#if (__GNUC__ == 4) && (__GNUC_MINOR__ <= 9)
#define vmul_f64(x, y) ((float64x1_t)( ((float64x1_t)(x)) * ((float64x1_t)(y)) ))
#endif
#endif

#if SIMDPP_USE_AVX512F
#if (__GNUC__ == 4) && !__INTEL_COMPILER
/*  See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70059.
    _mm512_inserti64x4(x, y, 0) and related intrinsics result in wrong code.
    _mm512_castsi256_si512 is not available in GCC 4.9, thus there's no way
    to convert between 256-bit and 512-bit vectors.
*/
#error "The first supported GCC version for AVX512F is 5.0"
#endif

#if ((__GNUC__ == 4) || (__GNUC__ == 5)) && !__INTEL_COMPILER
#define SIMDPP_WORKAROUND_AVX512F_NO_REDUCE 1
#endif
#endif

#if ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))) || \
    (defined(__clang__) && (__clang_major__ == 3) && (__clang_minor__ >= 6)) || \
    (defined(__clang__) && (__clang_major__ > 4))
#define SIMDPP_ATTRIBUTE_UNUSED __attribute__((unused))
#else
#define SIMDPP_ATTRIBUTE_UNUSED
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

#if (__clang_major__ == 3) && (__clang_minor <= 4)
#define SIMDPP_WORKAROUND_AVX2_SHIFT_INTRINSICS 1
/*  Clang 3.4 and older may crash when the following intrinsics are used with
    arguments that are known at compile time: _mm256_sll_epi{16,32,64},
    _mm256_srl_epi{16,32,64}, _mm256_sra_epi{16,32}
*/
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
