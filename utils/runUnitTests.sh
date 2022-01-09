#!/bin/bash

source "utils/config.sh"

if [[ -d $BUILD_DIR ]]; then

printf \
"${ansiColorGreen}${ansiThicknessBold}"\
"Running unit tests...\n"\
"===============================================================================\n"\
"${ansiThicknessReset}${ansiColorReset}"

$BUILD_DIR/tests/fibstdTests # --durations yes
fi
