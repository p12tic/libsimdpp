/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_TYPES_GENERIC_INL
#define LIBSIMDPP_SIMD_TYPES_GENERIC_INL

#include <simdpp/setup_arch.h>
#include <simdpp/expr.h>
#include <simdpp/detail/expr/vec.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

template<unsigned N, class E> SIMDPP_INL float32<N>           float32<N,E>::eval() const { return (float32<N>) detail::expr_eval<float32<N> >(e); }
template<unsigned N, class E> SIMDPP_INL mask_float32<N> mask_float32<N,E>::eval() const { return (mask_float32<N>) detail::expr_eval<mask_float32<N> >(e); }

template<unsigned N, class E> SIMDPP_INL float64<N>           float64<N,E>::eval() const { return (float64<N>) detail::expr_eval<float64<N> >(e); }
template<unsigned N, class E> SIMDPP_INL mask_float64<N> mask_float64<N,E>::eval() const { return (mask_float64<N>) detail::expr_eval<mask_float64<N> >(e); }

template<unsigned N, class E> SIMDPP_INL int8<N>           int8<N,E>::eval() const { return (int8<N>)      detail::expr_eval<int8<N> >(e); }
template<unsigned N, class E> SIMDPP_INL uint8<N>         uint8<N,E>::eval() const { return (uint8<N>)     detail::expr_eval<uint8<N> >(e); }
template<unsigned N, class E> SIMDPP_INL mask_int8<N> mask_int8<N,E>::eval() const { return (mask_int8<N>) detail::expr_eval<mask_int8<N> >(e); }

template<unsigned N, class E> SIMDPP_INL int16<N>           int16<N,E>::eval() const { return (int16<N>)      detail::expr_eval<int16<N> >(e); }
template<unsigned N, class E> SIMDPP_INL uint16<N>         uint16<N,E>::eval() const { return (uint16<N>)     detail::expr_eval<uint16<N> >(e); }
template<unsigned N, class E> SIMDPP_INL mask_int16<N> mask_int16<N,E>::eval() const { return (mask_int16<N>) detail::expr_eval<mask_int16<N> >(e); }

template<unsigned N, class E> SIMDPP_INL int32<N>           int32<N,E>::eval() const { return (int32<N>)      detail::expr_eval<int32<N> >(e); }
template<unsigned N, class E> SIMDPP_INL uint32<N>         uint32<N,E>::eval() const { return (uint32<N>)     detail::expr_eval<uint32<N> >(e); }
template<unsigned N, class E> SIMDPP_INL mask_int32<N> mask_int32<N,E>::eval() const { return (mask_int32<N>) detail::expr_eval<mask_int32<N> >(e); }

template<unsigned N, class E> SIMDPP_INL int64<N>           int64<N,E>::eval() const { return (int64<N>)      detail::expr_eval<int64<N> >(e); }
template<unsigned N, class E> SIMDPP_INL uint64<N>         uint64<N,E>::eval() const { return (uint64<N>)     detail::expr_eval<uint64<N> >(e); }
template<unsigned N, class E> SIMDPP_INL mask_int64<N> mask_int64<N,E>::eval() const { return (mask_int64<N>) detail::expr_eval<mask_int64<N> >(e); }

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
