/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT32X8_H
#define LIBSIMDPP_SIMD_FLOAT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int32x8.h>
#include <simdpp/simd/float32x4.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

class basic_int32x8;

/** Class representing a float32x8 vector
*/
class float32x8 {
public:

    float32x8() = default;
    float32x8(const float32x8&) = default;
    float32x8& operator=(const float32x8&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_AVX
    float32x8(__m256 d) : d_(d) {}
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_AVX
    operator __m256() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int32x8 integer vector type
#if SIMDPP_USE_AVX2
    explicit float32x8(basic_int32x8 d) : d_(_mm256_castsi256_ps(d)) {}
#elif SIMDPP_USE_AVX
    explicit float32x8(basic_int32x8 d)
    {
        d_ = _mm256_castsi256_ps(_mm256_inserti128_si256(_mm256_castsi128_si256(d[0]), d[1], 1));
    }
#else
    explicit float32x8(basic_int32x8 d)
    {
        d_[0] = int32x4(d[0]);
        d_[1] = int32x4(d[1]);
    }
#endif
    float32x8& operator=(basic_int32x8 d) { operator=(float32x8(d)); return *this; }
    /// @}

#if SIMDPP_USE_AVX
#else
    float32x8(float32x4 d0, float32x4 d1) { d_[0] = d0;  d_[1] = d1; }

    const float32x4& operator[](unsigned i) const { return d_[i]; }
          float32x4& operator[](unsigned i)       { return d_[i]; }
#endif

    /** Creates a float32x8 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32x8 zero();

    /** Creates a float32x8 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float32x8 load_broadcast(const float* v0);

    /** Creates a float32x8 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 2}
    */
    static float32x8 set_broadcast(float v0);

    /** Creates a float32x8 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static float32x8 make_const(float v0);

    /** Creates a float32x8 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static float32x8 make_const(float v0, float v1);

    /** Creates a float32x8 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static float32x8 make_const(float v0, float v1, float v2, float v3);

    /** Creates a float32x8 vector from four values known at compile-time

        @code
            | 0  1  ... 7  |
        r = [ v0 v1 ... v7 ]
        @endcode
    */
    static float32x8 make_const(float v0, float v1, float v2, float v3,
                                float v4, float v5, float v6, float v7);

private:
#if SIMDPP_USE_AVX
    __m256 d_;
#else
    float32x4 d_[2];
#endif
};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
