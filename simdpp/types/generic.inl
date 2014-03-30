/*  libsimdpp
    Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>
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

#ifndef LIBSIMDPP_SIMD_TYPES_GENERIC_INL
#define LIBSIMDPP_SIMD_TYPES_GENERIC_INL

#include <simdpp/setup_arch.h>
#include <simdpp/expr.h>
#include <simdpp/detail/expr/vec.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

template<unsigned N, class E> float32<N>           float32<N,E>::eval() const { return (float32<N>) detail::expr_eval(e); }
template<unsigned N, class E> mask_float32<N> mask_float32<N,E>::eval() const { return (mask_float32<N>) detail::expr_eval(e); }

template<unsigned N, class E> float64<N>           float64<N,E>::eval() const { return (float64<N>) detail::expr_eval(e); }
template<unsigned N, class E> mask_float64<N> mask_float64<N,E>::eval() const { return (mask_float64<N>) detail::expr_eval(e); }

template<unsigned N, class E> int8<N>           int8<N,E>::eval() const { return (int8<N>)      detail::expr_eval(e); }
template<unsigned N, class E> uint8<N>         uint8<N,E>::eval() const { return (uint8<N>)     detail::expr_eval(e); }
template<unsigned N, class E> mask_int8<N> mask_int8<N,E>::eval() const { return (mask_int8<N>) detail::expr_eval(e); }

template<unsigned N, class E> int16<N>           int16<N,E>::eval() const { return (int16<N>)      detail::expr_eval(e); }
template<unsigned N, class E> uint16<N>         uint16<N,E>::eval() const { return (uint16<N>)     detail::expr_eval(e); }
template<unsigned N, class E> mask_int16<N> mask_int16<N,E>::eval() const { return (mask_int16<N>) detail::expr_eval(e); }

template<unsigned N, class E> int32<N>           int32<N,E>::eval() const { return (int32<N>)      detail::expr_eval(e); }
template<unsigned N, class E> uint32<N>         uint32<N,E>::eval() const { return (uint32<N>)     detail::expr_eval(e); }
template<unsigned N, class E> mask_int32<N> mask_int32<N,E>::eval() const { return (mask_int32<N>) detail::expr_eval(e); }

template<unsigned N, class E> int64<N>           int64<N,E>::eval() const { return (int64<N>)      detail::expr_eval(e); }
template<unsigned N, class E> uint64<N>         uint64<N,E>::eval() const { return (uint64<N>)     detail::expr_eval(e); }
template<unsigned N, class E> mask_int64<N> mask_int64<N,E>::eval() const { return (mask_int64<N>) detail::expr_eval(e); }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
