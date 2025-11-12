# Embedded Workbench

**Embedded Workbench** is an embedded programming and learning environment built with Docker and other tools. It allows users to work from their host system while maintaining a completely isolated and cross-platform environment.
The repository also includes a tutorials section, where each supported board-starting with Arduino, ESP32, and others—has its own dedicated guide.

---

## Project Structure

```
embedded-workbench/
├── Makefile
├── docker-compose.yaml
├── Dockerfile
├── README.md
├── LICENSE
└── workspace/
│   ├── arduino/
│   │   ├── src/
│   │   │   └── main.c
│   │   └── platformio.ini
│   └── esp32/
│       ├── src/
│       │   └── main.c
│       └── platformio.ini
└── tutorials/
    ├── 1_arduino/
    └── 2_esp32/
```

---

## The project

### What is the Workspace?

The **workspace** folder is where the boards are implemented.
If you want to add your own board, place it here and update the **Makefile** configuration.
Many boards share the same workflow commands since they use the same framework, such as PlatformIO for Arduino and ESP32.

The project uses external dependencies to manage the logic, so implementation will be done step by step, starting with the PlatformIO library.

**Current compatibility:**

| Architecture     | Boards / Examples                                  |
| ---------------- | -------------------------------------------------- |
| **AVR**          | Arduino Uno, Nano, Mega, ATtiny                    |
| **ARM Cortex-M** | STM32 (F0/F1/F3/F4/F7/H7), Teensy 3.x/4.x          |
| **ESP**          | ESP32, ESP32-S2/S3, ESP8266                        |
| **RISC-V**       | SiFive FE310, ESP32-C3, GD32VF103                  |
| **PIC / PIC32**  | Limited support via toolchains                     |
| **RP2040**       | Raspberry Pi Pico, Arduino Nano RP2040             |
| **Other**        | Many IoT boards: Adafruit, Seeed, Nordic nRF, etc. |

---

### What is the Tutorials Folder?

The **tutorials** folder contains specific and advanced examples, including circuit schematics when needed.
Each folder is organized by board. Simply copy and paste the code into your board’s **main.c** file to get started.

**Note:** Do not copy the entire file—only the content of the tutorial into the corresponding **main.c** file.
**Note:** The tutorials will be the same for all boards at first. For example, if I have a course named 'debug', each board will have its own 'debug' course.

---

## Start Up
### Set up the environment

**Clone the repository**

```
git clone https://github.com/Rhaytou/embedded-workbench.git
```

**Change directory**

```
cd ./embedded-workbench
```

**Start the container**

```
make up
```

**Code**
Place your code in:

```
./workspace/arduino/src/main.c
```

or use one of the existing simple examples to test your setup.
You can also browse the **tutorials** section for more advanced examples.

**Important:**
If the board was unplugged before the container started:

```
1. Plug the board
2. make down
3. make up
```

**Note:**
The workspace and tutorials are stored on your host machine, so you won’t lose your work after shutting down the container.

---

### Workflow

**Build firmware**

```
make build BOARD=arduino
```

**Upload firmware**

```
make upload BOARD=arduino
```

**Open serial monitor**

```
make monitor BOARD=arduino
```

---

## Coming Soon

### Workspace

* STM32 setup (already supported but ready-to-use examples will be added soon)
* PIC architecture implementation (will use different libraries since PIC is not open-source)

### Tutorials

* More Arduino and ESP32 tutorials (up to 10 per board)

---

## Contribute

This section will be updated soon.

---























