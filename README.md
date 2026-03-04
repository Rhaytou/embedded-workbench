# Embedded Workbench

**Embedded Workbench** is a dockerized development environment for embedded systems engineering. Each service runs in an isolated container with all the necessary toolchains, libraries, and hardware access pre-configured — no host pollution, no dependency conflicts, ready to work.

The project is organized around three concerns: programming targets, communicating with hardware protocols, and setting up the host machine. Services are added incrementally — every service present in the repository is fully operational.

---

## Services

### Hardware programming
*Write code on host, cross-compile, deploy to target.*

**firmware-based** — no OS, direct hardware control, flash firmware (Arduino, ESP32, STM32)

**os-based** — full OS on target, deploy software via ADB/SSH (Raspberry Pi, Android)

### Hardware communication
*Observe, monitor and communicate with hardware protocols.*

**protocol** — wired low-level protocols between chips and devices (GPIO, UART, I2C, SPI, JTAG, SWD, USB)

**rf-wireless** — wireless signal capture and network monitoring (SDR, WiFi/BT, network)

### Hardware environment
*Set up the host machine to support the above workflows.*

**Linux** — host drivers, toolchains, udev rules

**Windows** — host drivers, toolchains, WSL setup

**macOS** — host drivers, toolchains, Homebrew setup

---

## Requirements

- Docker
- Docker Compose v2
- Make

---

## General Workflow

**Start all services**
```bash
make up
```

**Stop all services**
```bash
make down
```

**Full Docker cleanup**
```bash
make docker_clean_all
```

---

## firmware-based — Quick Start

The firmware-based service supports Arduino, ESP32, and STM32 via PlatformIO. All toolchains are pre-installed in the container at build time.

**Start the service**
```bash
make hpfb_start
```

**Build firmware** (default: arduino)
```bash
make hpfb_build REF=arduino
make hpfb_build REF=esp32
make hpfb_build REF=stm32
```

**Upload firmware to device**
```bash
make hpfb_upload REF=arduino
make hpfb_upload REF=esp32
make hpfb_upload REF=stm32
```

**Open serial monitor**
```bash
make hpfb_monitor REF=arduino
make hpfb_monitor REF=esp32
make hpfb_monitor REF=stm32
```

**Other commands**
```bash
make hpfb_bash            # open a shell inside the container
make hpfb_check_device    # list connected USB devices
make hpfb_clean REF=arduino  # clean build files
make hpfb_down            # stop the service
```

Your code lives in `workspace/hardware_programming/firmware-based/`. Edit your `main.cpp` there and use the commands above to build and deploy.

---

## Coming Soon

- os-based (Raspberry Pi, Android)
- protocol (GPIO, UART, I2C, SPI, JTAG, SWD, USB)
- rf-wireless (SDR, WiFi/BT, network)
- Hardware environment (Linux, Windows, macOS)



