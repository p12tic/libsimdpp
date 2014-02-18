/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_VEC_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_VEC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<unsigned N>      float32<N> expr_eval(const float32<N>& a) { return a; }
template<unsigned N> mask_float32<N> expr_eval(const mask_float32<N>& a) { return a; }

template<unsigned N>      float64<N> expr_eval(const float64<N>& a) { return a; }
template<unsigned N> mask_float64<N> expr_eval(const mask_float64<N>& a) { return a; }

template<unsigned N>     gint8<N> expr_eval(const gint8<N>& a) { return a; }
template<unsigned N>      int8<N> expr_eval(const  int8<N>& a) { return a; }
template<unsigned N>     uint8<N> expr_eval(const uint8<N>& a) { return a; }
template<unsigned N> mask_int8<N> expr_eval(const mask_int8<N>& a) { return a; }

template<unsigned N>     gint16<N> expr_eval(const gint16<N>& a) { return a; }
template<unsigned N>      int16<N> expr_eval(const  int16<N>& a) { return a; }
template<unsigned N>     uint16<N> expr_eval(const uint16<N>& a) { return a; }
template<unsigned N> mask_int16<N> expr_eval(const mask_int16<N>& a) { return a; }

template<unsigned N>     gint32<N> expr_eval(const gint32<N>& a) { return a; }
template<unsigned N>      int32<N> expr_eval(const  int32<N>& a) { return a; }
template<unsigned N>     uint32<N> expr_eval(const uint32<N>& a) { return a; }
template<unsigned N> mask_int32<N> expr_eval(const mask_int32<N>& a) { return a; }

template<unsigned N>     gint64<N> expr_eval(const gint64<N>& a) { return a; }
template<unsigned N>      int64<N> expr_eval(const  int64<N>& a) { return a; }
template<unsigned N>     uint64<N> expr_eval(const uint64<N>& a) { return a; }
template<unsigned N> mask_int64<N> expr_eval(const mask_int64<N>& a) { return a; }

} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
