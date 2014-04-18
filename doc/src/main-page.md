libsimdpp Documentation    {#mainpage}
=========

libsimdpp is a portable header-only zero-overhead C++ wrapper around
single-instruction multiple-data (SIMD) intrinsics found in many compilers. The
library presents a single interface over several instruction sets. In addition
to that, the library allows to compile the same source code for different
instruction sets and seamlessly hook the implementations to an internal dynamic
dispatch mechanism.

The library resolves differences between instruction sets by implementing the
missing functionality as a combination of several intrinsics. Moreover, the
library supplies a lot of additional, commonly used functionality, such as
various variants of matrix transpositions, interleaving loads/stores, optimized
compile-time shuffling instructions, etc. Each of these are implemented in the
most efficient manner for the target instruction set.

The library sits somewhere in the middle between programming directly in
intrinsics and even higher-level SIMD libraries. As much control as possible
is given to the developer, so that it's possible to exactly predict what code
the compiler will generate.

## Contents ##

The documentation is not complete at the moment.

- [Overview](@ref overview)
- [Tutorial](@ref tutorial)
- [Function overview](@ref overview-functions)
- [Selection of instruction set](@ref instruction-set)
- [Instruction counts](@ref insn-counts)
- [Dynamic dispatch](@ref dispatch)
