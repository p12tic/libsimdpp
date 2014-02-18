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

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/float64x4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_fp
/// @{

/** Class representing a @a float64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class float64 {
public:

    using element_type = double;
    using uint_element_type = uint64_t;
    using int_vector_type = gint64<N>;
    using uint_vector_type = uint64<N>;
    using base_vector_type = float64v;
    using mask_type = mask_float64<N>;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_FLOAT64_SIZE - 1) / SIMDPP_FAST_FLOAT64_SIZE;

    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    float64<N>() = default;
    float64<N>(const float64<N>&) = default;
    float64<N>& operator=(const float64<N>&) = default;

    /// @{
    /// Construct from compatible int64 integer vector type
    explicit float64<N>(gint64<N> d)
    {
        for (unsigned i = 0; i < vec_length; i++) {
            (*this)[i] = d[i];
        }
    }

    float64<N>& operator=(gint64<N> d)  { operator=(float64<N>(d)); return *this; }
    /// @}

    const float64v* begin() const   { return d_; }
    float64v* begin()               { return d_; }
    const float64v* end() const     { return d_+vec_length; }
    float64v* end()                 { return d_+vec_length; }
    const float64v& operator[](unsigned i) const { return *(d_+i); }
    float64v& operator[](unsigned i)             { return *(d_+i); }

    /** Creates a float64 vector with the contents set to zero

        @code
        r0 = 0.0f
        ...
        rN = 0.0f
        @endcode
    */
    static float64<N> zero()
    {
        return float64<N>::set_broadcast(float64v::zero());
    }

    /** Creates a double vector from a value loaded from memory.

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float64<N> load_broadcast(const double* v0)
    {
        return float64<N>::set_broadcast(float64v::load_broadcast(v0));
    }

    /** Creates a float vector from a value stored in a core register.

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float64<N> set_broadcast(double v0)
    {
        return float64<N>::set_broadcast(float64v::set_broadcast(v0));
    }

    /** Creates a float vector from a native vector

        @code
        r0 = v0
        ...
        rN = v0
        @endcode
    */
    static float64<N> set_broadcast(float64v v0)
    {
        float64<N> r;
        for (auto &v : r) v = v0;
        return r;
    }

    /** Creates a float64 vector from a value known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v0 v0 v0   ... ]
        @endcode
    */
    static float64x4 make_const(double v0)
    {
        return float64<N>::set_broadcast(float64v::make_const(v0));
    }

    /** Creates a float64 vector from two values known at compile-time

        @code
            | 0  1  2  3  | ... |
        r = [ v0 v1 v0 v1   ... ]
        @endcode
    */
    static float64x4 make_const(double v0, double v1)
    {
        return float64<N>::set_broadcast(float64v::make_const(v0, v1));
    }

private:
    float64v d_[vec_length];
};

/// Class representing a mask for 64-bit floating point vector of arbitrary
/// length. The vector always contains at least one native vector.
template<unsigned N>
class mask_float64 {
public:
    using base_vector_type = mask_float64v;
    static constexpr unsigned length = 8;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_FLOAT64_SIZE - 1) / SIMDPP_FAST_FLOAT64_SIZE;

    mask_float64<N>() = default;
    mask_float64<N>(const mask_float64 &) = default;
    mask_float64<N> &operator=(const mask_float64 &) = default;

    const mask_float64v* begin() const   { return d_; }
    mask_float64v* begin()               { return d_; }
    const mask_float64v* end() const     { return d_+vec_length; }
    mask_float64v* end()                 { return d_+vec_length; }
    const mask_float64v& operator[](unsigned i) const { return *(d_+i); }
    mask_float64v& operator[](unsigned i)             { return *(d_+i); }

    /// Convert to a regular vector
    operator float64<N>() const
    {
        float64<N> r;
        for (unsigned i = 0; i < vec_length; ++i) {
            r[i] = d_[i];
        }
        return r;
    }

private:
    mask_float64v d_[vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
