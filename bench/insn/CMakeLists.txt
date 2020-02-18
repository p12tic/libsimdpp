include_directories(${libsimdpp_SOURCE_DIR})
include_directories(${GOOGLE_BENCHMARK_INCLUDE_DIRS})

set(TEST_BENCH_SOURCES
    main.cc
    main.h
)

set(BENCH_INSN_ARCH_SOURCES
  algorithm/transform_unary.cc
  algorithm/transform_binary.cc
  algorithm/reduce_unary.cc
  algorithm/reduce_binary.cc
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
  if(SIMDPP_MSVC)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # enable _vectorcall on i386 builds (only works on MSVC 2013)
        #set_target_properties(${exename} PROPERTIES COMPILE_FLAGS "/Gv")
    endif()
  elseif(SIMDPP_MSVC_INTEL)
    set_target_properties(${exename} PROPERTIES COMPILE_FLAGS "/Qstd=c++11")
  else()
    # Xcode clang linker spends very long time in deduplication pass when
    # linking the test executable unless -fvisibility-inlines-hidden is passed.
    set_target_properties(${exename} PROPERTIES COMPILE_FLAGS "-std=c++11 -O2 -Wall -Wextra -fvisibility-inlines-hidden")
  endif()
  if(WIN32)
    target_link_libraries(${exename}
    PUBLIC benchmark  
    PUBLIC shlwapi.lib
    )
  else()
   target_link_libraries(${exename}
     PUBLIC benchmark
     PUBLIC pthread
    )
  add_dependencies(${exename} ${GOOGLE_BENCHMARK})  
  endif()
endforeach(ARCH ${${COMPILABLE_ARCHS}})


