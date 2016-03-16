#!/usr/bin/env python3

#   Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

import lxml.etree as e
import sys
import os
import shutil

if len(sys.argv) != 3:
    print("Please provide the source xml as the first argument and the output "
"directory as the second")
    sys.exit(1)

in_fn = sys.argv[1]
out_dir = sys.argv[2]

if not os.path.exists(in_fn):
    print("Could not find the source file")
    sys.exit(1)

if out_dir == '' or out_dir == '.':
    print("The output directory can not be the current directory")
    sys.exit(1)

data = open(in_fn, 'r').read().replace(' xmlns=', ' xmlns_ignore=')
if os.path.exists(out_dir):
    shutil.rmtree(out_dir)
os.makedirs(out_dir)

p = e.XMLParser(huge_tree=True)
el = e.fromstring(data, parser=p)

print('Parsed; ')

for page in el.iter():
    if page.tag != 'page':
        continue

    title = page.xpath('title')[0].text

    revisions = page.xpath('revision')

    revs=[]
    for r in revisions:
        rev={}
        rev['time'] = r.xpath('timestamp')[0].text
        rev['text'] = r.xpath('text')[0].text
        revs.append(rev)

    revs = sorted(revs, key=lambda x: x['time'])

    last_text = revs[-1]['text']
    if last_text == None:
        last_text = ''

    title = title.replace(' ', '_')
    title = title.replace('/', '#')

    if title.count(':') > 1:
        print("Invalid title: " + title)
        continue

    pathnames = title.replace(':', '/').split('/')
    pathnames = [ p for p in pathnames if p != '' ]
    dest_dir = out_dir + '/' + '/'.join(pathnames[:-1])
    dest_path = out_dir + '/' + '/'.join(pathnames) + '.mwiki'

    if dest_dir != '' and not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    open(dest_path, 'w').write(last_text)
    print(dest_path)
