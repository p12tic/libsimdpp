/*  Copyright (C) 2012-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X4_H
#define LIBSIMDPP_SIMDPP_TYPES_INT64X4_H

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

/** Class representing 4x 64-bit signed integer vector
*/
template<>
class int64<4, void> : public any_int64<4, int64<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int64_t;
    using base_vector_type = int64<4,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    int64<4>() = default;
    int64<4>(const int64<4> &) = default;
    int64<4> &operator=(const int64<4> &) = default;

    template<class E> SIMDPP_INL int64<4>(const int64<4,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int64<4>(const uint64<4,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int64<4>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int64<4>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int64<4>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int64<4>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    int64<4>(const native_type& d) : d_(d) {}
    int64<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL int64<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int64<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const int64<4>& vec(unsigned) const { return *this; }
          int64<4>& vec(unsigned)       { return *this; }
    /// @}

    int64<4> eval() const { return *this; }

    static int64<4> zero() { return detail::make_zero(); }
    static int64<4> ones() { return detail::make_ones(); }

private:
    native_type d_;
};

/** Class representing 4x 64-bit unsigned integer vector
*/
template<>
class uint64<4, void> : public any_int64<4, uint64<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint64_t;
    using base_vector_type = uint64<4,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    uint64<4>() = default;
    uint64<4>(const uint64<4> &) = default;
    uint64<4> &operator=(const uint64<4> &) = default;

    template<class E> SIMDPP_INL uint64<4>(const uint64<4,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint64<4>(const int64<4,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint64<4>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint64<4>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint64<4>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint64<4>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    uint64<4>(const native_type& d) : d_(d) {}
    uint64<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL uint64<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint64<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const uint64<4>& vec(unsigned) const { return *this; }
          uint64<4>& vec(unsigned)       { return *this; }
    /// @}

    uint64<4> eval() const { return *this; }

    static uint64<4> zero() { return detail::make_zero(); }
    static uint64<4> ones() { return detail::make_ones(); }

private:
    native_type d_;
};


/// Class representing possibly optimized mask data for 4x 64-bit integer
/// vector
template<>
class mask_int64<4, void> : public any_int64<4, mask_int64<4,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int64<4,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX2
    using native_type = __m256i;
#endif

    mask_int64<4>() = default;
    mask_int64<4>(const mask_int64<4> &) = default;
    mask_int64<4> &operator=(const mask_int64<4> &) = default;

    mask_int64<4>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    mask_int64<4>(const uint64<4>& d) : d_(d) {}
#endif

    template<class E> SIMDPP_INL explicit mask_int64<4>(const mask_float64<4,E>& d)
    {
        *this = bit_cast<mask_int64<4>>(d.eval());
    }
    template<class E> SIMDPP_INL mask_int64<4>& operator=(const mask_float64<4,E>& d)
    {
        *this = bit_cast<mask_int64<4>>(d.eval()); return *this;
    }

    operator native_type() const { return d_; }

    /// Access the underlying type
    uint64<4> unmask() const
    {
    #if SIMDPP_USE_AVX2
        return uint64<4>(d_);
    #endif
    }

    const mask_int64<4>& vec(unsigned) const { return *this; }
          mask_int64<4>& vec(unsigned)       { return *this; }

    mask_int64<4> eval() const { return *this; }

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
