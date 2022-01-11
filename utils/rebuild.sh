#!/bin/bash

source utils/config.sh

# if [[ ! -d $BUILD_DIR ]]; then
    rm -rf $BUILD_DIR
    mkdir $BUILD_DIR > /dev/null
# fi

pushd $BUILD_DIR
cmake ..
make