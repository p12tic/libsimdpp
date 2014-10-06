/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
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
    /// Indicates x86 AVX-512F suppotr
    X86_AVX512F = 1 << 10,

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

/// Checks if the bits set in @a required is a subset of bits set in @a current.
inline bool test_arch_subset(Arch current, Arch required)
{
    if ((~current & required) == Arch::NONE_NULL) {
        return true;
    }
    return false;
}

/// @} -- end defgroup

} // namespace simdpp

#endif
