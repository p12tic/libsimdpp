/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED3_H
#define LIBSIMDPP_SIMDPP_CORE_LOAD_PACKED3_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/load_packed3.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/** Loads 8-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+45) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+93) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+94) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+95) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void load_packed3(gint8<N>& a, gint8<N>& b, gint8<N>& c, const void* p)
{
    detail::insn::i_load_packed3(a, b, c, p);
}

/** Loads 16-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+45) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+46) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+47) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void load_packed3(gint16<N>& a, gint16<N>& b, gint16<N>& c, const void* p)
{
    detail::insn::i_load_packed3(a, b, c, p);
}

/** Loads 32-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void load_packed3(gint32<N>& a, gint32<N>& b, gint32<N>& c, const void* p)
{
    detail::insn::i_load_packed3(a, b, c, p);
}

/** Loads 64-bit values packed in triplets, de-interleaves them and stores the
    result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3) ]
    b = [ *(p+1), *(p+4) ]
    c = [ *(p+2), *(p+5) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void load_packed3(gint64<N>& a, gint64<N>& b, gint64<N>& c, const void* p)
{
    detail::insn::i_load_packed3(a, b, c, p);
}

/** Loads 32-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), ... , *(p+21) ]
    b = [ *(p+1), *(p+4), *(p+7), ... , *(p+22) ]
    c = [ *(p+2), *(p+5), *(p+8), ... , *(p+23) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void load_packed3(float32<N>& a, float32<N>& b, float32<N>& c, const float* p)
{
    detail::insn::i_load_packed3(a, b, c, p);
}

/** Loads 64-bit floating point values packed in triplets, de-interleaves them
    and stores the result into three vectors.

    @par 128-bit version:
    @code
    a = [ *(p),   *(p+3) ]
    b = [ *(p+1), *(p+4) ]
    c = [ *(p+2), *(p+5) ]
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    a = [ *(p),   *(p+3), *(p+6), *(p+9)  ]
    b = [ *(p+1), *(p+4), *(p+7), *(p+10) ]
    c = [ *(p+2), *(p+5), *(p+8), *(p+11) ]
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void load_packed3(float64<N>& a, float64<N>& b, float64<N>& c, const double* p)
{
    detail::insn::i_load_packed3(a, b, c, p);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

