FROM --platform=linux/amd64 ubuntu:24.04

WORKDIR /wasi

COPY lib *.c *.h *.sh /wasi/

RUN export DEBIAN_FRONTEND=noninteractive && ln -fs /usr/share/zoneinfo/Europe/Amsterdam /etc/localtime && \
    apt update --assume-yes && apt install --assume-yes --no-install-recommends python3.12 wget pip tzdata
    
RUN mkdir -p ~/.config/pip && echo '[global]' > ~/.config/pip/pip.conf && echo 'break-system-packages = true' >> ~/.config/pip/pip.conf

RUN pip install wasienv==0.5.4 && mkdir -p /usr/local/lib/python3.12/dist-packages/wasienv-storage/sdks/8/ && \
    export version=22 && cd /usr/local/lib/python3.12/dist-packages/wasienv-storage/sdks/8/ && rm -rf wasi* && \
    wget -q https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-$version/wasi-sdk-$version.0-linux.tar.gz && tar xzvf wasi-sdk-$version.0-linux.tar.gz && mv wasi-sdk-$version.0 wasi-sdk-8.0 && \
    export patchfile=/usr/local/lib/python3.12/dist-packages/wasienv-storage/sdks/8/wasi-sdk-8.0/share/wasi-sysroot/include/wasm32-wasi/signal.h && \
    cat "$patchfile"|grep -E -v '^void.+\*signal.*int.*void.*int' > /tmp/patchfile && cat /tmp/patchfile > "$patchfile"
        
RUN export DEBIAN_FRONTEND=noninteractive && apt-get clean --assume-yes autoclean && apt-get autoremove --assume-yes && rm -rf /var/lib/{apt,dpkg,cache,log}/ && \
    chmod +x ./build_wasi.sh

ENTRYPOINT [ "/wasi/build_wasi.sh" ]

# RUN cd /wasi && pwd && ls && chmod +x ./build_wasi.sh && ./build_wasi.sh 