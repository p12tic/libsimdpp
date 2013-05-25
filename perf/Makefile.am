
include $(top_srcdir)/common.mk

EXTRA_PROGRAMS = perf_null
perf_null_CXXFLAGS = $(AM_CXXFLAGS)
perf_null_SOURCES = null.cc

if HAS_SSE2
EXTRA_PROGRAMS += perf_sse2
perf_sse2_CXXFLAGS = $(AM_CXXFLAGS) -msse2
perf_sse2_SOURCES = sse2.cc
endif

if HAS_SSE3
EXTRA_PROGRAMS += perf_sse3
perf_sse3_CXXFLAGS = $(AM_CXXFLAGS) -msse3
perf_sse3_SOURCES = sse3.cc
endif

if HAS_SSSE3
EXTRA_PROGRAMS += perf_ssse3
perf_ssse3_CXXFLAGS = $(AM_CXXFLAGS) -mssse3
perf_ssse3_SOURCES = ssse3.cc
endif

if HAS_SSE4_1
EXTRA_PROGRAMS += perf_sse4_1
perf_sse4_1_CXXFLAGS = $(AM_CXXFLAGS) -msse4.1
perf_sse4_1_SOURCES = sse4_1.cc
endif

if HAS_NEON
EXTRA_PROGRAMS +=      \
    perf_neon           \
    perf_neon_vfp_sp    \
    perf_neon_vfp_dp

perf_neon_CXXFLAGS = $(AM_CXXFLAGS) -mfpu=neon
perf_neon_SOURCES = neon.cc
perf_neon_vfp_sp_CXXFLAGS = $(AM_CXXFLAGS) -mfpu=neon
perf_neon_vfp_sp_SOURCES = neon_vfp_sp.cc
perf_neon_vfp_dp_CXXFLAGS = $(AM_CXXFLAGS) -mfpu=neon
perf_neon_vfp_dp_SOURCES = neon_vfp_dp.cc
endif
