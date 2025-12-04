.PHONY: up down docker_clean_all detect_devices bash_pio BOARD_PIO clean_pio build_pio upload_pio monitor_pio


# Basics
## Start all Docker containers in detached mode
up:
	docker compose up -d

## Stop and remove all Docker containers and volumes defined in docker-compose
down:
	docker compose down -v

## Full Docker cleanup — stop, remove containers/images/volumes/networks, and prune system
docker_clean_all:
	docker stop $$(docker ps -aq) 2>/dev/null || true && \
	docker rm -f $$(docker ps -aq) 2>/dev/null || true && \
	docker rmi -f $$(docker images -q) 2>/dev/null || true && \
	docker volume rm $$(docker volume ls -q) 2>/dev/null || true && \
	docker network rm $$(docker network ls -q | grep -v "bridge\|host\|none") 2>/dev/null || true && \
	docker system prune -a --volumes -f

## Detect new devices or boards from docker !!!!!!!!!!!!!!!
detect_devices:
	docker exec -it platformio-dev bash -c "udevadm trigger --subsystem-match=usb --action=add"


# Platformio Boards
## Open an interactive bash shell inside the PlatformIO container
bash_pio:
	docker exec -it platformio-dev bash

BOARD_PIO ?= arduino
## Clean PlatformIO build files for the selected board
clean_pio:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD_PIO) && pio run -t clean"

## Build the PlatformIO project for the selected board
build_pio:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD_PIO) && pio run"

## Upload compiled firmware to the connected device
upload_pio:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD_PIO) && pio run -t upload"

## Open the serial monitor for the selected board
monitor_pio:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD_PIO) && pio device monitor"







