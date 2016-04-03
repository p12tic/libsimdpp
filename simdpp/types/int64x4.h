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
#include <stdint.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

#if SIMDPP_USE_AVX2

/// @ingroup simd_vec_int
/// @{

/** Class representing 4x 64-bit signed integer vector
*/
template<>
class int64<4, void> : public any_int64<4, int64<4,void> > {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    typedef int64_t element_type;
    typedef int64<4,void> base_vector_type;
    typedef void expr_type;

#if SIMDPP_USE_AVX2
    typedef __m256i native_type;
#endif

    SIMDPP_INL int64<4>() {}
    // SIMDPP_INL int64<4>(const int64<4> &) = default;
    // SIMDPP_INL int64<4> &operator=(const int64<4> &) = default;

    template<class E> SIMDPP_INL int64<4>(const int64<4,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int64<4>(const uint64<4,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int64<4>(const any_vec<32,V>& d)
    {
        *this = bit_cast<int64<4> >(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int64<4>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<int64<4> >(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL int64<4>(const native_type& d) : d_(d) {}
    SIMDPP_INL int64<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL int64<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int64<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const int64<4>& vec(unsigned) const { return *this; }
    SIMDPP_INL int64<4>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL int64<4> eval() const { return *this; }

private:
    native_type d_;
};

/** Class representing 4x 64-bit unsigned integer vector
*/
template<>
class uint64<4, void> : public any_int64<4, uint64<4,void> > {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    typedef uint64_t element_type;
    typedef uint64<4,void> base_vector_type;
    typedef void expr_type;

#if SIMDPP_USE_AVX2
    typedef __m256i native_type;
#endif

    SIMDPP_INL uint64<4>() {}
    // SIMDPP_INL uint64<4>(const uint64<4> &) = default;
    // SIMDPP_INL uint64<4> &operator=(const uint64<4> &) = default;

    template<class E> SIMDPP_INL uint64<4>(const uint64<4,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint64<4>(const int64<4,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint64<4>(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint64<4> >(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint64<4>& operator=(const any_vec<32,V>& d)
    {
        *this = bit_cast<uint64<4> >(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    SIMDPP_INL uint64<4>(const native_type& d) : d_(d) {}
    SIMDPP_INL uint64<4>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    SIMDPP_INL operator native_type() const { return d_; }

    template<class E> SIMDPP_INL uint64<4>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint64<4>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    /// @{
    /// Access base vectors
    SIMDPP_INL const uint64<4>& vec(unsigned) const { return *this; }
    SIMDPP_INL uint64<4>& vec(unsigned)       { return *this; }
    /// @}

    SIMDPP_INL uint64<4> eval() const { return *this; }

private:
    native_type d_;
};


/// Class representing possibly optimized mask data for 4x 64-bit integer
/// vector
template<>
class mask_int64<4, void> : public any_int64<4, mask_int64<4,void> > {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    typedef mask_int64<4,void> base_vector_type;
    typedef void expr_type;

#if SIMDPP_USE_AVX2
    typedef __m256i native_type;
#endif

    SIMDPP_INL mask_int64<4>() {}
    // SIMDPP_INL mask_int64<4>(const mask_int64<4> &) = default;
    // SIMDPP_INL mask_int64<4> &operator=(const mask_int64<4> &) = default;

    SIMDPP_INL mask_int64<4>(const native_type& d) : d_(d) {}

#if SIMDPP_USE_AVX2
    SIMDPP_INL mask_int64<4>(const uint64<4>& d) : d_(d) {}
#endif

    template<class E> SIMDPP_INL explicit mask_int64<4>(const mask_float64<4,E>& d)
    {
        *this = bit_cast<mask_int64<4> >(d.eval());
    }
    template<class E> SIMDPP_INL mask_int64<4>& operator=(const mask_float64<4,E>& d)
    {
        *this = bit_cast<mask_int64<4> >(d.eval()); return *this;
    }

    SIMDPP_INL operator native_type() const { return d_; }

    /// Access the underlying type
    SIMDPP_INL uint64<4> unmask() const
    {
    #if SIMDPP_USE_AVX2
        return uint64<4>(d_);
    #endif
    }

    SIMDPP_INL const mask_int64<4>& vec(unsigned) const { return *this; }
    SIMDPP_INL mask_int64<4>& vec(unsigned)       { return *this; }

    SIMDPP_INL mask_int64<4> eval() const { return *this; }

private:
    native_type d_;
};

/// @} -- end ingroup

#endif // SIMDPP_USE_AVX2

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
