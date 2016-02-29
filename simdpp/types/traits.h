/*  Copyright (C) 2012  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_TRAITS_H
#define LIBSIMDPP_SIMDPP_TYPES_TRAITS_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/cxx11_emul.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

namespace detail {

template<class T, T v>
struct integral_constant
{
    static const T value = v;
    typedef T value_type;
    typedef integral_constant type;
    operator value_type() const { return value; }
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template<class T, class U> struct is_same : false_type {};
template<class T> struct is_same<T, T> : true_type {};

template<class T> struct remove_const          { typedef T type; };
template<class T> struct remove_const<const T> { typedef T type; };

template<class T> struct remove_volatile             { typedef T type; };
template<class T> struct remove_volatile<volatile T> { typedef T type; };

template<class T> struct remove_cv
{
    typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

template<class T> struct is_void_impl : public false_type {};
template<>        struct is_void_impl<void> : public true_type {};

template<class T> struct is_void : public is_void_impl<typename remove_cv<T>::type> {};

} // namespace detail

/// Allows detection whether specific type is a simdpp vector
template<class T>
struct is_vector : detail::false_type {};

template<unsigned N, class E> struct is_vector<float32<N,E> >   : detail::true_type {};
template<unsigned N, class E> struct is_vector<float64<N,E> >   : detail::true_type {};
template<unsigned N, class E> struct is_vector<int8<N,E> >      : detail::true_type {};
template<unsigned N, class E> struct is_vector<int16<N,E> >     : detail::true_type {};
template<unsigned N, class E> struct is_vector<int32<N,E> >     : detail::true_type {};
template<unsigned N, class E> struct is_vector<int64<N,E> >     : detail::true_type {};
template<unsigned N, class E> struct is_vector<uint8<N,E> >     : detail::true_type {};
template<unsigned N, class E> struct is_vector<uint16<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_vector<uint32<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_vector<uint64<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_vector<mask_int8<N,E> > : detail::true_type {};
template<unsigned N, class E> struct is_vector<mask_int16<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_vector<mask_int32<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_vector<mask_int64<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_vector<mask_float32<N,E> >  : detail::true_type {};
template<unsigned N, class E> struct is_vector<mask_float64<N,E> >  : detail::true_type {};

/// Allows detection whether specific type is a simdpp value (i.e. not expression) vector
template<class V>
struct is_value_vector : detail::false_type {};

template<unsigned N> struct is_value_vector<float32<N> >         : detail::true_type {};
template<unsigned N> struct is_value_vector<float64<N> >         : detail::true_type {};
template<unsigned N> struct is_value_vector<int8<N> >            : detail::true_type {};
template<unsigned N> struct is_value_vector<int16<N> >           : detail::true_type {};
template<unsigned N> struct is_value_vector<int32<N> >           : detail::true_type {};
template<unsigned N> struct is_value_vector<int64<N> >           : detail::true_type {};
template<unsigned N> struct is_value_vector<uint8<N> >           : detail::true_type {};
template<unsigned N> struct is_value_vector<uint16<N> >          : detail::true_type {};
template<unsigned N> struct is_value_vector<uint32<N> >          : detail::true_type {};
template<unsigned N> struct is_value_vector<uint64<N> >          : detail::true_type {};
template<unsigned N> struct is_value_vector<mask_int8<N> >       : detail::true_type {};
template<unsigned N> struct is_value_vector<mask_int16<N> >      : detail::true_type {};
template<unsigned N> struct is_value_vector<mask_int32<N> >      : detail::true_type {};
template<unsigned N> struct is_value_vector<mask_int64<N> >      : detail::true_type {};
template<unsigned N> struct is_value_vector<mask_float32<N> >    : detail::true_type {};
template<unsigned N> struct is_value_vector<mask_float64<N> >    : detail::true_type {};

/// Allows detection whether specific type is a simdpp mask
template<class T>
struct is_mask : detail::false_type {};

template<unsigned N, class E> struct is_mask<mask_int8<N,E> >    : detail::true_type {};
template<unsigned N, class E> struct is_mask<mask_int16<N,E> >   : detail::true_type {};
template<unsigned N, class E> struct is_mask<mask_int32<N,E> >   : detail::true_type {};
template<unsigned N, class E> struct is_mask<mask_int64<N,E> >   : detail::true_type {};
template<unsigned N, class E> struct is_mask<mask_float32<N,E> > : detail::true_type {};
template<unsigned N, class E> struct is_mask<mask_float64<N,E> > : detail::true_type {};

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
