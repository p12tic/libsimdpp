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

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

template<class V>
V zip_lo(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length/2; i++) {
        r[i*2] = a[i];
        r[i*2+1] = b[i];
    }
    return r;
}

template<class V>
V zip_hi(V a, V b)
{
    V r;
    constexpr unsigned half = V::length/2;
    for (unsigned i = 0; i < half; i++) {
        r[i*2] = a[half+i];
        r[i*2+1] = b[half+i];
    }
    return r;
}

template<unsigned pos, class V>
V broadcast_w(V v)
{
    V r;
    for (unsigned i = 0; i < V::length; i++) {
        r[i] = v[pos];
    }
    return r;
}

template<unsigned shift, class V>
V align(V lo, V hi)
{
    V r;
    for (unsigned i = 0; i < 16-shift; i++) {
        r[i] = lo[i + shift];
    }
    for (unsigned i = 16-shift; i < 16; i++) {
        r[i] = hi[i - 16 + shift];
    }
    return r;
}

template<class V>
V unzip_lo(V a, V b)
{
    V r;
    unsigned half = V::length/2;
    for (unsigned i = 0; i < half; i++) {
        r[i] = a[i*2];
        r[i + half] = b[i*2];
    }
    return r;
}

template<class V>
V unzip_hi(V a, V b)
{
    V r;
    unsigned half = V::length/2;
    for (unsigned i = 0; i < half; i++) {
        r[i] = a[i*2+1];
        r[i + half] = b[i*2+1];
    }
    return r;
}

template<class V>
V blend(V on, V off, V mask)
{
    V r;
     on = bit_and(on, mask);
    off = bit_andnot(off, mask);
      r = bit_or(on, off);
    return r;
}

namespace detail_null {

template<unsigned L> struct blend_mask_impl {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        for (unsigned i = 0; i < L; i++) {
            r[i] = mask[i] ? on[i] : off[i];
        }
        return r;
    }
};

template<> struct blend_mask_impl<1> {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        r[0] = mask[0] ? on[0] : off[0];
        return r;
    }
};
template<> struct blend_mask_impl<2> {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        r[0] = mask[0] ? on[0] : off[0];
        r[1] = mask[1] ? on[1] : off[1];
        return r;
    }
};
template<> struct blend_mask_impl<4> {
    template<class V, class M>
    static V run(V on, V off, M mask)
    {
        V r;
        r[0] = mask[0] ? on[0] : off[0];
        r[1] = mask[1] ? on[1] : off[1];
        r[2] = mask[2] ? on[2] : off[2];
        r[3] = mask[3] ? on[3] : off[3];
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
        r[i] =   a[i + s0];
        r[i+1] = a[i + s1];
    }
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
V permute(V a)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=4) {
        r[i] =   a[i + s0];
        r[i+1] = a[i + s1];
        r[i+2] = a[i + s2];
        r[i+3] = a[i + s3];
    }
    return r;
}

template<unsigned s0, unsigned s1, class V>
V shuffle1(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=2) {
        r[i] =   a[i + s0];
        r[i+1] = b[i + s1];
    }
    return r;
}

template<unsigned s0, unsigned s1, unsigned s2, unsigned s3, class V>
V shuffle2(V a, V b)
{
    V r;
    for (unsigned i = 0; i < V::length; i+=4) {
        r[i] =   a[i + s0];
        r[i+1] = a[i + s1];
        r[i+2] = b[i + s2];
        r[i+3] = b[i + s3];
    }
    return r;
}

} // namespace null
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
