#!/bin/sh 
wasicc -msimd128 -mbulk-memory -ftls-model=local-exec -c ../libbf.c ../cutils.c ../libunicode.c wapper.c ../libregexp.c ../quickjs-libc.c -DNO_OS_POLL=1 -DCONFIG_BIGNUM=1 -DCONFIG_VERSION='"wasi"' -D_WASI_EMULATED_SIGNAL -lwasi-emulated-signal -O3 
wasiar -r libquickjs.a *.o 
bindgen wapper.h --no-layout-tests --size_t-is-usize -o binding.rs -- -D__wasi__ 
# cp static-lib and binding.rs to quickjs-rs-wasi
# change cp path
# cp libquickjs.a ../../quickjs-rs-wasi/lib/
# cp binding.rs ../../quickjs-rs-wasi/lib/
rm *.o 