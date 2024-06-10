
libsimdpp
=========

[![Travis build status](https://travis-ci.org/p12tic/libsimdpp.svg?branch=master)](https://travis-ci.org/p12tic/libsimdpp "Travis build status")
[![Appveyor build status](https://img.shields.io/appveyor/ci/p12tic/libsimdpp/master.svg)](https://ci.appveyor.com/project/p12tic/libsimdpp "Appveyor build status")
[![Join the chat at https://gitter.im/libsimdpp/Lobby](https://badges.gitter.im/libsimdpp/Lobby.svg)](https://gitter.im/libsimdpp/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

libsimdpp is a portable header-only zero-overhead C++ low level SIMD library.
The library presents a single interface over SIMD instruction sets present in
x86, ARM, PowerPC and MIPS architectures. On architectures that support
different SIMD instruction sets the library allows the same source code files
to be compiled for each SIMD instruction set and then hooked into an internal
or third-party dynamic dispatch mechanism. This allows the capabilities of the
processor to be queried on runtime and the most efficient implementation to be
selected.

The library sits somewhere in the middle between programming directly in SIMD
intrinsics and even higher-level SIMD libraries. As much control as possible
is given to the developer, so that it's possible to exactly predict what code
the compiler will generate.

No API-breaking changes are planned for the foreseeable future.

Documentation
-------------

Online documentation is provided
[here](http://p12tic.github.io/libsimdpp/v2.2-dev/libsimdpp/w/).

Compiler and instruction set support
------------------------------------

  - This describes the current branch only which may be unstable or otherwise
  unfit for use. For available releases please see the
  [libsimdpp wiki](https://github.com/p12tic/libsimdpp/wiki).

The library supports the following architectures and instruction sets:

 - x86, x86-64: SSE2, SSE3, SSSE3, SSE4.1, AVX, AVX2, FMA3, FMA4, AVX512F,
 AVX512BW, AVX512DQ, AVX512VL, XOP, popcnt
 - ARM 32-bit: NEON, NEONv2
 - ARM 64-bit: NEON, NEONv2
 - PowerPC 32-bit big-endian: Altivec, VSX v2.06, VSX v2.07
 - PowerPC 64-bit little-endian: Altivec, VSX v2.06, VSX v2.07
 - MIPS 32-bit little-endian: MSA
 - MIPS 64-bit little-endian: MSA

The primary development of the library happens in C++11. A C++98-compatible
version of the library is provided on the
[cxx98](https://github.com/p12tic/libsimdpp/tree/cxx98) branch.

Supported compilers:

 - C++11 version:
   - GCC: 4.8-7.x
   - Clang: 3.3-4.0
   - Xcode 7.0-9.x
   - MSVC: 2013, 2015, 2017
   - ICC (on both Linux and Windows): 2013, 2015, 2016, 2017

 - C++98 version
   - GCC: 4.4-7.x
   - Clang: 3.3-4.0
   - Xcode 7.0-9.x
   - MSVC: 2013, 2015, 2017
   - ICC (on both Linux and Windows): 2013, 2015, 2016, 2017

Newer versions of the aforementioned compilers will generally work with either
C++11 or C++98 version of the library. Older versions of these compilers will
generally work with the C++98 version of the library.

Various compiler versions are not supported on various instruction sets due to
compiler bugs or incompletely implemented instruction sets. See
simdpp/detail/workarounds.h for more details.

 - MSVC and ICC are only supported on x86 and x86-64.

 - AVX is not supported on Clang 3.6 or GCC 4.4

 - AVX2 is not supported on Clang 3.6.

 - AVX512F is not supported on:
    - GCC 5.x and older
    - Clang 5.0 and older
    - MSVC

 - NEON armv7 is not supported on Clang 3.3 and older.

 - NEON aarch64 is not supported on GCC 4.8 and older

 - Altivec on little-endian PPC is not suppported on GCC 5.x and older.

 - VSX on big-endian PPC is not supported on GCC 5.x and older.

 - MSA is not supported on GCC 6.x and older.

Contributing
------------

Contributions are welcome. Please see CONTRIBUTING.md for more information.

License
-------

The library may be freely used in commercial and non-commercial software. The
code is distributed under the Boost Software License, Version 1.0. Some
internal development scripts are licensed under different licenses -- see
comments in these files. The documentation is licensed under CC-BY-SA.

> Boost Software License - Version 1.0 - August 17th, 2003
>
> Permission is hereby granted, free of charge, to any person or organization
> obtaining a copy of the software and accompanying documentation covered by
> this license (the "Software") to use, reproduce, display, distribute,
> execute, and transmit the Software, and to prepare derivative works of the
> Software, and to permit third-parties to whom the Software is furnished to
> do so, all subject to the following:
>
> The copyright notices in the Software and this entire statement, including
> the above license grant, this restriction and the following disclaimer,
> must be included in all copies of the Software, in whole or in part, and
> all derivative works of the Software, unless such copies or derivative
> works are solely in the form of machine-executable object code generated by
> a source language processor.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
> SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
> FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
> ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
> DEALINGS IN THE SOFTWARE.
