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

#ifndef LIBSIMDPP_SIMDPP_CORE_BLEND_H
#define LIBSIMDPP_SIMDPP_CORE_BLEND_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/blend.h>
#include <simdpp/detail/expr/blend.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xff ) ? on0 : off0
    ...
    rN = (maskN == 0xff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}
    @icost{XOP, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
    @icost{XOP, 2}
*/
template<unsigned N, class E1, class E2, class E3>
gint8<N, expr_blend<gint8<N,E1>,
                    gint8<N,E2>,
                    gint8<N,E3>>> blend(gint8<N,E1> on,
                                        gint8<N,E2> off,
                                        gint8<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
gint8<N, expr_blend<gint8<N,E1>,
                    gint8<N,E2>,
                    mask_int8<N,E3>>> blend(gint8<N,E1> on,
                                            gint8<N,E2> off,
                                            mask_int8<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}
/// @}

/// @{
/** Composes vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2, class E3>
gint16<N, expr_blend<gint16<N,E1>,
                     gint16<N,E2>,
                     gint16<N,E3>>> blend(gint16<N,E1> on,
                                          gint16<N,E2> off,
                                          gint16<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
gint16<N, expr_blend<gint16<N,E1>,
                     gint16<N,E2>,
                     mask_int16<N,E3>>> blend(gint16<N,E1> on,
                                              gint16<N,E2> off,
                                              mask_int16<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2, class E3>
gint32<N, expr_blend<gint32<N,E1>,
                     gint32<N,E2>,
                     gint32<N,E3>>> blend(gint32<N,E1> on,
                                          gint32<N,E2> off,
                                          gint32<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
gint32<N, expr_blend<gint32<N,E1>,
                     gint32<N,E2>,
                     gint32<N,E3>>> blend(gint32<N,E1> on,
                                          gint32<N,E2> off,
                                          mask_int32<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 3}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2, class E3>
gint64<N, expr_blend<gint64<N,E1>,
                     gint64<N,E2>,
                     gint64<N,E3>>> blend(gint64<N,E1> on,
                                          gint64<N,E2> off,
                                          gint64<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
gint64<N, expr_blend<gint64<N,E1>,
                     gint64<N,E2>,
                     mask_int64<N,E3>>> blend(gint64<N,E1> on,
                                              gint64<N,E2> off,
                                              mask_int64<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}
/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 3}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned N, class E1, class E2, class E3>
float32<N, expr_blend<float32<N,E1>,
                      float32<N,E2>,
                      float32<N,E3>>> blend(float32<N,E1> on,
                                            float32<N,E2> off,
                                            float32<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
float32<N, expr_blend<float32<N,E1>,
                      float32<N,E2>,
                      mask_float32<N,E3>>> blend(float32<N,E1> on,
                                                 float32<N,E2> off,
                                                 mask_float32<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
float32<N, expr_blend<float32<N,E1>,
                      float32<N,E2>,
                      gint32<N,E3>>> blend(float32<N,E1> on,
                                           float32<N,E2> off,
                                           gint32<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

/// @}

/// @{
/** Composes a vector from two sources according to a mask. Each element within
    the mask must have either all bits set or all bits unset.

    @code
    r0 = (mask0 == 0xffffffffffffffff ) ? on0 : off0
    ...
    rN = (maskN == 0xffffffffffffffff ) ? onN : offN
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 3}
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 6}
    @novec{NEON, ALTIVEC}
*/
template<unsigned N, class E1, class E2, class E3>
float64<N, expr_blend<float64<N,E1>,
                      float64<N,E2>,
                      float64<N,E3>>> blend(float64<N,E1> on,
                                            float64<N,E2> off,
                                            float64<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
float64<N, expr_blend<float64<N,E1>,
                      float64<N,E2>,
                      gint64<N,E3>>> blend(float64<N,E1> on,
                                           float64<N,E2> off,
                                           gint64<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}

template<unsigned N, class E1, class E2, class E3>
float64<N, expr_blend<float64<N,E1>,
                      float64<N,E2>,
                      mask_float64<N,E3>>> blend(float64<N,E1> on,
                                                 float64<N,E2> off,
                                                 mask_float64<N,E3> mask)
{
    return { { on, off, mask }, 0 };
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif

