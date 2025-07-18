FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
ARG HTTP_PROXY=""
ENV http_proxy=${HTTP_PROXY}
ENV https_proxy=${HTTP_PROXY}
ENV no_proxy="localhost,127.0.0.1"

RUN apt-get update && apt-get install -y --no-install-recommends \
    git libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev bzip2 \
    libnfs-dev libiscsi-dev \
    ninja-build python3 python3-dev \
    cmake gperf \
    ccache dfu-util device-tree-compiler wget rsync    \
    python3-pip python3-setuptools python3-wheel python3-venv \
    xz-utils file make gcc gcc-multilib g++ g++-multilib gdb net-tools \
    libsdl2-dev libmagic1 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
# installs the whole available compilers. Check minimal version.
ARG ZEPHYR_SDK_INSTALL_DIR_ARG="/app/zephyr-sdk-0.17.0"
ENV ZEPHYR_SDK_INSTALL_DIR=${ZEPHYR_SDK_INSTALL_DIR_ARG}
RUN wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.0/zephyr-sdk-0.17.0_linux-x86_64.tar.xz \
    && wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.0/sha256.sum | shasum --check --ignore-missing \
    && tar xvf zephyr-sdk-0.17.0_linux-x86_64.tar.xz \
    && yes | ./zephyr-sdk-0.17.0/setup.sh \
    && rm zephyr-sdk-0.17.0_linux-x86_64.tar.xz

RUN git config --global http.proxy ${HTTP_PROXY} && \
    git config --global https.proxy ${HTTP_PROXY}

# Clone the zephyr_learning repository and initialize submodules
RUN git clone https://github.com/vzilkov/zephyr_learning.git && \
    cd zephyr_learning && \
    git submodule init && git submodule update --remote

WORKDIR /app/zephyr_learning

RUN ZEPHYR_BASE=/app/zephyr_learning/zephyr && \
    python3 -m venv .xvenv && \
    .xvenv/bin/python3 -m pip install --upgrade pip && \
    .xvenv/bin/python3 -m pip install -r requirements.txt && \
    cmake -P ${ZEPHYR_BASE}/share/zephyr-package/cmake/zephyr_export.cmake

EXPOSE 80 443 912 1234
