/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32X8_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int32x8.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_fp
/// @{

/// Class representing a float32x8 vector
template<>
class float32<8, void> {
public:

    using element_type = float;
    using uint_element_type = uint32_t;
    using int_vector_type = gint32x8;
    using uint_vector_type = uint32x8;
    using base_vector_type = float32x8;
    using mask_type = mask_float32x8;

    static constexpr unsigned vec_length = 1;
    static constexpr unsigned length = 8;
    static constexpr unsigned num_bits = 32;
    static constexpr uint_element_type all_bits = 0xffffffff;

    float32<8>() = default;
    float32<8>(const float32x8&) = default;
    float32<8>& operator=(const float32x8&) = default;

    /// Construct from the underlying vector type
    float32<8>(__m256 d) : d_(d) {}
    float32<8>& operator=(__m256 d) { d_ = d; return *this; }

    /// Convert to underlying vector type
    operator __m256() const { return d_; }

    /// @{
    /// Construct from compatible int32x8 integer vector type
    float32<8>(gint32x8 d)              { *this = bit_cast<float32x8>(d); }
    float32<8>& operator=(gint32x8 d)   { *this = bit_cast<float32x8>(d); return *this; }
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> float32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float32x8& operator[](unsigned) const { return *this; }
          float32x8& operator[](unsigned)       { return *this; }
    /// @}

    float32<8> eval() const { return *this; }

    /** Creates a float32x8 vector with the contents set to zero

        @code
        r0 = 0.0f
        r1 = 0.0f
        r2 = 0.0f
        r3 = 0.0f
        @endcode
    */
    static float32x8 zero();

private:
    __m256 d_;
};

/// Class representing possibly optimized mask data for 8x 32-bit floating point
/// vector
template<>
class maskdata_float32<8> {
public:
    using base_vector_type = maskdata_float32<8>;
    static constexpr unsigned length = 8;
    static constexpr unsigned vec_length = 1;

    maskdata_float32<8>() = default;
    maskdata_float32<8>(const maskdata_float32<8> &) = default;
    maskdata_float32<8> &operator=(const maskdata_float32<8> &) = default;

    maskdata_float32<8>(float32<8> d) : d_(d) {}

    /// Convert to bitmask
    operator float32<8>() const;

    /// @{
    /// Access base vectors
    const maskdata_float32<8>& operator[](unsigned) const { return *this; }
          maskdata_float32<8>& operator[](unsigned)       { return *this; }
    /// @}

private:
    float32<8> d_;
};


/// Class representing a mask for 8x 32-bit floating-point vector
template<>
class mask_float32<8, void> : public float32<8, void> {
public:
    mask_float32<8>() = default;
    mask_float32<8>(const mask_float32<8> &) = default;
    mask_float32<8> &operator=(const mask_float32<8> &) = default;
    mask_float32<8>(const maskdata_float32<8>& d);

    /// @{
    /// Construct from the underlying vector type
    mask_float32<8>(__m256 d);
    mask_float32<8>(float32<8> d);
    /// @}

    mask_float32<8> eval() const { return *this; }

    const maskdata_float32<8>& mask() const { return mask_; }

private:
    maskdata_float32<8> mask_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
