# C/C++ embedded compilation
C
    x86_64 Linux
        Compile: gcc -o /workspace/.exec/x86_64_linux /workspace/main.c
        Run: /workspace/.exec/x86_64_linux
        Compile for Gdb: gcc -g -O0 -o /workspace/.exec/x86_64_linux /workspace/main.c
        Run with Gdb: gdb /workspace/x86_64_linux

    ARM Cortex-M (bare-metal microcontrollers)  (qemu-user cannot run bare-metal Cortex-M binaries directly)
        Compile: arm-none-eabi-gcc -ffreestanding -nostdlib -nostartfiles /workspace/main.c -o /workspace/.exec/arm_bare_metal.elf
        Compile for Gdb: arm-none-eabi-gcc -ffreestanding -nostdlib -nostartfiles /workspace/main.c -o /workspace/.exec/arm_bare_metal.elf
        Run with gdb: gdb-multiarch /workspace/.exec/arm_bare_metal.elf

    ARM 32-bit (Linux)
        Compile
            arm-linux-gnueabihf-gcc -o /workspace/.exec/arm_32_linux /workspace/main.c
            arm-linux-gnueabihf-gcc -static /workspace/main.c -o /workspace/.exec/arm_32_linux
        Run: qemu-arm /workspace/.exec/arm_32_linux
        Compile for Gdb: arm-linux-gnueabihf-gcc -static /workspace/main.c -o /workspace/.exec/arm_32_linux
        Run with Gdb: gdb-multiarch /workspace/.exec/arm_32_linux

    ARM 64-bit (Linux)
        Compile
            aarch64-linux-gnu-gcc -o /workspace/.exec/arm_64_linux /workspace/main.c
            aarch64-linux-gnu-gcc -static /workspace/main.c -o /workspace/.exec/arm_64_linux
        Run: qemu-aarch64 /workspace/.exec/arm_64_linux
        Compile for Gdb: aarch64-linux-gnu-gcc -static /workspace/main.c -o /workspace/.exec/arm_64_linux
        Run with Gdb: gdb-multiarch /workspace/.exec/arm_64_linux

    RISC-V 64-bit (Linux)
        Compile
            riscv64-linux-gnu-gcc -o /workspace/.exec/risc_v_linux /workspace/main.c
            riscv64-linux-gnu-gcc -static /workspace/main.c -o /workspace/.exec/risc_v_linux
        Run: qemu-riscv64 /workspace/.exec/risc_v_linux
        Compile for Gdb: riscv64-linux-gnu-gcc -static /workspace/main.c -o /workspace/.exec/risc_v_linux
        Run with Gdb: gdb-multiarch /workspace/.exec/risc_v_linux

C++
    x86_64 Linux
        Compile: g++ -o /workspace/.exec/x86_64_linux /workspace/main.cpp
        Run: /workspace/.exec/x86_64_linux
        Compile for Gdb: g++ -g -O0 -o /workspace/.exec/x86_64_linux /workspace/main.cpp
        Run with Gdb: gdb /workspace/.exec/x86_64_linux

    ARM Cortex-M (bare-metal microcontrollers) (qemu-user cannot run bare-metal Cortex-M binaries directly)
        Compile: arm-none-eabi-g++ -ffreestanding -nostdlib -nostartfiles /workspace/main.cpp -o /workspace/.exec/arm_bare_metal.elf
        Compile for Gdb: arm-none-eabi-g++ -ffreestanding -nostdlib -nostartfiles /workspace/main.cpp -o /workspace/.exec/arm_bare_metal.elf
        Run with Gdb: gdb-multiarch /workspace/.exec/arm_bare_metal.elf

    ARM 32-bit (Linux)
        Compile
            arm-linux-gnueabihf-g++ -o /workspace/.exec/arm_32_linux /workspace/main.cpp
            arm-linux-gnueabihf-g++ -static /workspace/main.cpp -o /workspace/.exec/arm_32_linux
        Run: qemu-arm /workspace/.exec/arm_32_linux
        Compile for Gdb: arm-linux-gnueabihf-g++ -static /workspace/main.cpp -o /workspace/.exec/arm_32_linux
        Run with Gdb: gdb-multiarch /workspace/.exec/arm_32_linux

    ARM 64-bit (Linux)
        Compile
            aarch64-linux-gnu-g++ -o /workspace/.exec/arm_64_linux /workspace/main.cpp
            aarch64-linux-gnu-g++ -static /workspace/main.cpp -o /workspace/.exec/arm_64_linux
        Run: qemu-aarch64 /workspace/.exec/arm_64_linux
        Compile for Gdb: aarch64-linux-gnu-g++ -static /workspace/main.cpp -o /workspace/.exec/arm_64_linux
        Run with Gdb: gdb-multiarch /workspace/.exec/arm_64_linux

    RISC-V 64-bit (Linux)
        Compile
            riscv64-linux-gnu-g++ -o /workspace/.exec/risc_v_linux /workspace/main.c
            riscv64-linux-gnu-g++ -static /workspace/main.cpp -o /workspace/.exec/risc_v_linux
        Run: qemu-riscv64 /workspace/.exec/risc_v_linux
        Compile for Gdb: riscv64-linux-gnu-g++ -static /workspace/main.cpp -o /workspace/.exec/risc_v_linux
        Run with Gdb: gdb-multiarch /workspace/.exec/risc_v_linux


# Gdb embedded debugging
gdb or gdb-multiarch exe
    break main # set a breakpoint at the main function
    run # start the program
    next # step over the next line of code
    step # step into a function
    continue # continue running until next breakpoint
    print x # print the value of variable x
    display x # automatically display variable x each step
    info locals # show all local variables
    info breakpoints # list all breakpoints
    delete 1 # delete breakpoint number 1
    watch x # break when variable x changes
    finish # run until current function returns
    backtrace # show the call stack
    frame 2 # switch to frame number 2 in the call stack
    list # show source code around current line
    list 10,20 # show lines 10 to 20 of the current file
    set var x=5 # change the value of variable x
    info registers # show CPU registers
    x/10xw &x # examine memory at the address of x, 10 words in hex
    quit # exit GDB


# Usb embedded Monitor
## Basic
### usbutils
lsusb # List all USB devices connected to the system
lsusb -v # Verbose listing of USB devices, including configurations and endpoints
usb-devices # Display detailed information about USB devices

## Usb Raw
### coreutils: Can read/write raw data to devices exposed as /dev/ (like /dev/ttyUSB0 or /dev/sdb)
# Disk operations
dd if=/dev/zero of=file.img bs=1M count=100 # create a 100MB file of zeros

## DFU devices
### dfu-util: dfu-util is a command-line tool that allows you to flash firmware to USB devices using the DFU (Device Firmware Upgrade) protocol
dfu-util -l # List all DFU (Device Firmware Upgrade) devices connected
dfu-util -d 0483:df11 -D file.bin # Download (flash) firmware file.bin to the device
dfu-util -d 0483:df11 -a 0 -U flash.bin # Upload firmware from device to file.bin
dfu-util -a <alt> -D file.bin # Specify alternate interface for firmware download

## Sniffing
### usbmon: Usb sniffing. Monitor USB traffic (kernel module).
modprobe usbmon


# Uart embedded monitor: screen & minicom
Usb to TTL (FT232RL)

SEGGER J-Link (ARM - Uart & Jtag & Swd) (Bus 001 Device 008: ID 1366:0105 SEGGER J-Link)
    Arduino
        ls /dev/ttyACM*
        chmod 666 /dev/ttyACM0

        screen /dev/ttyACM0 9600 (115200 57600 38400 9600)
            Quit
                Ctrl + A  then  K
                Ctrl + A  then  D

        minicom -D /dev/ttyACM0 -b 115200

        Pins
            Probe TX → Arduino RX (pin 0)
            Probe RX → Arduino TX (pin 1)
            Probe GND → Arduino GND

    Esp32

    smt32


# Jtag & Swd embedded monitor: Openocd
## Uploading
## Monitoring
## Jtag
## Swd

SEGGER J-Link (ARM - Uart & Jtag & Swd) (Bus 001 Device 008: ID 1366:0105 SEGGER J-Link)
    stm32
        Start: openocd -f interface/jlink.cfg -f target/stm32f1x.cfg
        Flash
        Monitor
            Listening on port 4444 for telnet connections
            Listening on port 3333 for gdb connections

Jtlink (Jtag & Swd)
    smt32
        Start: openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg
        Flash
            openocd -f interface/stlink.cfg \
                    -f target/stm32f4x.cfg \
                    -c "program firmware.elf verify reset exit"
        Monitor
            Listening on port 4444 for telnet connections
            Listening on port 3333 for gdb connections

            ---- Monitor: In another terminal (no gdb)
                From another terminal:
                ```bash
                telnet localhost 4444
                run # run
                reset run # reboot and run
                halt # stop CPU
                reset halt # reset and halt
                resume      # continue execution
                reg         # show registers
                mdw 0x20000000 8
                ```

            ---- GDB
                ```bash
                arm-none-eabi-gdb firmware.elf
                ```

                Inside GDB:
                ```gdb
                target remote :3333
                monitor reset halt
                load
                continue
                ```









































