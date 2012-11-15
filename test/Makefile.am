
include $(top_srcdir)/common.mk

check_PROGRAMS = \
        test_simd

test_simd_SOURCES =                 \
    test_case.cc                    \
    test_main.cc                    \
    arch_registration.cc            \
    arch/null_main.cc               \
    arch/null_shuffle.cc            \
    arch/null_shuffle_bytes.cc

test_simd_CXXFLAGS = $(AM_CXXFLAGS) -save-temps

if HAS_SSE2
test_simd_CXXFLAGS += -msse2
test_simd_SOURCES +=                \
    arch/sse2_main.cc               \
    arch/sse2_shuffle.cc            \
    arch/sse2_shuffle_bytes.cc
endif
if HAS_SSE3
test_simd_CXXFLAGS += -msse3
test_simd_SOURCES +=                \
    arch/sse3_main.cc               \
    arch/sse3_shuffle.cc            \
    arch/sse3_shuffle_bytes.cc
endif
if HAS_SSSE3
test_simd_CXXFLAGS += -mssse3
test_simd_SOURCES +=                \
    arch/ssse3_main.cc              \
    arch/ssse3_shuffle.cc           \
    arch/ssse3_shuffle_bytes.cc
endif
if HAS_SSE4_1
test_simd_CXXFLAGS += -msse4.1
test_simd_SOURCES +=                \
    arch/sse4_1_main.cc             \
    arch/sse4_1_shuffle.cc          \
    arch/sse4_1_shuffle_bytes.cc
endif
if HAS_AVX
test_simd_CXXFLAGS += -mavx
test_simd_SOURCES +=                \
    arch/avx_main.cc                \
    arch/avx_shuffle.cc             \
    arch/avx_shuffle_bytes.cc
endif
if HAS_AVX2
test_simd_CXXFLAGS += -mavx2
test_simd_SOURCES +=                \
arch/avx2_main.cc                   \
arch/avx2_shuffle.cc                \
arch/avx2_shuffle_bytes.cc
endif

if HAS_NEON
test_simd_CXXFLAGS += -mfpu=neon
test_simd_SOURCES +=                \
    arch/neon_main.cc               \
    arch/neon_shuffle.cc            \
    arch/neon_shuffle_bytes.cc      \
    arch/neon_vfp_sp_main.cc        \
    arch/neon_vfp_sp_shuffle.cc     \
    arch/neon_vfp_sp_shuffle_bytes.cc   \
    arch/neon_vfp_dp_main.cc        \
    arch/neon_vfp_dp_shuffle.cc     \
    arch/neon_vfp_dp_shuffle_bytes.cc
endif

TESTS = test_simd
