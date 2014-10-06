/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64_H
#define LIBSIMDPP_SIMDPP_TYPES_INT64_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing an signed @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int64<N, void> : public any_int64<N, int64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_INT;
    using element_type = int64_t;
    using base_vector_type = int64v;
    using expr_type = void;

    int64<N>() = default;
    int64<N>(const int64<N>&) = default;
    int64<N>& operator=(const int64<N>&) = default;

    template<class E> SIMDPP_INL int64<N>(const int64<N,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL int64<N>(const uint64<N,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit int64<N>(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<int64<N>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL int64<N>& operator=(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<int64<N>>(d.wrapped().eval()); return *this;
    }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL int64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL int64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int64v& vec(unsigned i) const { return d_[i]; }
    int64v& vec(unsigned i)             { return d_[i]; }

    int64<N> eval() const { return *this; }

    static int64<N> zero() { return set_vec(int64v::zero()); }
    static int64<N> ones() { return set_vec(int64v::ones()); }

private:

    /// Creates a signed int64 vector with the contents set to copy of native
    /// register
    static int64<N> set_vec(int64v a)
    {
        int64<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }

private:
    int64v d_[int64::vec_length];
};

/** Class representing an unsigned @a int64 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint64<N, void> : public any_int64<N, uint64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_UINT;
    using element_type = uint64_t;
    using base_vector_type = uint64v;
    using expr_type = void;

    uint64<N>() = default;
    uint64<N>(const uint64<N>&) = default;
    uint64<N>& operator=(const uint64<N>&) = default;

    template<class E> SIMDPP_INL uint64<N>(const uint64<N,E>& d) { *this = d.eval(); }
    template<class E> SIMDPP_INL uint64<N>(const int64<N,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit uint64<N>(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<uint64<N>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL uint64<N>& operator=(const any_vec<N*8,V>& d)
    {
        *this = bit_cast<uint64<N>>(d.wrapped().eval()); return *this;
    }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL uint64<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL uint64<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const uint64v& vec(unsigned i) const { return d_[i]; }
    uint64v& vec(unsigned i)             { return d_[i]; }

    uint64<N> eval() const { return *this; }

    static uint64<N> zero() { return set_vec(uint64v::zero()); }
    static uint64<N> ones() { return set_vec(uint64v::ones()); }

private:
    /// Creates a unsigned int64 vector with the contents set to copy of native
    /// register
    static uint64<N> set_vec(uint64v a)
    {
        uint64<N> r;
        for (auto& v : r.d_) {
            v = a;
        }
        return r;
    }
private:
    uint64v d_[uint64::vec_length];
};

/// Class representing a mask for 64-bit integer vector of arbitrary
/// length.
template<unsigned N>
class mask_int64<N, void> : public any_int64<N, mask_int64<N,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_INT;
    using base_vector_type = mask_int64v;
    using expr_type = void;

    mask_int64<N>() = default;
    mask_int64<N>(const mask_int64<N> &) = default;
    mask_int64<N> &operator=(const mask_int64<N> &) = default;

    template<class E> SIMDPP_INL explicit mask_int64<N>(const mask_float64<N,E>& d)
    {
        *this = bit_cast<mask_int64<N>>(d.eval());
    }
    template<class E> SIMDPP_INL mask_int64<N>& operator=(const mask_float64<N,E>& d)
    {
        *this = bit_cast<mask_int64<N>>(d.eval()); return *this;
    }

    /// Access the underlying type
    uint64<N> unmask() const
    {
        uint64<N> r;
        for (unsigned i = 0; i < mask_int64::vec_length; ++i) {
            r.vec(i) = d_[i].unmask();
        }
        return r;
    }

    const mask_int64v& vec(unsigned i) const { return d_[i]; }
          mask_int64v& vec(unsigned i)       { return d_[i]; }

    mask_int64<N> eval() const { return *this; }

private:
    mask_int64v d_[mask_int64::vec_length];
};

/// @} -- end ingroup

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
