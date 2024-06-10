/*  Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16X32_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16X32_H

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
namespace SIMDPP_ARCH_NAMESPACE {

#if SIMDPP_USE_AVX512BW

/** Class representing 32x 16-bit signed integer vector
*/
template<>
class int16<32> : public any_int16<32, int16<32>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int16_t;
    using base_vector_type = int16<32>;
    using expr_type = void;

#if SIMDPP_USE_AVX512BW
    using native_type = __m512i;
#endif

    SIMDPP_INL int16<32>() = default;
    SIMDPP_INL int16<32>(const int16<32> &) = default;
    SIMDPP_INL int16<32> &operator=(const int16<32> &) = default;

    SIMDPP_INL int16<32>(const uint16<32>& d);
    template<class V> SIMDPP_INL explicit int16<32>(const any_vec<64,V>& d)
    {
        *this = bit_cast<int16<32>>(d.wrapped());
    }
    template<class V> SIMDPP_INL int16<32>& operator=(const any_vec<64,V>& d)
    {
        *this = bit_cast<int16<32>>(d.wrapped()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL int16<32>(const native_type& d) : d_(d) {}
    SIMDPP_INL int16<32>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
#if !SIMDPP_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    SIMDPP_INL operator native_type() const SIMDPP_IMPLICIT_CONVERSION_DEPRECATION_MSG
    { return d_; }
#endif
    SIMDPP_INL native_type native() const { return d_; }

    template<class E> SIMDPP_INL int16<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int16<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const int16<32>& vec(unsigned) const { return *this; }
    SIMDPP_INL int16<32>& vec(unsigned)       { return *this; }
    /// @}

private:
    native_type d_;
};

/** Class representing 16x 16-bit unsigned integer vector
*/
template<>
class uint16<32> : public any_int16<32, uint16<32>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint16_t;
    using base_vector_type = uint16<32>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m512i;
#endif

    SIMDPP_INL uint16<32>() = default;
    SIMDPP_INL uint16<32>(const uint16<32> &) = default;
    SIMDPP_INL uint16<32> &operator=(const uint16<32> &) = default;

    SIMDPP_INL uint16<32>(const int16<32>& d) { *this = d; }
    template<class V> SIMDPP_INL explicit uint16<32>(const any_vec<64,V>& d)
    {
        *this = bit_cast<uint16<32>>(d.wrapped());
    }
    template<class V> SIMDPP_INL uint16<32>& operator=(const any_vec<64,V>& d)
    {
        *this = bit_cast<uint16<32>>(d.wrapped()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL uint16<32>(const native_type& d) : d_(d) {}
    SIMDPP_INL uint16<32>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
#if !SIMDPP_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    SIMDPP_INL operator native_type() const SIMDPP_IMPLICIT_CONVERSION_DEPRECATION_MSG
    { return d_; }
#endif
    SIMDPP_INL native_type native() const { return d_; }

    template<class E> SIMDPP_INL uint16<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint16<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const uint16<32>& vec(unsigned) const { return *this; }
    SIMDPP_INL uint16<32>& vec(unsigned)       { return *this; }
    /// @}

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 8x 16-bit integer
/// vector
template<>
class mask_int16<32> : public any_int16<32, mask_int16<32>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16<32>;
    using expr_type = void;

#if SIMDPP_USE_AVX512BW
    using native_type = __mmask32;
#endif

    SIMDPP_INL mask_int16<32>() = default;
    SIMDPP_INL mask_int16<32>(const mask_int16<32> &) = default;
    SIMDPP_INL mask_int16<32> &operator=(const mask_int16<32> &) = default;

    SIMDPP_INL mask_int16<32>(const native_type& d) : d_(d) {}
    SIMDPP_INL mask_int16<32>& operator=(const native_type& d) { d_ = d; return *this; }

    /// Convert to the underlying vector type
#if !SIMDPP_DISABLE_DEPRECATED_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    SIMDPP_INL operator native_type() const SIMDPP_IMPLICIT_CONVERSION_DEPRECATION_MSG
    { return d_; }
#endif
    SIMDPP_INL native_type native() const { return d_; }

    /// Access the underlying type
    SIMDPP_INL uint16<32> unmask() const
    {
    #if SIMDPP_USE_AVX512BW
        return _mm512_movm_epi16(d_);
    #endif
    }

    SIMDPP_INL const mask_int16<32>& vec(unsigned) const { return *this; }
    SIMDPP_INL mask_int16<32>& vec(unsigned)       { return *this; }

private:
    native_type d_;
};

#endif // SIMDPP_USE_AVX512BW

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
