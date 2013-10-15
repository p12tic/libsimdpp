#!/bin/bash

# Accepts two arguments:
# * prefix: the name of the root directory within the archive
# * path: the location of the output archive
# The script must be run from the source directory.

git diff-index --quiet HEAD
if [ $? -ne 0 ]; then
    echo "Repository is not clean... Exiting..."
    exit 1
fi

git archive --prefix=$1/ HEAD --format=tar.gz > $2
