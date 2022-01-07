#!/bin/bash

source "utils/config.sh"

if [[ -d $BUILD_DIR ]]; then
$BUILD_DIR/tests/fibutilsTests
fi
