#!/bin/sh
# Get absolute path from which this script file was executed
# (Could be changed to "pwd -P" to resolve symlinks to their target)
SCRIPT_PATH=$( cd $(dirname $0) ; pwd )
cd "${SCRIPT_PATH}"

cmake --build ./../build/debug --config Debug --target all --
cmake --build ./../build/release --config Debug --target all --