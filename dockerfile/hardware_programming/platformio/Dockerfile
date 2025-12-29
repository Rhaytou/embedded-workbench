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


# Python
## Install Python, Pip, and venv
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-venv && \
    rm -rf /var/lib/apt/lists/*

## Create virtual environment
RUN python3 -m venv /opt/venv

## Activate venv by default
ENV PATH="/opt/venv/bin:$PATH"

## Upgrade pip inside venv
RUN pip install --no-cache-dir --upgrade pip setuptools wheel

## Copy and install Python dependencies
COPY requirements.txt /tmp/requirements.txt
RUN pip install --no-cache-dir -r /tmp/requirements.txt


# Platformio board env
## ATmega (e.g., 328P)
## Arduino Uno / Nano
WORKDIR /workspace
COPY boards/arduino arduino
WORKDIR /workspace/arduino
RUN pio run || true && rm -rf /workspace/arduino

## ESP32
WORKDIR /workspace
COPY boards/esp32 esp32
WORKDIR /workspace/esp32
RUN pio run || true && rm -rf /workspace/esp32

## Raspberry Pi Pico (RP2040)
## STM32 (F0–F7, L0–L4, H7, G0)
## SiFive FE310 (HiFive1)


# Workspace
WORKDIR /workspace

# Default command
CMD ["bash"]






