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
#include <simdpp/types/any.h>
#include <simdpp/types/int64x4.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x4 vector
template<>
class float64<4, void> : public any_float64<4, float64<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using element_type = double;
    using base_vector_type = float64<4,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX
    using native_type = __m256d;
#endif

    float64<4>() = default;
    float64<4>(const float64<4> &) = default;
    float64<4> &operator=(const float64<4> &) = default;

    template<class E> float64<4>(const float64<4,E>& d) { *this = d.eval(); }
    template<class V> explicit float64<4>(const any_vec<32,V>& d)
    {
        *this = bit_cast<float64<4>>(d.vec().eval());
    }
    template<class V> float64<4>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<float64<4>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    float64<4>(const native_type& d) : d_(d) {}
    float64<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> float64<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float64<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float64<4>& operator[](unsigned) const { return *this; }
          float64<4>& operator[](unsigned)       { return *this; }
    /// @}

    float64<4> eval() const { return *this; }

    /** Creates a float64x2 vector with the contens set to zero

        @code
        r0 = 0.0
        r1 = 0.0
        @endcode
    */
    static float64<4> zero();

private:
    native_type d_;
};


/// Class representing possibly optimized mask data for 2x 64-bit floating point
/// vector
template<>
class mask_float64<4, void> : public any_float64<4, mask_float64<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float64<4,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX
    using native_type = __m256d;
#endif

    mask_float64<4>() = default;
    mask_float64<4>(const mask_float64<4> &) = default;
    mask_float64<4> &operator=(const mask_float64<4> &) = default;

    mask_float64<4>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX
    mask_float64<4>(const float64<4>& d) : d_(d) {}
#endif

    /// Access the underlying type
    float64<4> unmask() const;

    const mask_float64<4>& operator[](unsigned) const { return *this; }
          mask_float64<4>& operator[](unsigned)       { return *this; }

    mask_float64<4> eval() const { return *this; }

private:
    native_type d_;
};
/// @} -- end ingroup

#endif // SIMDPP_USE_AVX || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
