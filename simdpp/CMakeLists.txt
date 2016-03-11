#   Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>
#
#   Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

set(HEADERS
    adv/detail/transpose.h
    adv/transpose.h
    altivec/load1.h
    core/align.h
    core/bit_and.h
    core/bit_andnot.h
    core/bit_not.h
    core/bit_or.h
    core/bit_xor.h
    core/blend.h
    core/broadcast.h
    core/splat.h
    core/cache.h
    core/cast.h
    core/cmp_eq.h
    core/cmp_ge.h
    core/cmp_gt.h
    core/cmp_le.h
    core/cmp_lt.h
    core/cmp_neq.h
    core/detail/cast.h
    core/detail/cast.inl
    core/detail/i_shift.h
    core/detail/mem_pack.h
    core/detail/mem_unpack.h
    core/detail/move_signed.h
    core/detail/shuffle128.h
    core/detail/shuffle_emul.h
    core/extract.h
    core/f_abs.h
    core/f_add.h
    core/f_ceil.h
    core/f_div.h
    core/f_floor.h
    core/f_fmadd.h
    core/f_fmsub.h
    core/f_isnan.h
    core/f_isnan2.h
    core/f_max.h
    core/f_min.h
    core/f_mul.h
    core/f_neg.h
    core/f_rcp_e.h
    core/f_rcp_rh.h
    core/f_rsqrt_e.h
    core/f_rsqrt_rh.h
    core/f_sign.h
    core/f_sqrt.h
    core/f_sub.h
    core/f_trunc.h
    core/i_abs.h
    core/i_add.h
    core/i_adds.h
    core/i_avg.h
    core/i_avg_trunc.h
    core/i_div_p.h
    core/i_max.h
    core/i_min.h
    core/i_mul.h
    core/i_mull.h
    core/i_neg.h
    core/i_shift_l.h
    core/i_shift_r.h
    core/i_sub.h
    core/i_subs.h
    core/insert.h
    core/load.h
    core/load_packed2.h
    core/load_packed3.h
    core/load_packed4.h
    core/load_u.h
    core/make_shuffle_bytes_mask.h
    core/move_l.h
    core/move_r.h
    core/permute2.h
    core/permute4.h
    core/permute_bytes16.h
    core/permute_zbytes16.h
    core/shuffle1.h
    core/shuffle2.h
    core/shuffle_bytes16.h
    core/shuffle_zbytes16.h
    core/store.h
    core/store_first.h
    core/store_last.h
    core/store_packed2.h
    core/store_packed3.h
    core/store_packed4.h
    core/store_u.h
    core/stream.h
    core/to_float32.h
    core/to_float64.h
    core/to_int16.h
    core/to_int32.h
    core/to_int64.h
    core/to_int8.h
    core/unzip_hi.h
    core/unzip_lo.h
    core/zip_hi.h
    core/zip_lo.h
    detail/align.h
    detail/mem_block.h
    detail/not_implemented.h
    detail/width.h
    detail/word_size.h
    dispatch/arch.h
    dispatch/dispatcher.h
    dispatch/get_arch_gcc_builtin_cpu_supports.h
    dispatch/get_arch_linux_cpuinfo.h
    dispatch/macros.h
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
    null/mask.h
    null/math.h
    null/memory.h
    null/set.h
    null/shuffle.h
    null/transpose.h
    setup_arch.h
    simd.h
    sse/cache.h
    sse/compare.h
    sse/convert.h
    sse/extract_half.h
    sse/math_int.h
    sse/memory_load.h
    sse/memory_store.h
    sse/shuffle.h
    this_compile_arch.h
    types.h
    types/float32.h
    types/float32x4.h
    types/float32x8.h
    types/float64.h
    types/float64x2.h
    types/float64x4.h
    types/fwd.h
    types/int16.h
    types/int16x16.h
    types/int16x8.h
    types/int32.h
    types/int32x4.h
    types/int32x8.h
    types/int64.h
    types/int64x2.h
    types/int64x4.h
    types/int8.h
    types/int8x16.h
    types/int8x32.h
    types/traits.h
)

foreach(FILE ${HEADERS})
    get_filename_component(FILE_PATH "${FILE}" PATH)
    install(FILES "${FILE}" DESTINATION "${SIMDPP_INCLUDEDIR}/simdpp/${FILE_PATH}")
endforeach()

simdpp_get_compilable_archs(COMPILABLE_ARCHS)
set(HEADER_TESTS "")
foreach(ARCH ${COMPILABLE_ARCHS})
    simdpp_get_arch_info(CXX_FLAGS DEFINES_LIST SUFFIX ${ARCH})
    foreach(FILE ${HEADERS})
        string(REPLACE "/" "_" TEST "${FILE}")
        string(REPLACE "." "_" TEST "${TEST}")
        set(TEST "check_headers/test_header_compiles_${TEST}${SUFFIX}")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/check_headers")
        separate_arguments(CXX_FLAGS)
        add_custom_command(
            OUTPUT ${TEST}
            COMMAND ${CMAKE_CXX_COMPILER}
                    -DLIBSIMDPP_SIMD_H
                    -I "${CMAKE_SOURCE_DIR}"
                    ${CXX_FLAGS} -x c++ -std=c++11 -g2 -Wall
                    ${CMAKE_SOURCE_DIR}/simdpp/${FILE}
                    -c -o ${CMAKE_BINARY_DIR}/${TEST}
            DEPENDS ${FILE} )
        #add_executable(${TEST} EXCLUDE_FROM_ALL ${FILE})
        #set_target_properties(${TEST} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS} -std=c++11 -g2 -Wall")
        #add_dependencies(check_headers "${TEST}")
        set(HEADER_TESTS ${HEADER_TESTS} ${TEST})
    endforeach()
endforeach()

add_custom_target(check_headers DEPENDS ${HEADER_TESTS})
