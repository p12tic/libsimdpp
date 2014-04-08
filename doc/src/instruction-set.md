Configuring the instruction set to use {#instruction-set}
======================================

The instruction set that the library uses is selected by defining one or more
macros before the first inclusion of any of the headers of the library.

Many instruction sets are extensions to other instruction sets. In these cases,
support for the instruction set subsets is implied and there's no need to
define selection macros for these instruction set subsets.

In some cases, multiple macros are needed to select all wanted extensions. For
example, this is the case with x86 FMA3 and AVX.

The following list documents the supported instruction sets. The title of each
entry documents the regular name of the instruction set and an _id_ that will
be used to unambiguously refer to the said instruction set throughout the
documentation.

#### None (`NULL_NONE`) ####

The instructions are not vectorized and use standard C++. This instruction set
is used if no SIMD instruction set is selected. (no macro defined).

#### x86 SSE2 (`X86_SSE2`) ####

The x86/x86_64 SSE and SSE2 instruction sets are used.

Macro: `SIMDPP_ARCH_X86_SSE2`

#### x86 SSE3 (`X86_SSE3`) ####

The x86/x86_64 SSE3 instruction set is used. This instruction set is a superset
of SSE and SSE2.

Macro: `SIMDPP_ARCH_X86_SSE3`

#### x86 SSSE3 (`X86_SSSE3`) ####

The x86/x86_64 SSSE3 instruction set is used. This instruction set is a
superset of SSE, SSE2 and SSE3

Macro: `SIMDPP_ARCH_X86_SSSE3`

#### x86 SSE4.1 (`X86_SSE4.1`) ####

The x86/x86_64 SSE4.1 instruction set is used. This instruction set is a
superset of SSE, SSE2, SSE3 and SSSE3.

Macro: `SIMDPP_ARCH_X86_SSE4_1`

#### x86 AVX (`X86_AVX`) ####

The x86/x86_64 AVX instruction set is used. This instruction set is a superset
of SSE, SSE2, SSE3 and SSSE3.

Macro: `SIMDPP_ARCH_X86_AVX`

#### x86 AVX2 (`X86_AVX2`) ####

The x86/x86_64 AVX2 instruction set is used. This instruction set is a superset
of SSE, SSE2, SSE3, SSSE3 and AVX.

Macro: `SIMDPP_ARCH_X86_AVX2`

#### x86 FMA3 (`X86_FMA3`) ####

The Intel x86/x86_64 FMA3 instruction set is used. This instruction set is a
superset of SSE, SSE2 and SSE3.

Macro: `SIMDPP_ARCH_X86_FMA3`

#### x86 FMA4 (`X86_FMA4`) ####

The AMD x86/x86_64 FMA4 instruction set is used. This instruction set is a
superset of SSE, SSE2 and SSE3.

Macro: `SIMDPP_ARCH_X86_FMA4`

#### x86 XOP (`X86_XOP`) ####

The AMD x86/x86_64 XOP instruction set is used. This instruction set is a
superset of SSE, SSE2 and SSE3.

Macro: `SIMDPP_ARCH_X86_XOP`

#### ARM NEON w/o SP float (`ARM_NEON`) ####

The ARM NEON instruction set. The VFP co-processor is used for any
floating-point functionality (NEON does not require the implementation to be
IEEE-754 compliant, whereas VFP does).

Macro `SIMDPP_ARCH_ARM_NEON`

#### ARM NEON including SP float (`ARM_NEON_FLT_SP`) ####

Performs 32-bit floating-point computations on the NEON vector unit. This
instruction set is a superset of NEON w/o SP float.

Macro `SIMDPP_ARCH_ARM_NEON_FLT_SP`

#### POWER_ALTIVEC (not supported yet) (`POWER_ALTIVEC`) ####

The POWER Altivec instruction set. 64-bit floating point operations are not
vectorized.

Macro `SIMDPP_ARCH_POWER_ALTIVEC`
