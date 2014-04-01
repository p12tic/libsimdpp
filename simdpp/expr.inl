/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_EXPR_EXPR_INL
#define LIBSIMDPP_SIMD_EXPR_EXPR_INL

#include <simdpp/setup_arch.h>
#include <simdpp/expr.h>
#include <simdpp/detail/expr/vec.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<unsigned N, class E> float32<N>           float32<N,E>::eval() const { return (float32<N>) detail::expr_eval(e); }
template<unsigned N, class E> mask_float32<N> mask_float32<N,E>::eval() const { return (mask_float32<N>) detail::expr_eval(float32<N,E>::e); }

template<unsigned N, class E> float64<N>           float64<N,E>::eval() const { return (float64<N>) detail::expr_eval(e); }
template<unsigned N, class E> mask_float64<N> mask_float64<N,E>::eval() const { return (mask_float64<N>) detail::expr_eval(float64<N,E>::e); }

template<unsigned N, class E> gint8<N>         gint8<N,E>::eval() const { return (gint8<N>)     detail::expr_eval(e); }
template<unsigned N, class E> int8<N>           int8<N,E>::eval() const { return (int8<N>)      detail::expr_eval(gint8<N,E>::e); }
template<unsigned N, class E> uint8<N>         uint8<N,E>::eval() const { return (uint8<N>)     detail::expr_eval(gint8<N,E>::e); }
template<unsigned N, class E> mask_int8<N> mask_int8<N,E>::eval() const { return (mask_int8<N>) detail::expr_eval(gint8<N,E>::e); }

template<unsigned N, class E> gint16<N>         gint16<N,E>::eval() const { return (gint16<N>)     detail::expr_eval(e); }
template<unsigned N, class E> int16<N>           int16<N,E>::eval() const { return (int16<N>)      detail::expr_eval(gint16<N,E>::e); }
template<unsigned N, class E> uint16<N>         uint16<N,E>::eval() const { return (uint16<N>)     detail::expr_eval(gint16<N,E>::e); }
template<unsigned N, class E> mask_int16<N> mask_int16<N,E>::eval() const { return (mask_int16<N>) detail::expr_eval(gint16<N,E>::e); }

template<unsigned N, class E> gint32<N>         gint32<N,E>::eval() const { return (gint32<N>)     detail::expr_eval(e); }
template<unsigned N, class E> int32<N>           int32<N,E>::eval() const { return (int32<N>)      detail::expr_eval(gint32<N,E>::e); }
template<unsigned N, class E> uint32<N>         uint32<N,E>::eval() const { return (uint32<N>)     detail::expr_eval(gint32<N,E>::e); }
template<unsigned N, class E> mask_int32<N> mask_int32<N,E>::eval() const { return (mask_int32<N>) detail::expr_eval(gint32<N,E>::e); }

template<unsigned N, class E> gint64<N>         gint64<N,E>::eval() const { return (gint64<N>)     detail::expr_eval(e); }
template<unsigned N, class E> int64<N>           int64<N,E>::eval() const { return (int64<N>)      detail::expr_eval(gint64<N,E>::e); }
template<unsigned N, class E> uint64<N>         uint64<N,E>::eval() const { return (uint64<N>)     detail::expr_eval(gint64<N,E>::e); }
template<unsigned N, class E> mask_int64<N> mask_int64<N,E>::eval() const { return (mask_int64<N>) detail::expr_eval(gint64<N,E>::e); }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
