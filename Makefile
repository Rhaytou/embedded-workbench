.PHONY: up down docker_clean_all


# General worflow
## Start all Docker containers
up:
	docker compose up -d --build

## Stop and remove all Docker containers and volumes defined in docker compose
down:
	docker compose down -v

## Full Docker cleanup
docker_clean_all:
	docker stop $$(docker ps -aq) 2>/dev/null || true && \
	docker rm -f $$(docker ps -aq) 2>/dev/null || true && \
	docker rmi -f $$(docker images -q) 2>/dev/null || true && \
	docker volume rm $$(docker volume ls -q) 2>/dev/null || true && \
	docker network rm $$(docker network ls -q | grep -v "bridge\|host\|none") 2>/dev/null || true && \
	docker system prune -a --volumes -f


# Hardware analysis
## gpio-uart-i2c-spi-logic-analyzer

## usb-uart-jtag-swd-monitor
### Variables
UJSM_SERVICE_NAME = usb-uart-jtag-swd-monitor

### Start the service
ujsm_start:
	docker compose up -d --build usb-uart-jtag-swd-monitor_service

### Down the service
ujsm_down:
	docker-compose stop usb-uart-jtag-swd-monitor_service

### Restart the service
ujsm_restart:
	docker compose up -d --build usb-uart-jtag-swd-monitor_service

### Show service's logs
ujsm_logs:
	docker compose logs usb-uart-jtag-swd-monitor_service

### Set up workspace auth
ujsm_worksapce_chmod:
	docker exec -it usb-uart-jtag-swd-monitor_container bash -c "find /workspace -type d -exec chmod 777 {} \; && find /workspace -type f -exec chmod 666 {} \;"

### Open an interactive bash shell
ujsm_bash:
	docker exec -it usb-uart-jtag-swd-monitor_container bash

### Check the device (Must target the arm jtag+swd device not "04d8")
ujsm_check_device:
	docker exec -it usb-uart-jtag-swd-monitor_container bash -c 'lsusb'

## software-defined-radio-monitor

## network-monitor
### Variables
UJSM_SERVICE_NAME = network-monitor

### Start the service
nm_start:
	docker compose up -d --build network-monitor_service

### Down the service
nm_down:
	docker-compose stop network-monitor_service

### Restart the service
nm_restart:
	docker compose up -d --build network-monitor_service

### Show service's logs
nm_logs:
	docker compose logs network-monitor_service

### Set up workspace auth
nm_worksapce_chmod:
	docker exec -it network-monitor_container bash -c "find /workspace -type d -exec chmod 777 {} \; && find /workspace -type f -exec chmod 666 {} \;"

### Open an interactive bash shell
nm_bash:
	docker exec -it network-monitor_container bash

### Check the device (Must target the arm jtag+swd device not "04d8")
nm_check_device:
	docker exec -it network-monitor_container bash -c 'lsusb'


# Hardeware programming
## platformio 
### Variables
PIO_NAME = platformio
PIO_BOARD ?= arduino

### Start the service
pio_start:
	docker compose up -d --build platformio_service

### Down the service
pio_down:
	docker-compose stop platformio_service

### Restart the service
pio_restart:
	docker compose up -d --build platformio_service

### Show service's logs
pio_logs:
	docker compose logs platformio_service

### Set up workspace auth
pio_worksapce_chmod: # docker exec -it platformio_container bash -c "find /workspace -type d -exec chmod 777 {} \; && find /workspace -type f -exec chmod 666 {} \;"
	docker exec -it platformio_container chmod 700 /workspace

### Open an interactive bash shell
pio_bash:
	docker exec -it platformio_container bash

### Check the device
pio_check_device:
	docker exec -it platformio_container bash -c 'lsusb'

### Build the PlatformIO project for the selected board
pio_build:
	docker exec -it platformio_container bash -c "cd /workspace/$(PIO_BOARD) && pio run"

### Upload compiled firmware to the connected device
pio_upload:
	docker exec -it platformio_container bash -c "cd /workspace/$(PIO_BOARD) && pio run -t upload"

### Open the serial monitor for the selected board # SEGGER J-Link: pio device monitor -p /dev/ttyACM0 -b 115200
pio_monitor:
	docker exec -it platformio_container bash -c "cd /workspace/$(PIO_BOARD) && pio device monitor"

### Clean PlatformIO build files for the selected board
pio_clean:
	docker exec -it platformio_container bash -c "rm -rf /workspace/$(PIO_BOARD)/.pio"

## Pic container Workflow
### References (Pic microcontrollers, ...)
REF_PIC ?= 18F4580
SRC=./workspace/pic/main.c

### Open an interactive bash shell
bash_pic:
	docker exec -it pic_container bash

### Restart the container
pic_restart:
	docker restart pic_container

### Set up workspace auth
pic_worksapce_chmod:
	docker exec -it pic_container bash -c "find /workspace -type d -exec chmod 777 {} \; && find /workspace -type f -exec chmod 666 {} \;"

### Check the device
pic_check_device:
	docker exec -it jtag-swd-openocd_container bash -c 'lsusb | grep -i "04d8"'

### Build
pic_build:
	xc8 \
	--chip=18F4580 \
	--opt=default \
	-I. \
	--outdir=./pic/.pic \
	./pic/main.c

### Upload
pic_upload:

### pk2cmd
####cp /opt/pk2cmdv1-20Linux2-6/PK2DeviceFile.dat /usr/local/bin/
####pk2cmd -PPIC18F4580 -F./pic/.pic/main.hex -M -Y
####usr/local/bin/pk2cmd -PPIC18F4580 -F./pic/.pic/main.hex -M -Y

### MPLAB
####lsusb | grep -i "04d8"
####ls -l /dev/bus/usb/001/007
####chmod 666 /dev/bus/usb/001/007

####cd /opt/microchip/MPLABX/mplab_platform/mplab_ipe
####./ipecmd.sh --help
####./ipecmd.sh 18F4580 PK3 -?
####./ipecmd.sh 18F4580 PK3 -OK
####./ipecmd.sh PIC18F4580 PK3 -OK 2>&1
####./ipecmd.sh -P18F4580 -T PK3 -F/workspace/pic/.pic/main.hex -M
####./ipecmd.sh -P18F4580 -T PK3 -F/workspace/pic/.pic/main.hex -MV

### Open the serial monitor
pic_monitor:
	picocom -b 9600 /dev/ttyUSB0

### Clean build files for the selected board
pic_clean:
	docker exec -it pic_container bash -c "rm -rf /workspace/pic/.pic/*"





## Raspberry Pi

## Spartan 6

# Hardware access
## Linux
## Android
## Windows
## Mac Os
## Ios











