/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>
#include <simdpp/detail/array.h>
#include <simdpp/detail/null/mask.h>
#include <cstdint>

#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
#define SIMDPP_DEFAULT_ARRAY 0
#else
#define SIMDPP_DEFAULT_ARRAY 1
#endif

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @ingroup simd_vec_int
/// @{

/** Class representing 8x 16-bit signed integer vector
*/
template<>
class int16<8, void> : public any_int16<8, int16<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int16_t;
    using base_vector_type = int16<8>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = int16x8_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector int16_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<int16_t, 8>;
#endif

    SIMDPP_INL int16<8>() = default;
    SIMDPP_INL int16<8>(const int16<8> &) = default;
    SIMDPP_INL int16<8> &operator=(const int16<8> &) = default;

    template<class E> SIMDPP_INL int16<8>(const int16<8,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int16<8>(const uint16<8,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int16<8>(const any_vec<16,V>& d)
    {
        *this = bit_cast<int16<8>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int16<8>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<int16<8>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL int16<8>(const native_type& d) : d_(d) {}
    SIMDPP_INL int16<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL int16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const int16<8>& vec(unsigned) const { return *this; }
    SIMDPP_INL int16<8>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL int16<8> eval() const { return *this; }

#if SIMDPP_DEFAULT_ARRAY
    /// For internal use only
    const int16_t& el(unsigned i) const  { return d_[i]; }
          int16_t& el(unsigned i)        { return d_[i]; }
#endif

private:
    native_type d_;
};

/** Class representing 8x 16-bit unsigned integer vector
*/
template<>
class uint16<8, void> : public any_int16<8, uint16<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint16_t;
    using base_vector_type = uint16<8,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint16x8_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint16_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<uint16_t, 8>;
#endif

    SIMDPP_INL uint16<8>() = default;
    SIMDPP_INL uint16<8>(const uint16<8> &) = default;
    SIMDPP_INL uint16<8> &operator=(const uint16<8> &) = default;

    template<class E> SIMDPP_INL uint16<8>(const uint16<8,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint16<8>(const int16<8,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint16<8>(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint16<8>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint16<8>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint16<8>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL uint16<8>(const native_type& d) : d_(d) {}
    SIMDPP_INL uint16<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL uint16<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint16<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const uint16<8>& vec(unsigned) const { return *this; }
    SIMDPP_INL uint16<8>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL uint16<8> eval() const { return *this; }

#if SIMDPP_DEFAULT_ARRAY
    /// For uinternal use only
    const uint16_t& el(unsigned i) const  { return d_[i]; }
          uint16_t& el(unsigned i)        { return d_[i]; }
#endif

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 8x 16-bit integer
/// vector
template<>
class mask_int16<8, void> : public any_int16<8, mask_int16<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16<8, void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint16x8_t;
#elif SIMDPP_USE_ALTIVEC
    using native_type = __vector uint16_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<bool, 8>;
#endif

    SIMDPP_INL mask_int16<8>() = default;
    SIMDPP_INL mask_int16<8>(const mask_int16<8> &) = default;
    SIMDPP_INL mask_int16<8> &operator=(const mask_int16<8> &) = default;

    SIMDPP_INL mask_int16<8>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_ALTIVEC
    SIMDPP_INL mask_int16<8>(const __vector __bool short& d) : d_((__vector uint16_t)d) {}
#endif

#if !SIMDPP_DEFAULT_ARRAY
    SIMDPP_INL mask_int16<8>(const uint16<8>& d) : d_(d) {}
#endif

    SIMDPP_INL operator native_type() const { return d_; }

    /// Access the underlying type
    SIMDPP_INL uint16<8> unmask() const
    {
    #if SIMDPP_DEFAULT_ARRAY
        return detail::null::unmask_mask<uint16<8>>(*this);
    #else
        return uint16<8>(d_);
    #endif
    }

#if SIMD_DEFAULT_ARRAY
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    SIMDPP_INL const mask_int16<8>& vec(unsigned) const { return *this; }
    SIMDPP_INL mask_int16<8>& vec(unsigned)       { return *this; }

    SIMDPP_INL mask_int16<8> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#undef SIMDPP_DEFAULT_ARRAY

#endif
