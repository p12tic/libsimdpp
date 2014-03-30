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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32X4_H
#define LIBSIMDPP_SIMDPP_TYPES_INT32X4_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>
#include <cstdint>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing 4x 32-bit signed integer vector
*/
template<>
class int32<4, void> : public any_int32<4, int32<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int32_t;
    using base_vector_type = int32<4,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = int32x4_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector int32_t;
#else
    using native_type = detail::array<int32_t, 4>;
#endif

    int32<4>() = default;
    int32<4>(const int32<4> &) = default;
    int32<4> &operator=(const int32<4> &) = default;

    template<class E> int32<4>(const int32<4,E>& d) { *this = d.eval(); }
    template<class E> int32<4>(const uint32<4,E>& d) { *this = d.eval(); }
    template<class V> explicit int32<4>(const any_vec<16,V>& d)
    {
        *this = bit_cast<int32<4>>(d.vec().eval());
    }
    template<class V> int32<4>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<int32<4>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int32<4>(const native_type& d) : d_(d) {}
    int32<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int32<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int32<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int32<4>& operator[](unsigned) const { return *this; }
          int32<4>& operator[](unsigned)       { return *this; }
    /// @}

    int32<4> eval() const { return *this; }

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    /// For internal use only
    const int32_t& el(unsigned i) const  { return d_[i]; }
          int32_t& el(unsigned i)        { return d_[i]; }
#endif

    static int32<4> zero();
    static int32<4> ones();

private:
    native_type d_;
};

/** Class representing 4x 32-bit unsigned integer vector
*/
template<>
class uint32<4, void> : public any_int32<4, uint32<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint32_t;
    using base_vector_type = uint32<4,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint32x4_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint32_t;
#else
    using native_type = detail::array<uint32_t, 4>;
#endif

    uint32<4>() = default;
    uint32<4>(const uint32<4> &) = default;
    uint32<4> &operator=(const uint32<4> &) = default;

    template<class E> uint32<4>(const uint32<4,E>& d) { *this = d.eval(); }
    template<class E> uint32<4>(const int32<4,E>& d) { *this = d.eval(); }
    template<class V> explicit uint32<4>(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint32<4>>(d.vec().eval());
    }
    template<class V> uint32<4>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint32<4>>(d.vec().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint32<4>(const native_type& d) : d_(d) {}
    uint32<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint32<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint32<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint32<4>& operator[](unsigned) const { return *this; }
          uint32<4>& operator[](unsigned)       { return *this; }
    /// @}

    uint32<4> eval() const { return *this; }

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    /// For uinternal use only
    const uint32_t& el(unsigned i) const  { return d_[i]; }
          uint32_t& el(unsigned i)        { return d_[i]; }
#endif

    static uint32<4> zero();
    static uint32<4> ones();

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 4x 32-bit integer
/// vector
template<>
class mask_int32<4, void> : public any_int32<4, mask_int32<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int32<4,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint32x4_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint32_t;
#else
    using native_type = detail::array<bool, 4>;
#endif

    mask_int32<4>() = default;
    mask_int32<4>(const mask_int32<4> &) = default;
    mask_int32<4> &operator=(const mask_int32<4> &) = default;

    mask_int32<4>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    mask_int32<4>(const uint32<4>& d) : d_(d) {}
#endif

    /// Access the underlying type
    uint32<4> unmask() const;

#if SIMDPP_USE_NULL && !DOXYGEN_SHOULD_SKIP_THIS
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    const mask_int32<4>& operator[](unsigned) const { return *this; }
          mask_int32<4>& operator[](unsigned)       { return *this; }

    mask_int32<4> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
