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

#ifndef LIBSIMDPP_SIMDPP_CORE_STORE_PACKED2_H
#define LIBSIMDPP_SIMDPP_CORE_STORE_PACKED2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/store_packed2.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/** Interleaves 8-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+30) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+62) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+63) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void store_packed2(void* p, gint8<N> a, gint8<N> b)
{
    detail::insn::i_store_packed2(reinterpret_cast<char*>(p), a, b);
}

/** Interleaves 16-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+30) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+31) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void store_packed2(void* p, gint16<N> a, gint16<N> b)
{
    detail::insn::i_store_packed2(reinterpret_cast<char*>(p), a, b);
}

/** Interleaves 32-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), *(p+6) ] = a
    [ *(p+1), *(p+3), *(p+5), *(p+7) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void store_packed2(void* p, gint32<N> a, gint32<N> b)
{
    detail::insn::i_store_packed2(reinterpret_cast<char*>(p), a, b);
}

/** Interleaves 64-bit values from two vectors and stores the result into
    successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2) ] = a
    [ *(p+1), *(p+3) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void store_packed2(void* p, gint64<N> a, gint64<N> b)
{
    detail::insn::i_store_packed2(reinterpret_cast<char*>(p), a, b);
}

/** Interleaves 32-bit floating-point values from two vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+6) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+7) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), ... , *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), ... , *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes.
*/
template<unsigned N>
void store_packed2(void* p, float32<N> a, float32<N> b)
{
    detail::insn::i_store_packed2(reinterpret_cast<char*>(p), a, b);
}

/** Interleaves 64-bit floating-point values from two vectors and stores
    the result into successive locations starting from @a p.

    @par 128-bit version:
    @code
    [ *(p),   *(p+2) ] = a
    [ *(p+1), *(p+3) ] = b
    @endcode
    @a p must be aligned to 16 bytes.

    @par 256-bit version:
    @code
    [ *(p),   *(p+2), *(p+4), *(p+14) ] = a
    [ *(p+1), *(p+3), *(p+5), *(p+15) ] = b
    @endcode
    @a p must be aligned to 32 bytes
*/
template<unsigned N>
void store_packed2(void* p, float64<N> a, float64<N> b)
{
    detail::insn::i_store_packed2(reinterpret_cast<char*>(p), a, b);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

