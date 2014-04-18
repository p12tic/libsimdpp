
&nbsp;&nbsp;&nbsp;&nbsp;This is internal documentation

This file documents the expression types returned by various functions in the
library.

In a perfect world an expression would be composed using the argument types
without any conversions. That is, for example, the prototype of `add` function
would look something like this:

template<unsigned N, class V1, class V2>
typename get_expr2_nomask<V1, V2, expr_add<V1, V2>>::type
        add(const any_int8<N,V1>&, const any_int8<N,V2>&);

Unfortunately, this function returns different type for each combinations of V1
and V2. Given that V1 and V2 each may one of `int8`, `uint8` and `mask_int8`,
we will need to implement 9 different cases in the expression evaluator when
ideally only one case should be needed as the implementation is the same in
each case. It's obvious that this approach is not sustainable if we want to
take advantage of any micro-optimizations made possible by expresion templates.

The solution that is employed throughout the library is to convert V1 and V2
to a reduced set of vector/expression type combinations when building the
expression tree. Then in the expression evaluator we only need to match that
reduced set of vector/expression types. Most of the time that set only needs to
be as large as there are different type combinations we want different behavious
for. For example, in the `add` case we can convert both V1 and V2 to `uint8`
without losing usable information, whereas in the case of `blend` we need 18
cases.

The following list documents the types that may be returned by different
functions. Only functions that return non-empty expression are documented.

bit_and, bit_andnot:
    - `expr_bit_{and,andnot}<V1,V2>`, where V1,V2 is one of:
        * uint8, uint8
        * uint8, mask_int8
        * mask_int8, mask_int8
        * uint16, uint16
        * uint16, mask_int16
        * mask_int16, mask_int16
        * uint32, uint32
        * uint32, mask_int32
        * mask_int32, mask_int32
        * uint64, uint64
        * uint64, mask_int64
        * mask_int64, mask_int64
        * float32, float32
        * float32, mask_float32
        * mask_float32, mask_float32
        * float64, float64
        * float64, mask_float64
        * mask_float64, mask_float64

bit_or, bit_xor:
    - `expr_bit_or<V1,V2>`, where V1,V2 is one of:
        * mask_int8, mask_int8
        * uint8, uint8
        * mask_int16, mask_int16
        * uint16, uint16
        * mask_int32, mask_int32
        * uint32, uint32
        * mask_int64, mask_int64
        * uint64, uint64
        * mask_float32, mask_float32
        * float32, float32
        * mask_float64, mask_float64
        * float64, float64

bit_not (TODO, not implemented yet)

blend
    - `expr_blend<V1,V2,V3>`, where V1,V2,V3 is one of:
        * mask_int8, mask_int8, mask_int8
        * uint8, uint8, uint8
        * uint8, uint8, mask_int8
        * mask_int16, mask_int16, mask_int16
        * uint16, uint16, uint16
        * uint16, uint16, mask_uint16
        * mask_int32, mask_int32, mask_int32
        * mask_float32, mask_float32, mask_float32
        * uint32, uint32, uint32
        * uint32, uint32, mask_int32
        * float32, float32, float32
        * float32, float32, mask_float32
        * mask_int64, mask_int64, mask_int64
        * mask_float64, mask_float64, mask_float64
        * uint64, uint64, uint64
        * uint64, uint64, mask_int64
        * float64, float64, float64
        * float64, float64, mask_float64

abs
    - `expr_abs<V1>`, where V1 is one of:
        * int8
        * int16
        * int32
        * int64
        * float32
        * float64

add
    - `expr_add<V1,V2>`, where V1,V2 is one of:
        * uint8, uint8
        * uint16, uint16
        * uint32, uint32
        * uint64, uint64
        * float32, float32
        * float64, float64

add_sat
    - `expr_add_sat<V1,V2>`, where V1,V2 is one of:
        * uint8, uint8
        * int8, int8
        * uint16, uint16
        * int16, int16

fmadd
    - `expr_fmadd<V1,V2,V3>`, where V1,V2,V3 is one of:
        * float32, float32, float32
        * float64, float64, float64

fmsub
    - `expr_fmsub<V1,V2,V3>`, where V1,V2,V3 is one of:
        * float32, float32, float32
        * float64, float64, float64

mul
    - `expr_mul<V1,V2>`, where V1,V2 is one of:
        * float32, float32
        * float64, float64

mull
    - `expr_mull<V1,V2>`, where V1,V2 is one of:
        * uint16, uint16
        * int16, int16
        * uint32, uint32
        * int32, int32

mul_lo
    - `expr_mul_lo<V1,V2>`, where V1,V2 is one of:
        * uint16, uint16
        * uint32, uint32

mul_hi
    - `expr_mul_hi<V1,V2>`, where V1,V2 is one of:
        * int16, int16
        * uint16, uint16

neg
    - `expr_neg<V1>`, where V1 is one of:
        * int8
        * int16
        * int32
        * int64
        * float32
        * float64

sub
    - `expr_sub<V1,V2>`, where V1,V2 is one of:
        * uint8, uint8
        * uint16, uint16
        * uint32, uint32
        * uint64, uint64
        * float32, float32
        * float64, float64

sub_sat
    - `expr_sub_sat<V1,V2>`, where V1,V2 is one of:
        * uint8, uint8
        * int8, int8
        * uint16, uint16
        * int16, int16
