/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_SCALAR_ARG_IMPL_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_SCALAR_ARG_IMPL_H

#include <simdpp/types.h>
#include <simdpp/expr.h>
#include <simdpp/core/make_float.h>
#include <simdpp/core/make_int.h>
#include <simdpp/core/make_uint.h>
#include <simdpp/detail/expr/scalar.h>

/*  The following implements the boilerplate for binary function wrappers that
    accept values as scalar arguments.
*/

// simple implementation returning empty expression
#define SIMDPP_SCALAR_ARG_IMPL_VEC(FUNC, RET_VEC, VEC)                                                                   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const unsigned& a,              const VEC<N>& b) { return FUNC(make_uint<VEC<N>>(a), b); }   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const unsigned long& a,         const VEC<N>& b) { return FUNC(make_uint<VEC<N>>(a), b); }   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const unsigned long long& a,    const VEC<N>& b) { return FUNC(make_uint<VEC<N>>(a), b); }   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const int& a,                   const VEC<N>& b) { return FUNC(make_int<VEC<N>>(a), b); }    \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const long& a,                  const VEC<N>& b) { return FUNC(make_int<VEC<N>>(a), b); }    \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const long long& a,             const VEC<N>& b) { return FUNC(make_int<VEC<N>>(a), b); }    \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const float& a,                 const VEC<N>& b) { return FUNC(make_float<VEC<N>>(a), b); }  \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const double& a,                const VEC<N>& b) { return FUNC(make_float<VEC<N>>(a), b); }  \
                                                                                                                                               \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const unsigned& b          ) { return FUNC(a, make_uint<VEC<N>>(b)); }   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const unsigned long& b     ) { return FUNC(a, make_uint<VEC<N>>(b)); }   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const unsigned long long& b) { return FUNC(a, make_uint<VEC<N>>(b)); }   \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const int& b               ) { return FUNC(a, make_int<VEC<N>>(b)); }    \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const long& b              ) { return FUNC(a, make_int<VEC<N>>(b)); }    \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const long long& b         ) { return FUNC(a, make_int<VEC<N>>(b)); }    \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const float& b             ) { return FUNC(a, make_float<VEC<N>>(b)); }  \
template<unsigned N> SIMDPP_INL RET_VEC<N> FUNC(const VEC<N>& a, const double& b            ) { return FUNC(a, make_float<VEC<N>>(b)); }
// end #define

#define SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR_IMPL(FUNC, RET_VEC, EXPR, NEW_VEC)                                                                   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const unsigned& a,              const EXPR<N,V>& b) { return FUNC(make_uint<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const unsigned long& a,         const EXPR<N,V>& b) { return FUNC(make_uint<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const unsigned long long& a,    const EXPR<N,V>& b) { return FUNC(make_uint<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const int& a,                   const EXPR<N,V>& b) { return FUNC(make_int<NEW_VEC>(a), b); }    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const long& a,                  const EXPR<N,V>& b) { return FUNC(make_int<NEW_VEC>(a), b); }    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const long long& a,             const EXPR<N,V>& b) { return FUNC(make_int<NEW_VEC>(a), b); }    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const float& a,                 const EXPR<N,V>& b) { return FUNC(make_float<NEW_VEC>(a), b); }  \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const double& a,                const EXPR<N,V>& b) { return FUNC(make_float<NEW_VEC>(a), b); }  \
                                                                                                                                                    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const unsigned& b          ) { return FUNC(a, make_uint<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const unsigned long& b     ) { return FUNC(a, make_uint<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const unsigned long long& b) { return FUNC(a, make_uint<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const int& b               ) { return FUNC(a, make_int<NEW_VEC>(b)); }    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const long& b              ) { return FUNC(a, make_int<NEW_VEC>(b)); }    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const long long& b         ) { return FUNC(a, make_int<NEW_VEC>(b)); }    \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const float& b             ) { return FUNC(a, make_float<NEW_VEC>(b)); }  \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N> FUNC(const EXPR<N,V>& a, const double& b            ) { return FUNC(a, make_float<NEW_VEC>(b)); }
// end #define

#define SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(FUNC, RET_VEC, EXPR) \
    SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR_IMPL(FUNC, RET_VEC, EXPR, typename detail::get_expr<V>::type)
// end #define

// a implementation for integer operations that use get_expr_uint
#define SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(FUNC, EXPR, VEC, INT_VEC)           \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, unsigned>::type                               \
        FUNC(const VEC<N,V>& a, const unsigned& b)                              \
{ return FUNC(a, make_uint<INT_VEC>(b)); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, unsigned long>::type                          \
        FUNC(const VEC<N,V>& a, const unsigned long& b)                         \
{ return FUNC(a, make_uint<INT_VEC>(b)); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, unsigned long long>::type                     \
        FUNC(const VEC<N,V>& a, const unsigned long long& b)                    \
{ return FUNC(a, make_uint<INT_VEC>(b)); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, int>::type                                    \
        FUNC(const VEC<N,V>& a, const int& b)                                   \
{ return FUNC(a, make_int<INT_VEC>(b)); }                                       \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, long>::type                                   \
        FUNC(const VEC<N,V>& a, const long& b)                                  \
{ return FUNC(a, make_int<INT_VEC>(b)); }                                       \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, long long>::type                              \
        FUNC(const VEC<N,V>& a, const long long& b)                             \
{ return FUNC(a, make_int<INT_VEC>(b)); }                                       \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, float>::type                                  \
        FUNC(const VEC<N,V>& a, const float& b)                                 \
{ return FUNC(a, make_float<INT_VEC>(b)); }                                     \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<V, double>::type                                 \
        FUNC(const VEC<N,V>& a, const double& b)                                \
{ return FUNC(make_uint<INT_VEC>(a), b); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<unsigned, V>::type                               \
        FUNC(const unsigned& a, const VEC<N,V>& b)                              \
{ return FUNC(make_uint<INT_VEC>(a), b); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<unsigned long, V>::type                          \
        FUNC(const unsigned long& a, const VEC<N,V>& b)                         \
{ return FUNC(make_uint<INT_VEC>(a), b); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<unsigned long long, V>::type                     \
        FUNC(const unsigned long long& a, const VEC<N,V>& b)                    \
{ return FUNC(make_uint<INT_VEC>(a), b); }                                      \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<int, V>::type                                    \
        FUNC(const int& a, const VEC<N,V>& b)                                   \
{ return FUNC(make_int<INT_VEC>(a), b); }                                       \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<long, V>::type                                   \
        FUNC(const long& a, const VEC<N,V>& b)                                  \
{ return FUNC(make_int<INT_VEC>(a), b); }                                       \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<long long, V>::type                              \
        FUNC(const long long& a, const VEC<N,V>& b)                             \
{ return FUNC(make_int<INT_VEC>(a), b); }                                       \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<float, V>::type                                  \
        FUNC(const float& a, const VEC<N,V>& b)                                 \
{ return FUNC(make_float<INT_VEC>(a), b); }                                     \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                        \
typename detail::get_expr_uint<double, V>::type                                 \
        FUNC(const double& a, const VEC<N,V>& b)                                \
{ return FUNC(make_float<INT_VEC>(a), b); }
// end #define

#endif
