/*  libsimdpp
    Copyright (C) 2012-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT64X4_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT64X4_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int64x4.h>
#include <simdpp/types/float64x4.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX2

inline gint64<4>::gint64(const gint8x32& d) { *this = bit_cast<gint64x4>(d); }
inline gint64<4>::gint64(const gint16x16& d) { *this = bit_cast<gint64x4>(d); }
inline gint64<4>::gint64(const gint32x8& d) { *this = bit_cast<gint64x4>(d); }
inline gint64<4>& gint64<4>::operator=(const gint8x32& d) { *this = bit_cast<gint64x4>(d); return *this; }
inline gint64<4>& gint64<4>::operator=(const gint16x16& d){ *this = bit_cast<gint64x4>(d); return *this; }
inline gint64<4>& gint64<4>::operator=(const gint32x8& d) { *this = bit_cast<gint64x4>(d); return *this; }

inline int64<4>::int64(const gint8x32& d) : gint64x4(bit_cast<gint64x4>(d)) {}
inline int64<4>::int64(const gint16x16& d): gint64x4(bit_cast<gint64x4>(d)) {}
inline int64<4>::int64(const gint32x8& d) : gint64x4(bit_cast<gint64x4>(d)) {}
inline int64<4>::int64(const gint64x4& d) : gint64x4(d) {}
inline int64<4>& int64<4>::operator=(const gint8x32& d) { gint64x4::operator=(d); return *this; }
inline int64<4>& int64<4>::operator=(const gint16x16& d){ gint64x4::operator=(d); return *this; }
inline int64<4>& int64<4>::operator=(const gint32x8& d) { gint64x4::operator=(d); return *this; }
inline int64<4>& int64<4>::operator=(const gint64x4& d) { gint64x4::operator=(d); return *this; }

inline uint64<4>::uint64(const gint8x32& d) : gint64x4(bit_cast<gint64x4>(d)) {}
inline uint64<4>::uint64(const gint16x16& d): gint64x4(bit_cast<gint64x4>(d)) {}
inline uint64<4>::uint64(const gint32x8& d) : gint64x4(bit_cast<gint64x4>(d)) {}
inline uint64<4>::uint64(const gint64x4& d) : gint64x4(d) {}
inline uint64<4>& uint64<4>::operator=(const gint8x32& d) { gint64x4::operator=(d); return *this; }
inline uint64<4>& uint64<4>::operator=(const gint16x16& d){ gint64x4::operator=(d); return *this; }
inline uint64<4>& uint64<4>::operator=(const gint32x8& d) { gint64x4::operator=(d); return *this; }
inline uint64<4>& uint64<4>::operator=(const gint64x4& d) { gint64x4::operator=(d); return *this; }

inline gint64<4>::gint64(const float64x4& d)
{
    *this = bit_cast<gint64x4>(d);
}

inline gint64x4 gint64x4::zero()
{
    return uint64x4::make_const(0);
}

inline gint64x4 gint64x4::ones()
{
    return uint64x4::make_const(0xffffffffffffffff);
}

inline int64x4 int64x4::load_broadcast(const int64_t* v0)
{
    return uint64x4::load_broadcast(reinterpret_cast<const uint64_t*>(v0));
}

inline int64x4 int64x4::set_broadcast(int64_t v0)
{
    return uint64x4::set_broadcast(v0);
}

inline int64x4 int64x4::make_const(int64_t v0)
{
    return uint64x4::make_const(v0);
}

inline int64x4 int64x4::make_const(int64_t v0, int64_t v1)
{
    return uint64x4::make_const(v0, v1);
}

inline int64x4 int64x4::make_const(int64_t v0, int64_t v1, int64_t v2, int64_t v3)
{
    return uint64x4::make_const(v0, v1, v2, v3);
}

inline uint64x4 uint64x4::load_broadcast(const uint64_t* v0)
{
    return uint64x4::set_broadcast(*v0);
}

inline uint64x4 uint64x4::set_broadcast(uint64_t v0)
{
    uint64x2 a = _mm_cvtsi64_si128(v0);
    return _mm256_broadcastq_epi64(a);
}

inline uint64x4 uint64x4::make_const(uint64_t v0)
{
    return uint64x4::make_const(v0, v0, v0, v0);
}

inline uint64x4 uint64x4::make_const(uint64_t v0, uint64_t v1)
{
    return uint64x4::make_const(v0, v1, v0, v1);
}

inline uint64x4 uint64x4::make_const(uint64_t v0, uint64_t v1, uint64_t v2, uint64_t v3)
{
    return _mm256_set_epi64x(v3, v2, v1, v0);
}

inline mask_int64x4::operator gint64x4() const
{
    return d_;
}

#endif // SIMDPP_USE_AVX2

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
