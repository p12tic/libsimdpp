/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_BITWISE_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_BITWISE_H

#include <simdpp/types.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

/*  Note that in this function we are invoking undefined behavior that happens
    to work in all compilers the library supports. The only non-undefined way
    to do bitwise data transfer between unrelated types without breaking strict
    aliasing rules is the memcpy() function. Unfortunately some compilers can't
    fully optimize out the overhead of the function which leads to unnecessary
    data movement to the stack.
*/
template<class T, class R> SIMDPP_INL
void cast_bitwise(const T& t, R& r)
{
    static_assert(sizeof(R) == sizeof(T), "Size mismatch");
    union {
        T t_union;
        R r_union;
    };
    t_union = t;
    r = r_union;
}

template<class T, class R> SIMDPP_INL
void cast_bitwise_vector(const T& t, R& r)
{
    static_assert(sizeof(R) == sizeof(T), "Size mismatch");
#if SIMDPP_LIBRARY_VERSION_CXX98 || (defined(_MSC_VER) && _MSC_VER < 1900) || (__GNUC__ == 5) || (__GNUC__ == 6)
    // We can't create use union of vector types because they are not trivial
    // types. In pre-C++11 version of the library they have empty user-defined
    // default constructor, which is required as the compiler will not provide
    // one by default due to additional constructors being present. Instead we
    // create union of native_type which are trivial types in all supported
    // configurations.
    // - MSVC 2013 and older incorrectly deduce type triviality
    // - GCC 5 and 6 crashes in certain cases when converting between vectors
    // containing multiple native vectors.
    using NativeT = typename T::base_vector_type::native_type;
    using NativeR = typename R::base_vector_type::native_type;
    union {
        NativeT t_union[T::vec_length];
        NativeR r_union[R::vec_length];
    };
    for (unsigned i = 0; i < T::vec_length; ++i)
        t_union[i] = t.vec(i).native();
    for (unsigned i = 0; i < R::vec_length; ++i)
        r.vec(i) = r_union[i];
#else
    union {
        T t_union;
        R r_union;
    };
    t_union = t;
    r = r_union;
#endif
}

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif
