/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_DETAIL_SCALAR_ARG_IMPL_H
#define LIBSIMDPP_SIMDPP_CORE_DETAIL_SCALAR_ARG_IMPL_H

#include <simdpp/types.h>
#include <simdpp/detail/insn/make_const.h>
#include <simdpp/core/make_float.h>
#include <simdpp/core/make_int.h>
#include <simdpp/core/make_uint.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {

template<class Int> void scalar_convert(Int& d, uint64_t x) { d = x; }
template<class Int> void scalar_convert(Int& d, float x) { d = bit_cast<uint32_t>(x); }
template<class Int> void scalar_convert(Int& d, double x) { d = bit_cast<uint64_t>(x); }
inline void scalar_convert(float& d, uint64_t x) { d = bit_cast<float>(uint32_t(x)); }
inline void scalar_convert(float& d, float x) { d = x; }
inline void scalar_convert(float& d, double x) { d = x; }
inline void scalar_convert(double& d, uint64_t x) { d = bit_cast<double>(x); }
inline void scalar_convert(double& d, float x) { d = x; }
inline void scalar_convert(double& d, double x) { d = x; }

template<class T>
class scalar_param {
public:
    scalar_param(char x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(unsigned char x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(signed char x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(unsigned short x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(signed short x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(unsigned int x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(signed int x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(unsigned long x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(signed long x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(unsigned long long x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(signed long long x) { scalar_convert(d, (uint64_t)x); }
    scalar_param(float x) { scalar_convert(d, x); }
    scalar_param(double x) { scalar_convert(d, x); }

    operator T() const { return d; }
private:
    T d;
};

template<class V>
V make_const(typename V::element_type t)
{
    typename detail::remove_sign<V>::type r;
    expr_vec_make_const<typename V::element_type, 1> e; e.a[0] = t;
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
#if SIMDPP_DOXYGEN

#define SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(FUNC, RET_VEC, VEC) \
template<unsigned N, class V>                               \
RET_VEC<N, _DETAIL_> FUNC(detail::scalar_param<typename V::element_type> a, const VEC<N,V>& b);   \
template<unsigned N, class V>                               \
RET_VEC<N, _DETAIL_> FUNC(const VEC<N,V>& a, detail::scalar_param<typename V::element_type> b);   \
// end #define

#else

#define SIMDPP_SCALAR_ARG_IMPL_VEC_EXPR(FUNC, RET_VEC, EXPR) \
template<unsigned N, class V>                               \
RET_VEC<N, RET_VEC<N>> FUNC(detail::scalar_param<typename V::element_type> a, const EXPR<N,V>& b)  \
{                                                           \
    return FUNC(detail::make_const<typename detail::get_expr<V>::type>(a), b);         \
}                                                           \
                                                            \
template<unsigned N, class V>                               \
RET_VEC<N, RET_VEC<N>> FUNC(const EXPR<N,V>& a, detail::scalar_param<typename V::element_type> b)  \
{                                                           \
    return FUNC(a, detail::make_const<typename detail::get_expr<V>::type>(b));                  \
}

#define SIMDPP_SCALAR_ARG_IMPL_VEC(FUNC, RET_VEC, VEC) \
template<unsigned N, class V>                               \
RET_VEC<N, RET_VEC<N>> FUNC(detail::scalar_param<typename VEC<N>::element_type> a, const VEC<N,V>& b)  \
{                                                           \
    return FUNC(detail::make_const<VEC<N>>(a), b);         \
}                                                           \
                                                            \
template<unsigned N, class V>                               \
RET_VEC<N, RET_VEC<N>> FUNC(const VEC<N,V>& a, detail::scalar_param<typename VEC<N>::element_type> b)  \
{                                                           \
    return FUNC(a, detail::make_const<VEC<N>>(b));                  \
}

// end #define

#endif // SIMDPP_DOXYGEN

// implementation returning an expression for vector arguments
#if SIMDPP_DOXYGEN

#define SIMDPP_SCALAR_ARG_IMPL_EXPR(FUNC, EXPR, RET_VEC, VEC)   \
template<unsigned N, class V>                                   \
RET_VEC<N, _DETAIL_> FUNC(detail::scalar_param<typename V::element_type> a, const VEC<N,V>& b);         \
template<unsigned N, class V>                                   \
RET_VEC<N, _DETAIL_> FUNC(const VEC<N,V>& a, detail::scalar_param<typename V::element_type> b);
// end #define

#else

#define SIMDPP_SCALAR_ARG_IMPL_EXPR(FUNC, EXPR, RET_VEC, VEC)           \
template<unsigned N, class V>                                           \
RET_VEC<N, EXPR<VEC<N>, VEC<N,V>>> FUNC(detail::scalar_param<typename VEC<N>::element_type> a, const VEC<N,V>& b)  \
{                                                                       \
    return FUNC(make_uint<VEC<N>>(a), b);                               \
}                                                                       \
                                                                        \
template<unsigned N, class V>                                           \
RET_VEC<N, EXPR<VEC<N,V>, VEC<N>>> FUNC(const VEC<N,V>& a, detail::scalar_param<typename VEC<N>::element_type> b)  \
{                                                                       \
    return FUNC(a, make_uint<VEC<N>>(b));                               \
}
// end #define

#endif // SIMDPP_DOXYGEN

// a implementation for integer operations that optimize the returned expression
#if SIMDPP_DOXYGEN

#define SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(FUNC, EXPR, VEC, UINT_VEC)      \
template<unsigned N, class V>                                           \
_PROMOTED_NOMASK_EXPRESSION_ FUNC(detail::scalar_param<typename V::element_type> a, const VEC<N,V>& b);         \
template<unsigned N, class V>                                           \
_PROMOTED_NOMASK_EXPRESSION_ FUNC(const VEC<N,V>& a, detail::scalar_param<typename V::element_type> b);       \
// end #define

#else

#define SIMDPP_SCALAR_ARG_IMPL_INT_UNSIGNED(FUNC, EXPR, VEC, UINT_VEC)          \
template<unsigned N, class V>                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(const VEC<N,V>& a, detail::scalar_param<typename V::element_type> b)                                     \
{ return FUNC(a, detail::make_const<typename detail::get_expr_nomask<V>::type>(b)); }             \
template<unsigned N, class V>                                                   \
typename detail::get_expr_nomask<V, EXPR<UINT_VEC<N, typename V::expr_type>,    \
                                         UINT_VEC<N>>>::type                    \
        FUNC(detail::scalar_param<typename V::element_type> a, const VEC<N,V>& b)                                     \
{ return FUNC(detail::make_const<typename detail::get_expr_nomask<V>::type>(a), b); }

// end #define

#endif // SIMDPP_DOXYGEN

#endif
