# The starting image
FROM ubuntu:24.04

# Prevent interactive tzdata config
ARG DEBIAN_FRONTEND=noninteractive

# Base system
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    bash \
    sudo \
    ca-certificates \
    curl \
    wget \
    git \
    build-essential \
    cmake \
    pkg-config \
    software-properties-common \
    locales \
    usbutils \
    tzdata && \
    rm -rf /var/lib/apt/lists/*

# Embedded / USB tools
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    picocom \
    minicom \
    sdcc \
    sdcc-libraries \
    libusb-1.0-0-dev && \
    rm -rf /var/lib/apt/lists/*


# Microchip XC8
ENV XC8_VERSION=2.46
ENV XC8_DIR=/opt/microchip/xc8

RUN wget -O /tmp/xc8.run \
    --header="User-Agent: Mozilla/5.0" \
    "https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v${XC8_VERSION}-full-install-linux-x64-installer.run" && \
    chmod +x /tmp/xc8.run && \
    /tmp/xc8.run --mode unattended --netservername localhost --prefix ${XC8_DIR} && \
    ln -s ${XC8_DIR}/bin/xc8 /usr/local/bin/xc8 && \
    rm /tmp/xc8.run


# Add user to dialout (It adds the user root to the Linux group dialout. On Linux systems, the dialout group is traditionally used to grant access to serial devices.)
RUN usermod -aG dialout root


# Add i386 architecture
RUN dpkg --add-architecture i386 && apt-get update

RUN apt-get install -y \
        libc6:i386 \
        libstdc++6:i386 \
        libx11-6:i386 \
        libxext6:i386 \
        libxrender1:i386 \
        libxtst6:i386 \
        libxi6:i386 \
        libusb-0.1-4:i386 \
        && rm -rf /var/lib/apt/lists/*

# Force install4j to bypass root detection
ENV INSTALL4J_ADD_VM_PARAMS="-Dinstall4j.sudo=true"
ENV USER=root
ENV HOME=/root


# pk2cmd from Microchip (precompiled binary)
##RUN wget -O /tmp/pk2cmdv1-20Linux2-6.tar.gz http://ww1.microchip.com/downloads/en/DeviceDoc/pk2cmdv1-20Linux2-6.tar.gz && \
##    tar -xzf /tmp/pk2cmdv1-20Linux2-6.tar.gz -C /opt && \
##    cp /opt/pk2cmdv1-20Linux2-6/pk2cmd /usr/local/bin/ && \
##    rm /tmp/pk2cmdv1-20Linux2-6.tar.gz


# Copy MPLAB installer
COPY MPLABX-v6.25-linux-installer.sh /tmp/MPLABX.sh

RUN chmod +x /tmp/MPLABX.sh && \
    /tmp/MPLABX.sh --nox11 -- --mode unattended \
        --unattendedmodeui none \
        --ide 0 \
        --ipe 1 \
        --8bitmcu 1 \
        --16bitmcu 1 \
        --32bitmcu 1 \
        --installdir /opt/microchip/MPLABX && \
    rm /tmp/MPLABX.sh

ENV LD_LIBRARY_PATH=/usr/lib/i386-linux-gnu:/usr/lib/i386-linux-gnu/libusb-0.1:$LD_LIBRARY_PATH

# Workspace
WORKDIR /workspace

# Default command
##CMD ["bash"]
CMD ["bash", "-c", "chmod 666 /dev/bus/usb/*/* && exec bash"]















