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

#include <simdpp/types.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @ingroup simd_vec_int
/// @{

/** Class representing a @a gint16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class gint16<N, void> {
public:

    using element_type = int16_t;
    using uint_element_type = uint16_t;
    using int_vector_type = gint16<N>;
    using uint_vector_type = uint16<N>;
    using mask_type = mask_int16<N>;
    using base_vector_type = gint16v;
    using maskdata_type = maskdata_int16<N>;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT16_SIZE - 1) / SIMDPP_FAST_INT16_SIZE;

    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;

    gint16<N>() = default;
    gint16<N>(const gint16<N>&) = default;
    gint16<N>& operator=(const gint16<N>&) = default;

    template<class E> explicit gint16<N>(const  gint8<N*2,E>& d);
    template<class E>          gint16<N>(const gint16<N,E>& d);
    template<class E> explicit gint16<N>(const gint32<N/2,E>& d);
    template<class E> explicit gint16<N>(const gint64<N/4,E>& d);
    template<class E> gint16<N>& operator=(const  gint8<N*2,E>& d);
    template<class E> gint16<N>& operator=(const gint16<N,E>& d);
    template<class E> gint16<N>& operator=(const gint32<N/2,E>& d);
    template<class E> gint16<N>& operator=(const gint64<N/4,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint16<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint16<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const gint16v& operator[](unsigned i) const { return *(du_+i); }
    gint16v& operator[](unsigned i)             { return *(du_+i); }

    gint16<N> eval() const { return *this; }

    /// Creates a int16 vector with the contents set to zero
    static gint16<N> zero()
    {
        return set_vec(gint16v::zero());
    }

    /// Creates a int16 vector with the contents set to ones
    static gint16<N> ones()
    {
        return set_vec(gint16v::ones());
    }

protected:

    /// Creates a int16 vector with the contents set to copy of native register
    static gint16<N> set_vec(gint16v a)
    {
        gint16<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }

    union {
        uint16v du_[vec_length];
        int16v di_[vec_length];
    };
};


/** Class representing an signed @a int16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int16<N, void> : public gint16<N, void> {
public:

    using element_type = int16_t;
    using gint16<N>::vec_length;
    using base_vector_type = int16v;

    int16<N>() = default;
    int16<N>(const int16<N>&) = default;
    int16<N>& operator=(const int16<N>&) = default;

    template<class E> explicit int16<N>(const  gint8<N*2,E>& d);
    template<class E>          int16<N>(const gint16<N,E>& d);
    template<class E> explicit int16<N>(const gint32<N/2,E>& d);
    template<class E> explicit int16<N>(const gint64<N/4,E>& d);
    template<class E> int16<N>& operator=(const  gint8<N*2,E>& d);
    template<class E> int16<N>& operator=(const gint16<N,E>& d);
    template<class E> int16<N>& operator=(const gint32<N/2,E>& d);
    template<class E> int16<N>& operator=(const gint64<N/4,E>& d);

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

    const int16v& operator[](unsigned i) const { return *(gint16<N>::di_+i); }
    int16v& operator[](unsigned i)             { return *(gint16<N>::di_+i); }

    int16<N> eval() const { return *this; }

    static int16<N> zero() { return gint16<N>::zero(); }
    static int16<N> ones() { return gint16<N>::ones(); }
};

/** Class representing an unsigned @a int16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint16<N, void> : public gint16<N, void> {
public:

    using element_type = uint16_t;
    using gint16<N>::vec_length;
    using base_vector_type = uint16v;

    uint16<N>() = default;
    uint16<N>(const uint16<N>&) = default;
    uint16<N>& operator=(const uint16<N>&) = default;

    template<class E> explicit uint16<N>(const  gint8<N*2,E>& d);
    template<class E>          uint16<N>(const gint16<N,E>& d);
    template<class E> explicit uint16<N>(const gint32<N/2,E>& d);
    template<class E> explicit uint16<N>(const gint64<N/4,E>& d);
    template<class E> uint16<N>& operator=(const  gint8<N*2,E>& d);
    template<class E> uint16<N>& operator=(const gint16<N,E>& d);
    template<class E> uint16<N>& operator=(const gint32<N/2,E>& d);
    template<class E> uint16<N>& operator=(const gint64<N/4,E>& d);

    const uint16v& operator[](unsigned i) const { return *(gint16<N>::du_+i); }
    uint16v& operator[](unsigned i)             { return *(gint16<N>::du_+i); }

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

    static uint16<N> zero() { return gint16<N>::zero(); }
    static uint16<N> ones() { return gint16<N>::ones(); }
};

/// Class representing possibly optimized mask data for arbitrary length 16-bit
/// integer vector
template<unsigned N>
class maskdata_int16 {
public:
    using base_vector_type = maskdata_int16<N>;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = int16<N>::vec_length;

    maskdata_int16<N>() = default;
    maskdata_int16<N>(const maskdata_int16<N> &) = default;
    maskdata_int16<N> &operator=(const maskdata_int16<N> &) = default;

    /// Access the underlying type
    operator uint16<N>() const;

    const maskdata_int16v& operator[](unsigned i) const { return *(d_+i); }
          maskdata_int16v& operator[](unsigned i)       { return *(d_+i); }

    mask_int16<N> eval() const { return *this; }

private:
    maskdata_int16v d_[vec_length];
};


/// Class representing a mask for 16-bit integer point vector of arbitrary
/// length.
template<unsigned N>
class mask_int16<N, void> : public uint16<N, void> {
public:    
    mask_int16<N>() = default;
    mask_int16<N>(const mask_int16<N> &) = default;
    mask_int16<N> &operator=(const mask_int16<N> &) = default;
    mask_int16<N>(const maskdata_int16<N>& d);

    mask_int16<N> eval() const { return *this; }

    maskdata_int16<N> mask() const { return mask_; }
private:
    maskdata_int16<N> mask_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
