# ARG HTTP_PROXY

FROM ubuntu:22.04

ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV DEBIAN_FRONTEND=noninteractive

# RUN groupadd --gid $USER_GID $USERNAME \
#     && useradd --uid $USER_UID --gid $USER_GID -ms /bin/bash dev

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

# RUN mkdir -p /home/${USERNAME}/app \
    # && chmod 777 -R /home/${USERNAME}/app
    # && chown ${USERNAME}:${USERNAME} /home/${USERNAME}/app
# USER ${USERNAME}
# WORKDIR /app
# RUN git config --global http.proxy ${HTTP_PROXY} && git config --global https.proxy ${HTTP_PROXY}

# RUN git clone https://github.com/foss-for-synopsys-dwc-arc-processors/qemu
# WORKDIR /app/qemu
# RUN ./configure --target-list=x86_64-softmmu \
#                 --enable-debug \
#                 --enable-debug-tcg --enable-trace-backends=simple --disable-plugins \
#                 --skip-meson --disable-werror \
#     && make
# arc-softmmu, ,arm-softmmu

WORKDIR /app

RUN git clone https://github.com/zephyrproject-rtos/zephyr
ENV ZEPHYR_BASE=/app/zephyr
# /home/$USERNAME/app/zephyr
RUN pip install -r ${ZEPHYR_BASE}/scripts/requirements.txt
RUN cmake -P ${ZEPHYR_BASE}/share/zephyr-package/cmake/zephyr_export.cmake

# COPY zephyr-sdk-0.17.0_linux-x86_64.tar.xz /home/${USERNAME}/app
RUN wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.0/zephyr-sdk-0.17.0_linux-x86_64.tar.xz \
    && wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.0/sha256.sum | shasum --check --ignore-missing \
    && tar xvf zephyr-sdk-0.17.0_linux-x86_64.tar.xz \
    && yes | ./zephyr-sdk-0.17.0/setup.sh
    # && rm zephyr-sdk-0.17.0_linux-x86_64.tar.xz
    # installs the whole available compilers. Check minimal version.
ENV ZEPHYR_SDK_INSTALL_DIR=/app/zephyr-sdk-0.17.0

EXPOSE 80 443 1234
