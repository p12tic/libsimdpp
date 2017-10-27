#!/usr/bin/env python3

#   Copyright (C) 2016-2017  Povilas Kanapickas <povilas@radix.lt>
#
# Distributed under the Boost Software License, Version 1.0.
#   (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

# This script depends on pywikibot framework. Install using
# pip install pywikibot --pre

import os

# pywikibot loads 'user-config.py' file in current directory by default
# disable this behavior. We want the same information to be supplied via
# command line.
os.environ['PYWIKIBOT2_NO_USER_CONFIG']='1'

import pywikibot
import pywikibot.config2
import pywikibot.pagegenerators
import pywikibot.data.api

import argparse
import itertools
import shutil
import sys

SYNC_DIRECTION_UPLOAD = 1
SYNC_DIRECTION_DOWNLOAD = 2

def get_path_from_title(title):
    title = title.replace(' ', '_')

    pathnames = title.replace(':', '/').split('/')
    pathnames = [ p for p in pathnames if p != '' ]

    return '/'.join(pathnames) + '.mwiki'

def sync_single_page(page, direction, dest_root):
    title = page.title()
    text = page.get(get_redirect=True)

    dest_path = os.path.join(dest_root, get_path_from_title(title))

    if direction == SYNC_DIRECTION_UPLOAD:
        if not os.path.exists(dest_path):
            return
        with open(dest_path, 'r') as file:
            new_text = file.read()
        if text != new_text:
            page.put(new_text, 'sync with git')
            print('Uploaded {0}'.format(title))

    elif direction == SYNC_DIRECTION_DOWNLOAD:
        dest_dir = os.path.dirname(dest_path)
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)

        with open(dest_path, 'w') as file:
            file.write(text)
        print('Downloaded {0}'.format(dest_path))

def perform_sync(url, direction, dest_root, user, password):

    if direction == SYNC_DIRECTION_DOWNLOAD:
        if os.path.exists(dest_root):
            shutil.rmtree(dest_root)
        os.makedirs(dest_root)

    # Supply information to config that would otherwise be defined in
    # user-config.py
    pywikibot.config2.family = 'libsimdpp'
    pywikibot.config2.mylang = 'en'
    pywikibot.config2.family_files['libsimdpp'] = url
    pywikibot.config2.step = 100
    pywikibot.config2.put_throttle = 0

    site = pywikibot.Site(user=user, fam='libsimdpp')

    # pywikibot.login.LoginManager seems to be not fully implemented and broken
    # Comments in the source suggest that data.api module contains full
    # implementation. Use it instead.
    login_manager = pywikibot.data.api.LoginManager(password=password,
                                                    site=site, user=user)
    login_manager.login()

    pages = itertools.chain(
        pywikibot.pagegenerators.AllpagesPageGenerator(namespace=0, site=site),
        pywikibot.pagegenerators.AllpagesPageGenerator(namespace=10, site=site)
    )
    pages = pywikibot.pagegenerators.PreloadingGenerator(pages, groupsize=100)

    for page in pages:
        sync_single_page(page, direction, dest_root)

def main():
    parser = argparse.ArgumentParser(prog='sync_mediawiki')
    parser.add_argument('url', type=str,
                        help='URL to root of a MediaWiki instance')
    parser.add_argument('direction', type=str,
                        help='"upload" or "download"')
    parser.add_argument('destination_root', type=str,
                        help='Destination directory to place results to')
    parser.add_argument('user', type=str,
                        help='Username to perform bot operations under')
    parser.add_argument('password', type=str,
                        help='User password to authenticate with')
    args = parser.parse_args()

    direction = None
    if args.direction == 'upload':
        direction = SYNC_DIRECTION_UPLOAD
    elif args.direction == 'download':
        direction = SYNC_DIRECTION_DOWNLOAD
    else:
        print('Incorrect direction option. Expected "upload" or "download"')
        sys.exit(1)

    if args.destination_root == '' or args.destination_root == '.':
        print("The output directory can not be the current directory")
        sys.exit(1)

    perform_sync(args.url, direction, args.destination_root,
                 args.user, args.password)

if __name__ == '__main__':
    main()
