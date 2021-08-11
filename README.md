## Build dependencies:
- LLVM (`brew install llvm`)
- [`wasi-sdk(12)`](https://github.com/WebAssembly/wasi-sdk/releases).

## Compilation

```sh
wasicc cutils.c libunicode.c quickjs.c libregexp.c qjs.c quickjs-libc.c -o qjs.wasm -DCONFIG_VERSION='"version"' -D_WASI_EMULATED_SIGNAL -lwasi-emulated-signal -O3
```

## Run with WasmEdge(0.8.2-rc4+)

```sh
wasmedge --dir .:. qjs.wasm -e "console.log('hello')"

wasmedge --dir .:. qjs.wasm repl.js
```

## Acknowledgment
This project is fork from [dip-proto/quickjs-wasi](https://github.com/dip-proto/quickjs-wasi)