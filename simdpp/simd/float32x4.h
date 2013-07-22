/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_FLOAT32X4_H
#define LIBSIMDPP_SIMD_FLOAT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int32x4.h>

namespace simdpp {
SIMDPP_ARCH_NAMESPACE_BEGIN

class basic_int32x4;

/** Class representing float32x4 vector
*/
class float32x4 {
public:

    float32x4() = default;
    float32x4(const float32x4&) = default;
    float32x4& operator=(const float32x4&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    float32x4(__m128 d) : d_(d) {}
#elif SIMDPP_USE_NEON
    float32x4(float32x4_t d) : d_(d) {}
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_SSE2
    operator __m128() const { return d_; }
#elif SIMDPP_USE_NEON
    operator float32x4_t() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int32x4 integer vector type
#if SIMDPP_USE_SSE2
    explicit float32x4(basic_int32x4 d) : d_(_mm_castsi128_ps(d)) {}
    float32x4& operator=(basic_int32x4 d) { d_ = _mm_castsi128_ps(d); return *this; }
#elif SIMDPP_USE_NEON
    explicit float32x4(basic_int32x4 d)  : d_(float32x4_t(d)) {}
    float32x4& operator=(basic_int32x4 d) { d_ = float32x4_t(d); return *this; }
#elif SIMDPP_USE_NULL
    explicit float32x4(basic_int32x4 d)
    {
        f32_[0] = bit_cast<float>(d[0]);
        f32_[1] = bit_cast<float>(d[1]);
        f32_[2] = bit_cast<float>(d[2]);
        f32_[3] = bit_cast<float>(d[3]);
    }
    float32x4& operator=(basic_int32x4 d) { operator=(float32x4(d)); return *this; }
#endif
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON_VFP_SP
    /// For internal use only
    const float& operator[](unsigned i) const { return f32_[i]; }
          float& operator[](unsigned i)       { return f32_[i]; }
#endif
#endif

    /** Creates a float32x4 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32x4 zero();

    /** Creates a float32x4 vector from a value loaded from memory.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float32x4 load_broadcast(const float* v0);

    /** Creates a float32x4 vector from a value stored in a core register.

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
        @icost{NEON, 2}
    */
    static float32x4 set_broadcast(float v0);

    /** Creates a float32x4 vector from a value known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v0 v0 v0 ]
        @endcode
    */
    static float32x4 make_const(float v0);

    /** Creates a float32x4 vector from two values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v0 v1 ]
        @endcode
    */
    static float32x4 make_const(float v0, float v1);

    /** Creates a float32x4 vector from four values known at compile-time

        @code
            | 0  1  2  3  |
        r = [ v0 v1 v2 v3 ]
        @endcode
    */
    static float32x4 make_const(float v0, float v1, float v2, float v3);

private:
#if SIMDPP_USE_SSE2
    __m128 d_;
#elif SIMDPP_USE_NEON_VFP_SP
    union {
        float f32_[4];
        float32x4_t d_;
    };
#elif SIMDPP_USE_NEON
    float32x4_t d_;
#elif SIMDPP_USE_NULL
    float f32_[4];
#endif
};

SIMDPP_ARCH_NAMESPACE_END
} // namespace simdpp

#endif
