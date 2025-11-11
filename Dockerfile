# The starting image
FROM ubuntu:24.04

# Install general dev tools
RUN apt-get update && apt-get install -y \
    build-essential gcc g++ make cmake \
    python3 python3-pip python3-venv git curl udev \
    && rm -rf /var/lib/apt/lists/*

# Install PlatformIO Core
RUN pip install --break-system-packages -U platformio

# Manual udev rules for USB device access
RUN mkdir -p /etc/udev/rules.d && \
    echo 'SUBSYSTEM=="usb", MODE="0666"' > /etc/udev/rules.d/99-platformio.rules

# Add user to dialout
RUN usermod -aG dialout root

# Workspace
WORKDIR /workspace
VOLUME ["/workspace"]

# Default command
CMD ["bash"]























## Base image
#FROM ubuntu:24.04
#
## General Dev Tools
#RUN apt-get update && apt-get install -y \
#    build-essential \
#    gcc \
#    g++ \
#    gdb \
#    make \
#    cmake \
#    openocd \
#    nano \
#    git \
#    wget \
#    curl \
#    python3 \
#    python3-pip \
#    python3-venv \
#    python3-setuptools \
#    dfu-util \
#    unzip \
#
#    gcc-avr \
#    binutils-avr \
#    gdb-avr \
#
#    && rm -rf /var/lib/apt/lists/*
#
## Arduino
#RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
#ENV PATH="/root/bin:${PATH}"
#
#RUN for i in 1 2 3; do \
#      arduino-cli core update-index && \
#      arduino-cli core install arduino:avr && \
#      arduino-cli core install arduino:samd && \
#      arduino-cli core install arduino:megaavr && break || sleep 10; \
#    done
#
## ESP32 ********************* remove doubles
#RUN apt-get update && apt-get install -y \
#    flex bison gperf \
#    python3-serial python3-pyparsing python3-click python3-colorama \
#    ninja-build ccache libffi-dev libssl-dev dfu-util xz-utils file \
#    && rm -rf /var/lib/apt/lists/*
#
### Fix Python binary name for ESP-IDF (Ubuntu 24+)
#RUN ln -sf /usr/bin/python3 /usr/bin/python
#
### Set IDF path
#ENV IDF_PATH=/opt/esp-idf
#
### Clone ESP-IDF
#RUN git clone --depth 1 --branch v5.3 https://github.com/espressif/esp-idf.git ${IDF_PATH}
#
### Install the toolchains + Python environment in one step
#RUN bash -c "cd ${IDF_PATH} && ./install.sh all"
#
### Make ESP-IDF environment available for all shells
#RUN echo 'source ${IDF_PATH}/export.sh' >> /etc/bash.bashrc && \
#    echo 'source ${IDF_PATH}/export.sh' >> /root/.bashrc
#
### Environment variables for IDF tools
#ENV PATH="${IDF_PATH}/tools:${PATH}"
#ENV IDF_TOOLS_PATH="${IDF_PATH}/tools"
#ENV IDF_PYTHON_ENV_PATH="${IDF_PATH}/python_env"
#
#RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/*
#
## STM32
#RUN apt-get update && apt-get install -y \
#    gcc-arm-none-eabi \
#    gdb-multiarch \
#    stlink-tools \
#    && rm -rf /var/lib/apt/lists/*
#
## Workspace
#WORKDIR /workspace
#VOLUME ["/workspace"]
#
#CMD bash -c "chmod -R 777 /workspace && exec bash"















