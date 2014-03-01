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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT8_H
#define LIBSIMDPP_SIMDPP_TYPES_INT8_H

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

/** Class representing a @a gint8 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class gint8<N, void> {
public:

    using element_type = int8_t;
    using uint_element_type = uint8_t;
    using int_vector_type = gint8<N>;
    using uint_vector_type = uint8<N>;
    using base_vector_type = gint8v;
    using mask_type = mask_int8<N>;
    using maskdata_type = maskdata_int8<N>;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT8_SIZE - 1) / SIMDPP_FAST_INT8_SIZE;

    static constexpr unsigned num_bits = 8;
    static constexpr uint_element_type all_bits = 0xff;

    gint8<N>() = default;
    gint8<N>(const gint8<N>&) = default;
    gint8<N>& operator=(const gint8<N>&) = default;

    template<class E>          gint8<N>(const  gint8<N,E>& d);
    template<class E> explicit gint8<N>(const gint16<N/2,E>& d);
    template<class E> explicit gint8<N>(const gint32<N/4,E>& d);
    template<class E> explicit gint8<N>(const gint64<N/8,E>& d);
    template<class E> gint8<N>& operator=(const  gint8<N,E>& d);
    template<class E> gint8<N>& operator=(const gint16<N/2,E>& d);
    template<class E> gint8<N>& operator=(const gint32<N/4,E>& d);
    template<class E> gint8<N>& operator=(const gint64<N/8,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> gint8<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> gint8<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const gint8v& operator[](unsigned i) const { return *(du_+i); }
    gint8v& operator[](unsigned i)             { return *(du_+i); }

    gint8<N> eval() const { return *this; }

    /// Creates a int8 vector with the contents set to zero
    static gint8<N> zero()
    {
        return set_vec(gint8v::zero());
    }

    /// Creates a int8 vector with the contents set to ones
    static gint8<N> ones()
    {
        return set_vec(gint8v::ones());
    }

private:
    /// Creates a int8 vector with the contents set to copy of native register
    static gint8<N> set_vec(gint8v a)
    {
        gint8<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }

protected:
    union {
        uint8v du_[vec_length];
        int8v di_[vec_length];
    };
};


/** Class representing an signed @a int8 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int8<N, void> : public gint8<N, void> {
public:

    using element_type = int8_t;
    using gint8<N>::vec_length;
    using base_vector_type = int8v;

    int8<N>() = default;
    int8<N>(const int8<N>&) = default;
    int8<N>& operator=(const int8<N>&) = default;

    template<class E>          int8<N>(const  gint8<N,E>& d);
    template<class E> explicit int8<N>(const gint16<N/2,E>& d);
    template<class E> explicit int8<N>(const gint32<N/4,E>& d);
    template<class E> explicit int8<N>(const gint64<N/8,E>& d);
    template<class E> int8<N>& operator=(const  gint8<N,E>& d);
    template<class E> int8<N>& operator=(const gint16<N/2,E>& d);
    template<class E> int8<N>& operator=(const gint32<N/4,E>& d);
    template<class E> int8<N>& operator=(const gint64<N/8,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> int8<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> int8<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const int8v& operator[](unsigned i) const { return *(gint8<N>::di_+i); }
    int8v& operator[](unsigned i)             { return *(gint8<N>::di_+i); }

    int8<N> eval() const { return *this; }

    static int8<N> zero() { return gint8<N>::zero(); }
    static int8<N> ones() { return gint8<N>::ones(); }

    /** Creates a signed int8 vector from a value known at compile-time

        @code
            | 0  1  2  ...  15  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0)
    {
        return set_vec(int8v::make_const(v0));
    }

    /** Creates a signed int8 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 15  | ... |
        r = [ v0 v1 v0 v1 ... v1   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0, int8_t v1)
    {
        return set_vec(int8v::make_const(v0, v1));
    }

    /** Creates a signed int8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  ... 15  | ... |
        r = [ v0 v1 v2 v3 v0 ... v3   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3)
    {
        return set_vec(int8v::make_const(v0, v1, v2, v3));
    }

    /** Creates a signed int8 vector from eight values known at compile-time

        @code
            | 0  1  2  ... 7  8  ... 15 | ... |
        r = [ v0 v1 v2 ... v7 v0 ... v7   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                              int8_t v4, int8_t v5, int8_t v6, int8_t v7)
    {
        return set_vec(int8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7));
    }

    /** Creates a signed int8 vector from sixteen values known at compile-time

        @code
            | 0  1  2  ... 15  | ... |
        r = [ v0 v1 v2 ... v15   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3,
                               int8_t v4, int8_t v5, int8_t v6, int8_t v7,
                               int8_t v8, int8_t v9, int8_t v10, int8_t v11,
                               int8_t v12, int8_t v13, int8_t v14, int8_t v15)
    {
        return set_vec(int8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                         v8, v9, v10,v11,v12,v13,v14,v15));
    }

private:
    /// Creates a signed int8 vector with the contents set to copy of native
    /// register
    static int8<N> set_vec(int8v a)
    {
        int8<N> r;
        for (auto& v : r.di_) {
            v = a;
        }
        return r;
    }
};

/** Class representing an unsigned @a int8 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint8<N, void> : public gint8<N, void> {
public:

    using element_type = uint8_t;
    using gint8<N>::vec_length;
    using base_vector_type = uint8v;

    uint8<N>() = default;
    uint8<N>(const uint8<N>&) = default;
    uint8<N>& operator=(const uint8<N>&) = default;

    template<class E>          uint8<N>(const  gint8<N,E>& d);
    template<class E> explicit uint8<N>(const gint16<N/2,E>& d);
    template<class E> explicit uint8<N>(const gint32<N/4,E>& d);
    template<class E> explicit uint8<N>(const gint64<N/8,E>& d);
    template<class E> uint8<N>& operator=(const  gint8<N,E>& d);
    template<class E> uint8<N>& operator=(const gint16<N/2,E>& d);
    template<class E> uint8<N>& operator=(const gint32<N/4,E>& d);
    template<class E> uint8<N>& operator=(const gint64<N/8,E>& d);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template<class E> uint8<N>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> uint8<N>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    const uint8v& operator[](unsigned i) const { return *(gint8<N>::du_+i); }
    uint8v& operator[](unsigned i)             { return *(gint8<N>::du_+i); }

    uint8<N> eval() const { return *this; }

    static uint8<N> zero() { return gint8<N>::zero(); }
    static uint8<N> ones() { return gint8<N>::ones(); }

    /** Creates a unsigned int8 vector from a value known at compile-time

        @code
            | 0  1  2  ...  15  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0)
    {
        return set_vec(uint8v::make_const(v0));
    }

    /** Creates a unsigned int8 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 15  | ... |
        r = [ v0 v1 v0 v1 ... v1   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0, uint8_t v1)
    {
        return set_vec(uint8v::make_const(v0, v1));
    }

    /** Creates a unsigned int8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  ... 15  | ... |
        r = [ v0 v1 v2 v3 v0 ... v3   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3)
    {
        return set_vec(uint8v::make_const(v0, v1, v2, v3));
    }

    /** Creates a unsigned int8 vector from eight values known at compile-time

        @code
            | 0  1  2  ... 7  8  ... 15 | ... |
        r = [ v0 v1 v2 ... v7 v0 ... v7   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7)
    {
        return set_vec(uint8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7));
    }

    /** Creates a unsigned int8 vector from sixteen values known at compile-time

        @code
            | 0  1  2  ... 15  | ... |
        r = [ v0 v1 v2 ... v15   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3,
                               uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7,
                               uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11,
                               uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15)
    {
        return set_vec(uint8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                          v8, v9, v10,v11,v12,v13,v14,v15));
    }

private:
    /// Creates a unsigned int8 vector with the contents set to copy of native
    /// register
    static uint8<N> set_vec(uint8v a)
    {
        uint8<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }
};

/// Class representing possibly optimized mask data for arbitrary length 8-bit
/// integer vector
template<unsigned N>
class maskdata_int8 {
public:
    using base_vector_type = maskdata_int8<N>;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = uint8<N>::vec_length;

    maskdata_int8<N>() = default;
    maskdata_int8<N>(const maskdata_int8<N> &) = default;
    maskdata_int8<N> &operator=(const maskdata_int8<N> &) = default;

    /// Convert to bitmask
    operator uint8<N>() const;

    const maskdata_int8v& operator[](unsigned i) const { return *(d_+i); }
          maskdata_int8v& operator[](unsigned i)       { return *(d_+i); }

    mask_int8<N> eval() const { return *this; }

private:
    maskdata_int8v d_[vec_length];
};


/// Class representing a mask for 8-bit integer point vector of arbitrary
/// length.
template<unsigned N>
class mask_int8<N, void> : public uint8<N, void> {
public:
    mask_int8<N>() = default;
    mask_int8<N>(const mask_int8<N> &) = default;
    mask_int8<N> &operator=(const mask_int8<N> &) = default;
    mask_int8<N>(const maskdata_int8<N>& d);

    mask_int8<N> eval() const { return *this; }

    maskdata_int8<N> mask() const { return mask_; }

private:
    maskdata_int8<N> mask_;
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
