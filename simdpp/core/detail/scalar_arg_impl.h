/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_SCALAR_ARG_IMPL_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_SCALAR_ARG_IMPL_H

#include <simdpp/types.h>
#include <simdpp/detail/insn/make_const.h>
namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class Int> void scalar_convert(Int& d, uint64_t x) { d = x; }
SIMDPP_INL void scalar_convert(float& d, uint64_t x) { d = bit_cast<float>(uint32_t(x)); }
SIMDPP_INL void scalar_convert(double& d, uint64_t x) { d = bit_cast<double>(x); }

template<class V> SIMDPP_INL
V make_const(uint64_t t)
{
    typename detail::remove_sign<V>::type r;
    expr_vec_make_const<typename V::element_type, 1> e;
    scalar_convert(e.a[0], t);
    insn::i_make_const(r, e);
    return V(r);
}

template<class V>
V make_const_same(const typename V::element_type& t)
{
    typename detail::remove_sign<V>::type r;
    expr_vec_make_const<typename V::element_type, 1> e;
    e.a[0] = t;
    insn::i_make_const(r, e);
    return V(r);
}

} // namespace detail
#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

/*  The following implements the boilerplate for binary function wrappers that
    accept values as scalar arguments.
*/

// simple implementation returning empty expression
#define SIMDPP_SCALAR_ARG_IMPL_VEC_IMPL(FUNC, RET_VEC, EXPR, NEW_VEC)                                                                   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(uint32_t a, const EXPR<N,V>& b) { return FUNC(detail::make_const_same<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(uint64_t a, const EXPR<N,V>& b) { return FUNC(detail::make_const_same<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(int32_t a,  const EXPR<N,V>& b) { return FUNC(detail::make_const_same<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(int64_t a,  const EXPR<N,V>& b) { return FUNC(detail::make_const_same<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(float a,    const EXPR<N,V>& b) { return FUNC(detail::make_const_same<NEW_VEC>(a), b); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(double a,   const EXPR<N,V>& b) { return FUNC(detail::make_const_same<NEW_VEC>(a), b); }   \
                                                                                                                                        \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, uint32_t b) { return FUNC(a, detail::make_const_same<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, uint64_t b) { return FUNC(a, detail::make_const_same<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, int32_t b)  { return FUNC(a, detail::make_const_same<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, int64_t b)  { return FUNC(a, detail::make_const_same<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, float b)    { return FUNC(a, detail::make_const_same<NEW_VEC>(b)); }   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, double b)   { return FUNC(a, detail::make_const_same<NEW_VEC>(b)); }
// end #define


#define SIMDPP_SCALAR_ARG_IMPL_VEC(FUNC, RET_VEC, VEC) \
    SIMDPP_SCALAR_ARG_IMPL_VEC_IMPL(FUNC, RET_VEC, VEC, VEC<N>)
#define SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(FUNC, RET_VEC, EXPR) \
    SIMDPP_SCALAR_ARG_IMPL_VEC_IMPL(FUNC, RET_VEC, EXPR, typename detail::get_expr<V>::type)
// end #define

// implementation returning an expression for vector arguments
#define SIMDPP_SCALAR_ARG_IMPL_EXPR(FUNC, EXPR, RET_VEC, VEC)                                                                                   \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(uint32_t a, const VEC<N,V>& b) { return FUNC(detail::make_const_same<VEC<N>>(a), b); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(uint64_t a, const VEC<N,V>& b) { return FUNC(detail::make_const_same<VEC<N>>(a), b); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(int32_t a, const VEC<N,V>& b)  { return FUNC(detail::make_const_same<VEC<N>>(a), b); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(int64_t a, const VEC<N,V>& b)  { return FUNC(detail::make_const_same<VEC<N>>(a), b); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(float a, const VEC<N,V>& b)    { return FUNC(detail::make_const_same<VEC<N>>(a), b); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(double a, const VEC<N,V>& b)   { return FUNC(detail::make_const_same<VEC<N>>(a), b); } \
                                                                                                                                                \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, uint32_t b) { return FUNC(a, detail::make_const_same<VEC<N>>(b)); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, uint64_t b) { return FUNC(a, detail::make_const_same<VEC<N>>(b)); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, int32_t b)  { return FUNC(a, detail::make_const_same<VEC<N>>(b)); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, int64_t b)  { return FUNC(a, detail::make_const_same<VEC<N>>(b)); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, float b)    { return FUNC(a, detail::make_const_same<VEC<N>>(b)); } \
template<unsigned N, class V> SIMDPP_INL RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, double b)   { return FUNC(a, detail::make_const_same<VEC<N>>(b)); }
// end #define

// a implementation for integer operations that optimize the returned expression
#define SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(FUNC, EXPR, VEC, UINT_VEC)          \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, uint32_t b)                                     \
{ return FUNC(a, detail::make_const_same<UINT_VEC<N>>(b)); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, uint64_t b)                                     \
{ return FUNC(a, detail::make_const_same<UINT_VEC<N>>(b)); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, int32_t b)                                      \
{ return FUNC(a, detail::make_const_same<UINT_VEC<N>>(b)); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, int64_t b)                                      \
{ return FUNC(a, detail::make_const_same<UINT_VEC<N>>(b)); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, float b)                                        \
{ return FUNC(a, detail::make_const_same<UINT_VEC<N>>(b)); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, double b)                                       \
{ return FUNC(a, detail::make_const_same<UINT_VEC<N>>(b)); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(uint32_t a, const VEC<N,V>& b)                                     \
{ return FUNC(detail::make_const_same<UINT_VEC<N>>(a), b); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(uint64_t a, const VEC<N,V>& b)                                     \
{ return FUNC(detail::make_const_same<UINT_VEC<N>>(a), b); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(int32_t a, const VEC<N,V>& b)                                      \
{ return FUNC(detail::make_const_same<UINT_VEC<N>>(a), b); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(int64_t a, const VEC<N,V>& b)                                      \
{ return FUNC(detail::make_const_same<UINT_VEC<N>>(a), b); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(float a, const VEC<N,V>& b)                                        \
{ return FUNC(detail::make_const_same<UINT_VEC<N>>(a), b); }                    \
                                                                                \
template<unsigned N, class V> SIMDPP_INL                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(double a, const VEC<N,V>& b)                                       \
{ return FUNC(detail::make_const_same<UINT_VEC<N>>(a), b); }
// end #define

#endif
