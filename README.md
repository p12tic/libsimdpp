
What is libsimdpp
=================

libsimdpp is a header-only zero-overhead C++ wrapper around single-instruction
multiple-data (SIMD) intrinsics found in many compilers. The library presents
a single interface over several instruction sets. In addition to that, the
library allows to compile the same source code for different instruction sets
and seamlessly hook the implementations to an internal dynamic dispatch
mechanism.

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

Supported instruction sets
==========================

The library supports SSE2, SSE3, SSSE3, SSE4.1, AVX, AVX2 and NEON instruction
sets. The library presents a common interface for all those instruction sets in
the simdpp:: namespace. Some instruction set specific intrinsics are available
in simdpp::sse:: or simdpp::neon:: namespaces. A lot of domain-specific
instructions are not wrapped at all -- the original intrinsics must be used for
these.

Documentation
=============

Online documentation is provided
[here](http://p12tic.github.io/libsimdpp/doc/html).

Caveats
=======

On ARM systems 64-bit floating point support is provided only in scalar VFP
core. To make matters worse, the transition between the VFP and NEON
instruction sets is very expensive, so the traditional vector processing idioms
(such as performing IF by ANDNOT, AND and OR) can not be used. Therefore, the
library is not useful for this use-case.

Roadmap
=======

 - Implement an interface that would allow the library to seamlessly choose the
   vector type that is most optimal for the target instruction set. Currently
   the vector width is selected explicitly, which doesn't produce optimal code
   when the same code is compiled to an architecture with wider or narrower
   vector unit.

License
=======

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

