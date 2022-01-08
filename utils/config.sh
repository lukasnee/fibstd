#!/bin/bash

set -e

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

ansiColorReset='\e[0m'
ansiColorBlack='\e[0;30m'
ansiColorRed='\e[0;31m'
ansiColorGreen='\e[0;32m'
ansiColorYellow='\e[0;33m'
ansiColorBlue='\e[0;34m'
ansiColorPurple='\e[0;35m'
ansiColorCyan='\e[0;36m'
ansiColorWhite='\e[0;37m'

ansiThicknessBold='\e[1m'
ansiThicknessReset='\e[22m'

BUILD_DIR=".build"
