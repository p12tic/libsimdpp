/*  libsimdpp
    Copyright (C) 2011-2012  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_NULL_SHUFFLE_H
#define LIBSIMDPP_NULL_SHUFFLE_H
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || defined(DOXYGEN_SHOULD_READ_THIS)

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_or.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

namespace null_detail {

template<class V>
V zip_lo_impl(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length/2; i++) {
        r.el(i*2) = a.el(i);
        r.el(i*2+1) = b.el(i);
    }
    return r;
}

template<class V>
V zip_hi_impl(V a, V b)
{
    V r;
    constexpr unsigned half = V::length/2;
    for (unsigned i = 0; i < half; i++) {
        r.el(i*2) = a.el(half+i);
        r.el(i*2+1) = b.el(half+i);
    }
    return r;
}


template<class V>
V unzip_lo_impl(V a, V b)
{
    V r;
    unsigned half = V::length/2;
    for (unsigned i = 0; i < half; i++) {
        r.el(i) = a.el(i*2);
        r.el(i + half) = b.el(i*2);
    }
    return r;
}

template<class V>
V unzip_hi_impl(V a, V b)
{
    V r;
    unsigned half = V::length/2;
    for (unsigned i = 0; i < half; i++) {
        r.el(i) = a.el(i*2+1);
        r.el(i + half) = b.el(i*2+1);
    }
    return r;
}

} // namespace null_detail

template<class V> V zip16_lo(V a, V b) { return null_detail::zip_lo_impl(a, b); }
template<class V> V zip8_lo(V a, V b)  { return null_detail::zip_lo_impl(a, b); }
template<class V> V zip4_lo(V a, V b)  { return null_detail::zip_lo_impl(a, b); }
template<class V> V zip2_lo(V a, V b)  { return null_detail::zip_lo_impl(a, b); }
template<class V> V zip16_hi(V a, V b) { return null_detail::zip_hi_impl(a, b); }
template<class V> V zip8_hi(V a, V b)  { return null_detail::zip_hi_impl(a, b); }
template<class V> V zip4_hi(V a, V b)  { return null_detail::zip_hi_impl(a, b); }
template<class V> V zip2_hi(V a, V b)  { return null_detail::zip_hi_impl(a, b); }

template<class V> V unzip16_lo(V a, V b) { return null_detail::unzip_lo_impl(a, b); }
template<class V> V unzip8_lo(V a, V b)  { return null_detail::unzip_lo_impl(a, b); }
template<class V> V unzip4_lo(V a, V b)  { return null_detail::unzip_lo_impl(a, b); }
template<class V> V unzip2_lo(V a, V b)  { return null_detail::unzip_lo_impl(a, b); }
template<class V> V unzip16_hi(V a, V b) { return null_detail::unzip_hi_impl(a, b); }
template<class V> V unzip8_hi(V a, V b)  { return null_detail::unzip_hi_impl(a, b); }
template<class V> V unzip4_hi(V a, V b)  { return null_detail::unzip_hi_impl(a, b); }
template<class V> V unzip2_hi(V a, V b)  { return null_detail::unzip_hi_impl(a, b); }

template<unsigned pos, class V>
V splat(V v)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r.el(i) = v.el(pos);
    }
    return r;
}

template<unsigned shift, class V>
V align(V lo, V hi)
{
    V r;
    for (unsigned i = 0; i < 16-shift; i++) {
        r.el(i) = lo.el(i + shift);
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r.el(i) = hi.el(i - 16 + shift);
    }
    return r;
}

template<class V>
V blend(V on, V off, V mask)
{
    V r;
     on = null::bit_and(on, mask);
    off = null::bit_andnot(off, mask);
      r = null::bit_or(on, off);
    return r;
}

namespace detail_null {

template<unsigned L> struct blend_mask_impl {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        for (unsigned i = 0; i < L; i++) {
            r.el(i) = mask.el(i) ? on.el(i) : off.el(i);
        }
        return r;
    }
};

template<> struct blend_mask_impl<1> {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        r.el(0) = mask.el(0) ? on.el(0) : off.el(0);
        return r;
    }
};
template<> struct blend_mask_impl<2> {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        r.el(0) = mask.el(0) ? on.el(0) : off.el(0);
        r.el(1) = mask.el(1) ? on.el(1) : off.el(1);
        return r;
    }
};
template<> struct blend_mask_impl<4> {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        r.el(0) = mask.el(0) ? on.el(0) : off.el(0);
        r.el(1) = mask.el(1) ? on.el(1) : off.el(1);
        r.el(2) = mask.el(2) ? on.el(2) : off.el(2);
        r.el(3) = mask.el(3) ? on.el(3) : off.el(3);
        return r;
    }
};

} // namespace detail_null

template<class V, class M>
V blend_mask(V on, V off, M mask)
{
    return detail_null::blend_mask_impl<V::length>::run(on, off, mask);
}

template<unsigned s0, unsigned s1, class V>
V permute(V a)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=2) {
        r.el(i) =   a.el(i + s0);
        r.el(i+1) = a.el(i + s1);
    }
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
V permute(V a)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=4) {
        r.el(i) =   a.el(i + s0);
        r.el(i+1) = a.el(i + s1);
        r.el(i+2) = a.el(i + s2);
        r.el(i+3) = a.el(i + s3);
    }
    return r;
}

template<unsigned s0, unsigned s1, class V>
V shuffle1(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=2) {
        r.el(i) =   a.el(i + s0);
        r.el(i+1) = b.el(i + s1);
    }
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
V shuffle2(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=4) {
        r.el(i) =   a.el(i + s0);
        r.el(i+1) = a.el(i + s1);
        r.el(i+2) = b.el(i + s2);
        r.el(i+3) = b.el(i + s3);
    }
    return r;
}

} // namespace null
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
#endif
