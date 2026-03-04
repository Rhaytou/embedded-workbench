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


# Hardware programming
## firmware-based: no OS, direct hardware control, flash firmware (Arduino, ESP32, STM32)
### Variables
REF ?= arduino

### Start the service
hpfb_start:
	docker compose up -d --build hpfb_service

### Down the service
hpfb_down:
	docker compose stop hpfb_service

### Restart the service
hpfb_restart:
	docker compose up -d --build hpfb_service

### Show service's logs
hpfb_logs:
	docker compose logs hpfb_service

### Set up workspace auth
hpfb_workspace_chmod:
	docker exec -it hpfb_container chmod 700 /workspace

### Open an interactive bash shell
hpfb_bash:
	docker exec -it hpfb_container bash

### Check the device
hpfb_check_device:
	docker exec -it hpfb_container bash -c 'lsusb'

### Build the PlatformIO project for the selected board
hpfb_build:
	docker exec -it hpfb_container bash -c "cd /workspace/$(REF) && pio run"

### Upload compiled firmware to the connected device
hpfb_upload:
	docker exec -it hpfb_container bash -c "cd /workspace/$(REF) && pio run -t upload"

### Open the serial monitor for the selected board # SEGGER J-Link: pio device monitor -p /dev/ttyACM0 -b 115200
hpfb_monitor:
	docker exec -it hpfb_container bash -c "cd /workspace/$(REF) && pio device monitor"

### Clean PlatformIO build files for the selected board
hpfb_clean:
	docker exec -it hpfb_container bash -c "rm -rf /workspace/$(REF)/.pio"


## os-based


# Hardware communication
## protocol
## rf-wireless


# Hardware environment
## Linux
## Windows
## macOS




