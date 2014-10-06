/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/float64x4.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/** Class representing a @a float64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class float64<N, void> : public any_float64<N, float64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using element_type = double;
    using base_vector_type = float64v;
    using expr_type = void;

    float64<N>() = default;
    float64<N>(const float64<N>&) = default;
    float64<N>& operator=(const float64<N>&) = default;

    template<class E> SIMDPP_INL float64<N>(const float64<N,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit float64<N>(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<float64<N>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL float64<N>& operator=(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<float64<N>>(d.wrapped().eval()); return *this;
    }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL float64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL float64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const float64v& vec(unsigned i) const { return d_[i]; }
    float64v& vec(unsigned i)             { return d_[i]; }

    float64<N> eval() const { return *this; }

    /** Creates a float64 vector with the contents set to zero

        @code
        r0 = 0.0f
        ...
        rN = 0.0f
        @endcode
    */
    static float64<N> zero()
    {
        return set_vec(float64v::zero());
    }

private:
    /** Creates a float vector from a native vector

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float64<N> set_vec(float64v v0)
    {
        float64<N> r;
        for (unsigned i = 0; i < r.vec_length; i++) r.vec(i) = v0;
        return r;
    }

    float64v d_[float64::vec_length];
};

/// Class representing possibly optimized mask data for 2x 64-bit floating point
/// vector
template<unsigned N>
class mask_float64<N, void> : public any_float64<N, mask_float64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float64v;
    using expr_type = void;

    mask_float64<N>() = default;
    mask_float64<N>(const mask_float64<N> &) = default;
    mask_float64<N> &operator=(const mask_float64<N> &) = default;

    template<class E> SIMDPP_INL explicit mask_float64<N>(const mask_int64<N,E>& d)
    {
        *this = bit_cast<mask_float64<N>>(d.eval());
    }
    template<class E> SIMDPP_INL mask_float64<N>& operator=(const mask_int64<N,E>& d)
    {
        *this = bit_cast<mask_float64<N>>(d.eval()); return *this;
    }

    /// Access the underlying type
    float64<N> unmask() const
    {
        float64<N> r;
        for (unsigned i = 0; i < mask_float64::vec_length; ++i) {
            r.vec(i) = d_[i].unmask();
        }
        return r;
    }

    const mask_float64v& vec(unsigned i) const { return d_[i]; }
          mask_float64v& vec(unsigned i)       { return d_[i]; }

    mask_float64<N> eval() const { return *this; }

private:
    mask_float64v d_[mask_float64::vec_length];
};

/// @} -- end ingroup

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
