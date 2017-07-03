/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X16_H
#define LIBSIMDPP_SIMDPP_TYPES_INT8X16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <cstdint>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>
#include <simdpp/detail/null/mask.h>

#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
#define SIMDPP_DEFAULT_ARRAY 0
#else
#define SIMDPP_DEFAULT_ARRAY 1

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @ingroup simd_vec_int
/// @{

/** Class representing 16x 8-bit signed integer vector
*/
template<>
class int8<16, void> : public any_int8<16, int8<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int8_t;
    using base_vector_type = int8<16>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = int8x16_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector int8_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<int8_t, 16>;
#endif

    SIMDPP_INL int8<16>() = default;
    SIMDPP_INL int8<16>(const int8<16> &) = default;
    SIMDPP_INL int8<16> &operator=(const int8<16> &) = default;

    template<class E> SIMDPP_INL int8<16>(const int8<16,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int8<16>(const uint8<16,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int8<16>(const any_vec<16,V>& d)
    {
        *this = bit_cast<int8<16>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int8<16>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<int8<16>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL int8<16>(const native_type& d) : d_(d) {}
    SIMDPP_INL int8<16>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL int8<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int8<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const int8<16>& vec(unsigned) const { return *this; }
    SIMDPP_INL int8<16>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL int8<16> eval() const { return *this; }

#if SIMDPP_DEFAULT_ARRAY
    /// For internal use only
    const int8_t& el(unsigned i) const  { return d_[i]; }
          int8_t& el(unsigned i)        { return d_[i]; }
#endif

private:
    native_type d_;
};

/** Class representing 16x 8-bit unsigned integer vector
*/
template<>
class uint8<16, void> : public any_int8<16, uint8<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint8_t;
    using base_vector_type = uint8<16>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint8x16_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint8_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<uint8_t, 16>;
#endif

    SIMDPP_INL uint8<16>() = default;
    SIMDPP_INL uint8<16>(const uint8<16> &) = default;
    SIMDPP_INL uint8<16> &operator=(const uint8<16> &) = default;

    template<class E> SIMDPP_INL uint8<16>(const uint8<16,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint8<16>(const int8<16,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint8<16>(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint8<16>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint8<16>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint8<16>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL uint8<16>(const native_type& d) : d_(d) {}
    SIMDPP_INL uint8<16>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL uint8<16>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint8<16>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const uint8<16>& vec(unsigned) const { return *this; }
    SIMDPP_INL uint8<16>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL uint8<16> eval() const { return *this; }

#if SIMDPP_DEFAULT_ARRAY
    /// For uinternal use only
    const uint8_t& el(unsigned i) const  { return d_[i]; }
          uint8_t& el(unsigned i)        { return d_[i]; }
#endif

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 16x 8-bit integer
/// vector
template<>
class mask_int8<16, void> : public any_int8<16, mask_int8<16,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16v;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint8x16_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint8_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<bool, 16>;
#endif

    SIMDPP_INL mask_int8<16>() = default;
    SIMDPP_INL mask_int8<16>(const mask_int8<16> &) = default;
    SIMDPP_INL mask_int8<16> &operator=(const mask_int8<16> &) = default;

    SIMDPP_INL mask_int8<16>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_ALTIVEC
    SIMDPP_INL mask_int8<16>(const __vector __bool char& d) : d_((__vector uint8_t)d) {}
#endif

#if !SIMDPP_DEFAULT_ARRAY
    SIMDPP_INL mask_int8<16>(const uint8<16>& d) : d_(d) {}
#endif

    SIMDPP_INL operator native_type() const { return d_; }

    /// Access the underlying type
    SIMDPP_INL uint8<16> unmask() const
    {
    #if SIMDPP_DEFAULT_ARRAY
        return detail::null::unmask_mask<uint8<16>>(*this);
    #else
        return uint8<16>(d_);
    #endif
    }

#if SIMDPP_DEFAULT_ARRAY
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    SIMDPP_INL const mask_int8<16>& vec(unsigned) const { return *this; }
    SIMDPP_INL mask_int8<16>& vec(unsigned)       { return *this; }

    SIMDPP_INL mask_int8<16> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#undef SIMDPP_DEFAULT_ARRAY

#endif
