# Header basic
## The starting image
FROM ubuntu:24.04

## Prevent interactive tzdata config
ARG DEBIAN_FRONTEND=noninteractive

## System basics
RUN apt-get update && apt-get install -y \
    ca-certificates \
    bash \
    sudo \
    build-essential \
    autoconf \
    libtool \
    pkg-config \
    texinfo \
    # In Linux, the locales library/package is responsible for managing localization and internationalization settings—basically, it tells the system how to handle language, regional formats, and character encoding.
    locales \
    #
    make \
    #
    cmake \
    #
    tzdata \
    #
    curl \
    #
    wget \
    #
    telnet \
    #
    git \
    # Clean
    && rm -rf /var/lib/apt/lists/*


# Environnement
## C/C++ embedded compilation
RUN apt-get update && apt-get install -y \
    # X86_64
    gcc g++ \
    # Arm Cortex-M
    gcc-arm-none-eabi \
    # Arm 32
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf \
    # Arm 64
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    # Risc V
    gcc-riscv64-linux-gnu \
    g++-riscv64-linux-gnu \
    # Multi architecture run
    qemu-user \
    # Clean
    && rm -rf /var/lib/apt/lists/*

## Gdb embedded debugging: Linux, ARM, Risc-V
RUN apt-get update && apt-get install -y \
    # Gdb
    gdb-multiarch \
    # Clean
    && rm -rf /var/lib/apt/lists/*

## Embedded Monitor
### Usb, Hdmi, Ethernet
RUN apt-get update && apt-get install -y \
    # Usb
    ## usbutils: lsusb → Lists all USB buses and devices connected to your system. usb-devices → Shows detailed information about each USB device (like vendor ID, product ID, driver, and configuration). usbreset (sometimes) → Allows resetting a USB device from userspace.
    usbutils \
    ## dd: Can read/write raw data to devices exposed as /dev/ (like /dev/ttyUSB0 or /dev/sdb)
    coreutils \
    ## dfu-util: dfu-util is a command-line tool that allows you to flash firmware to USB devices using the DFU (Device Firmware Upgrade) protocol
    dfu-util \
    ## kmod: usb sniffing
    kmod \
    ## C
    ### libusb-1.0-0-dev: Sending / receiving raw USB packets
    libusb-1.0-0-dev \
    ### libhidapi-dev: communicating with USB and Bluetooth HID (Human Interface Device: Keyboards, Mice, Gamepads, Many debug probes, ...)
    libhidapi-dev \
    ### libftdi1-dev: read/write directly to FTDI chips
    libftdi1-dev \
    # Hdmi
    ## libdrm-dev: DRM (Direct Rendering Manager) is a Linux kernel subsystem for graphics devices. libdrm → User-space library to communicate with DRM/KMS.
    libdrm-dev \
    ## libasound2-dev: controls audio devices, including HDMI audio output.
    libasound2-dev \
    ## libcec-dev: Control HDMI devices that support CEC (Consumer Electronics Control)
    libcec-dev \
    # Ethernet
    ## libnl-3-dev: Can configure Ethernet interfaces, routing tables, or wireless interfaces
    libnl-3-dev \
    libnl-genl-3-dev \
    ## Clean
    && rm -rf /var/lib/apt/lists/*
#### Adds the user root to the dialout group. The dialout group usually has permission to access: UART / USB / serial ports
RUN usermod -aG dialout root

### Uart: Minicom & Screen
RUN apt-get update && apt-get install -y \
    # Screen
    screen \
    # Minicom
    minicom \
    # Clean
    && rm -rf /var/lib/apt/lists/*

### Jtag & Swd: OpenOCD
RUN git clone --branch v0.12.0 https://github.com/ntfreak/openocd.git /opt/openocd \
    && cd /opt/openocd \
    && ./bootstrap \
    && ./configure --enable-ftdi --enable-stlink \
    && make -j$(nproc) \
    && make install
RUN mkdir -p /usr/share/openocd/scripts \
    && cp -r /opt/openocd/tcl/* /usr/share/openocd/scripts/


# Footer basic
## Ports
#EXPOSE 8080

## Set PATH for convenience. Prepends /usr/local/bin to the PATH environment variable. When you install tools manually (pip, custom binaries, scripts).
ENV PATH="/usr/local/bin:$PATH"

## Workspace
WORKDIR /workspace

## Default command
CMD ["bash"]





















