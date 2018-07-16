include_directories(${libsimdpp_SOURCE_DIR})
include_directories(${GOOGLE_BENCHMARK_INCLUDE_DIRS})

set(TEST_BENCH_SOURCES
    main.cc
    main.h
)

set(BENCH_INSN_ARCH_SOURCES
  algorithm/transform_unary.cc
  algorithm/reduce_unary.cc
  load_store.cc
  )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
foreach(ARCH ${COMPILABLE_ARCHS}})
  simdpp_get_arch_info(CXX_FLAGS DEFINES_LIST SUFFIX ${ARCH})
  #message("Create benchmark for arch : ${SUFFIX} with flags: ${CXX_FLAGS} with defines ${DEFINES_LIST}")
  SET(exename "bench_insn_${SUFFIX}")
  add_executable(${exename} ${BENCH_INSN_ARCH_SOURCES} ${TEST_BENCH_SOURCES})
  set_target_properties( ${exename} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}" )
  set_target_properties (${exename} PROPERTIES FOLDER bench)
  if(WIN32)
    target_link_libraries(${exename}
    PUBLIC benchmark  
    PUBLIC shlwapi.lib
    )
  else()
   target_link_libraries(${exename}
    PUBLIC benchmark  
    )
  add_dependencies(${exename} ${GOOGLE_BENCHMARK})  
  endif()
endforeach(ARCH ${${COMPILABLE_ARCHS}})


