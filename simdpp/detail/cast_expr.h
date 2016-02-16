/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_CAST_EXPR_H
#define LIBSIMDPP_SIMDPP_DETAIL_CAST_EXPR_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/core/cast.h>

#include <cstring>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

/*  Casts the base type of an expression.

    DANGER: this must be used with caution.

    Must not be used if the form of R and S is not one of the following:

    * R<N,E> and S<N,E> respectively; E is not void
    * R<N,S<N,void>> and S<N,void> respectively

    Why can we do this safely?

    All vector expression types are standard layout types. In addition
    to that, all vector expressions defined in simdpp/types/general.inl have
    a single data member, which has the type of the second template argument.
    This means for any vector expression X<N,A> we can safely cast X<N,A>& to
    A& and then to a reference to any other vector expression Y<N,A>&.

    So, for the first case, we effectively cast S<N,E>& to E& and then to
    S<N,E>&.

    For the second case we cast effectively cast G& to R<N,G>&, where G is
    S<N,void>.
*/
#if !SIMDPP_EXPR_DEBUG
template<class R, class S> SIMDPP_INL
const R& cast_expr(const S& expr)
{
    return reinterpret_cast<const R&>(expr);
}
#else
template<class R, class S>
struct cast_expr_check {
    static_assert(std::is_same<R, R>::value, "Bad cast_expr");
};

template<template<unsigned, class> class R,
         template<unsigned, class> class S,
         unsigned N, class E>
struct cast_expr_check< R<N,E>, S<N,E> > {
    static_assert(!std::is_void<E>::value, "Bad cast_expr");
};

template<template<unsigned, template<unsigned, class> class> class R,
         template<unsigned, class> class S,
         unsigned N, class E>
struct cast_expr_check< R<N, S<N,E> >, S<N,E> > { };

template<class R, class S> SIMDPP_INL
const R& cast_expr(const S& expr)
{
    cast_expr_check<R,S> x;
    return reinterpret_cast<const R&>(expr);
}
#endif

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
