/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT32_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/types/any.h>
#include <simdpp/types/tag.h>
#include <simdpp/core/cast.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @ingroup simd_vec_fp
/// @{

/** Class representing a @a float32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class float32<N, void> : public any_float32<N, float32<N,void> > {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    typedef void expr_type;
    typedef float element_type;
    typedef float32v base_vector_type;

    SIMDPP_INL float32<N>() {}
    // SIMDPP_INL float32<N>(const float32<N>&) = default;
    // SIMDPP_INL float32<N>& operator=(const float32<N>&) = default;

    template<class E> SIMDPP_INL float32<N>(const float32<N,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit float32<N>(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<float32<N> >(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL float32<N>& operator=(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<float32<N> >(d.wrapped().eval()); return *this;
    }

    template<class E> SIMDPP_INL float32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL float32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }

    SIMDPP_INL const float32v& vec(unsigned i) const { return d_[i]; }
    SIMDPP_INL float32v& vec(unsigned i)             { return d_[i]; }

    SIMDPP_INL float32<N> eval() const { return *this; }

private:
    /** Creates a float vector from a native vector

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static SIMDPP_INL float32<N> set_vec(const float32v& v0)
    {
        float32<N> r;
        for (unsigned i = 0; i < r.vec_length; i++)
            r.vec(i) = v0;
        return r;
    }

    float32v d_[float32::vec_length];
};


/// Class representing a mask for 32-bit floating-point vector of arbitrary
/// length.
template<unsigned N>
class mask_float32<N, void> : public any_float32<N, mask_float32<N,void> > {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    typedef mask_float32v base_vector_type;
    typedef void expr_type;

    SIMDPP_INL mask_float32<N>() {}
    // SIMDPP_INL mask_float32<N>(const mask_float32<N> &) = default;
    // SIMDPP_INL mask_float32<N> &operator=(const mask_float32<N> &) = default;

    template<class E> SIMDPP_INL explicit mask_float32<N>(const mask_int32<N,E>& d)
    {
        *this = bit_cast<mask_float32<N> >(d.eval());
    }
    template<class E> SIMDPP_INL mask_float32<N>& operator=(const mask_int32<N,E>& d)
    {
        *this = bit_cast<mask_float32<N> >(d.eval()); return *this;
    }

    /// Access the underlying type
    SIMDPP_INL float32<N> unmask() const
    {
        float32<N> r;
        for (unsigned i = 0; i < mask_float32::vec_length; ++i) {
            r.vec(i) = d_[i].unmask();
        }
        return r;
    }

    SIMDPP_INL const mask_float32v& vec(unsigned i) const { return d_[i]; }
    SIMDPP_INL mask_float32v& vec(unsigned i)       { return d_[i]; }

    SIMDPP_INL mask_float32<N> eval() const { return *this; }

private:
    mask_float32v d_[mask_float32::vec_length];
};

/// @} -- end ingroup

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
