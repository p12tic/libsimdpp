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

#ifndef LIBSIMDPP_SIMDPP_TYPES_TAG_H
#define LIBSIMDPP_SIMDPP_TYPES_TAG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

/*  The values of the tags are such that it is easy to retrieve the result type
    of an operation that involves two different types. That is, if the
    arguments have types with type tags A and B then the type tag of the result
    type will be max(A, B). Similarly, if the arguments have types with size
    tags P and Q then the size tag of the result type will be max(P, Q).

    The only exception is operation on masks with masks with different size
    tags. In that case the type tag of the result type is always TAG_UINT.

    Several examples:

    mask_int32 | mask_float32 -> mask_float32
    mask_int32 | uint32 -> uint32
    int32 | int32 -> int32
    int32 | uint32 -> uint32

    int8 | uint32 -> uint32
    int8 | float32 -> float32
    int8 | mask_int32 -> int32

    mask_int8 | mask_int32 -> uint32
    mask_int8 | mask_float32 -> uint32

    See also simdpp/detail/get_expr.h

    If particular operation does not support masks, the masks are expanded
    internally. If both arguments are masks, then the result type is the
    underlying type of the mask type which would be retrieved using the usual
    rules (see get_expr2_nomask).

    Several examples:

    mask_int32 + mask_int32 -> uint32
    int32 + mask_int32 -> int32
    uint32 + mask_int32 -> uint32
*/
#define SIMDPP_TAG_MASK_INT     1
#define SIMDPP_TAG_MASK_FLOAT   2
#define SIMDPP_TAG_INT          3
#define SIMDPP_TAG_UINT         4
#define SIMDPP_TAG_FLOAT        5
#define SIMDPP_TAG_SIZE8        10
#define SIMDPP_TAG_SIZE16       20
#define SIMDPP_TAG_SIZE32       30
#define SIMDPP_TAG_SIZE64       40

#endif
