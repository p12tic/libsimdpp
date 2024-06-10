What's new in v2.2 development master:
 * Nothing yet

What's new in v2.1:
 * Various bug fixes
 * Documentation has been significantly improved. The public API is now almost
 fully documented.
 * Added support for MIPS MSA instruction set.
 * Added support for PowerPC VSX v2.06 and v2.07 instruction sets.
 * Added support for x86 AVX512BW, AVX512DQ and AVX512VL instruction sets.
 * Added support for 64-bit little-endian PowerPC.
 * Added support for arbitrary width vectors in extract() and insert()
 * Added support for arbitrary source vectors to to_int8(), to_uint8(),
 `to_int16()`, `to_uint16()`, `to_int32()`, `to_uint32()`, `to_int64()`,
 `to_uint64()`, `to_float32()`, `to_float64()`.
 * Added support for per-element integer shifts to `shift_r()` and `shift_l()`.
 Fallback paths are provided for SSE2-AVX instruction sets that lack hardware
 per-element integer shift support.
 * Make `shuffle_bytes16()`, `shuffle_zbytes16()`, `permute_bytes16()` and
 `permute_zbytes()` more generic.
 * New functions: `popcnt()`, `reduce_popcnt()`, `for_each()`, `to_mask()`.
 * Xcode is now supported.
 * The library has been refactored in such a way that older compilers are able
 to optimize vector emulation code paths much better than before.
 * Deprecation: implicit conversion operators to native vector types has been
 deprecated and a replacement method has been provided instead. The implicit
 conversion operators may lead to wrong code being accepted without a compile
 error on Clang.

What's new in v2.0:

 * Various bug fixes.
 * Intel compiler is now supported on Windows. Newer versions of other compilers
 are now supported.

What's new in v2.0~rc2:

 * Various bug fixes.

What's new in v2.0~rc1:

 * Expression template-based backend.
 * Support scalar arguments to certain functions.
 * Support for vectors much longer than the native vector type. The only
 limitation is that the length must be a power of 2.
 * Operator overloads are provided that fully mimic free functions.
 * New functions: `store_masked()`, `store_u()`, `shuffle4x2()`, `shuffle2x2()`,
 `test_bits_any()`.
 * PowerPC Altivec, NEONv2 support. More compilers are now supported.
 * API break: The built-in dispatcher has been rewritten to generate hard
 link-time dependencies on the versioned functions. It is no longer susceptible
 in lazy static variable initialization breaking function registration. User
 must supply the list of generated architectures via predefined macro values.
 See examples/dispatcher for an example.
 * API break: `SIMDPP_USER_ARCH_INFO` now accepts any expression, not only a
 function.
 * API break: `int128` and `int256` types have been removed. On some archs
 it's more efficient to have different physical representations for vectors
 with different element widths.
 * API break: `broadcast()` family of functions have been renamed to `splat()`.
 * API break: `permute()` family of functions has been renamed to `permute2()`
 and `permute4()` depending on the number of template arguments taken.
 * API break: value conversion functions such as `to_float32x4()` have been
 renamed and now returns a vector with the same number of elements as the
 source vector.
 * API break: certain functions return "empty" expressions instead of vectors.
 * API break: saturated add and sub are now called `add_sat()` and `sub_sat()`.
 * API break: the `zero()` and `ones()` member functions of the vector types
 have been removed.
 * API break: the functions in the `sse::` and `neon::` namespaces have been
 replaced with equivalent functions within the main simdpp namespace
 * Various other enhancements.
