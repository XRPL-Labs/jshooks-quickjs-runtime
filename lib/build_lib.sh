#!/bin/sh

rm *.o
wasicc -c ../libbf.c ../cutils.c ../libunicode.c wapper.c ../libregexp.c ../quickjs-libc.c -DCONFIG_BIGNUM=1 -DCONFIG_VERSION='"wasi"' -D_WASI_EMULATED_SIGNAL -lwasi-emulated-signal -O3
wasiar -r libquickjs.a *.o
bindgen wapper.h --size_t-is-usize -o binding.rs -- -D__wasi__
# cp static-lib and binding.rs to quickjs-rs-wasi
# change cp path
# cp libquickjs.a ../../quickjs-rs-wasi/lib/
# cp binding.rs ../../quickjs-rs-wasi/lib/