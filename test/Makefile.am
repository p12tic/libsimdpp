
include $(top_srcdir)/common.mk

check_PROGRAMS = \
        test_simd

test_simd_CXXFLAGS = $(AM_CXXFLAGS)
test_simd_SOURCES =                 \
    test_case.cc                    \
    test_main.cc                    \
    arch_registration.cc

SIMD_TESTS = \
    tests/bitwise.cc        \
    tests/compare.cc        \
    tests/construct.cc      \
    tests/convert.cc        \
    tests/main.cc           \
    tests/math_int.cc       \
    tests/math_fp.cc        \
    tests/math_shift.cc     \
    tests/memory_load.cc    \
    tests/memory_store.cc   \
    tests/shuffle.cc        \
    tests/shuffle_bytes.cc  \
    tests/shuffle_generic.cc  \
    tests/transpose.cc

SIMD_TESTS_CXXFLAGS = $(AM_CXXFLAGS)

noinst_LIBRARIES = libtest_simd_null.a
test_simd_DEPENDENCIES = libtest_simd_null.a
test_simd_LDFLAGS = -Wl,--whole-archive libtest_simd_null.a -Wl,--no-whole-archive
libtest_simd_null_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS)
libtest_simd_null_a_SOURCES = $(SIMD_TESTS)

if HAS_SSE2
noinst_LIBRARIES += libtest_simd_sse2.a
test_simd_DEPENDENCIES += libtest_simd_sse2.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_sse2.a -Wl,--no-whole-archive
libtest_simd_sse2_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -msse2 -DSIMDPP_ARCH_X86_SSE2
libtest_simd_sse2_a_SOURCES = $(SIMD_TESTS)
endif

if HAS_SSE3
noinst_LIBRARIES += libtest_simd_sse3.a
test_simd_DEPENDENCIES += libtest_simd_sse3.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_sse3.a -Wl,--no-whole-archive
libtest_simd_sse3_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -msse3 -DSIMDPP_ARCH_X86_SSE3
libtest_simd_sse3_a_SOURCES = $(SIMD_TESTS)
endif

if HAS_SSSE3
noinst_LIBRARIES += libtest_simd_ssse3.a
test_simd_DEPENDENCIES += libtest_simd_ssse3.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_ssse3.a -Wl,--no-whole-archive
libtest_simd_ssse3_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -mssse3 -DSIMDPP_ARCH_X86_SSSE3
libtest_simd_ssse3_a_SOURCES = $(SIMD_TESTS)
endif

if HAS_SSE4_1
noinst_LIBRARIES += libtest_simd_sse4_1.a
test_simd_DEPENDENCIES += libtest_simd_sse4_1.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_sse4_1.a -Wl,--no-whole-archive
libtest_simd_sse4_1_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -msse4.1 -DSIMDPP_ARCH_X86_SSE4_1
libtest_simd_sse4_1_a_SOURCES = $(SIMD_TESTS)
endif

if HAS_AVX
noinst_LIBRARIES += libtest_simd_avx.a
test_simd_DEPENDENCIES += libtest_simd_avx.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_avx.a -Wl,--no-whole-archive
libtest_simd_avx_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -mavx -DSIMDPP_ARCH_X86_AVX
libtest_simd_avx_a_SOURCES = $(SIMD_TESTS)
endif

if HAS_AVX2
noinst_LIBRARIES += libtest_simd_avx2.a
test_simd_DEPENDENCIES += libtest_simd_avx2.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_avx2.a -Wl,--no-whole-archive
libtest_simd_avx2_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -mavx2 -DSIMDPP_ARCH_X86_AVX2
libtest_simd_avx2_a_SOURCES = $(SIMD_TESTS)
endif

if HAS_NEON
noinst_LIBRARIES += libtest_simd_neon.a
test_simd_DEPENDENCIES += libtest_simd_neon.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_neon.a -Wl,--no-whole-archive
libtest_simd_neon_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -mfpu=neon -DSIMDPP_ARCH_ARM_NEON
libtest_simd_neon_a_SOURCES = $(SIMD_TESTS)

noinst_LIBRARIES += libtest_simd_neon_flt_sp.a
test_simd_DEPENDENCIES += libtest_simd_neon_flt_sp.a
test_simd_LDFLAGS += -Wl,--whole-archive libtest_simd_neon_flt_sp.a -Wl,--no-whole-archive
libtest_simd_neon_flt_sp_a_CXXFLAGS = $(SIMD_TESTS_CXXFLAGS) -mfpu=neon -DSIMDPP_ARCH_ARM_NEON_FLT_SP
libtest_simd_neon_flt_sp_a_SOURCES = $(SIMD_TESTS)
endif

TESTS = test_simd
