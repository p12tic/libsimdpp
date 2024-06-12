#   Copyright (C) 2024  Povilas Kanapickas <povilas@radix.lt>
#
#   Distributed under the Boost Software License, Version 1.0.
#       (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

set(SOURCES
    main.cc
)

set(ARCH_SOURCES
    checks.cc
    log_approx.cc
)

set(ARCH_GEN_SOURCES "")

find_package(OpenMP REQUIRED)

foreach(SRC ${ARCH_SOURCES})
    simdpp_multiarch(ARCH_GEN_SOURCES ${SRC} ${COMPILABLE_ARCHS})
endforeach()

add_executable(test_math_accuracy
    ${SOURCES}
    ${ARCH_GEN_SOURCES}
)

target_link_libraries(test_math_accuracy OpenMP::OpenMP_CXX)

target_include_directories(test_math_accuracy PUBLIC ${libsimdpp_SOURCE_DIR})
