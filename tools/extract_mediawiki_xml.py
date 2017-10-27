#!/usr/bin/env python3

#   Copyright (C) 2016  Povilas Kanapickas <povilas@radix.lt>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

import argparse
import lxml.etree as e
import os
import shutil
import sys

def extract_single_page(page, dest_root):

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

    if title.count(':') > 1:
        print("Invalid title: " + title)
        return None

    pathnames = title.replace(':', '/').split('/')
    pathnames = [ p for p in pathnames if p != '' ]
    dest_dir = dest_root + '/' + '/'.join(pathnames[:-1])
    dest_path = dest_root + '/' + '/'.join(pathnames) + '.mwiki'

    if dest_dir != '' and not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    open(dest_path, 'w').write(last_text)
    return dest_path

def extract_mediawiki_xml(src_xml_path, dest_root):

    data = open(src_xml_path, 'r').read().replace(' xmlns=', ' xmlns_ignore=')
    if os.path.exists(dest_root):
        shutil.rmtree(dest_root)
    os.makedirs(dest_root)

    p = e.XMLParser(huge_tree=True)
    el = e.fromstring(data, parser=p)

    print('Parsed XML ')

    for page in el.iter():
        if page.tag != 'page':
            continue
        dest_path = extract_single_page(page, dest_root)

        if dest_path is not None:
            print('Extracted {0}'.format(dest_path))

def main():
    parser = argparse.ArgumentParser(prog='extract_mediawiki_xml')
    parser.add_argument('source_xml', type=str, help='Source XML file')
    parser.add_argument('destination_dir', type=str,
                        help='Destination directory to place results to')
    args = parser.parse_args()

    if not os.path.exists(args.source_xml):
        print("Could not find the source file")
        sys.exit(1)

    if args.destination_dir == '' or args.destination_dir == '.':
        print("The output directory can not be the current directory")
        sys.exit(1)

    extract_mediawiki_xml(args.source_xml, args.destination_dir)

if __name__ == '__main__':
    main()
