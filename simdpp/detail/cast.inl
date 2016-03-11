/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_INL
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_DETAIL_CAST_INL

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/cast.h>
#include <simdpp/core/cmp_neq.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {
namespace detail {

template<class T> struct base_mask_vector_type { using type = T; };
template<unsigned N> struct base_mask_vector_type<mask_int8<N>> { using type = uint8<N>; };
template<unsigned N> struct base_mask_vector_type<mask_int16<N>> { using type = uint16<N>; };
template<unsigned N> struct base_mask_vector_type<mask_int32<N>> { using type = uint32<N>; };
template<unsigned N> struct base_mask_vector_type<mask_int64<N>> { using type = uint64<N>; };
template<unsigned N> struct base_mask_vector_type<mask_float32<N>> { using type = float32<N>; };
template<unsigned N> struct base_mask_vector_type<mask_float64<N>> { using type = float64<N>; };

#if _MSC_VER
#pragma intrinsic(memcpy)
#endif

template<class R, class T> SIMDPP_INL
R cast_memcpy(const T& t)
{
    static_assert(sizeof(R) == sizeof(T), "Size mismatch");
    R r;
    ::memcpy(&r, &t, sizeof(R));
    return r;
}

template<class R, class T> SIMDPP_INL
R cast_memcpy_unmask(const T& t)
{
    using TT = typename base_mask_vector_type<T>::type;
    TT tt = t.unmask();
    return cast_memcpy<R>(tt);
}

template<class R, class T> SIMDPP_INL
R cast_memcpy_remask(const T& t)
{
    using RR = typename base_mask_vector_type<R>::type;
    RR rr = cast_memcpy<RR>(t.unmask());
    return cmp_neq(rr, (RR) make_zero());
}

template<>
struct cast_wrapper<true/*IsRMask*/, true/*IsLMask*/, CAST_MASK_MEMCPY> {
    template<class R, class T> SIMDPP_INL
    static R run(const T& t)
    {
        static_assert(R::size_tag == T::size_tag,
                      "Conversions between masks with different element size is"
                      " not allowed");
        return cast_memcpy<R>(t);
    }
};

template<>
struct cast_wrapper<true/*IsRMask*/, true/*IsLMask*/, CAST_MASK_UNMASK> {
    template<class R, class T> SIMDPP_INL
    static R run(const T& t)
    {
        static_assert(R::size_tag == T::size_tag,
                      "Conversions between masks with different element size is"
                      " not allowed");
        return cast_memcpy_unmask<R>(t);
    }
};

template<>
struct cast_wrapper<true/*IsRMask*/, true/*IsLMask*/, CAST_MASK_REMASK> {
    template<class R, class T> SIMDPP_INL
    static R run(const T& t)
    {
        static_assert(R::size_tag == T::size_tag,
                      "Conversions between masks with different element size is"
                      " not allowed");
        return cast_memcpy_remask<R>(t);
    }
};

template<unsigned MaskCastOverride>
struct cast_wrapper<true/*IsRMask*/, false/*IsLMask*/, MaskCastOverride> {
    template<class R, class T> SIMDPP_INL
    static R run(const T&)
    {
        static_assert(!std::is_same<T,T>::value, // fake dependency
                      "Conversion from non-mask type to a mask type is not allowed");
    }
};

template<unsigned MaskCastOverride>
struct cast_wrapper<false/*IsRMask*/, true/*IsLMask*/, MaskCastOverride> {
    template<class R, class T> SIMDPP_INL
    static R run(const T& t)
    {
        return cast_memcpy_unmask<R>(t);
    }
};

template<unsigned MaskCastOverride>
struct cast_wrapper<false/*IsRMask*/, false/*IsLMask*/, MaskCastOverride> {
    template<class R, class T> SIMDPP_INL
    static R run(const T& t)
    {
        return cast_memcpy<R>(t);
    }
};

} // namespace detail
} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

