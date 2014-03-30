/*  libsimdpp
    Copyright (C) 2012  Povilas Kanapickas tir5c3@yahoo.co.uk
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

#ifndef LIBSIMDPP_SIMDPP_TYPES_H
#define LIBSIMDPP_SIMDPP_TYPES_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif
#include <simdpp/setup_arch.h>

#include <simdpp/expr.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int8x16.h>
#include <simdpp/types/int16x8.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/types/int64x2.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/int8x32.h>
#include <simdpp/types/int16x16.h>
#include <simdpp/types/int32x8.h>
#include <simdpp/types/int64x4.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/types/float64x4.h>
#include <simdpp/types/int8.h>
#include <simdpp/types/int16.h>
#include <simdpp/types/int32.h>
#include <simdpp/types/int64.h>
#include <simdpp/types/float32.h>
#include <simdpp/types/float64.h>
#include <simdpp/types/generic.h>

#define SIMDPP_VEC_ARRAY_IMPL1(RTYPE, OP, V1)                   \
    RTYPE r; for (unsigned i = 0; i < RTYPE::vec_length; ++i) { \
        r[i] = OP((V1)[i]); }                                   \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL2(RTYPE, OP, V1, V2)               \
    RTYPE r; for (unsigned i = 0; i < RTYPE::vec_length; ++i) { \
        r[i] = OP((V1)[i], (V2)[i]); }                          \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL2S(RTYPE, OP, V1, A2)              \
    RTYPE r; for (unsigned i = 0; i < RTYPE::vec_length; ++i) { \
        r[i] = OP((V1)[i], (A2)); }                             \
    return r;

#define SIMDPP_VEC_ARRAY_IMPL3(RTYPE, OP, V1, V2, V3)           \
    RTYPE r; for (unsigned i = 0; i < RTYPE::vec_length; ++i) { \
        r[i] = OP((V1)[i], (V2)[i], (V3)[i]);                   \
    }                                                           \
    return r;

#endif
