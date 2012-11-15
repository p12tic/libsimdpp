#initialize autoconf/automake
AC_INIT(
        [libsimdpp],
        [0.9],
        [tir5c3@yahoo.co.uk],
        [libsimdpp])

CXXFLAGS="-O0 -g"

AC_PREREQ([2.59])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_CXX

AM_INIT_AUTOMAKE([1.10 no-define subdir-objects -Wno-portability])
AM_MAINTAINER_MODE
AM_SILENT_RULES([yes])

LT_INIT

# Initialize documentation
MM_PREREQ([0.9.3])

MM_CONFIG_DOCTOOL_DIR([doc])
MM_ARG_ENABLE_DOCUMENTATION

# Library version
#AC_SUBST([LIBSIMDPP_SO_VERSION], [0:0:0])
AC_SUBST([LIBSIMDPP_API_VERSION], [0.9])

# -----------------------------------------------------------------------------
# Check which instructions our architecture supports. Used for testing
AC_LANG(C++)

saved_CXXFLAGS="$CXXFLAGS"

CXXFLAGS="$saved_CXXFLAGS -msse2"
AC_MSG_CHECKING([whether we can use SSE2 instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <emmintrin.h>]], [[
    volatile char a[16];
    __m128i one = _mm_load_si128((__m128i*)(a));
    one = _mm_or_si128(one, one);
    _mm_store_si128((__m128i*)(a), one);
    ]])],
    [has_msse2=yes],
    [has_msse2=no],
    [has_msse2=no]
)
AC_MSG_RESULT($has_msse2)
AM_CONDITIONAL([HAS_SSE2], [test x$has_msse2 = xyes])

CXXFLAGS="$saved_CXXFLAGS -msse3"
AC_MSG_CHECKING([whether we can use SSE3 instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <pmmintrin.h>]], [[
    volatile float a[4];
    __m128 one = _mm_load_ps((float*)(a));
    one = _mm_hadd_ps(one, one);
    _mm_store_ps((float*)(a), one);
    ]])],
    [has_msse3=yes],
    [has_msse3=no],
    [has_msse3=no]
)
AC_MSG_RESULT($has_msse3)
AM_CONDITIONAL([HAS_SSE3], [test x$has_msse3 = xyes])

CXXFLAGS="$saved_CXXFLAGS -mssse3"
AC_MSG_CHECKING([whether we can use SSSE3 instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <tmmintrin.h>]], [[
    volatile char a[16];
    __m128i one = _mm_load_si128((__m128i*)(a));
    one = _mm_abs_epi8(one);
    _mm_store_si128((__m128i*)(a), one);
    ]])],
    [has_mssse3=yes],
    [has_mssse3=no],
    [has_mssse3=no]
)
AC_MSG_RESULT($has_mssse3)
AM_CONDITIONAL([HAS_SSSE3], [test x$has_mssse3 = xyes])

CXXFLAGS="$saved_CXXFLAGS -msse4.1"
AC_MSG_CHECKING([whether we can use SSE4.1 instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <smmintrin.h>]], [[
    volatile char a[16];
    __m128i one = _mm_load_si128((__m128i*)(a));
    one = _mm_cvtepi16_epi32(one);
    _mm_store_si128((__m128i*)(a), one);
    ]])],
    [has_msse4_1=yes],
    [has_msse4_1=no],
    [has_msse4_1=no]
)
AC_MSG_RESULT($has_msse4_1)
AM_CONDITIONAL([HAS_SSE4_1], [test x$has_msse4_1 = xyes])

CXXFLAGS="$saved_CXXFLAGS -mavx"
AC_MSG_CHECKING([whether we can use AVX instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <avxintrin.h>]], [[
    volatile char a[32];
    __m256 one = _mm256_load_ps((__m256*)(a));
    one = _mm256_add_ps(one, one);
    _mm256_store_ps((__m256*)(a), one);
    ]])],
    [has_mavx=yes],
    [has_mavx=no],
    [has_mavx=no]
)
AC_MSG_RESULT($has_mavx)
AM_CONDITIONAL([HAS_AVX], [test x$has_mavx = xyes])

CXXFLAGS="$saved_CXXFLAGS -mavx2"
AC_MSG_CHECKING([whether we can use AVX2 instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <avx2intrin.h>]], [[
    volatile char a[32];
    __m256i one = _mm256_load_si256((__m256i*)(a));
    one = _mm256_or_si256(one, one);
    _mm_store_si256((__m256i*)(a), one);
    ]])],
    [has_mavx2=yes],
    [has_mavx2=no],
    [has_mavx2=no]
    )
AC_MSG_RESULT($has_mavx2)
AM_CONDITIONAL([HAS_AVX2], [test x$has_mavx2 = xyes])

CXXFLAGS="$saved_CXXFLAGS -mfpu=neon"
AC_MSG_CHECKING([whether we can use NEON instructions for testing])
AC_RUN_IFELSE(  [AC_LANG_PROGRAM([[#include <arm_neon.h>]], [[
    volatile long long a[4];
    uint32x4_t one = vld1q_u32((uint32_t*)(a));
    one = vaddq_u32(one, one);
    vst1q_u32((uint32_t*)(a), one);
    ]])],
    [has_neon=yes],
    [has_neon=no],
    [has_neon=no]
    )
AC_MSG_RESULT($has_neon)
AM_CONDITIONAL([HAS_NEON], [test x$has_neon = xyes])

CXXFLAGS="$saved_CXXFLAGS"
# -----------------------------------------------------------------------------

#files to generate
AC_CONFIG_FILES([
        Makefile
        simdpp/Makefile
        doc/Makefile
        doc/reference/Doxyfile
        test/Makefile
        libsimdpp.pc:libsimdpp.pc.in
        ])

AC_OUTPUT
