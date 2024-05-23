#!/usr/bin/env bash

cd /wasi

wasicc libunicode.c cutils.c libbf.c libregexp.c quickjs.c quickjs-libc.c $1.c \
    -DCONFIG_VERSION='"wasi"' \
    -D_WASI_EMULATED_SIGNAL \
    -D_WASI_EMULATED_PROCESS_CLOCKS \
    -DCONFIG_BIGNUM=y \
    -lwasi-emulated-signal \
    -lwasi-emulated-process-clocks \
    -O3 -o $1.wasm

cp *.wasm ./build/
