# QuickJS Runtime for Hooks

### JS Runtime for on chain Rule Engine (Smart Contracts)

##### This project is based on:

- [bellard/quickjs](https://github.com/bellard/quickjs)
    - Forked by and modified for Hooks by @RichardAH: [RichardAH/quickjslite](https://github.com/RichardAH/quickjslite)
- [second-state/quickjs-wasi](https://github.com/second-state/quickjs-wasi)
    - As originally forked from: [dip-proto/quickjs-wasi](https://github.com/dip-proto/quickjs-wasi)

##### This project depends on:

- [WebAssembly/wasi-sdk](https://github.com/WebAssembly/wasi-sdk/) (wasi-sdk-22)

# Build

You can conveniently build using Docker.

To build the container image for the build process:

```bash
docker build --tag quickjs-wasm-builder .
```

## Compiler JS for use as a Hook

To build the `qjsc.wasm` JS Compiler WebAssembly binary using the previously created container:

```bash
docker run --rm --platform linux/amd64 -v $(pwd)/build:/wasi/build \
    quickjs-wasm-builder qjsc
```

## Runtime to run/execute Javascript

To build `qjs.wasm` (QuickJS Runtime) WebAssembly binary using the previously created container:

```bash
docker run --rm --platform linux/amd64 -v $(pwd)/build:/wasi/build \
    quickjs-wasm-builder qjs
```

# Run (use) - CLI

To run the `.wasm` binaries, we're using `wasmedge`: we need a virtual filesystem, stdin, stdout, etc. and
`wasmedge` happily provides this context:

### To compile a Javascript/... file to be used as a Hook

After building `qjsc.wasm`:

```bash
wasmedge --dir=.:. ./build/qjsc.wasm -c -o whatever.bc whatever.js
```

### To run a Javascript/... file & upcode debugging

After building `qjs.wasm`:

```bash
wasmedge --dir=.:. ./build/qjs.wasm -e "console.log('Hello World');"
```

# Run - Browser

To use the above `.wasm` files in your browser, create Javascript code like below, and save it as `qjsc.mjs`.
You can build this `.mjs` file for the browser with `esbuild`:

```bash
esbuild qjsc.mjs --bundle --minify --tree-shaking=true --platform=browser --format=esm --target=es2017 > qjsc-browser.js
```

Now you have a `qjsc-browser.js` file to use in the browser, which you can include as modules:

```html
<script type="module" src="./qjsc-browser.js"></script>
```

`qjsc.mjs` example source code:

```javascript
import { WASI } from "@runno/wasi"
import { Buffer } from 'buffer/' // Browser needs this, node (CLI) doesn't

const wasmLocation = 'https://my-site.com/qjsc.wasm' // Must be served with mime type application/wasm!

const result = WASI.start(fetch(wasmLocation), {
    args: ["qjsc", "-c", "-o", "/hook.bc", '/hook.js'],
    env: { SOME_KEY: "some value" },
    stdout: (out) => alert("stdout: " + out),
    stderr: (err) => alert("stderr:" + err),
    stdin: () => prompt("stdin:"),
    fs: {
        "/hook.js": {
            mode: "string",
            content: 'console.log("Hello World!")', // Contents here, read from file / textinput / fs (node) / fetch ...
        },
    },
})

result.then(r => {
    // Sanitize some things to make it ready for a SetHook create code:

    const compiledHook = Buffer.from(r.fs?.['/hook.bc']?.content)
        .toString('utf-8')
        .match(/\{[^0-9a-fx]+?(0x[0-9a-f]{2}[^0-9a-fx]+?)+\}/misg)?.[0]
        .slice(1, -1).trim().split(',').map(o => o.trim().slice(-2)).join('')

    document.write(compiledHook)
})
```

### Test @ `https://runno.dev/wasi`

Upload `qjsc.wasm` and create a `.js` file @ the virtual filesystem, e.g. `sample.js`, and then use argument:

```bash
-c -o sample.bc sample.js
```
