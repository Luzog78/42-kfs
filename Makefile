# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 10:10:50 by luzog78           #+#    #+#              #
#    Updated: 2026/02/04 11:08:46 by luzog78          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ISO_FILE	= dist/kfs.iso

DOCKER_VOLUMES	= -v "$$(pwd)/src":/workspace/src \
				  -v "$$(pwd)/dist":/workspace/dist \
				  -v "$$(pwd)/obj":/workspace/obj


# **************************************************************************** #


all: re qemu

help:
	@echo "Makefile targets:"
	@echo "  all          - Do build-quick and qemu-quick"
	@echo
	@echo "  build        - Build the ISO file"
	@echo "  build-quick  - Build the ISO file quickly (no compression)"
	@echo "  qemu         - Run the ISO in QEMU"
	@echo "  qemu-quick   - Run the quick ISO in QEMU with verbose"
	@echo
	@echo "  env-run      - Build and Start the container"
	@echo "  env-build    - Build the container"
	@echo "  env-stop     - Stop the container"
	@echo "  env-rm       - Remove the container and its image"
	@echo "  env-re       - Rebuild and start the container"
	@echo
	@echo "  help         - Show this help message"


# **************************************************************************** #


build: env-build
	docker run $(DOCKER_VOLUMES) kfs-env make -C /workspace/src build

build-quick: env-build
	docker run $(DOCKER_VOLUMES) kfs-env make -C /workspace/src build-quick

clean: env-build
	docker run $(DOCKER_VOLUMES) kfs-env make -C /workspace/src clean

fclean: env-build
	docker run $(DOCKER_VOLUMES) kfs-env make -C /workspace/src fclean

re: env-build
	docker run $(DOCKER_VOLUMES) kfs-env make -C /workspace/src re

re-quick: env-build
	docker run $(DOCKER_VOLUMES) kfs-env make -C /workspace/src re-quick

qemu:
	qemu-system-x86_64 -cdrom ./dist/kfs.iso

qemu-quick:
	qemu-system-x86_64 -cdrom ./dist/kfs_quick.iso -serial stdio -d int,cpu_reset


# **************************************************************************** #


env-run: env-build
	docker run -it $(DOCKER_VOLUMES) kfs-env

env-build:
	mkdir -p dist
	docker build -t kfs-env .

env-stop:
	-docker stop kfs-env

env-rm: env-stop
	-docker rm kfs-env
	-docker rmi kfs-env

env-re: env-rm env-run


# **************************************************************************** #


.PHONY: all help build build-quick qemu qemu-quick clean fclean re re-quick env-run env-build env-stop env-rm env-re
