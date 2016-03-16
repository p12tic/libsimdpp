
SHELL := /bin/bash

source:
	rm -rf "reference"
	mkdir "reference"

	pushd "reference" > /dev/null; \
	regex=".*index\\.php.*|.*/Special:.*|.*/Talk:.*" \
	regex+="|.*/Help:.*|.*/File:.*|.*/Cppreference:.*" \
	regex+="|.*/WhatLinksHere:.*|.*/Template:.*|.*/Category:.*" \
	regex+="|.*action=.*|.*printable=.*" ; \
	echo $$regex ; \
	wget --adjust-extension --page-requisites --convert-links \
	  --force-directories --recursive --level=15 \
	  --span-hosts --domains=doc.radix.lt \
	  --reject-regex $$regex \
	  --timeout=180 --no-verbose --no-check-certificate \
	  --retry-connrefused --waitretry=1 --read-timeout=20 \
	  http://doc.radix.lt/libsimdpp/ ; \
	popd > /dev/null

output:
	python3 preprocess.py

