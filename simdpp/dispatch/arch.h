/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_DISPATCH_ARCH_H
#define LIBSIMDPP_DISPATCH_ARCH_H

#include <cstdint>

namespace simdpp {

/** @defgroup simd_dispatcher Dispatching support
    @{
*/

/** Identifies supported instruction set. This type is a bitmask type

    Note: the exact values may change release to release.
*/
/*  The values are assigned in such a way that the result of comparison of two
    ORed flag sets is likely identify which instruction set the binary is more
    likely to run faster on.

    detail::select_version depends on this.
*/
enum class Arch : std::uint32_t {
    /// Indicates that no SIMD instructions are supported
    NONE_NULL = 0,
    /// Indicates x86 SSE2 support
    X86_SSE2 = 1 << 1,
    /// Indicates x86 SSE3 support
    X86_SSE3 = 1 << 2,
    /// Indicates x86 SSSE3 support
    X86_SSSE3 = 1 << 3,
    /// Indicates x86 SSE4.1 support
    X86_SSE4_1 = 1 << 4,
    /// Indicates x86 AVX support
    X86_AVX = 1 << 5,
    /// Indicates x86 AVX2 support
    X86_AVX2 = 1 << 6,
    /// Indicates x86 FMA3 (Intel) support
    X86_FMA3 = 1 << 7,
    /// Indicates x86 FMA4 (AMD) support
    X86_FMA4 = 1 << 8,
    /// Indicates x86 XOP (AMD) support
    X86_XOP = 1 << 9,

    /// Indicates ARM NEON support (SP and DP floating-point math is executed
    /// on VFP)
    ARM_NEON = 1 << 0,
    /// Indicates ARM NEON support (SP floating-point math is executed on NEON,
    /// DP floating-point math is executed on VFP)
    ARM_NEON_FLT_SP = 1 << 1,

    /// Indicates POWER ALTIVEC support.
    POWER_ALTIVEC = 1 << 0
};

/// Bitwise operators for @c Arch
/// @{
inline Arch& operator|=(Arch& x, const Arch& y)
{
    using T = std::uint32_t;
    x = static_cast<Arch>(static_cast<T>(x) | static_cast<T>(y));
    return x;
}

inline Arch& operator&=(Arch& x, const Arch& y)
{
    using T = std::uint32_t;
    x = static_cast<Arch>(static_cast<T>(x) & static_cast<T>(y));
    return x;
}

inline Arch operator|(const Arch& x, const Arch& y)
{
    using T = std::uint32_t;
    return static_cast<Arch>(static_cast<T>(x) | static_cast<T>(y));
}

inline Arch operator&(const Arch& x, const Arch& y)
{
    using T = std::uint32_t;
    return static_cast<Arch>(static_cast<T>(x) & static_cast<T>(y));
}

inline Arch operator~(const Arch& x)
{
    using T = std::uint32_t;
    return static_cast<Arch>(~static_cast<T>(x));
}
/// @}

/// @} -- end defgroup

} // namespace simdpp

#endif
