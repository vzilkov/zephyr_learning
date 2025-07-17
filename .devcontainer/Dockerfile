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

RUN git config --global http.proxy ${HTTP_PROXY} && \
    git config --global https.proxy ${HTTP_PROXY}

WORKDIR /app/zephyr_learning
RUN git submodule update --init --recursive
ENV ZEPHYR_BASE=/app/zephyr_learning/zephyr
RUN pip install west && \
    pip install -r ${ZEPHYR_BASE}/scripts/requirements.txt && \
    cmake -P ${ZEPHYR_BASE}/share/zephyr-package/cmake/zephyr_export.cmake

WORKDIR /app
RUN wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.0/zephyr-sdk-0.17.0_linux-x86_64.tar.xz \
    && wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.0/sha256.sum | shasum --check --ignore-missing \
    && tar xvf zephyr-sdk-0.17.0_linux-x86_64.tar.xz \
    && yes | ./zephyr-sdk-0.17.0/setup.sh \
    && rm zephyr-sdk-0.17.0_linux-x86_64.tar.xz
# installs the whole available compilers. Check minimal version.
ENV ZEPHYR_SDK_INSTALL_DIR=/app/zephyr-sdk-0.17.0

EXPOSE 80 443 912 1234
