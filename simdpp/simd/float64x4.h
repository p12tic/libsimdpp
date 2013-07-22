/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT64X4_H
#define LIBSIMDPP_SIMD_FLOAT64X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int64x4.h>
#include <simdpp/simd/float64x2.h>
#include <simdpp/simd/cast.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

class basic_int64x4;

/** Class representing float64x4 vector
*/
class float64x4 {
public:

    float64x4() = default;
    float64x4(const float64x4&) = default;
    float64x4& operator=(const float64x4&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    float64x4(__m256d d) : d_(d) {}
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_AVX
    operator __m256d() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int64x4 integer vector type
#if SIMDPP_USE_AVX2
    explicit float64x4(basic_int64x4 d) : d_(_mm256_castsi256_pd(d)) {}
#elif SIMDPP_USE_AVX
    explicit float64x4(basic_int64x4 d);
#else
    explicit float64x4(basic_int64x4 d)
    {
        d_[0] = float64x2(d[0]);
        d_[1] = float64x2(d[1]);
    }
#endif
    float64x4& operator=(basic_int64x4 d) { operator=(float64x4(d)); return *this; }

    /// @}

#if SIMDPP_USE_AVX
    float64x4(float64x2 d0, float64x2 d1)
    {
        d_ = _mm256_insertf128_pd(_mm256_castpd128_pd256(d0), d1, 1);
    }
#else
    float64x4(float64x2 d0, float64x2 d1) { d_[0] = d0; d_[1] = d1; }

    const float64x2& operator[](unsigned i) const { return d_[i]; }
          float64x2& operator[](unsigned i)       { return d_[i]; }
#endif


    /** Creates a float64x4 vector with the contens set to zero

        @code
        r0 = 0.0
        ...
        r7 = 0.0
        @endcode
    */
    static float64x4 zero();

    /** Creates a float64x4 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float64x4 load_broadcast(const double* v0);

    /** Creates a float64x4 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float64x4 set_broadcast(double v0);

    /** Creates a float64x4 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static float64x4 make_const(double v0);

    /** Creates a float64x4 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static float64x4 make_const(double v0, double v1);

    /** Creates a float64x4 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static float64x4 make_const(double v0, double v1, double v2, double v3);

private:
#if SIMDPP_USE_AVX
    __m256d d_;
#else
    float64x2 d_[2];
#endif
};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
