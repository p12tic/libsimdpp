/*  Copyright (C) 2011-2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMD_H
#define LIBSIMDPP_SIMD_H

/* For documentation, see doc/src/libsimdpp-doc.h or http:// TODO .html
*/

/* The following file sets up the preprocessor variables and includes the
   required system headers for the specific architecture
*/
#include <simdpp/setup_arch.h>

#include <cstdlib>


#include <simdpp/altivec/load1.h>
#include <simdpp/core/align.h>
#include <simdpp/core/aligned_allocator.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/bit_not.h>
#include <simdpp/core/bit_or.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/blend.h>
#include <simdpp/core/cache.h>
#include <simdpp/core/cast.h>
#include <simdpp/core/cmp_eq.h>
#include <simdpp/core/cmp_ge.h>
#include <simdpp/core/cmp_gt.h>
#include <simdpp/core/cmp_le.h>
#include <simdpp/core/cmp_lt.h>
#include <simdpp/core/cmp_neq.h>
#include <simdpp/core/extract.h>
#include <simdpp/core/f_abs.h>
#include <simdpp/core/f_add.h>
#include <simdpp/core/f_ceil.h>
#include <simdpp/core/f_div.h>
#include <simdpp/core/f_floor.h>
#include <simdpp/core/f_fmadd.h>
#include <simdpp/core/f_fmsub.h>
#include <simdpp/core/f_isnan.h>
#include <simdpp/core/f_isnan2.h>
#include <simdpp/core/f_max.h>
#include <simdpp/core/f_min.h>
#include <simdpp/core/f_mul.h>
#include <simdpp/core/f_neg.h>
#include <simdpp/core/f_rcp_e.h>
#include <simdpp/core/f_rcp_rh.h>
#include <simdpp/core/f_rsqrt_e.h>
#include <simdpp/core/f_rsqrt_rh.h>
#include <simdpp/core/f_sign.h>
#include <simdpp/core/f_sqrt.h>
#include <simdpp/core/f_sub.h>
#include <simdpp/core/f_trunc.h>
#include <simdpp/core/i_abs.h>
#include <simdpp/core/i_add.h>
#include <simdpp/core/i_add_sat.h>
#include <simdpp/core/i_avg.h>
#include <simdpp/core/i_avg_trunc.h>
#include <simdpp/core/i_div_p.h>
#include <simdpp/core/i_max.h>
#include <simdpp/core/i_min.h>
#include <simdpp/core/i_mul.h>
#include <simdpp/core/i_mull.h>
#include <simdpp/core/i_neg.h>
#include <simdpp/core/i_shift_l.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/core/i_sub.h>
#include <simdpp/core/i_sub_sat.h>
#include <simdpp/core/insert.h>
#include <simdpp/core/load.h>
#include <simdpp/core/load_packed2.h>
#include <simdpp/core/load_packed3.h>
#include <simdpp/core/load_packed4.h>
#include <simdpp/core/load_splat.h>
#include <simdpp/core/load_u.h>
#include <simdpp/core/make_float.h>
#include <simdpp/core/make_int.h>
#include <simdpp/core/make_uint.h>
#include <simdpp/core/make_shuffle_bytes_mask.h>
#include <simdpp/core/move_l.h>
#include <simdpp/core/move_r.h>
#include <simdpp/core/permute2.h>
#include <simdpp/core/permute4.h>
#include <simdpp/core/permute_bytes16.h>
#include <simdpp/core/permute_zbytes16.h>
#include <simdpp/core/set_splat.h>
#include <simdpp/core/shuffle1.h>
#include <simdpp/core/shuffle2.h>
#include <simdpp/core/shuffle_bytes16.h>
#include <simdpp/core/shuffle_zbytes16.h>
#include <simdpp/core/splat.h>
#include <simdpp/core/splat_n.h>
#include <simdpp/core/store_first.h>
#include <simdpp/core/store.h>
#include <simdpp/core/store_last.h>
#include <simdpp/core/store_packed2.h>
#include <simdpp/core/store_packed3.h>
#include <simdpp/core/store_packed4.h>
#include <simdpp/core/stream.h>
#include <simdpp/core/to_float32.h>
#include <simdpp/core/to_float64.h>
#include <simdpp/core/to_int16.h>
#include <simdpp/core/to_int32.h>
#include <simdpp/core/to_int64.h>
#include <simdpp/core/to_int8.h>
#include <simdpp/core/transpose.h>
#include <simdpp/core/unzip_hi.h>
#include <simdpp/core/unzip_lo.h>
#include <simdpp/core/zip_hi.h>
#include <simdpp/core/zip_lo.h>
#include <simdpp/detail/cast.h>
#include <simdpp/detail/cast.inl>

#include <simdpp/neon/math_int.h>
#include <simdpp/neon/memory_store.h>
#include <simdpp/neon/shuffle.h>

#include <simdpp/detail/null/bitwise.h>
#include <simdpp/detail/null/compare.h>
#include <simdpp/detail/null/foreach.h>
#include <simdpp/detail/null/mask.h>
#include <simdpp/detail/null/math.h>
#include <simdpp/detail/null/memory.h>
#include <simdpp/detail/null/set.h>
#include <simdpp/detail/null/shuffle.h>
#include <simdpp/detail/null/transpose.h>

#include <simdpp/sse/cache.h>
#include <simdpp/sse/compare.h>
#include <simdpp/sse/convert.h>
#include <simdpp/sse/extract_half.h>
#include <simdpp/sse/math_fp.h>
#include <simdpp/sse/math_int.h>
#include <simdpp/sse/memory_load.h>
#include <simdpp/sse/memory_store.h>
#include <simdpp/sse/shuffle.h>

#include <simdpp/types.h>
#include <simdpp/types/generic.h>
#include <simdpp/types/float32.h>
#include <simdpp/types/float32x4.h>
#include <simdpp/types/float32x8.h>
#include <simdpp/types/float64.h>
#include <simdpp/types/float64x2.h>
#include <simdpp/types/float64x4.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/int16.h>
#include <simdpp/types/int16x16.h>
#include <simdpp/types/int16x8.h>
#include <simdpp/types/int32.h>
#include <simdpp/types/int32x4.h>
#include <simdpp/types/int32x8.h>
#include <simdpp/types/int64.h>
#include <simdpp/types/int64x2.h>
#include <simdpp/types/int64x4.h>
#include <simdpp/types/int8.h>
#include <simdpp/types/int8x16.h>
#include <simdpp/types/int8x32.h>
#include <simdpp/types/traits.h>
#include <simdpp/types/generic.inl>

#include <simdpp/operators/bit_and.h>
#include <simdpp/operators/bit_or.h>
#include <simdpp/operators/bit_xor.h>
#include <simdpp/operators/bit_not.h>
#include <simdpp/operators/cmp_eq.h>
#include <simdpp/operators/cmp_neq.h>
#include <simdpp/operators/cmp_ge.h>
#include <simdpp/operators/cmp_gt.h>
#include <simdpp/operators/cmp_le.h>
#include <simdpp/operators/cmp_lt.h>
#include <simdpp/operators/f_add.h>
#include <simdpp/operators/f_mul.h>
#include <simdpp/operators/f_sub.h>
#include <simdpp/operators/i_add.h>
#include <simdpp/operators/i_mul.h>
#include <simdpp/operators/i_shift_l.h>
#include <simdpp/operators/i_shift_r.h>
#include <simdpp/operators/i_sub.h>

/** @def SIMDPP_NO_DISPATCHER
    Disables internal dispatching functionality. If the internal dispathcher
    mechanism is not needed, the user can define the @c SIMDPP_NO_DISPATCHER.
    On cxx98 branch, this results in the library not depending on boost.
*/
#ifndef SIMDPP_NO_DISPATCHER
#include <simdpp/this_compile_arch.h>
#include <simdpp/dispatch/dispatcher.h>
#endif

namespace simdpp {
using namespace SIMDPP_ARCH_NAMESPACE;
namespace detail {
using namespace ::simdpp::SIMDPP_ARCH_NAMESPACE::detail;
} // namespace detail
} // namespace simdpp

#endif
