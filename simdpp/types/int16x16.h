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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X16_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

/// @ingroup simd_vec_int
/// @{

/** Class representing 16x 16-bit signed integer vector
*/
template<>
class int16<16, void> : public any_int16<16, int16<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int16_t;
    using base_vector_type = int16<16>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    int16<16>() = default;
    int16<16>(const int16<16> &) = default;
    int16<16> &operator=(const int16<16> &) = default;

    template<class E> int16<16>(const int16<16,E>& d) { *this = d.eval(); }
    template<class E> int16<16>(const uint16<16,E>& d) { *this = d.eval(); }
    template<class V> explicit int16<16>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int16<16>>(d.vec().eval());
    }
    template<class V> int16<16>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int16<16>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int16<16>(const native_type& d) : d_(d) {}
    int16<16>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int16<16>& operator[](unsigned) const { return *this; }
          int16<16>& operator[](unsigned)       { return *this; }
    /// @}

    int16<16> eval() const { return *this; }

    static int16<16> zero();
    static int16<16> ones();

private:
    native_type d_;
};

/** Class representing 16x 16-bit unsigned integer vector
*/
template<>
class uint16<16, void> : public any_int16<16, uint16<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint16_t;
    using base_vector_type = uint16<16,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    uint16<16>() = default;
    uint16<16>(const uint16<16> &) = default;
    uint16<16> &operator=(const uint16<16> &) = default;

    template<class E> uint16<16>(const uint16<16,E>& d) { *this = d.eval(); }
    template<class E> uint16<16>(const int16<16,E>& d) { *this = d.eval(); }
    template<class V> explicit uint16<16>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint16<16>>(d.vec().eval());
    }
    template<class V> uint16<16>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint16<16>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint16<16>(const native_type& d) : d_(d) {}
    uint16<16>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint16<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint16<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint16<16>& operator[](unsigned) const { return *this; }
          uint16<16>& operator[](unsigned)       { return *this; }
    /// @}

    uint16<16> eval() const { return *this; }

    static uint16<16> zero();
    static uint16<16> ones();

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 8x 16-bit integer
/// vector
template<>
class mask_int16<16, void> : public any_int16<16, mask_int16<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16<16, void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    mask_int16<16>() = default;
    mask_int16<16>(const mask_int16<16> &) = default;
    mask_int16<16> &operator=(const mask_int16<16> &) = default;

    mask_int16<16>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    mask_int16<16>(const uint16<16>& d) : d_(d) {}
#endif

    /// Access the underlying type
    uint16<16> unmask() const;

    const mask_int16<16>& operator[](unsigned) const { return *this; }
          mask_int16<16>& operator[](unsigned)       { return *this; }

    mask_int16<16> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || DOXYGEN_SHOULD_READ_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
