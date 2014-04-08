
&nbsp;&nbsp;&nbsp;&nbsp;This is incomplete internal documentation

## Design of the library ##

 - If you find some part of the documentation of the library design unclear or
    missing, please open a bug.

Architecture of the library
---------------------------

In most basic terms, libsimdpp consists of two parts:

 * a number of vector types that wrap vector types available in the target
   instruction set
 * a number of functions that operate on these vectors

Vector types
------------

The vector types are templates which accept two parameters: the number of
elements and expression type.

- Width

The first parameter allows the vectors to have arbitrarily large number of
elements. Native vectors are implemented as template specializations, so, for
example, `float32<4>` holds a `__m128` object on SSE#. On AVX, `float32<8>` is
also defined, which holds a `__m256` object.

Long vectors consist of a number of vectors of largest natively supported
width. For example, `float32<32>` internally holds 8 `float32<4>` objects on
SSE# and 4 `float32<8>` objects on AVX. Any operation on such vector will
simply loop through the internal vector objects.

Naturally, using unnecessarily long vectors increases register pressure, so the
developers are expected to use the lowest vector length that is needed to
implement their algorithms efficiently.

- Expressions

The second, expression parameter is there to allow use of expression templates.

The reason for combining vector and expression types into the same template
lies in the fact that implicit conversions are not allowed whet deducing
template parameters. So, if expression type was different, then for each
function template accepting two vectors, four variants would need to be written.
Fortunately, combining vector and expression types does not have any
complications except being a bit confusing: by using template specializations
the vector and expression types have been made completely separate.

'void' expression type (default) corresponds to a value vector, i.e. a vector
that is not an expression. Any other type corresponds to an expression. All
useful expression types are defined in libsimdpp/expr.h .

Thus, for example:

* `float<4,void>` or just `float<4>` is a SSE `__m128` (or NEON `float32x4_t`,
    etc.) vector

* `float<4,expr_add<float<4>, float<4>>>` is an add expression. The object
    stores two `float<4>` vectors. It's possible to store other expressions
    instead of the `float<4>` vectors, thus building a tree-like structure.
    The resulting type are later matched by overloads of
    `simdpp::detail::expr_eval` function, which could optimize the expression.
    For example:

* `float<4,expr_add<float<4>,float<4,expr_mul<float<4>, float<4>>>>>` denotes
    a multiply-add expression that can be executed by a single instruction on
    processors that have FMA instruction.

Both vector and expression types have `eval()` member function that in the
case of vector types returns `*this` and in the case of expression types,
evaluates the expression using `simdpp::detail::expr_eval` and returns the
resulting vector.

Expression types are _almost_ invisible to the user. One practical difference
is that expression types can't be implicitly converted to the native type, thus
the user can't use the result of, say, `bit_and` directly as an argument to
`_mm_add_ps`. Also, if the expression type is captused via `auto` in C++11, the
resulting object is inferior as it can't be assigned a value to, etc. This needs
to be properly documented, if it isn't already.

- Vector types

There are 14 different vector types in libsimdpp: 4 signed integer
vector types, 4 unsigned integer vector types, 2 floating-point vector types,
4 integer mask types and 2 floating-point mask types:

`int8`, `uint8`, `mask_int8`,
`int16`, `uint16`, `mask_int16`,
`int32`, `uint32`, `mask_int32`,
`int64`, `uint64`, `mask_int64`,
`float32`, `mask_float32`, `float64`, `mask_float64`


The reason for mask types is that on some SIMD instruction sets (e.g. AVX512)
there are separate registers for vector masks, using which for masking
operations is considerably more efficient.

Also, the library does not vectorize all code paths on e.g. NEON, so storing
results of comparisons as `bool` values allows the compiler to properly
devectorize the code. That is code such as the following:

    float64<2> r = blend(a, b, cmp_lt(a, b))

is properly converted to something equivalent to the following:

    for (unsigned i = 0; i < 2; ++i) {
        r[i] = (a[i] < b[i]) ? a[i] : b[i];
    }

Hierarchy
---------

Vector and expression types inherit from several common types using Curiously
recurrint template pattern (CRTP). The resulting inheritance hierarchy is used
to categorize vector types (see simdpp/types/any.h) so that it's possible to
write function templates that operate on some category of vector types, such
as, e.g. any vectors that have size of 16 bytes, or any vectors that have 4
32-bit elements, etc.

The hierarchy is as follows:

 - any_vec<B,V> - any vector with size of B bytes
   - any_vec8<N,V> - any vector with N 8-bit elements
     - any_int8<N,V> - any integer vector with N 8-bit elements
   - any_vec16<N,V> - any vector with N 16-bit elements
     - any_int16<N,V> - any integer vector with N 16-bit elements
   - any_vec32<N,V> - any vector with N 32-bit elements
     - any_int32<N,V> - any integer vector with N 32-bit elements
     - any_float32<N,V> - any floating-point vector with N 32-bit elements
   - any_vec64<N,V> - any vector with N 64-bit elements
     - any_int64<N,V> - any integer vector with N 64-bit elements
     - any_float64<N,V> - any floating-point vector with N 64-bit elements

The `any_vec` template has `vec()` member function that converts `*this` to the
actual vector type `V`.

Functions
---------

All functions that operate on vectors are implemented in roughly the following
way: there's a simple interface in one of the files in simdpp/core directory,
which wraps an internal implementation in simdpp/detail/insn and possibly in
simdpp/detail/expr directories. Collectively, the public interface is called
the front-end and the internal implementation is called the back-end.

The back-end of a function usually consists of many overloads. Each of them
reside in simdpp::detail::insn namespace and have prefix `i_` to prevent name
clashes whenever a front-end function needs to be used.

For each vector type there's a template that loops over arbitrarily long
vectors and a separate overload for each native vector type. The latter are
what

Proper implementation is selected via conditional inclusion depending on
macro constants that are set in simdpp/setup_arch.h file. This header must be
directly or indirectly included into each source file of the library.

Namespace
---------

All functionality of the library is put into a namespace whose name depends on
the currently enabled instruction sets. This allows to avoid violations of One
Definition Rule when the same source file is compiled seeral times for different
SIMD instruction sets and linked into the same target executable or library.
The namespace is set up as a macro SIMDPP_ARCH_NAMESPACE in simdpp/setup_arch.h
header file. This header file must be directly or indirectly included into all
files of the libsimdpp library.

Why there's so much duplication in type definitions?
----------------------------------------------------

It's not possible to implement the specializations of core templates (int8,
uint16, mask_int32) as templates themselves in C++98. It's only possible in C++11.
Thus we're simply duplicating stuff until the library can drop the C++98
support (i.e. that is not planned).
