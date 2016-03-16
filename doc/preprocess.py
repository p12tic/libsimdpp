#!/usr/bin/env python3

#   Copyright (C) 2011, 2012  Povilas Kanapickas <povilas@radix.lt>
#
#   This file is part of cppreference-doc
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see http://www.gnu.org/licenses/.

import fnmatch
import re
import os
import sys
import shutil
import urllib.parse

# copy the source tree
os.system('rm -rf output/reference')
os.system('mkdir -p output/reference')
os.system('cp -r reference/* output/reference ')

# find files that need to be preprocessed
html_files = []
for root, dirnames, filenames in os.walk('output/reference/'):
    for filename in fnmatch.filter(filenames, '*.html'):
        html_files.append(os.path.join(root, filename))

# clean the html files
for fn in html_files:
    f = open(fn, "r")
    text = f.read()
    f.close()

    f = open(fn, "w")
    f.write(text)
    f.close()

    tmpfile = fn + '.tmp';
    ret = os.system('xsltproc --novalid --html --encoding UTF-8 preprocess.xsl "' + fn + '" > "' + tmpfile + '"')
    if ret != 0:
        print("FAIL: " + fn)
        continue
    os.system('mv "' + tmpfile + '" "' + fn + '"')


