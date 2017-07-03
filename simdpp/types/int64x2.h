/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X2_H
#define LIBSIMDPP_SIMDPP_TYPES_INT64X2_H

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

#if SIMDPP_USE_SSE2 || SIMDPP_USE_NEON
#define SIMDPP_DEFAULT_ARRAY 0
#else
#define SIMDPP_DEFAULT_ARRAY 1
#endif

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @ingroup simd_vec_int
/// @{

/** Class representing 2x 64-bit signed integer vector
*/
template<>
class int64<2, void> : public any_int64<2, int64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int64_t;
    using base_vector_type = int64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = int64x2_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<int64_t, 2>;
#endif

    SIMDPP_INL int64<2>() = default;
    SIMDPP_INL int64<2>(const int64<2> &) = default;
    SIMDPP_INL int64<2> &operator=(const int64<2> &) = default;

    template<class E> SIMDPP_INL int64<2>(const int64<2,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int64<2>(const uint64<2,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int64<2>(const any_vec<16,V>& d)
    {
        *this = bit_cast<int64<2>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int64<2>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<int64<2>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL int64<2>(const native_type& d) : d_(d) {}
    SIMDPP_INL int64<2>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL int64<2>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int64<2>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const int64<2>& vec(unsigned) const { return *this; }
    SIMDPP_INL int64<2>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL int64<2> eval() const { return *this; }

#if SIMDPP_DEFAULT_ARRAY
    /// For internal use only
    const int64_t& el(unsigned i) const  { return d_[i]; }
          int64_t& el(unsigned i)        { return d_[i]; }
#endif

private:
    native_type d_;
};

/** Class representing 2x 64-bit unsigned integer vector
*/
template<>
class uint64<2, void> : public any_int64<2, uint64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint64_t;
    using base_vector_type = uint64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint64x2_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<uint64_t, 2>;
#endif

    SIMDPP_INL uint64<2>() = default;
    SIMDPP_INL uint64<2>(const uint64<2> &) = default;
    SIMDPP_INL uint64<2> &operator=(const uint64<2> &) = default;

    template<class E> SIMDPP_INL uint64<2>(const uint64<2,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint64<2>(const int64<2,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint64<2>(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint64<2>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint64<2>& operator=(const any_vec<16,V>& d)
    {
        *this = bit_cast<uint64<2>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL uint64<2>(const native_type& d) : d_(d) {}
    SIMDPP_INL uint64<2>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL uint64<2>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint64<2>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const uint64<2>& vec(unsigned) const { return *this; }
    SIMDPP_INL uint64<2>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL uint64<2> eval() const { return *this; }

#if SIMDPP_DEFAULT_ARRAY
    /// For uinternal use only
    const uint64_t& el(unsigned i) const  { return d_[i]; }
          uint64_t& el(unsigned i)        { return d_[i]; }
#endif

private:
    native_type d_;
};


/// Class representing possibly optimized mask data for 2x 64-bit integer
/// vector
template<>
class mask_int64<2, void> : public any_int64<2, mask_int64<2,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int64<2,void>;
    using expr_type = void;

#if SIMDPP_USE_SSE2
    using native_type = __m128i;
#elif SIMDPP_USE_NEON
    using native_type = uint64x2_t;
#elif SIMDPP_DEFAULT_ARRAY
    using native_type = detail::array<bool, 2>;
#endif

    SIMDPP_INL mask_int64<2>() = default;
    SIMDPP_INL mask_int64<2>(const mask_int64<2> &) = default;
    SIMDPP_INL mask_int64<2> &operator=(const mask_int64<2> &) = default;

    SIMDPP_INL mask_int64<2>(const native_type& d) : d_(d) {}

#if !SIMDPP_DEFAULT_ARRAY
    SIMDPP_INL mask_int64<2>(const uint64<2>& d) : d_(d) {}
#endif

    template<class E> SIMDPP_INL explicit mask_int64<2>(const mask_float64<2,E>& d)
    {
        *this = bit_cast<mask_int64<2>>(d.eval());
    }
    template<class E> SIMDPP_INL mask_int64<2>& operator=(const mask_float64<2,E>& d)
    {
        *this = bit_cast<mask_int64<2>>(d.eval()); return *this;
    }

    SIMDPP_INL operator native_type() const { return d_; }

    /// Access the underlying type
    SIMDPP_INL uint64<2> unmask() const
    {
    #if SIMDPP_DEFAULT_ARRAY
        return detail::null::unmask_mask<uint64<2>>(*this);
    #else
        return uint64<2>(d_);
    #endif
    }

#if SIMDPP_DEFAULT_ARRAY
    bool& el(unsigned id) { return d_[id]; }
    const bool& el(unsigned id) const { return d_[id]; }
#endif

    SIMDPP_INL const mask_int64<2>& vec(unsigned) const { return *this; }
    SIMDPP_INL mask_int64<2>& vec(unsigned)       { return *this; }

    SIMDPP_INL mask_int64<2> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#undef SIMDPP_DEFAULT_ARRAY

#endif
