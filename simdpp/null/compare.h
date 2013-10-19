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

#ifndef LIBSIMDPP_NULL_COMPARE_H
#define LIBSIMDPP_NULL_COMPARE_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/null/traits.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace null {

template<class V>
typename traits<V>::int_vector_type cmp_eq(V a, V b)
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] == b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

template<class V>
typename traits<V>::int_vector_type cmp_neq(V a, V b)
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] != b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

template<class V>
typename traits<V>::int_vector_type cmp_lt(V a, V b)
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] < b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

template<class V>
typename traits<V>::int_vector_type cmp_gt(V a, V b)
{
    typename traits<V>::int_vector_type r;
    for (unsigned i = 0; i < traits<V>::length; i++) {
        r[i] = (a[i] > b[i]) ? traits<V>::all_bits : 0;
    }
    return r;
}

} // namespace null
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
