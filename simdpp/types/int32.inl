/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_INT32_INL
#define LIBSIMDPP_SIMDPP_TYPES_INT32_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types/int32.h>
#include <simdpp/null/mask.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<unsigned N> template<class E> gint32<N>::gint32(const  gint8<N*4,E>& d) { *this = bit_cast<gint32<N>>(d.eval()); }
template<unsigned N> template<class E> gint32<N>::gint32(const gint16<N*2,E>& d) { *this = bit_cast<gint32<N>>(d.eval()); }
template<unsigned N> template<class E> gint32<N>::gint32(const gint32<N,E>& d)   { *this = bit_cast<gint32<N>>(d.eval()); }
template<unsigned N> template<class E> gint32<N>::gint32(const gint64<N/2,E>& d) { *this = bit_cast<gint32<N>>(d.eval()); }
template<unsigned N> template<class E> gint32<N>& gint32<N>::operator=(const  gint8<N*4,E>& d) { *this = bit_cast<gint32<N>>(d.eval()); return *this; }
template<unsigned N> template<class E> gint32<N>& gint32<N>::operator=(const gint16<N*2,E>& d) { *this = bit_cast<gint32<N>>(d.eval()); return *this; }
template<unsigned N> template<class E> gint32<N>& gint32<N>::operator=(const gint32<N,E>& d)   { *this = bit_cast<gint32<N>>(d.eval()); return *this; }
template<unsigned N> template<class E> gint32<N>& gint32<N>::operator=(const gint64<N/2,E>& d) { *this = bit_cast<gint32<N>>(d.eval()); return *this; }

template<unsigned N> template<class E> int32<N>::int32(const  gint8<N*4,E>& d) : gint32<N>(d) {}
template<unsigned N> template<class E> int32<N>::int32(const gint16<N*2,E>& d) : gint32<N>(d) {}
template<unsigned N> template<class E> int32<N>::int32(const gint32<N,E>& d)   : gint32<N>(d) {}
template<unsigned N> template<class E> int32<N>::int32(const gint64<N/2,E>& d) : gint32<N>(d) {}
template<unsigned N> template<class E> int32<N>& int32<N>::operator=(const  gint8<N*4,E>& d) { gint32<N>::operator=(d); return *this; }
template<unsigned N> template<class E> int32<N>& int32<N>::operator=(const gint16<N*2,E>& d) { gint32<N>::operator=(d); return *this; }
template<unsigned N> template<class E> int32<N>& int32<N>::operator=(const gint32<N,E>& d)   { gint32<N>::operator=(d); return *this; }
template<unsigned N> template<class E> int32<N>& int32<N>::operator=(const gint64<N/2,E>& d) { gint32<N>::operator=(d); return *this; }

template<unsigned N> template<class E> uint32<N>::uint32(const  gint8<N*4,E>& d) : gint32<N>(d) {}
template<unsigned N> template<class E> uint32<N>::uint32(const gint16<N*2,E>& d) : gint32<N>(d) {}
template<unsigned N> template<class E> uint32<N>::uint32(const gint32<N,E>& d)   : gint32<N>(d) {}
template<unsigned N> template<class E> uint32<N>::uint32(const gint64<N/2,E>& d) : gint32<N>(d) {}
template<unsigned N> template<class E> uint32<N>& uint32<N>::operator=(const  gint8<N*4,E>& d) { gint32<N>::operator=(d); return *this; }
template<unsigned N> template<class E> uint32<N>& uint32<N>::operator=(const gint16<N*2,E>& d) { gint32<N>::operator=(d); return *this; }
template<unsigned N> template<class E> uint32<N>& uint32<N>::operator=(const gint32<N,E>& d)   { gint32<N>::operator=(d); return *this; }
template<unsigned N> template<class E> uint32<N>& uint32<N>::operator=(const gint64<N/2,E>& d) { gint32<N>::operator=(d); return *this; }

template<unsigned N> maskdata_int32<N>::operator uint32<N>() const
{
    uint32<N> r;
    for (unsigned i = 0; i < vec_length; ++i) r[i] = d_[i];
    return r;
}

template<unsigned N> mask_int32<N>::mask_int32(const maskdata_int32<N>& d) : uint32<N>(d), mask_(d) {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
