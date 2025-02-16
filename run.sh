#!/usr/bin/env bash

if [ -z "$1" ]; then
    echo "Usage: $0 <path-to-verilog-src> [args]"
    exit
fi

vvp -M./build -mlib ./build/$1vp ${@:2}
