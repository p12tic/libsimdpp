/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_EXPR_VEC_H
#define LIBSIMDPP_SIMDPP_DETAIL_EXPR_VEC_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class R, unsigned N> SIMDPP_INL      float32<N> expr_eval(const float32<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL mask_float32<N> expr_eval(const mask_float32<N>& a) { return a; }

template<class R, unsigned N> SIMDPP_INL      float64<N> expr_eval(const float64<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL mask_float64<N> expr_eval(const mask_float64<N>& a) { return a; }

template<class R, unsigned N> SIMDPP_INL     uint8<N> expr_eval(const uint8<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL      int8<N> expr_eval(const  int8<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL mask_int8<N> expr_eval(const mask_int8<N>& a) { return a; }

template<class R, unsigned N> SIMDPP_INL     uint16<N> expr_eval(const uint16<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL      int16<N> expr_eval(const  int16<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL mask_int16<N> expr_eval(const mask_int16<N>& a) { return a; }

template<class R, unsigned N> SIMDPP_INL     uint32<N> expr_eval(const uint32<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL      int32<N> expr_eval(const  int32<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL mask_int32<N> expr_eval(const mask_int32<N>& a) { return a; }

template<class R, unsigned N> SIMDPP_INL     uint64<N> expr_eval(const uint64<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL      int64<N> expr_eval(const  int64<N>& a) { return a; }
template<class R, unsigned N> SIMDPP_INL mask_int64<N> expr_eval(const mask_int64<N>& a) { return a; }

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
