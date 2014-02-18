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
class gint16 {
public:

    using element_type = int16_t;
    using uint_element_type = uint16_t;
    using int_vector_type = gint16<N>;
    using uint_vector_type = uint16<N>;
    using mask_type = mask_int16<N>;

    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT16_SIZE - 1) / SIMDPP_FAST_INT16_SIZE;

    static constexpr unsigned num_bits = 16;
    static constexpr uint_element_type all_bits = 0xffff;

    gint16<N>() = default;
    gint16<N>(const gint16<N>&) = default;
    gint16<N>& operator=(const gint16<N>&) = default;

    gint16<N>(const gint8<N*2>& d);
    gint16<N>(const gint32<N/2>& d);
    gint16<N>(const gint64<N/4>& d);
    gint16<N>& operator=(const gint8<N*2>& d);
    gint16<N>& operator=(const gint32<N/2>& d);
    gint16<N>& operator=(const gint64<N/4>& d);

    const gint16v* begin() const   { return du_; }
    gint16v* begin()               { return du_; }
    const gint16v* end() const     { return du_+vec_length; }
    gint16v* end()                 { return du_+vec_length; }
    const gint16v& operator[](unsigned i) const { return *(du_+i); }
    gint16v& operator[](unsigned i)             { return *(du_+i); }

    /// Creates a int16 vector with the contents set to zero
    static gint16<N> zero()
    {
        return set_broadcast(gint16v::zero());
    }

    /// Creates a int16 vector with the contents set to ones
    static gint16<N> ones()
    {
        return set_broadcast(gint16v::ones());
    }

    /// Creates a int16 vector with the contents set to copy of native register
    static gint16<N> set_broadcast(gint16v a)
    {
        gint16<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }

protected:
    union {
        uint16v du_[vec_length];
        int16v di_[vec_length];
    };
};


/** Class representing an signed @a int16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class int16 : public gint16<N> {
public:

    using element_type = int16_t;
    using gint16<N>::vec_length;

    int16<N>() = default;
    int16<N>(const int16<N>&) = default;
    int16<N>& operator=(const int16<N>&) = default;

    int16<N>(const gint8<N*2>& d);
    int16<N>(const gint16<N>& d);
    int16<N>(const gint32<N/2>& d);
    int16<N>(const gint64<N/4>& d);
    int16<N>& operator=(const gint8<N*2>& d);
    int16<N>& operator=(const gint16<N>& d);
    int16<N>& operator=(const gint32<N/2>& d);
    int16<N>& operator=(const gint64<N/4>& d);

    const int16v* begin() const { return gint16<N>::di_; }
    int16v* begin()             { return gint16<N>::di_; }
    const int16v* end() const   { return gint16<N>::di_+vec_length; }
    int16v* end()               { return gint16<N>::di_+vec_length; }
    const int16v& operator[](unsigned i) const { return *(gint16<N>::di_+i); }
    int16v& operator[](unsigned i)             { return *(gint16<N>::di_+i); }

    /** Creates a signed int16 vector from a value loaded from memory.

        @code
            | 0  1  2  ... 7  | ... |
        r = [ v0 v0 v0 ... v0   ... ]
        @endcode
    */
    static int16<N> load_broadcast(const int16_t* v0)
    {
        return set_broadcast(int16v::load_broadcast(v0));
    }

    /** Creates a signed int16 vector from a value stored in a core register.

        @code
            | 0  1  2  ...  7  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static int16<N> set_broadcast(int16_t v0)
    {
        return set_broadcast(int16v::set_broadcast(v0));
    }

    /** Creates a signed int16 vector from a value known at compile-time

        @code
            | 0  1  2  ...  7  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static int16<N> make_const(int16_t v0)
    {
        return set_broadcast(int16v::make_const(v0));
    }

    /** Creates a signed int16 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 7  | ... |
        r = [ v0 v1 v0 v1 ... v1   ... ]
        @endcode
    */
    static int16<N> make_const(int16_t v0, int16_t v1)
    {
        return set_broadcast(int16v::make_const(v0, v1));
    }

    /** Creates a signed int16 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  ... 7  | ... |
        r = [ v0 v1 v2 v3 v0 ... v3   ... ]
        @endcode
    */
    static int16<N> make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3)
    {
        return set_broadcast(int16v::make_const(v0, v1, v2, v3));
    }

    /** Creates a signed int16 vector from eight values known at compile-time

        @code
            | 0  1  2  ... 7  | ... |
        r = [ v0 v1 v2 ... v7   ... ]
        @endcode
    */
    static int16<N> make_const(int16_t v0, int16_t v1, int16_t v2, int16_t v3,
                               int16_t v4, int16_t v5, int16_t v6, int16_t v7)
    {
        return set_broadcast(int16v::make_const(v0, v1, v2, v3, v4, v5, v6, v7));
    }

    /// Creates a signed int16 vector with the contents set to copy of native
    /// register
    static int16<N> set_broadcast(int16v a)
    {
        int16<N> r;
        for (auto& v : r.di_) {
            v = a;
        }
        return r;
    }
};

/** Class representing an unsigned @a int16 vector of arbitrary length. The vector
    always contains at least one native vector.
*/
template<unsigned N>
class uint16 : public gint16<N> {
public:

    using element_type = uint16_t;
    using gint16<N>::vec_length;

    uint16<N>() = default;
    uint16<N>(const uint16<N>&) = default;
    uint16<N>& operator=(const uint16<N>&) = default;

    uint16<N>(const gint8<N*2>& d);
    uint16<N>(const gint16<N>& d);
    uint16<N>(const gint32<N/2>& d);
    uint16<N>(const gint64<N/4>& d);
    uint16<N>& operator=(const gint8<N*2>& d);
    uint16<N>& operator=(const gint16<N>& d);
    uint16<N>& operator=(const gint32<N/2>& d);
    uint16<N>& operator=(const gint64<N/4>& d);

    const uint16v* begin() const { return gint16<N>::du_; }
    uint16v* begin()             { return gint16<N>::du_; }
    const uint16v* end() const   { return gint16<N>::du_+vec_length; }
    uint16v* end()               { return gint16<N>::du_+vec_length; }
    const uint16v& operator[](unsigned i) const { return *(gint16<N>::du_+i); }
    uint16v& operator[](unsigned i)             { return *(gint16<N>::du_+i); }

    /** Creates a unsigned int16 vector from a value loaded from memory.

        @code
            | 0  1  2  ... 7  | ... |
        r = [ v0 v0 v0 ... v0   ... ]
        @endcode
    */
    static uint16<N> load_broadcast(const uint16_t* v0)
    {
        return set_broadcast(uint16v::load_broadcast(v0));
    }

    /** Creates a unsigned int16 vector from a value stored in a core register.

        @code
            | 0  1  2  ...  7  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static uint16<N> set_broadcast(uint16_t v0)
    {
        return set_broadcast(uint16v::set_broadcast(v0));
    }

    /** Creates a unsigned int16 vector from a value known at compile-time

        @code
            | 0  1  2  ...  7  | ... |
        r = [ v0 v0 v0 ...  v0   ... ]
        @endcode
    */
    static uint16<N> make_const(uint16_t v0)
    {
        return set_broadcast(uint16v::make_const(v0));
    }

    /** Creates a unsigned int16 vector from two values known at compile-time

        @code
            | 0  1  2  3  ... 7  | ... |
        r = [ v0 v1 v0 v1 ... v1   ... ]
        @endcode
    */
    static uint16<N> make_const(uint16_t v0, uint16_t v1)
    {
        return set_broadcast(uint16v::make_const(v0, v1));
    }

    /** Creates a unsigned int16 vector from four values known at compile-time

        @code
            | 0  1  2  3  4  ... 7  | ... |
        r = [ v0 v1 v2 v3 v0 ... v3   ... ]
        @endcode
    */
    static uint16<N> make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3)
    {
        return set_broadcast(uint16v::make_const(v0, v1, v2, v3));
    }

    /** Creates a unsigned int16 vector from eight values known at compile-time

        @code
            | 0  1  2  ... 7  | ... |
        r = [ v0 v1 v2 ... v7   ... ]
        @endcode
    */
    static uint16<N> make_const(uint16_t v0, uint16_t v1, uint16_t v2, uint16_t v3,
                                uint16_t v4, uint16_t v5, uint16_t v6, uint16_t v7)
    {
        return set_broadcast(uint16v::make_const(v0, v1, v2, v3, v4, v5, v6, v7));
    }

    /// Creates a unsigned int16 vector with the contents set to copy of native
    /// register
    static uint16<N> set_broadcast(uint16v a)
    {
        uint16<N> r;
        for (auto& v : r.du_) {
            v = a;
        }
        return r;
    }
};

/// Class representing a mask for @a gint16 vector of arbitrary length. The
/// vector always contains at least one native vector.
template<unsigned N>
class mask_int16 {
public:
    using base_vector_type = mask_int16v;
    static constexpr unsigned length = N;
    static constexpr unsigned vec_length = (N + SIMDPP_FAST_INT16_SIZE - 1) / SIMDPP_FAST_INT16_SIZE;

    mask_int16<N>() = default;
    mask_int16<N>(const mask_int16 &) = default;
    mask_int16<N> &operator=(const mask_int16 &) = default;

    const mask_int16v* begin() const   { return d_; }
    mask_int16v* begin()               { return d_; }
    const mask_int16v* end() const     { return d_+vec_length; }
    mask_int16v* end()                 { return d_+vec_length; }
    const mask_int16v& operator[](unsigned i) const { return *(d_+i); }
    mask_int16v& operator[](unsigned i)             { return *(d_+i); }

    /// Convert to a regular vector
    operator gint16<N>() const
    {
        gint16<N> r;
        for (unsigned i = 0; i < vec_length; ++i) {
            r[i] = d_[i];
        }
        return r;
    }

private:
    mask_int16v d_[vec_length];
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
