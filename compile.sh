#!/usr/bin/env bash

if [ -z "$1" ]; then
    echo "Usage: $0 <verilog-src>"
    exit
fi

mkdir -p build
cd build

iverilog-vpi ../src/lib.cpp

iverilog -o $1vp ../$1
