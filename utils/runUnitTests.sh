#!/bin/bash

set -e

source utils/config.sh

if [[ ! -f $UNIT_TEST_EXE_PATH ]]; then
    printf "${ansiColorRed}error: no unit tests executable. Expected at '$UNIT_TEST_EXE_PATH'\n${ansiColorReset}"
else
    printf \
    "${ansiColorGreen}${ansiThicknessBold}"\
    "Running unit tests...\n"\
    "===============================================================================\n"\
    "${ansiThicknessReset}${ansiColorReset}"
    
    ./$UNIT_TEST_EXE_PATH $@ # --durations yes
fi
