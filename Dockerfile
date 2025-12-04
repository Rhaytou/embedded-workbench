# The starting image
FROM ubuntu:24.04

# Install general dev tools
RUN apt-get update && apt-get install -y \
    build-essential gcc g++ make cmake \
    python3 python3-pip python3-venv git curl udev \
    && rm -rf /var/lib/apt/lists/*

# PlatformIO
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






















