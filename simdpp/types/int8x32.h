/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8X32_H
#define LIBSIMDPP_SIMDPP_TYPES_INT8X32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/detail/construct_eval.h>
#include <cstdint>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2 || SIMDPP_DOXYGEN

/// @ingroup simd_vec_int
/// @{

/** Class representing 32x 8-bit signed integer vector
*/
template<>
class int8<32, void> : public any_int8<32, int8<32,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int8_t;
    using base_vector_type = int8<32>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    int8<32>() = default;
    int8<32>(const int8<32> &) = default;
    int8<32> &operator=(const int8<32> &) = default;

    template<class E> SIMDPP_INL int8<32>(const int8<32,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int8<32>(const uint8<32,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int8<32>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int8<32>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int8<32>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int8<32>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int8<32>(const native_type& d) : d_(d) {}
    int8<32>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL int8<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int8<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int8<32>& vec(unsigned) const { return *this; }
          int8<32>& vec(unsigned)       { return *this; }
    /// @}

    int8<32> eval() const { return *this; }

    static int8<32> zero() { return detail::make_zero(); }
    static int8<32> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/** Class representing 32x 8-bit unsigned integer vector
*/
template<>
class uint8<32, void> : public any_int8<32, uint8<32,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint8_t;
    using base_vector_type = uint8<32>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    uint8<32>() = default;
    uint8<32>(const uint8<32> &) = default;
    uint8<32> &operator=(const uint8<32> &) = default;

    template<class E> SIMDPP_INL uint8<32>(const uint8<32,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint8<32>(const int8<32,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint8<32>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint8<32>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint8<32>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint8<32>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint8<32>(const native_type& d) : d_(d) {}
    uint8<32>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL uint8<32>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint8<32>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint8<32>& vec(unsigned) const { return *this; }
          uint8<32>& vec(unsigned)       { return *this; }
    /// @}

    uint8<32> eval() const { return *this; }

    static uint8<32> zero() { return detail::make_zero(); }
    static uint8<32> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/// Class representing possibly optimized mask data for 16x 8-bit integer
/// vector
template<>
class mask_int8<32, void> : public any_int8<32, mask_int8<32,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16v;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    mask_int8<32>() = default;
    mask_int8<32>(const mask_int8<32> &) = default;
    mask_int8<32> &operator=(const mask_int8<32> &) = default;

    mask_int8<32>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    mask_int8<32>(const uint8<32>& d) : d_(d) {}
#endif

    operator native_type() const { return d_; }

    /// Access the underlying type
    uint8<32> unmask() const
    {
    #if SIMDPP_USE_AVX2
        return uint8<32>(d_);
    #endif
    }

    const mask_int8<32>& vec(unsigned) const { return *this; }
          mask_int8<32>& vec(unsigned)       { return *this; }

    mask_int8<32> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2 || SIMDPP_DOXYGEN

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
