
include $(top_srcdir)/common.mk

check_PROGRAMS = \
        test_simd

test_simd_SOURCES =                 \
    test_case.cc                    \
    test_main.cc                    \
    arch_registration.cc

SIMD_TESTS = \
    tests/bitwise.cc        \
    tests/compare.cc        \
    tests/construct.cc      \
    tests/convert.cc        \
    tests/math_int.cc       \
    tests/math_fp.cc        \
    tests/math_shift.cc     \
    tests/memory_load.cc    \
    tests/memory_store.cc   \
    tests/shuffle.cc        \
    tests/shuffle_bytes.cc  \
    tests/shuffle_generic.cc  \
    tests/transpose.cc

test_simd_CXXFLAGS = $(AM_CXXFLAGS)

test_simd_LDADD += test_simd_null
test_simd_null_CXXFLAGS +=
test_simd_null_SOURCES = $(SIMD_TESTS)

if HAS_SSE2
test_simd_LDADD += test_simd_sse2
test_simd_sse2_CXXFLAGS += -msse2 -DSIMDPP_ARCH_X86_SSE2
test_simd_sse2_SOURCES = $(SIMD_TESTS)
endif

if HAS_SSE3
test_simd_LDADD += test_simd_sse3
test_simd_sse3_CXXFLAGS += -msse3 -DSIMDPP_ARCH_X86_SSE3
test_simd_sse3_SOURCES = $(SIMD_TESTS)
endif

if HAS_SSSE3
test_simd_LDADD += test_simd_ssse3
test_simd_ssse3_CXXFLAGS += -mssse3 -DSIMDPP_ARCH_X86_SSSE3
test_simd_ssse3_SOURCES = $(SIMD_TESTS)
endif

if HAS_SSE4_1
test_simd_LDADD += test_simd_sse4_1
test_simd_sse4_1_CXXFLAGS += -msse4.1 -DSIMDPP_ARCH_X86_SSE4_1
test_simd_sse4_1_SOURCES = $(SIMD_TESTS)
endif

if HAS_AVX
test_simd_LDADD += test_simd_avx
test_simd_avx_CXXFLAGS += -mavx -DSIMDPP_ARCH_X86_AVX
test_simd_avx_SOURCES = $(SIMD_TESTS)
endif

if HAS_AVX2
test_simd_LDADD += test_simd_avx2
test_simd_avx2_CXXFLAGS += -mavx -DSIMDPP_ARCH_X86_AVX2
test_simd_avx2_SOURCES = $(SIMD_TESTS)
endif

if HAS_NEON
test_simd_LDADD += test_simd_neon
test_simd_neon_CXXFLAGS += -mfpu=neon -DSIMDPP_ARCH_ARM_NEON
test_simd_neon_SOURCES = $(SIMD_TESTS)

test_simd_LDADD += test_simd_neon_flt_sp
test_simd_neon_flt_sp_CXXFLAGS += -mfpu=neon -DSIMDPP_ARCH_ARM_NEON_FLT_SP
test_simd_neon_flt_sp_SOURCES = $(SIMD_TESTS)
endif

TESTS = test_simd
