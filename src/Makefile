# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 14:31:06 by luzog78           #+#    #+#              #
#    Updated: 2026/01/20 15:38:41 by luzog78          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WD				:= /workspace

ASM_SRC			:= src/boot.asm src/main.asm
ASM_OBJ			:= $(ASM_SRC:.asm=.o)
LINKER_FILE		:= src/linker.ld

MULTIBOOT_OUT	:= src/iso/boot/multiboot.bin
ISO_WD			:= src/iso
ISO_OUT			:= dist/kfs.iso

ASM_OBJ			:= $(addprefix $(WD)/, $(ASM_OBJ))
LINKER_FILE		:= $(addprefix $(WD)/, $(LINKER_FILE))
MULTIBOOT_OUT	:= $(addprefix $(WD)/, $(MULTIBOOT_OUT))
ISO_WD			:= $(addprefix $(WD)/, $(ISO_WD))
ISO_OUT			:= $(addprefix $(WD)/, $(ISO_OUT))


LD				:= ld
LD_FLAGS		:= -m elf_i386 -b elf32-i386

CC				:= gcc
CFLAGS			:= -march=i386 -ffreestanding -O2 -Wall -Wextra -c

NASM			:= nasm
NASM_FLAGS		:= -f elf32


# **************************************************************************** #


build: $(ASM_OBJ)
	$(LD) $(LD_FLAGS) -n -o $(MULTIBOOT_OUT) -T $(LINKER_FILE) $(ASM_OBJ)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO_OUT) $(ISO_WD)

%.o: %.asm
	$(NASM) $(NASM_FLAGS) -o $@ $<

clean:
	rm -f $(ASM_OBJ) $(MULTIBOOT_OUT) $(ISO_OUT)

re: clean build

.PHONY: build clean re
