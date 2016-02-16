/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_SHUFFLE_SHUFFLE_MASK_H
#define LIBSIMDPP_SIMDPP_DETAIL_SHUFFLE_SHUFFLE_MASK_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#define SIMDPP_SHUFFLE_MASK_2x2(x0, x1) (((x1) << 1) | (x0))
#define SIMDPP_SHUFFLE_MASK_2x2_2(x0, x1) ((SIMDPP_SHUFFLE_MASK_2x2(x0, x1) << 2) | SIMDPP_SHUFFLE_MASK_2x2(x0, x1))

#endif
