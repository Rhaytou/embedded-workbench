.PHONY: up down clean bash docker_clean_all build upload monitor

# Default board (can be overridden with BOARD=<name>)
BOARD ?= arduino


# Start all Docker containers in detached mode
up:
	docker compose up -d

# Stop and remove all Docker containers and volumes defined in docker-compose
down:
	docker compose down -v

# Clean PlatformIO build files for the selected board
clean:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD) && pio run -t clean"

# Open an interactive bash shell inside the PlatformIO container
bash:
	docker exec -it platformio-dev bash

# Full Docker cleanup — stop, remove containers/images/volumes/networks, and prune system
docker_clean_all:
	docker stop $$(docker ps -aq) 2>/dev/null || true && \
	docker rm -f $$(docker ps -aq) 2>/dev/null || true && \
	docker rmi -f $$(docker images -q) 2>/dev/null || true && \
	docker volume rm $$(docker volume ls -q) 2>/dev/null || true && \
	docker network rm $$(docker network ls -q | grep -v "bridge\|host\|none") 2>/dev/null || true && \
	docker system prune -a --volumes -f

# Build the PlatformIO project for the selected board
build:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD) && pio run"

# Upload compiled firmware to the connected device
upload:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD) && pio run -t upload"

# Open the serial monitor for the selected board
monitor:
	docker exec -it platformio-dev bash -c "cd /workspace/$(BOARD) && pio device monitor"




