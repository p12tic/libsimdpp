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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64X4_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int64x4.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/core/cast.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x4 vector
template<>
class float64<4, void> {
public:

    using element_type = double;
    using uint_element_type = uint64_t;
    using int_vector_type = gint64x4;
    using uint_vector_type = uint64x4;
    using base_vector_type = float64x4;
    using mask_type = mask_float64x4;

    static constexpr unsigned vec_length = 1;
    static constexpr unsigned length = 4;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    float64<4>() = default;
    float64<4>(const float64x4&) = default;
    float64<4>& operator=(const float64x4&) = default;

    /// Construct from the underlying vector type
    float64<4>(__m256d d) : d_(d) {}
    float64<4>& operator=(__m256d d) { d_ = d; return *this; }

    /// Convert to underlying vector type
    operator __m256d() const { return d_; }

    /// @{
    /// Construct from compatible int64x4 integer vector type
    explicit float64<4>(gint64x4 d)     { *this = bit_cast<float64x4>(d); }
    float64<4>& operator=(gint64x4 d)   { *this = bit_cast<float64x4>(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class VE>
    float64<4>(const expr_vec_set_splat<VE>& e);
    float64<4>(const expr_vec_load_splat& e);
    template<class VE>
    float64<4>& operator=(const expr_vec_set_splat<VE>& e);
    float64<4>& operator=(const expr_vec_load_splat& e);
#endif

    /// @{
    /// Access base vectors
    const float64x4& operator[](unsigned) const { return *this; }
          float64x4& operator[](unsigned)       { return *this; }
    /// @}

    float64<4> eval() const { return *this; }

    /** Creates a float64x4 vector with the contens set to zero

        @code
        r0 = 0.0
        ...
        r7 = 0.0
        @endcode
    */
    static float64x4 zero();

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
    __m256d d_;
};

/// Class representing possibly optimized mask data for 4x 64-bit floating point
/// vector
template<>
class maskdata_float64<4> {
public:
    using base_vector_type = maskdata_float64<4>;
    static constexpr unsigned length = 4;
    static constexpr unsigned vec_length = 1;

    maskdata_float64<4>() = default;
    maskdata_float64<4>(const maskdata_float64<4> &) = default;
    maskdata_float64<4> &operator=(const maskdata_float64<4> &) = default;

    maskdata_float64<4>(float64<4> d) : d_(d) {}

    /// Convert to bitmask
    operator float64<4>() const;

    /// @{
    /// Access base vectors
    const maskdata_float64<4>& operator[](unsigned) const { return *this; }
          maskdata_float64<4>& operator[](unsigned)       { return *this; }
    /// @}

private:
    float64<4> d_;
};


/// Class representing a mask for 4x 64-bit floating-point vector
template<>
class mask_float64<4, void> : public float64<4, void> {
public:
    mask_float64<4>() = default;
    mask_float64<4>(const mask_float64<4> &) = default;
    mask_float64<4> &operator=(const mask_float64<4> &) = default;
    mask_float64<4>(const maskdata_float64<4>& d);

    /// @{
    /// Construct from the underlying vector type
    mask_float64<4>(__m256 d);
    mask_float64<4>(float64<4> d);
    /// @}

    mask_float64<4> eval() const { return *this; }

    const maskdata_float64<4>& mask() const { return mask_; }
private:
    maskdata_float64<4> mask_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
