# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 10:10:50 by luzog78           #+#    #+#              #
#    Updated: 2026/01/20 16:49:11 by luzog78          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


env-run: env-build
	docker run -it --rm -v ./src:/workspace/src -v ./dist:/workspace/dist -v ./obj:/workspace/obj kfs-env

env-build:
	docker build -t kfs-env .

env-stop:
	-docker stop kfs-env

env-rm: env-stop
	-docker rm kfs-env
	-docker rmi kfs-env

env-re: env-rm env-run

qemu:
	qemu-system-x86_64 -cdrom ./dist/kfs.iso
#	-m 512M -boot d -enable-kvm

