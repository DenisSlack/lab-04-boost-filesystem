#!/bin/bash

set -e

cmake -H. -B_builds $CMAKE_OPTS
cmake --build _builds
./_builds/lab_04_boost_filesysytem