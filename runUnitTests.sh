#1/bin/bash

set -e

BUILD_DIR=".build"

if [[ ! -d $BUILD_DIR ]]; then
    rm -rf $BUILD_DIR
    mkdir $BUILD_DIR > /dev/null

else
.build/tests

fi
