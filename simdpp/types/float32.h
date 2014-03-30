/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/** Class representing a @a float32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class float32<N, void> : public any_float32<N, float32<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using expr_type = void;
    using element_type = float;
    using base_vector_type = float32v;

    float32<N>() = default;
    float32<N>(const float32<N>&) = default;
    float32<N>& operator=(const float32<N>&) = default;

    template<class E> float32<N>(const float32<N,E>& d) { *this = d.eval(); }
    template<class V> explicit float32<N>(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<float32<N>>(d.vec().eval());
    }
    template<class V> float32<N>& operator=(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<float32<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> float32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> float32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const float32v& operator[](unsigned i) const { return d_[i]; }
    float32v& operator[](unsigned i)             { return d_[i]; }

    float32<N> eval() const { return *this; }

    /** Creates a float32 vector with the contents set to zero

        @code
        r0 = 0.0f
        ...
        rN = 0.0f
        @endcode
    */
    static float32<N> zero()
    {
        return set_vec(float32v::zero());
    }

private:
    /** Creates a float vector from a native vector

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float32<N> set_vec(float32v v0)
    {
        float32<N> r;
        for (unsigned i = 0; i < r.vec_length; i++) r[i] = v0;
        return r;
    }

    float32v d_[float32::vec_length];
};


/// Class representing a mask for 32-bit floating-point vector of arbitrary
/// length.
template<unsigned N>
class mask_float32<N, void> : public any_float32<N, mask_float32<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float32v;
    using expr_type = void;

    mask_float32<N>() = default;
    mask_float32<N>(const mask_float32<N> &) = default;
    mask_float32<N> &operator=(const mask_float32<N> &) = default;

    /// Access the underlying type
    float32<N> unmask() const
    {
        float32<N> r;
        for (unsigned i = 0; i < mask_float32::vec_length; ++i) {
            r[i] = d_[i].unmask();
        }
        return r;
    }

    const mask_float32v& operator[](unsigned i) const { return d_[i]; }
          mask_float32v& operator[](unsigned i)       { return d_[i]; }

    mask_float32<N> eval() const { return *this; }

private:
    mask_float32v d_[mask_float32::vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
