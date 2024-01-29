#!/bin/sh 
~/wasi-sdk-21.0/bin/clang --sysroot=${WASI_ROOT_PATH} -msimd128 -mbulk-memory -c ../libbf.c ../cutils.c ../libunicode.c wapper.c ../libregexp.c ../quickjs-libc.c -DNO_OS_POLL=1 -DCONFIG_BIGNUM=1 -DCONFIG_VERSION='"wasi"' -D_WASI_EMULATED_SIGNAL -O3 -fPIC
~/wasi-sdk-21.0/bin/ar -r libquickjs.a *.o 
bindgen wapper.h --no-layout-tests --allowlist-item '(JS|js|Js).*' -o binding.rs -- -D__wasi__
# cp static-lib and binding.rs to quickjs-rs-wasi
# change cp path
# cp libquickjs.a ../../quickjs-rs-wasi/lib/
# cp binding.rs ../../quickjs-rs-wasi/lib/
rm *.o 