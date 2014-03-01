/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X2_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT64X2_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int64x2.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/detail/word_size.h>
#include <simdpp/detail/mem_block.h>
#include <simdpp/core/permute2.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/null/mask.h>
#include <simdpp/null/set.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<class E> gint64<2>::gint64(const gint8<16,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); }
template<class E> gint64<2>::gint64(const gint16<8,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); }
template<class E> gint64<2>::gint64(const gint32<4,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); }
template<class E> gint64<2>::gint64(const gint64<2,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); }
template<class E> gint64<2>& gint64<2>::operator=(const gint8<16,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); return *this; }
template<class E> gint64<2>& gint64<2>::operator=(const gint16<8,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); return *this; }
template<class E> gint64<2>& gint64<2>::operator=(const gint32<4,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); return *this; }
template<class E> gint64<2>& gint64<2>::operator=(const gint64<2,E>& d) { *this = bit_cast<gint64<2>>(d.eval()); return *this; }

template<class E> int64<2>::int64(const gint8<16,E>& d) : gint64(d) {}
template<class E> int64<2>::int64(const gint16<8,E>& d) : gint64(d) {}
template<class E> int64<2>::int64(const gint32<4,E>& d) : gint64(d) {}
template<class E> int64<2>::int64(const gint64<2,E>& d) : gint64(d) {}
template<class E> int64<2>& int64<2>::operator=(const gint8<16,E>& d) { gint64::operator=(d); return *this; }
template<class E> int64<2>& int64<2>::operator=(const gint16<8,E>& d) { gint64::operator=(d); return *this; }
template<class E> int64<2>& int64<2>::operator=(const gint32<4,E>& d) { gint64::operator=(d); return *this; }
template<class E> int64<2>& int64<2>::operator=(const gint64<2,E>& d) { gint64::operator=(d); return *this; }

template<class E> uint64<2>::uint64(const gint8<16,E>& d) : gint64(d) {}
template<class E> uint64<2>::uint64(const gint16<8,E>& d) : gint64(d) {}
template<class E> uint64<2>::uint64(const gint32<4,E>& d) : gint64(d) {}
template<class E> uint64<2>::uint64(const gint64<2,E>& d) : gint64(d) {}
template<class E> uint64<2>& uint64<2>::operator=(const gint8<16,E>& d) { gint64::operator=(d); return *this; }
template<class E> uint64<2>& uint64<2>::operator=(const gint16<8,E>& d) { gint64::operator=(d); return *this; }
template<class E> uint64<2>& uint64<2>::operator=(const gint32<4,E>& d) { gint64::operator=(d); return *this; }
template<class E> uint64<2>& uint64<2>::operator=(const gint64<2,E>& d) { gint64::operator=(d); return *this; }

inline gint64<2>::gint64(const float64x2& d)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    detail::mem_block<gint64x2> ax;
    ax[0] = bit_cast<uint64_t>(d.el(0));
    ax[1] = bit_cast<uint64_t>(d.el(1));
    operator=(gint64x2(ax));
#elif SIMDPP_USE_SSE2
    operator=(_mm_castpd_si128(d));
#endif
}

inline gint64x2 gint64x2::zero()
{
    return uint64x2::make_const(0);
}

inline gint64x2 gint64x2::ones()
{
    return uint64x2::make_const(0xffffffffffffffff);
}

inline int64x2 int64x2::make_const(int64_t v0)
{
    return uint64x2::make_const(v0);
}

inline int64x2 int64x2::make_const(int64_t v0, int64_t v1)
{
    return uint64x2::make_const(v0, v1);
}

inline uint64x2 uint64x2::make_const(uint64_t v0)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2 || SIMDPP_USE_ALTIVEC
    return uint64x2::make_const(v0, v0);
#elif SIMDPP_USE_NEON
    uint64x1_t r0 = vcreate_u64(v0);
    return vcombine_u64(r0, r0);
#endif
}

inline uint64x2 uint64x2::make_const(uint64_t v0, uint64_t v1)
{
#if SIMDPP_USE_NULL
    return null::make_vec<uint64x2>(v0, v1);
#elif SIMDPP_USE_SSE2
    return _mm_set_epi64x(v1, v0);
#elif SIMDPP_USE_NEON
    union {
        uint64x2 align;
        uint64_t v[2];
    };
    v[0] = v0;
    v[1] = v1;
    return vld1q_u64(v);
#elif SIMDPP_USE_ALTIVEC
    return uint32x4::make_const(v0 >> 32, v0, v1 >> 32, v1); // big endian
#endif
}

inline mask_int64<2>::mask_int64(const maskdata_int64<2>& d) : uint64<2>(d), mask_(d) {}

#if SIMDPP_USE_SSE2
inline mask_int64<2>::mask_int64(__m128i d)   : uint64<2>(d), mask_(d) {}
inline mask_int64<2>::mask_int64(gint64<2> d) : uint64<2>(d), mask_(d) {}
#elif SIMDPP_USE_NEON
inline mask_int64<2>::mask_int64(uint64x2_t d) : uint64<2>(d), mask_(d) {}
inline mask_int64<2>::mask_int64(gint64<2> d)  : uint64<2>(d),  mask_(d) {}
#elif SIMDPP_USE_ALTIVEC
inline mask_int64<2>::mask_int64(__vector uint64_t d) : uint64<2>(d), mask_(d) {}
inline mask_int64<2>::mask_int64(gint64<2> d)         : uint64<2>(d), mask_(d) {}
#endif



#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
