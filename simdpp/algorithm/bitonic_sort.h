/*  Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_ALGORITHM_BITONIC_SORT
#define LIBSIMDPP_SIMDPP_ALGORITHM_BITONIC_SORT

#include <simdpp/simd.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

namespace detail {

template<unsigned N, class T>
SIMDPP_INL T sort_4lane_2el_asc_2el_dec(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T swapped = permute4<1, 0, 3, 2>(aw);

    T res_min = min(aw, swapped);
    T res_max = max(aw, swapped);

    return shuffle4x2<1, 4, 7, 2>(res_min, res_max);
}

template<unsigned N, class T>
SIMDPP_INL T sort_4lane_2el_asc_2el_asc(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T swapped = permute4<1, 0, 3, 2>(aw);

    T res_min = min(aw, swapped);
    T res_max = max(aw, swapped);

    return shuffle4x2<1, 4, 2, 7>(res_min, res_max);
}

template<unsigned N, class T>
SIMDPP_INL T sort_4lane_2el_dec_2el_dec(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T swapped = permute4<1, 0, 3, 2>(aw);

    T res_max = max(aw, swapped);
    T res_min = min(aw, swapped);

    return shuffle4x2<1, 4, 2, 7>(res_max, res_min);
}

template<unsigned N, class T>
SIMDPP_INL T sort_4lane_corresponding_2el_asc(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();
    T swapped = permute4<2, 3, 0, 1>(aw);

    T res_min = min(aw, swapped);
    T res_max = max(aw, swapped);

    return shuffle4x2<0, 1, 4, 5>(res_min, res_max);
}

template<unsigned N, class T>
SIMDPP_INL T sort_4lane_corresponding_2el_dec(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();
    T swapped = permute4<2, 3, 0, 1>(aw);

    T res_max = max(aw, swapped);
    T res_min = min(aw, swapped);

    return shuffle4x2<0, 1, 4, 5>(res_max, res_min);
}

template<unsigned N, class T>
SIMDPP_INL T sort_8lane_corresponding_4el_asc(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();
    T lo = shuffle1_128<0, 0>(aw, aw);
    T hi = shuffle1_128<1, 1>(aw, aw);

    T res_min = min(lo, hi);
    T res_max = max(lo, hi);

    return shuffle1_128<0, 0>(res_min, res_max);
}

template<unsigned N, class T>
SIMDPP_INL T sort_8lane_corresponding_4el_dec(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();
    T lo = shuffle1_128<0, 0>(aw, aw);
    T hi = shuffle1_128<1, 1>(aw, aw);

    T res_max = max(lo, hi);
    T res_min = min(lo, hi);

    return shuffle1_128<0, 0>(res_max, res_min);
}

template<unsigned N, class T>
SIMDPP_INL T reverse_8lane_top4(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T reversed = permute4<3, 2, 1, 0>(aw);

    return shuffle1_128<0, 1>(aw, reversed);
}

template<unsigned N, class T>
SIMDPP_INL T reverse_8lane_bottom4(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T reversed = permute4<3, 2, 1, 0>(aw);

    return shuffle1_128<0, 1>(reversed, aw);
}

template<unsigned N, class T>
SIMDPP_INL T sort_8lane_4el_asc_4el_dec(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T step1_res = sort_4lane_2el_asc_2el_dec(aw);
    T step2_res = sort_4lane_corresponding_2el_asc(step1_res);
    T step3_res = sort_4lane_2el_asc_2el_asc(step2_res);

    return reverse_8lane_top4(step3_res);
}

template<unsigned N, class T>
SIMDPP_INL T sort_8lane_4el_dec_4el_asc(const any_vec32<N,T>& a)
{
    auto& aw = a.wrapped();

    T step1_res = sort_4lane_2el_asc_2el_dec(aw);
    T step2_res = sort_4lane_corresponding_2el_asc(step1_res);
    T step3_res = sort_4lane_2el_asc_2el_asc(step2_res);

    return reverse_8lane_bottom4(step3_res);
}

template<unsigned N, class T>
SIMDPP_INL T bitonic_sort_8lane_finalize_asc(const any_vec32<N, T>& a)
{
    auto& aw = a.wrapped();

    T step1_res = sort_8lane_corresponding_4el_asc(aw);
    T step2_res = sort_4lane_corresponding_2el_asc(step1_res);
    return sort_4lane_2el_asc_2el_asc(step2_res);
}

template<unsigned N, class T>
SIMDPP_INL T bitonic_sort_8lane_finalize_dec(const any_vec32<N, T>& a)
{
    auto& aw = a.wrapped();

    T step1_res = sort_8lane_corresponding_4el_dec(aw);
    T step2_res = sort_4lane_corresponding_2el_dec(step1_res);
    return sort_4lane_2el_dec_2el_dec(step2_res);
}

} // namespace detail

/** Sorts data in the given SIMD registers in increasing order. Sort is not stable.
*/
template<class T>
void bitonic_sort_asc(any_vec32<8,T>& a0)
{
    auto r = detail::sort_8lane_4el_asc_4el_dec(a0.wrapped());
    a0.wrapped() = detail::bitonic_sort_8lane_finalize_asc(r);
}

template<class T>
void bitonic_sort_dec(any_vec32<8,T>& a0)
{
    auto r = detail::sort_8lane_4el_dec_4el_asc(a0.wrapped());
    a0.wrapped() = detail::bitonic_sort_8lane_finalize_dec(r);
}


template<class T>
void bitonic_sort_asc(any_vec32<8,T>& a0, any_vec32<8,T>& a1)
{
    auto r0 = a0.wrapped();
    auto r1 = a1.wrapped();
    r0 = detail::sort_8lane_4el_asc_4el_dec(r0);
    r0 = detail::bitonic_sort_8lane_finalize_asc(r0);
    r1 = detail::sort_8lane_4el_asc_4el_dec(r1);
    r1 = detail::bitonic_sort_8lane_finalize_dec(r1);

    T res_max = max(r0, r1);
    T res_min = min(r0, r1);

    r0 = detail::bitonic_sort_8lane_finalize_asc(res_min);
    r1 = detail::bitonic_sort_8lane_finalize_asc(res_max);
    a0.wrapped() = r0;
    a1.wrapped() = r1;
}

template<class T>
void bitonic_sort_dec(any_vec32<8,T>& a0, any_vec32<8,T>& a1)
{
    auto r0 = a0.wrapped();
    auto r1 = a1.wrapped();
    r0 = detail::sort_8lane_4el_dec_4el_asc(r0);
    r0 = detail::bitonic_sort_8lane_finalize_dec(r0);
    r1 = detail::sort_8lane_4el_dec_4el_asc(r1);
    r1 = detail::bitonic_sort_8lane_finalize_asc(r1);

    T res_max = max(r0, r1);
    T res_min = min(r0, r1);

    r0 = detail::bitonic_sort_8lane_finalize_dec(res_max);
    r1 = detail::bitonic_sort_8lane_finalize_dec(res_min);
    a0.wrapped() = r0;
    a1.wrapped() = r1;
}

} // namespace simdpp
} // namespace SIMDPP_ARCH_NAMESPACE

#endif // LIBSIMDPP_SIMDPP_ALGORITHM_BITONIC_SORT
