Overview of available functions    {#overview-functions}
========

TODO

@class _PROMOTED_EXPRESSION_
This is a dummy type to simplify the documentation of the library.

In functions with single argument, this identifier is equivalent to a
expression vector type corresponding to the argument type.

In functions with more than one argument, this identifier corresponds to a
vector expression type obtained according to the vector promotion rules
(see @ref overview).

@class _PROMOTED_NOMASK_EXPRESSION_
This is a dummy type to simplify the documentation of the library.

This is similar to @c _PROMOTED_EXPRESSION_, except that if the result type
is an integer mask, it is converted to unsigned integer vector and if the
result type is a floating-point vector, then it is converted to the
corresponding floating-point type.

@class _DETAIL_
This is a dummy type to simplify the documentation of the library. It
corresponds to an implementation-defined non-void type. The vector types
that use this as the second template argument are expression vector types.
