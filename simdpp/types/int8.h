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
class gint8 {
public:

    using element_type = int8_t;
    using uint_element_type = uint8_t;
    using int_vector_type = gint8<N>;
    using uint_vector_type = uint8<N>;
    using mask_type = mask_int8<N>;
    using base_vector_type = gint8v;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT8_SIZE - 1) / SIMDPP_FAST_INT8_SIZE;

    static constexpr unsigned num_bits = 8;
    static constexpr uint_element_type all_bits = 0xff;

    gint8<N>() = default;
    gint8<N>(const gint8<N>&) = default;
    gint8<N>& operator=(const gint8<N>&) = default;

    gint8<N>(const gint16<N/2>& d);
    gint8<N>(const gint32<N/4>& d);
    gint8<N>(const gint64<N/8>& d);
    gint8<N>& operator=(const gint16<N/2>& d);
    gint8<N>& operator=(const gint32<N/4>& d);
    gint8<N>& operator=(const gint64<N/8>& d);

    const gint8v* begin() const   { return du_; }
    gint8v* begin()               { return du_; }
    const gint8v* end() const     { return du_+vec_length; }
    gint8v* end()                 { return du_+vec_length; }
    const gint8v& operator[](unsigned i) const { return *(du_+i); }
    gint8v& operator[](unsigned i)             { return *(du_+i); }

    /// Creates a int8 vector with the contents set to zero
    static gint8<N> zero()
    {
        return set_broadcast(gint8v::zero());
    }

    /// Creates a int8 vector with the contents set to ones
    static gint8<N> ones()
    {
        return set_broadcast(gint8v::ones());
    }

    /// Creates a int8 vector with the contents set to copy of native register
    static gint8<N> set_broadcast(gint8v a)
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
class int8 : public gint8<N> {
public:

    using element_type = int8_t;
    using gint8<N>::vec_length;
    using base_vector_type = int8v;

    int8<N>() = default;
    int8<N>(const int8<N>&) = default;
    int8<N>& operator=(const int8<N>&) = default;

    int8<N>(const gint8<N>& d);
    int8<N>(const gint16<N/2>& d);
    int8<N>(const gint32<N/4>& d);
    int8<N>(const gint64<N/8>& d);
    int8<N>& operator=(const gint8<N>& d);
    int8<N>& operator=(const gint16<N/2>& d);
    int8<N>& operator=(const gint32<N/4>& d);
    int8<N>& operator=(const gint64<N/8>& d);

    const int8v* begin() const { return gint8<N>::di_; }
    int8v* begin()             { return gint8<N>::di_; }
    const int8v* end() const   { return gint8<N>::di_+vec_length; }
    int8v* end()               { return gint8<N>::di_+vec_length; }
    const int8v& operator[](unsigned i) const { return *(gint8<N>::di_+i); }
    int8v& operator[](unsigned i)             { return *(gint8<N>::di_+i); }

    /** Creates a signed int8 vector from a value loaded from memory.

        @code
            | 0  1  2  ... 15  | ... |
        r = [ v0 v0 v0 ... v0   ... ]
        @endcode
    */
    static int8<N> load_broadcast(const int8_t* v0)
    {
        return set_broadcast(int8v::load_broadcast(v0));
    }

    /** Creates a signed int8 vector from a value stored in a core register.

        @code
            | 0  1  2  ...  15  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static int8<N> set_broadcast(int8_t v0)
    {
        return set_broadcast(int8v::set_broadcast(v0));
    }

    /** Creates a signed int8 vector from a value known at compile-time

        @code
            | 0  1  2  ...  15  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0)
    {
        return set_broadcast(int8v::make_const(v0));
    }

    /** Creates a signed int8 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 15  | ... |
        r = [ v0 v1 v0 v1 ... v1   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0, int8_t v1)
    {
        return set_broadcast(int8v::make_const(v0, v1));
    }

    /** Creates a signed int8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  ... 15  | ... |
        r = [ v0 v1 v2 v3 v0 ... v3   ... ]
        @endcode
    */
    static int8<N> make_const(int8_t v0, int8_t v1, int8_t v2, int8_t v3)
    {
        return set_broadcast(int8v::make_const(v0, v1, v2, v3));
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
        return set_broadcast(int8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7));
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
        return set_broadcast(int8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                                v8, v9, v10,v11,v12,v13,v14,v15));
    }

    /// Creates a signed int8 vector with the contents set to copy of native
    /// register
    static int8<N> set_broadcast(int8v a)
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
class uint8 : public gint8<N> {
public:

    using element_type = uint8_t;
    using gint8<N>::vec_length;
    using base_vector_type = uint8v;

    uint8<N>() = default;
    uint8<N>(const uint8<N>&) = default;
    uint8<N>& operator=(const uint8<N>&) = default;

    uint8<N>(const gint8<N>& d);
    uint8<N>(const gint16<N/2>& d);
    uint8<N>(const gint32<N/4>& d);
    uint8<N>(const gint64<N/8>& d);
    uint8<N>& operator=(const gint8<N>& d);
    uint8<N>& operator=(const gint16<N/2>& d);
    uint8<N>& operator=(const gint32<N/4>& d);
    uint8<N>& operator=(const gint64<N/8>& d);

    const uint8v* begin() const { return gint8<N>::du_; }
    uint8v* begin()             { return gint8<N>::du_; }
    const uint8v* end() const   { return gint8<N>::du_+vec_length; }
    uint8v* end()               { return gint8<N>::du_+vec_length; }
    const uint8v& operator[](unsigned i) const { return *(gint8<N>::du_+i); }
    uint8v& operator[](unsigned i)             { return *(gint8<N>::du_+i); }

    /** Creates a unsigned int8 vector from a value loaded from memory.

        @code
            | 0  1  2  ... 15  | ... |
        r = [ v0 v0 v0 ... v0   ... ]
        @endcode
    */
    static uint8<N> load_broadcast(const uint8_t* v0)
    {
        return set_broadcast(uint8v::load_broadcast(v0));
    }

    /** Creates a unsigned int8 vector from a value stored in a core register.

        @code
            | 0  1  2  ...  15  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static uint8<N> set_broadcast(uint8_t v0)
    {
        return set_broadcast(uint8v::set_broadcast(v0));
    }

    /** Creates a unsigned int8 vector from a value known at compile-time

        @code
            | 0  1  2  ...  15  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0)
    {
        return set_broadcast(uint8v::make_const(v0));
    }

    /** Creates a unsigned int8 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 15  | ... |
        r = [ v0 v1 v0 v1 ... v1   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0, uint8_t v1)
    {
        return set_broadcast(uint8v::make_const(v0, v1));
    }

    /** Creates a unsigned int8 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  ... 15  | ... |
        r = [ v0 v1 v2 v3 v0 ... v3   ... ]
        @endcode
    */
    static uint8<N> make_const(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3)
    {
        return set_broadcast(uint8v::make_const(v0, v1, v2, v3));
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
        return set_broadcast(uint8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7));
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
        return set_broadcast(uint8v::make_const(v0, v1, v2, v3, v4, v5, v6, v7,
                                                v8, v9, v10,v11,v12,v13,v14,v15));
    }

    /// Creates a unsigned int8 vector with the contents set to copy of native
    /// register
    static uint8<N> set_broadcast(uint8v a)
    {
        uint8<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }
};

/// Class representing a mask for @a gint8 vector of arbitrary length. The
/// vector always contains at least one native vector.
template<unsigned N>
class mask_int8 {
public:
    using base_vector_type = mask_int8v;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT8_SIZE - 1) / SIMDPP_FAST_INT8_SIZE;

    mask_int8<N>() = default;
    mask_int8<N>(const mask_int8 &) = default;
    mask_int8<N> &operator=(const mask_int8 &) = default;

    const mask_int8v* begin() const   { return d_; }
    mask_int8v* begin()               { return d_; }
    const mask_int8v* end() const     { return d_+vec_length; }
    mask_int8v* end()                 { return d_+vec_length; }
    const mask_int8v& operator[](unsigned i) const { return *(d_+i); }
    mask_int8v& operator[](unsigned i)             { return *(d_+i); }

    /// Convert to a regular vector
    operator gint8<N>() const
    {
        gint8<N> r;
        for (unsigned i = 0; i < vec_length; ++i) {
            r[i] = d_[i];
        }
        return r;
    }

private:
    mask_int8v d_[vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
