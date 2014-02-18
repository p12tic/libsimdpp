/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>
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

#ifndef LIBSIMDPP_SIMD_EXPR_EXPR_H
#define LIBSIMDPP_SIMD_EXPR_EXPR_H

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <type_traits>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

// -----------------------------------------------------------------------------

template<class E1, class E2>
struct expr_bit_and {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_bit_andnot {
    E1 a;
    E2 b;
};

template<class E>
struct expr_bit_not {
    E a;
};

template<class E1, class E2>
struct expr_bit_or {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_bit_xor {
    E1 a;
    E2 b;
};

template<class E1, class E2, class E3>
struct expr_blend {
    E1 on;
    E2 off;
    E3 mask;
};

template<unsigned S, class E>
struct expr_broadcast {
    E a;
};

template<class E1, class E2>
struct expr_add {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_adds {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_sub {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_subs {
    E1 a;
    E2 b;
};

template<class E>
struct expr_abs {
    E a;
};

template<class E>
struct expr_neg {
    E a;
};

template<class E1, class E2>
struct expr_mul {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_mul_lo {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_mul_hi {
    E1 a;
    E2 b;
};

template<class E1, class E2>
struct expr_mull {
    E1 a;
    E2 b;
};

template<class E1, class E2, class E3>
struct expr_fmadd { // a * b + c
    E1 a;
    E2 b;
    E3 c;
};

template<class E1, class E2, class E3>
struct expr_fmsub { // a * b - c
    E1 a;
    E2 b;
    E3 c;
};

template<unsigned S, class E>
struct expr_imm_shift_l {
    E a;
    static const unsigned shift = S;
};

template<unsigned S, class E>
struct expr_imm_shift_r {
    E a;
    static const unsigned shift = S;
};


// -----------------------------------------------------------------------------

/*
    The dummy parameter in the template definitions below specifies that we
    want to perform initialization of the underlying expression and not to
    perform a conversion.

    The conversions are provided for the 'empty' expression types
    (e.g. float32<N, float32<N>>) so that they can be initialized with
    different vector type.

    TODO: explain better
    TODO: investigate whether conversions are still needed.
*/

// -----------------------------------------------------------------------------
// float32

template<unsigned N, class E>
class float32 {
public:
    E e;

    float32(const E& a, int /* dummy */) : e(a) {}
    float32(const float32<N>& a) : e(a) {}

    operator float32<N>() const { return eval(); }
    float32<N> eval() const;
};

template<unsigned N, class E>
class mask_float32 : public float32<N,E> {
private:
    using super = float32<N,E>;
public:

    mask_float32(const E& a, int dummy) : super(a, dummy) {}
    mask_float32(const mask_float32<N>& a) : super(a, 0) {}

    operator mask_float32<N>() const { return eval(); }
    operator float32<N>() const { return eval(); }
    mask_float32<N> eval() const;
};

// -----------------------------------------------------------------------------
// float64

template<unsigned N, class E>
class float64 {
public:
    E e;

    float64(const E& a, int /* dummy */) : e(a) {}
    float64(const float64<N>& a) : e(a) {}

    operator float64<N>() const { return eval(); }
    float64<N> eval() const;
};

template<unsigned N, class E>
class mask_float64 : public float64<N,E> {
private:
    using super = float64<N,E>;
public:

    mask_float64(const E& a, int dummy) : super(a, dummy) {}
    mask_float64(const mask_float64<N>& a) : super(a, 0) {}

    operator mask_float64<N>() const { return eval(); }
    operator float64<N>() const { return eval(); }
    mask_float64<N> eval() const;
};

// -----------------------------------------------------------------------------
// gint8<N>

template<unsigned N, class E>
class gint8 {
public:

    E e;

    gint8(const E& a, int /* dummy */) : e(a) {}
    gint8(const gint8<N>& a)     : e(a) {}
    gint8(const gint16<N/2>& a)  : e(a) {}
    gint8(const gint32<N/4>& a)  : e(a) {}
    gint8(const gint64<N/8>& a)  : e(a) {}

    gint8(const gint8<N,E>& a)     : e(a.e) {}
    gint8(const gint16<N/2,E>& a)  : e(a.e) {}
    gint8(const gint32<N/4,E>& a)  : e(a.e) {}
    gint8(const gint64<N/8,E>& a)  : e(a.e) {}

    operator gint8<N>() const { return eval(); }
    gint8<N> eval() const;
};

template<unsigned N, class E>
class int8 : public gint8<N,E> {
private:
    using super = gint8<N,E>;
public:

    int8(const E& a, int dummy) : super(a, dummy) {}
    int8(const gint8<N>& a)     : super(a) {}
    int8(const gint16<N/2>& a)  : super(a) {}
    int8(const gint32<N/4>& a)  : super(a) {}
    int8(const gint64<N/8>& a)  : super(a) {}

    int8(const gint8<N,E>& a)     : super(a.e) {}
    int8(const gint16<N/2,E>& a)  : super(a.e) {}
    int8(const gint32<N/4,E>& a)  : super(a.e) {}
    int8(const gint64<N/8,E>& a)  : super(a.e) {}

    operator int8<N>() const { return eval(); }
    int8<N> eval() const;
};


template<unsigned N, class E>
class uint8 : public gint8<N,E> {
private:
    using super = gint8<N,E>;
public:

    uint8(const E& a, int dummy) : super(a, dummy) {}
    uint8(const gint8<N>& a)     : super(a) {}
    uint8(const gint16<N/2>& a)  : super(a) {}
    uint8(const gint32<N/4>& a)  : super(a) {}
    uint8(const gint64<N/8>& a)  : super(a) {}

    uint8(const gint8<N,E>& a)     : super(a.e) {}
    uint8(const gint16<N/2,E>& a)  : super(a.e) {}
    uint8(const gint32<N/4,E>& a)  : super(a.e) {}
    uint8(const gint64<N/8,E>& a)  : super(a.e) {}

    operator uint8<N>() const { return eval(); }
    uint8<N> eval() const;
};

template<unsigned N, class E>
class mask_int8 : public uint8<N,E> {
private:
    using super = uint8<N,E>;
public:

    mask_int8(const E& a, int dummy) : super(a, dummy) {}
    mask_int8(const mask_int8<N>& a) : super(a, 0) {}

    operator mask_int8<N>() const { return eval(); }
    operator int8<N>() const { return eval(); }
    mask_int8<N> eval() const;
};

// -----------------------------------------------------------------------------
// gint16<N>

template<unsigned N, class E>
class gint16 {
public:

    E e;

    gint16(const E& a, int /* dummy */) : e(a) {}
    gint16(const gint8<N*2>& a)   : e(a) {}
    gint16(const gint16<N>& a)    : e(a) {}
    gint16(const gint32<N/2>& a)  : e(a) {}
    gint16(const gint64<N/4>& a)  : e(a) {}

    gint16(const gint8<N*2,E>& a)   : e(a.e) {}
    gint16(const gint16<N,E>& a)    : e(a.e) {}
    gint16(const gint32<N/2,E>& a)  : e(a.e) {}
    gint16(const gint64<N/4,E>& a)  : e(a.e) {}

    operator gint16<N>() const { return eval(); }
    gint16<N> eval() const;
};

template<unsigned N, class E>
class int16 : public gint16<N,E> {
private:
    using super = gint16<N,E>;
public:

    int16(const E& a, int dummy) : super(a, dummy) {}
    int16(const gint8<N*2>& a)   : super(a) {}
    int16(const gint16<N>& a)    : super(a) {}
    int16(const gint32<N/2>& a)  : super(a) {}
    int16(const gint64<N/4>& a)  : super(a) {}

    int16(const gint8<N*2,E>& a)   : super(a.e) {}
    int16(const gint16<N,E>& a)    : super(a.e) {}
    int16(const gint32<N/2,E>& a)  : super(a.e) {}
    int16(const gint64<N/4,E>& a)  : super(a.e) {}

    operator int16<N>() const { return eval(); }
    int16<N> eval() const;
};


template<unsigned N, class E>
class uint16 : public gint16<N,E> {
private:
    using super = gint16<N,E>;
public:

    uint16(const E& a, int dummy) : super(a, dummy) {}
    uint16(const gint8<N*2>& a)   : super(a) {}
    uint16(const gint16<N>& a)    : super(a) {}
    uint16(const gint32<N/2>& a)  : super(a) {}
    uint16(const gint64<N/4>& a)  : super(a) {}

    uint16(const gint8<N*2,E>& a)   : super(a.e) {}
    uint16(const gint16<N,E>& a)    : super(a.e) {}
    uint16(const gint32<N/2,E>& a)  : super(a.e) {}
    uint16(const gint64<N/4,E>& a)  : super(a.e) {}

    operator uint16<N>() const { return eval(); }
    uint16<N> eval() const;
};

template<unsigned N, class E>
class mask_int16 : public uint16<N,E> {
private:
    using super = uint16<N,E>;
public:

    mask_int16(const E& a, int dummy) : super(a, dummy) {}
    mask_int16(const mask_int16<N>& a) : super(a, 0) {}

    operator mask_int16<N>() const { return eval(); }
    operator int16<N>() const { return eval(); }
    mask_int16<N> eval() const;
};

// -----------------------------------------------------------------------------
// gint32<N>

template<unsigned N, class E>
class gint32 {
public:

    E e;

    gint32(const E& a, int /* dummy */) : e(a) {}
    gint32(const gint8<N*4>& a)   : e(a) {}
    gint32(const gint16<N*2>& a)  : e(a) {}
    gint32(const gint32<N>& a)    : e(a) {}
    gint32(const gint64<N/2>& a)  : e(a) {}

    gint32(const gint8<N*4,E>& a)   : e(a.e) {}
    gint32(const gint16<N*2,E>& a)  : e(a.e) {}
    gint32(const gint32<N,E>& a)    : e(a.e) {}
    gint32(const gint64<N/2,E>& a)  : e(a.e) {}

    operator gint32<N>() const { return eval(); }
    gint32<N> eval() const;
};

template<unsigned N, class E>
class int32 : public gint32<N,E> {
private:
    using super = gint32<N,E>;
public:

    int32(const E& a, int dummy) : super(a, dummy) {}
    int32(const gint8<N*4>& a)   : super(a) {}
    int32(const gint16<N*2>& a)  : super(a) {}
    int32(const gint32<N>& a)    : super(a) {}
    int32(const gint64<N/2>& a)  : super(a) {}

    int32(const gint8<N*4,E>& a)   : super(a.e) {}
    int32(const gint16<N*2,E>& a)  : super(a.e) {}
    int32(const gint32<N,E>& a)    : super(a.e) {}
    int32(const gint64<N/2,E>& a)  : super(a.e) {}

    operator int32<N>() const { return eval(); }
    int32<N> eval() const;
};


template<unsigned N, class E>
class uint32 : public gint32<N,E> {
private:
    using super = gint32<N,E>;
public:

    uint32(const E& a, int dummy) : super(a, dummy) {}
    uint32(const gint8<N*4>& a)   : super(a) {}
    uint32(const gint16<N*2>& a)  : super(a) {}
    uint32(const gint32<N>& a)    : super(a) {}
    uint32(const gint64<N/2>& a)  : super(a) {}

    uint32(const gint8<N*4,E>& a)   : super(a.e) {}
    uint32(const gint16<N*2,E>& a)  : super(a.e) {}
    uint32(const gint32<N,E>& a)    : super(a.e) {}
    uint32(const gint64<N/2,E>& a)  : super(a.e) {}

    operator uint32<N>() const { return eval(); }
    uint32<N> eval() const;
};

template<unsigned N, class E>
class mask_int32 : public uint32<N,E> {
private:
    using super = uint32<N,E>;
public:

    mask_int32(const E& a, int dummy) : super(a, dummy) {}
    mask_int32(const mask_int32<N>& a) : super(a, 0) {}

    operator mask_int32<N>() const { return eval(); }
    operator int32<N>() const { return eval(); }
    mask_int32<N> eval() const;
};

// -----------------------------------------------------------------------------
// gint64<N>

template<unsigned N, class E>
class gint64 {
public:
    E e;

    gint64(const E& a, int /* dummy */) : e(a) {}
    gint64(const gint8<N*8>& a)   : e(a) {}
    gint64(const gint16<N*4>& a)  : e(a) {}
    gint64(const gint32<N*2>& a)  : e(a) {}
    gint64(const gint64<N>& a)    : e(a) {}

    gint64(const gint8<N*8,E>& a)   : e(a.e) {}
    gint64(const gint16<N*4,E>& a)  : e(a.e) {}
    gint64(const gint32<N*2,E>& a)  : e(a.e) {}
    gint64(const gint64<N,E>& a)    : e(a.e) {}

    operator gint64<N>() const { return eval(); }
    gint64<N> eval() const;
};

template<unsigned N, class E>
class int64 : public gint64<N,E> {
private:
    using super = gint64<N,E>;
public:

    int64(const E& a, int dummy) : super(a, dummy) {}
    int64(const gint8<N*8>& a)   : super(a) {}
    int64(const gint16<N*4>& a)  : super(a) {}
    int64(const gint32<N*2>& a)  : super(a) {}
    int64(const gint64<N>& a)    : super(a) {}

    int64(const gint8<N*8,E>& a)   : super(a.e) {}
    int64(const gint16<N*4,E>& a)  : super(a.e) {}
    int64(const gint32<N*2,E>& a)  : super(a.e) {}
    int64(const gint64<N,E>& a)    : super(a.e) {}

    operator int64<N>() const { return eval(); }
    int64<N> eval() const;
};


template<unsigned N, class E>
class uint64 : public gint64<N,E> {
private:
    using super = gint64<N,E>;
public:

    uint64(const E& a, int dummy) : super(a, dummy) {}
    uint64(const gint8<N*8>& a)   : super(a) {}
    uint64(const gint16<N*4>& a)  : super(a) {}
    uint64(const gint32<N*2>& a)  : super(a) {}
    uint64(const gint64<N>& a)    : super(a) {}

    uint64(const gint8<N*8,E>& a)   : super(a.e) {}
    uint64(const gint16<N*4,E>& a)  : super(a.e) {}
    uint64(const gint32<N*2,E>& a)  : super(a.e) {}
    uint64(const gint64<N,E>& a)    : super(a.e) {}

    operator uint64<N>() const { return eval(); }
    uint64<N> eval() const;
};


template<unsigned N, class E>
class mask_int64 : public uint64<N,E> {
private:
    using super = uint64<N,E>;
public:

    mask_int64(const E& a, int dummy) : super(a, dummy) {}
    mask_int64(const mask_int64<N>& a) : super(a, 0) {}

    operator mask_int64<N>() const { return eval(); }
    operator int64<N>() const { return eval(); }
    mask_int64<N> eval() const;
};



#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

