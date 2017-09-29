#!/usr/bin/env python3

#   Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

# Generates the simdpp/dispatch/macros_generated.h file
# Use as $ ./tools/gen_dispatcher_macros.py > simdpp/dispatch/macros_generated.h

from gen_common import output_template

num_args = 10

''' The following defines a template for each macro. $xxx$ are template
    parameters that are later replaced in output_template function.

    $macro_end$ - last part of the name of the macro.
    $ret_param$ - the return type macro parameter, with a preceding comma, if
        defined.
    $type_params$ - the same as $types$, just contains a preceding comma, if
        not empty.
    $ret_type$ - the return type -- 'void' if $ret_param$ not defined,
        $ret_param$ minus the preceding comma otherwise.
    $types_vars$ - same as $types$, just parenthesized type is followed with
        some identifier
    $n$ - identifies the backslash character
'''

# Define the dispatched function only for NULL architecture to avoid defining
# the same non-inline function several times.

redirect_template = '''
#define SIMDPP_MAKE_DISPATCHER_$macro_end$(NAME$ret_param$$type_params$)    $n$
    SIMDPP_MAKE_DISPATCHER(($ret_type$)(NAME)($type_arg_params$))'''

# Returns a string T1,T2,T3,...,T_num
def get_Tn_list(num):
    if num == 0:
        return ''
    identifiers = [ 'T{0}'.format(i+1) for i in range(num) ]
    return ','.join(identifiers)

# Returns a string (T1) a1, (T2) a2, (T3) a3,...,(T_num) a_num
def get_Tn_an_list(num):
    if num == 0:
        return ''
    identifiers = [ '(T{0}) a{0}'.format(i+1) for i in range(num) ]
    return ','.join(identifiers)

# Prints the macros given a template
def do_template(template):
    # void, no callback
    for i in range(0,num_args):
        Tn = get_Tn_list(i)
        Tn_an = get_Tn_an_list(i)

        vars = {}
        vars['macro_end'] = 'VOID' + str(i)
        vars['ret_param'] = ''
        vars['type_params'] = '' if i == 0 else ',' + Tn
        vars['ret_type'] = 'void'
        vars['types'] = Tn
        vars['type_arg_params'] = Tn_an
        output_template(template, vars)

    # R, no callback
    for i in range(0,num_args):
        Tn = get_Tn_list(i)
        Tn_an = get_Tn_an_list(i)

        vars = {}
        vars['macro_end'] = 'RET' + str(i)
        vars['ret_param'] = ',R'
        vars['type_params'] = '' if i == 0 else ',' + Tn
        vars['ret_type'] = 'R'
        vars['types'] = Tn
        vars['type_arg_params'] = Tn_an
        output_template(template, vars)

# print the actual file

print('''/*  Copyright (C) 2013  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/


// This file is generated automatically. See tools/gen_dispatcher_macros.py

#ifndef LIBSIMDPP_DISPATCH_MACROS_GENERATED_H
#define LIBSIMDPP_DISPATCH_MACROS_GENERATED_H

#include <simdpp/dispatch/collect_macros_generated.h>
#include <simdpp/dispatch/make_dispatcher.h>

/** Note: the following macros are deprecated and provided only for backwards
    compatibility. See SIMDPP_MAKE_DISPATCHER for a more versatile replacement.

    Builds a dispatcher for a specific non-member function. Different macros
    are provided for functions with or without return value and for each
    parameter count.

    Macros in the form @a SIMDPP_MAKE_DISPATCHER_VOID# are to be used for
    functions with no return value. It accepts the following macro parameters:

    * NAME: the unqualified name of the function to dispatch.

    * T1, T2, ..., T#: the types of the parameters of the function that is
      dispatched.

    Macros in the form @a SIMDPP_MAKE_DISPATCHER_RET# are to be used for
    functions that return a value. It accepts the following macro parameters:

    * NAME: the unqualified name of the function to dispatch.

    * R: the type of the return value

    * T1, T2, ..., T#: the types of the parameters of the function that is
      dispatcher.


    @c SIMDPP_ARCH_NAMESPACE::NAME must refer to the function to be disptached
    relative to the namespace in which the @a MAKE_DISPATCHER* macro is used in.
    That is, the macro must be used in a namespace one level up than the
    dispatched function, and that namespace must be @c SIMDPP_ARCH_NAMESPACE

    @a R, T1, T2, ..., T# must be exactly the same as those of the function
    to be dispatched. The dispatched function may be overloaded.

    The macro defines a function with the same signature as the dispatched
    function in the namespace the macro is used. The body of that function
    implements the dispatch mechanism.

    The dispatch functions check the enabled instruction set and select the
    best function on first call. The initialization does not introduce race
    conditions when done concurrently.
*/
''')
do_template(redirect_template)
print('''

#endif
''')
