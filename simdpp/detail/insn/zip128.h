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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP128_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_ZIP128_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/zip_hi.h>
#include <simdpp/detail/insn/zip_lo.h>
#include <simdpp/detail/insn/unzip_hi.h>
#include <simdpp/detail/insn/unzip_lo.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {

template<unsigned N> gint8<N> unzip128_lo(gint8<N> a, gint8<N> b) { return unzip16_lo(a, b); }
template<unsigned N> gint16<N> unzip128_lo(gint16<N> a, gint16<N> b) { return unzip8_lo(a, b); }
template<unsigned N> gint32<N> unzip128_lo(gint32<N> a, gint32<N> b) { return unzip4_lo(a, b); }
template<unsigned N> gint64<N> unzip128_lo(gint64<N> a, gint64<N> b) { return unzip2_lo(a, b); }
template<unsigned N> float32<N> unzip128_lo(float32<N> a, float32<N> b) { return unzip4_lo(a, b); }
template<unsigned N> float64<N> unzip128_lo(float64<N> a, float64<N> b) { return unzip2_lo(a, b); }

template<unsigned N> gint8<N> unzip128_hi(gint8<N> a, gint8<N> b) { return unzip16_hi(a, b); }
template<unsigned N> gint16<N> unzip128_hi(gint16<N> a, gint16<N> b) { return unzip8_hi(a, b); }
template<unsigned N> gint32<N> unzip128_hi(gint32<N> a, gint32<N> b) { return unzip4_hi(a, b); }
template<unsigned N> gint64<N> unzip128_hi(gint64<N> a, gint64<N> b) { return unzip2_hi(a, b); }
template<unsigned N> float32<N> unzip128_hi(float32<N> a, float32<N> b) { return unzip4_hi(a, b); }
template<unsigned N> float64<N> unzip128_hi(float64<N> a, float64<N> b) { return unzip2_hi(a, b); }

template<unsigned N> gint8<N> zip128_lo(gint8<N> a, gint8<N> b) { return zip16_lo(a, b); }
template<unsigned N> gint16<N> zip128_lo(gint16<N> a, gint16<N> b) { return zip8_lo(a, b); }
template<unsigned N> gint32<N> zip128_lo(gint32<N> a, gint32<N> b) { return zip4_lo(a, b); }
template<unsigned N> gint64<N> zip128_lo(gint64<N> a, gint64<N> b) { return zip2_lo(a, b); }
template<unsigned N> float32<N> zip128_lo(float32<N> a, float32<N> b) { return zip4_lo(a, b); }
template<unsigned N> float64<N> zip128_lo(float64<N> a, float64<N> b) { return zip2_lo(a, b); }

template<unsigned N> gint8<N> zip128_hi(gint8<N> a, gint8<N> b) { return zip16_hi(a, b); }
template<unsigned N> gint16<N> zip128_hi(gint16<N> a, gint16<N> b) { return zip8_hi(a, b); }
template<unsigned N> gint32<N> zip128_hi(gint32<N> a, gint32<N> b) { return zip4_hi(a, b); }
template<unsigned N> gint64<N> zip128_hi(gint64<N> a, gint64<N> b) { return zip2_hi(a, b); }
template<unsigned N> float32<N> zip128_hi(float32<N> a, float32<N> b) { return zip4_hi(a, b); }
template<unsigned N> float64<N> zip128_hi(float64<N> a, float64<N> b) { return zip2_hi(a, b); }


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


