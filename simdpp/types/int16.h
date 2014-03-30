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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT16_H
#define LIBSIMDPP_SIMDPP_TYPES_INT16_H

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

/** Class representing an signed @a int16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int16<N, void> : public any_int16<N, int16<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int16_t;
    using base_vector_type = int16v;
    using expr_type = void;

    int16<N>() = default;
    int16<N>(const int16<N>&) = default;
    int16<N>& operator=(const int16<N>&) = default;

    template<class E> int16<N>(const int16<N,E>& d) { *this = d.eval(); }
    template<class E> int16<N>(const uint16<N,E>& d) { *this = d.eval(); }
    template<class V> explicit int16<N>(const any_vec<N*2,V>& d)
    {
        *this = bit_cast<int16<N>>(d.vec().eval());
    }
    template<class V> int16<N>& operator=(const any_vec<N*2,V>& d)
    {
        *this = bit_cast<int16<N>>(d.vec().eval()); return *this;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int16<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int16<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int16v& operator[](unsigned i) const { return d_[i]; }
    int16v& operator[](unsigned i)             { return d_[i]; }

    int16<N> eval() const { return *this; }

    static int16<N> zero() { return set_vec(int16v::zero()); }
    static int16<N> ones() { return set_vec(int16v::ones()); }

private:
    /// Creates a signed int16 vector with the contents set to copy of native
    /// register
    static int16<N> set_vec(int16v a)
    {
        int16<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

    int16v d_[int16::vec_length];
};

/** Class representing an unsigned @a int16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint16<N, void> : public any_int16<N, uint16<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint16_t;
    using base_vector_type = uint16v;
    using expr_type = void;

    uint16<N>() = default;
    uint16<N>(const uint16<N>&) = default;
    uint16<N>& operator=(const uint16<N>&) = default;

    template<class E> uint16<N>(const uint16<N,E>& d) { *this = d.eval(); }
    template<class E> uint16<N>(const int16<N,E>& d) { *this = d.eval(); }
    template<class V> explicit uint16<N>(const any_vec<N*2,V>& d)
    {
        *this = bit_cast<uint16<N>>(d.vec().eval());
    }
    template<class V> uint16<N>& operator=(const any_vec<N*2,V>& d)
    {
        *this = bit_cast<uint16<N>>(d.vec().eval()); return *this;
    }

    const uint16v& operator[](unsigned i) const { return d_[i]; }
    uint16v& operator[](unsigned i)             { return d_[i]; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint16<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint16<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    uint16<N> eval() const { return *this; }

    static uint16<N> zero() { return set_vec(uint16v::zero()); }
    static uint16<N> ones() { return set_vec(uint16v::ones()); }

private:
    /// Creates a unsigned int16 vector with the contents set to copy of native
    /// register
    static uint16<N> set_vec(uint16v a)
    {
        uint16<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

    uint16v d_[uint16::vec_length];
};

/// Class representing a mask for 16-bit integer vector of arbitrary
/// length.
template<unsigned N>
class mask_int16<N, void> : public any_int16<N, mask_int16<N,void>> {
public:    
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int16v;
    using expr_type = void;

    mask_int16<N>() = default;
    mask_int16<N>(const mask_int16<N> &) = default;
    mask_int16<N> &operator=(const mask_int16<N> &) = default;

    /// Access the underlying type
    uint16<N> unmask() const
    {
        uint16<N> r;
        for (unsigned i = 0; i < mask_int16::vec_length; ++i) {
            r[i] = d_[i].unmask();
        }
        return r;
    }

    const mask_int16v& operator[](unsigned i) const { return d_[i]; }
          mask_int16v& operator[](unsigned i)       { return d_[i]; }

    mask_int16<N> eval() const { return *this; }

private:
    mask_int16v d_[mask_int16::vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
