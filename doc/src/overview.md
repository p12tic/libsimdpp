Overview     {#overview}
========

&nbsp;&nbsp;The overview assumes the reader already knows basic concepts of
SIMD programming.

### Vector types ###

libsimdpp supports vectors holding data of 10 different data formats. For each
of these formats, a separate vector type is provided. These following data
formats are supported:

 - 8-bit signed and unsigned integers (`int8`, `uint8`)
 - 16-bit signed and unsigned integers (`int16`, `uint16`)
 - 32-bit signed and unsigned integers (`int32`, `uint32`)
 - 64-bit signed and unsigned integers (`int64`, `uint64`)
 - 32-bit floating-point numbers (`float32`)
 - 64-bit floating-point numbers (`float64`)

In addition to these, 6 mask formats are provided.

A mask is a vector that contains elements with either all set bits or all unset
bits. It is possible to represent the data on such vector using just single bit
per element. Some architectures such as AVX-512 use separate vector registers
for masks, which allows much improved performance. Having separate type for
masks thus allows to fully use the potential on such architectures.

The following mask types are provided:

 - mask for 8-bit integer elements (`mask_int8`)
 - mask for 16-bit integer elements (`mask_int16`)
 - mask for 32-bit integer elements (`mask_int32`)
 - mask for 64-bit integer elements (`mask_int64`)
 - mask for 32-bit floating-point elements (`mask_float32`)
 - mask for 64-bit floating-point elements (`mask_float64`)

Each vector type is implemented as a template that accepts 2 arguments (here
_vector_type_ is any of the vector types mentioned above):

~~~
template<unsigned NumElements, class Expression = void>
class _vector_type_ { ... };
~~~

The first parameter defines the number of elements in a vector. `NumElements`
must be any power of two such that the size of the resulting vector is not less
than 16 bytes. If the target instruction set does not support vector of such
size, then the library automatically uses the widest vector type for the
particular type. For example, on AVX, `int8<128>` uses `__m128i`, whereas
`float32<32>` uses `__m256`.

Using unnecessarily long vectors increases register pressure, so the developers
are expected to use the lowest vector length that is needed to implement their
algorithms efficiently.

The second parameter is implementation detail, i.e. non-`void` types are
reserved. Vectors with `Expression` parameter being `void` are _value_ vectors,
that is, they directly correspond to one or more instances of native vector
types, as would be expected. Vectors with `Expression` parameter being non-`void`
are _expression_ vectors, that is, they hold an expression with all its
parameters.

This technique is called "expression templates" and allows to pick more
efficient algorithm for entire expression. For example, `add(a, mul(b, c))`
will be optimized into a single multiple-add operation on architectures where
it is available. Even though this optimization can be easily done at the
compiler level, usually the compilers are very reluctant to optimize low level
intrinsic functions that this library uses. This makes the expression template
usage necessary rather than optional.

For the user, expression vector types should be viewed as some wrapper type
that can be implicitly converted to the corresponding value vector type. To
obtain a value vector without inconvenience of typing the type name, use the
`.eval()` member function which is provided for both value and expression
vectors.

### Casts ###

The vector types can be casted from one to another rather easily. The following
casts are supported:

 * Any non-mask value vector can be explicitly constructed from any other
 non-mask value vector of the same size (mask vectors may be created only as
 results of vector comparison functions).
 * A non-mask value vector can be assigned a value of any vector type of the
 same size.
 * An _expression_ vector can be implicitly converted to a corresponding
 _value_ vector.

Mask types may only be assigned to or constructed from the same mask type. The
only way to create a mask is by using comparison functions such as `cmp_eq` or
`cmp_lt`.

Note that expression vectors are not meant to be created or assigned to by the
user. Assignment can happen quite easily if C++11 `auto` is used, e.g.

~~~.cc
auto v = add(a, b);
v = add(v, c);
~~~

The second line, even if compiles, is not supported and not supposed to be used
by the user.

### Vector categorization hierarchy ###

The vector types inherit from several common types using Curiously recurrint
template pattern (CRTP). The resulting inheritance hierarchy is used to
categorize vector types so that it's possible to write function templates that
operate on some category of vector types.

For example, bitwise AND is implemented as a single function template that
accepts any two vectors of the same size. Implementing this functionality
without some kind of categorization would require 256 overloads, which is not
feasible.

The hierarchy is as follows. Note that the users of the library do not ever
need to use any of the following types directly. Knowing the categorization
hierarchy is only useful when reading the documentation.

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
actual vector type `V`. Users of the library should never need to call this. It
is only useful to implementers of generic function templates.

### Vector promotion ###

As mentioned in the above section, some generic operations are implemented as
function templates that accept a variety of vector types. The type of the
returned vector is determined by rules that are very similar to the C++ type
promotion rules and thus are called "vector promotion" rules. The same set of
rules is used throughout the library, with a single exception related to masks.

The rules are as follows (it may be clearer just to look at the table below):

 - The `mask_int`, `mask_float`, `int`, `uint` and `float` vector types are
 assigned ranks in an increasing order irrespective of number of elements. The
 result type of a generic operation always has the highest rank among the
 argument types. I.e. `int @ uint -> uint`, `mask_int @ float -> float`.

 - If the arguments of a generic operation have different element widths, then
 the result type has elements with largest element width (or smallest number of
 elements). I.e. `float32 @ int64 -> float64`.

 - If the arguments are two masks with different element widths, then the
 result type is an unsigned integer vector. The element width is governed by
 the second rule.

The following list illustrates the conversion rules. The first two items
are the argument types and the third item is the result type.

~~~
[ Same element sizes ]

       intXX |        intXX ->        intXX
       intXX |       uintXX ->       uintXX
      uintXX |       uintXX ->       uintXX
     floatXX |        intXX ->      floatXX
     floatXX |       uintXX ->      floatXX
     floatXX |      floatXX ->      floatXX
  mask_intXX |        intXX ->       uintXX
  mask_intXX |       uintXX ->       uintXX
  mask_intXX |   mask_intXX ->   mask_intXX
  mask_intXX |      floatXX ->      floatXX
  mask_intXX | mask_floatXX -> mask_floatXX
mask_floatXX |      floatXX ->      floatXX
mask_floatXX | mask_floatXX -> mask_floatXX

[ Different element sizes ]

       intXX |        intYY ->        int{ max(XX, YY) }
       intXX |       uintYY ->       uint{ max(XX, YY) }
      uintXX |       uintYY ->       uint{ max(XX, YY) }
     floatXX |        intYY ->      float{ max(XX, YY) }
     floatXX |       uintYY ->      float{ max(XX, YY) }
     floatXX |      floatYY ->      float{ max(XX, YY) }
  mask_intXX |        intYY ->       uint{ max(XX, YY) }
  mask_intXX |       uintYY ->       uint{ max(XX, YY) }
  mask_intXX |   mask_intYY ->       uint{ max(XX, YY) }
  mask_intXX |      floatYY ->      float{ max(XX, YY) }
  mask_intXX | mask_floatYY ->       uint{ max(XX, YY) }
mask_floatXX |      floatYY ->      float{ max(XX, YY) }
mask_floatXX | mask_floatYY ->       uint{ max(XX, YY) }
~~~

If a particular operation does not support masks, the masks are expanded
internally. If both arguments are masks, then the result type is unsigned
integer vector if both masks are `mask_int` and floating-point vector otherwise.

