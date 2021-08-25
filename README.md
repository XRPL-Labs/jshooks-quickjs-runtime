## Build dependencies:
- [`wasi-sdk(12)`](https://github.com/WebAssembly/wasi-sdk/releases).

## Compilation

```sh
# build qjs.wasm
./build_wasi.sh
```

## Run with WasmEdge(0.8.2-rc4+)

```sh
#eval
wasmedge --dir=.:. qjs.wasm -e "print('hello')"

#repl
wasmedge --dir=.:. qjs.wasm
```

## Acknowledgment
This project is form from [bellard/quickjs](https://github.com/bellard/quickjs)

### reference project 
[dip-proto/quickjs-wasi](https://github.com/dip-proto/quickjs-wasi)