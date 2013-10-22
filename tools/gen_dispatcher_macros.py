#!/usr/bin/env python3

#   Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#
#   * Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#   POSSIBILITY OF SUCH DAMAGE.

# Generates the simd/dispatch_macros.h file
# Use as $ ./tools/gen_dispatch_macros.py > simd/dispatch_macros.h

import re

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
    $return$ - 'return ' if $ret_type$ is not 'void'
    $types$ - the dispatched function parameter types.
    $types_vars$ - same as $types$, just each type is followed with some
        identifier
    $vars$ - the list of identifiers referred to by $types_vars$
    $n$ - identifies the backslash character
'''

# Define the dispatched function only for NULL architecture to avoid defining
# the same non-inline function several times.

template_head = '''
#define SIMDPP_MAKE_DISPATCHER_$macro_end$(NAME$ret_param$$type_params$)    $n$
struct simdpp_ ## NAME ## _tag;                                             $n$
                                                                            $n$'''

template_fn = '''
$ret_type$ NAME($types_vars$)                                               $n$
{                                                                           $n$
    using Tag = simdpp_ ## NAME ## _tag;                                    $n$
    $return$ ::simdpp::detail::Dispatcher<                                  $n$
        Tag,$ret_type$$type_params$                                         $n$
    >::get_fun_ptr(SIMDPP_USER_ARCH_INFO)($vars$);                          $n$
}                                                                           $n$
                                                                            $n$'''

template_registration = '''
namespace SIMDPP_ARCH_NAMESPACE {                                           $n$
                                                                            $n$
static ::simdpp::detail::DispatchRegistrator<                               $n$
        simdpp_ ## NAME ## _tag,$ret_type$$types$                           $n$
> simdpp_dispatch_registrator_ ## NAME {                                    $n$
        ::simdpp::SIMDPP_ARCH_NAMESPACE::this_compile_arch(),               $n$
        static_cast<$ret_type$(*)($types$)>(&NAME)};                        $n$
                                                                            $n$
} /* namespace SIMDPP_ARCH_NAMESPACE */
'''

template_null = template_head + template_fn + template_registration
template_not_null = template_head + template_registration

# Prints a template substituting the given variables with given replacements
def output_template(template, vars):
    text = template
    for var in vars:
        text = text.replace('$'+var+'$', vars[var])

    # make the position of the backslash fixed
    lines = text.split('\n')
    text = []
    for line in lines:
        line = re.sub(' *\$n\$', '$n$', line)
        padlen = 80 + 3 - 2 - len(line)
        pad = ''
        if padlen > 0:
            pad = ' ' * padlen
        line = line.replace('$n$', pad + '\\')
        text.append(line)

    text = '\n'.join(text)
    print(text)

# Returns a string T1,T2,T3,...,T_num
def get_Tn_list(num):
    if num == 0:
        return ''
    out = 'T1'
    for i in range(1, num):
        out += ',T' + str(i+1)
    return out

# Returns a string a1,a2,a3,...,a_num
def get_an_list(num):
    if num == 0:
        return ''
    out = 'a1'
    for i in range(1, num):
        out += ',a' + str(i+1)
    return out

# Returns a string T1 a1, T2 a2, T3 a3,...,T_num a_num
def get_Tn_an_list(num):
    if num == 0:
        return ''
    out = 'T1 a1'
    for i in range(1, num):
        out += ',T' + str(i+1) + ' ' + 'a' + str(i+1)
    return out

# Prints the macros given a template
def do_template(template):
    # void, no callback
    for i in range(0,num_args):
        Tn = get_Tn_list(i)
        an = get_an_list(i)
        Tn_an = get_Tn_an_list(i)

        vars = {}
        vars['macro_end'] = 'VOID' + str(i)
        vars['ret_param'] = ''
        vars['type_params'] = '' if i == 0 else ',' + Tn
        vars['ret_type'] = 'void'
        vars['return'] = ''
        vars['types'] = Tn
        vars['types_vars'] = Tn_an
        vars['vars'] = an
        output_template(template, vars)

    # R, no callback
    for i in range(0,num_args):
        Tn = get_Tn_list(i)
        an = get_an_list(i)
        Tn_an = get_Tn_an_list(i)

        vars = {}
        vars['macro_end'] = 'RET' + str(i)
        vars['ret_param'] = ',R'
        vars['type_params'] = '' if i == 0 else ',' + Tn
        vars['ret_type'] = 'R'
        vars['return'] = 'return'
        vars['types'] = Tn
        vars['types_vars'] = Tn_an
        vars['vars'] = an
        output_template(template, vars)

# print the actual file

print('''/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

// This file is generated automatically. See tools/gen_dispatcher_macros.py

#ifndef LIBSIMDPP_DISPATCHER_MACROS_H
#define LIBSIMDPP_DISPATCHER_MACROS_H

/** @def SIMDPP_MAKE_DISPATCHER_***
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
    implements the dispatch mechanism. The function must not be called before
    main() starts.
*/
/// @{
#ifdef SIMDPP_USE_NULL
''')
do_template(template_null)
print('''
#else
''')
do_template(template_not_null)
print('''
#endif
/// @}

#endif
''')
