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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32_H
#define LIBSIMDPP_SIMDPP_TYPES_INT32_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing an signed @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int32<N, void> : public any_int32<N, int32<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int32_t;
    using base_vector_type = int32v;
    using expr_type = void;

    int32<N>() = default;
    int32<N>(const int32<N>&) = default;
    int32<N>& operator=(const int32<N>&) = default;

    template<class E> int32<N>(const int32<N,E>& d) { *this = d.eval(); }
    template<class E> int32<N>(const uint32<N,E>& d) { *this = d.eval(); }
    template<class V> explicit int32<N>(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<int32<N>>(d.vec().eval());
    }
    template<class V> int32<N>& operator=(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<int32<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int32v& operator[](unsigned i) const { return d_[i]; }
    int32v& operator[](unsigned i)             { return d_[i]; }

    int32<N> eval() const { return *this; }

    static int32<N> zero() { return set_vec(int32v::zero()); }
    static int32<N> ones() { return set_vec(int32v::ones()); }

private:
    /// Creates a signed int32 vector with the contents set to copy of native
    /// register
    static int32<N> set_vec(int32v a)
    {
        int32<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

    int32v d_[int32::vec_length];
};

/** Class representing an unsigned @a int32 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint32<N, void> : public any_int32<N, uint32<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint32_t;
    using base_vector_type = uint32v;
    using expr_type = void;

    uint32<N>() = default;
    uint32<N>(const uint32<N>&) = default;
    uint32<N>& operator=(const uint32<N>&) = default;

    template<class E> uint32<N>(const uint32<N,E>& d) { *this = d.eval(); }
    template<class E> uint32<N>(const int32<N,E>& d) { *this = d.eval(); }
    template<class V> explicit uint32<N>(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<uint32<N>>(d.vec().eval());
    }
    template<class V> uint32<N>& operator=(const any_vec<N*4,V>& d)
    {
        *this = bit_cast<uint32<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint32<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint32<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const uint32v& operator[](unsigned i) const { return d_[i]; }
    uint32v& operator[](unsigned i)             { return d_[i]; }

    uint32<N> eval() const { return *this; }

    static uint32<N> zero() { return set_vec(uint32v::zero()); }
    static uint32<N> ones() { return set_vec(uint32v::ones()); }

private:
    /// Creates a unsigned int32 vector with the contents set to copy of native
    /// register
    static uint32<N> set_vec(uint32v a)
    {
        uint32<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

    uint32v d_[uint32::vec_length];
};


/// Class representing a mask for 32-bit integer vector of arbitrary
/// length.
template<unsigned N>
class mask_int32<N, void> : public any_int32<N, mask_int32<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int32v;
    using expr_type = void;

    mask_int32<N>() = default;
    mask_int32<N>(const mask_int32<N> &) = default;
    mask_int32<N> &operator=(const mask_int32<N> &) = default;

    /// Access the underlying type
    uint32<N> unmask() const
    {
        uint32<N> r;
        for (unsigned i = 0; i < mask_int32::vec_length; ++i) {
            r[i] = d_[i].unmask();
        }
        return r;
    }

    const mask_int32v& operator[](unsigned i) const { return d_[i]; }
          mask_int32v& operator[](unsigned i)       { return d_[i]; }

    mask_int32<N> eval() const { return *this; }

private:
    mask_int32v d_[mask_int32::vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
