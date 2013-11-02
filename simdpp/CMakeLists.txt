#   libsimdpp
#   Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#
#   * Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#   POSSIBILITY OF SUCH DAMAGE.

set(HEADERS
    simd.h


    dispatch/arch.h
    dispatch/dispatcher.h
    dispatch/get_arch_gcc_builtin_cpu_supports.h
    dispatch/get_arch_linux_cpuinfo.h
    dispatch/macros.h

    altivec/load1.h

    neon/detail/math_shift.h
    neon/detail/shuffle.h
    neon/detail/shuffle_int16x8.h
    neon/detail/shuffle_int32x4.h
    neon/detail/shuffle_int64x2.h
    neon/math_int.h
    neon/memory_store.h
    neon/shuffle.h

    null/bitwise.h
    null/compare.h
    null/foreach.h
    null/math.h
    null/mask.h
    null/memory.h
    null/set.h
    null/shuffle.h
    null/transpose.h

    simd/detail/align.h
    simd/detail/not_implemented.h
    simd/detail/move_signed.h
    simd/detail/mem_block.h
    simd/detail/mem_pack.h
    simd/detail/mem_unpack.h
    simd/detail/shuffle128.h
    simd/detail/shuffle_emul.h
    simd/detail/transpose.h
    simd/detail/width.h
    simd/detail/word_size.h

    simd/bitwise.h
    simd/cache.h
    simd/cast.h
    simd/compare.h
    simd/convert.h
    simd/extract.h
    simd/float32x4.h
    simd/float32x4.inl
    simd/float32x8.h
    simd/float32x8.inl
    simd/float64x2.h
    simd/float64x2.inl
    simd/float64x4.h
    simd/float64x4.inl
    simd/fwd.h
    simd/insert.h
    simd/int128.h
    simd/int128.inl
    simd/int16x16.h
    simd/int16x16.inl
    simd/int16x8.h
    simd/int16x8.inl
    simd/int256.h
    simd/int256.inl
    simd/int32x4.h
    simd/int32x4.inl
    simd/int32x8.h
    simd/int32x8.inl
    simd/int64x2.h
    simd/int64x2.inl
    simd/int64x4.h
    simd/int64x4.inl
    simd/int8x16.h
    simd/int8x16.inl
    simd/int8x32.h
    simd/int8x32.inl
    simd/make_shuffle_bytes_mask.h
    simd/math_fp_adv.h
    simd/math_fp_basic.h
    simd/math_int_adv.h
    simd/math_int_basic.h
    simd/math_shift.h
    simd/memory_load.h
    simd/memory_store.h
    simd/shuffle_bytes.h
    simd/shuffle_generic.h
    simd/shuffle.h
    simd/this_compile_arch.h
    simd/traits.h
    simd/transpose.h
    simd/types.h

    sse/cache.h
    sse/compare.h
    sse/convert.h
    sse/extract_half.h
    sse/math_fp.h
    sse/math_int.h
    sse/memory_load.h
    sse/memory_store.h
    sse/shuffle.h
)

foreach(FILE ${HEADERS})
    get_filename_component(FILE_PATH "${FILE}" PATH)
    install(FILES "${FILE}" DESTINATION "${SIMDPP_INCLUDEDIR}/simdpp/${FILE_PATH}")
endforeach()
