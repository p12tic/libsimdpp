#!/usr/bin/env python3

#   Copyright (C) 2015  Povilas Kanapickas <povilas@radix.lt>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

import re

''' Prints a template substituting the given variables with given replacements.
    The substitution variables in template should be surrounded by $ characters,
    e.g. $variable$. The vars parameter must be a dictionary mapping variable
    names to replacement values.

    One special variable is defined: "n" ($n$ in the template). It is replaced
    by a backslash at 80th column by stripping or padding whitespace as
    required.
'''
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
