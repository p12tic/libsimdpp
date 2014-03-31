
Overview
--------

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

Compiler and instruction set support
------------------------------------

  - This describes the current branch only which may be unstable or otherwise
  unfit for use. For available releases please see the
  [libsimdpp wiki](https://github.com/p12tic/libsimdpp/wiki).

The library supports SSE2, SSE3, SSSE3, SSE4.1, AVX, AVX2, FMA3, FMA4, XOP and
NEON instruction sets.

Code for ALTIVEC instruction set has been added, but it has not been tested
on actual hardware, thus definitely contains bugs.

The primary development of the library happens in C++11. A C++98-compatible
version of the library is provided on the
[cxx98](https://github.com/p12tic/libsimdpp/tree/cxx98) branch. Boost libraries
are used as a replacement for C++11-only functionality. The library does not
depend on boost if the built-in dispatcher functionality is not used. The
library has been tested with the following compilers:

 - C++11 version:
   - GCC: 4.8.1, 4.7.3
   - Clang: 3.3, 3.4

 - C++98 version
   - GCC: 4.8.1, 4.7.3
   - Clang: 3.3, 3.4

The C++98 version has been tested with boost 1.53 and 1.54. Most probably other
versions will work too.

Documentation
-------------

Online documentation is provided
[here](http://p12tic.github.io/libsimdpp/doc/html).

Caveats
-------

Due to [bug #28831] (http://gcc.gnu.org/bugzilla/show_bug.cgi?id=28831), GCC
produces non-optimal code for double precision floating point math on ARM.
Clang does not have this problem.

License
-------

The library is distributed under two-clause BSD license:

> Copyright (C) 2011-2013  Povilas Kanapickas tir5c3@yahoo.co.uk
> All rights reserved.
>
> Redistribution and use in source and binary forms, with or without
> modification, are permitted provided that the following conditions are met:
>
> * Redistributions of source code must retain the above copyright notice,
>   this list of conditions and the following disclaimer.
>
> * Redistributions in binary form must reproduce the above copyright notice,
>   this list of conditions and the following disclaimer in the documentation
>   and/or other materials provided with the distribution.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
> AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
> IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
> ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
> LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
> CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
> SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
> INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
> CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
> ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
> POSSIBILITY OF SUCH DAMAGE.

