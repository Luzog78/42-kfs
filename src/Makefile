# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 14:31:06 by luzog78           #+#    #+#              #
#    Updated: 2026/01/20 16:52:45 by luzog78          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WD				:= /workspace
OBJ_DIR			:= /workspace/obj

ASM_SRC			:= src/boot.asm
ASM_OBJ			:= $(ASM_SRC:.asm=.asm.o)

C_SRC			:= src/main.c
C_OBJ			:= $(C_SRC:.c=.c.o)

LINKER_FILE		:= src/linker.ld

MULTIBOOT_OUT	:= src/iso/boot/multiboot.bin
ISO_WD			:= src/iso
ISO_OUT			:= dist/kfs.iso


ASM_OBJ			:= $(addprefix $(OBJ_DIR)/, $(ASM_OBJ))
C_OBJ			:= $(addprefix $(OBJ_DIR)/, $(C_OBJ))
LINKER_FILE		:= $(addprefix $(WD)/, $(LINKER_FILE))
MULTIBOOT_OUT	:= $(addprefix $(WD)/, $(MULTIBOOT_OUT))
ISO_WD			:= $(addprefix $(WD)/, $(ISO_WD))
ISO_OUT			:= $(addprefix $(WD)/, $(ISO_OUT))


LD				:= ld
LD_FLAGS		:= -m elf_i386 -b elf32-i386

CC				:= g++
CFLAGS			:= -m32 -ffreestanding -O2 -Wall -Wextra -c -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs

NASM			:= nasm
NASM_FLAGS		:= -f elf32


# **************************************************************************** #


build: $(MULTIBOOT_OUT)

$(MULTIBOOT_OUT): $(ASM_OBJ) $(C_OBJ)
	$(LD) $(LD_FLAGS) -n -o $(MULTIBOOT_OUT) -T $(LINKER_FILE) $(ASM_OBJ) $(C_OBJ)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO_OUT) $(ISO_WD)

$(OBJ_DIR)/%.asm.o: $(WD)/%.asm
	mkdir -p $(dir $@)
	$(NASM) $(NASM_FLAGS) -o $@ $<

$(OBJ_DIR)/%.c.o: $(WD)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(ASM_OBJ) $(C_OBJ) $(MULTIBOOT_OUT)

fclean: clean
	rm -rf $(ISO_OUT)

re: fclean build

verify: $(MULTIBOOT_OUT)
	-grub-file --is-x86-multiboot $(MULTIBOOT_OUT) \
		&& (echo "Multiboot1 verified"; exit 0) \
		|| (grub-file --is-x86-multiboot2 $(MULTIBOOT_OUT) \
			&& (echo "Multiboot1 verified"; exit 0) \
			&& (echo "Multiboot2 verification failed"; exit 1))

.PHONY: build clean fclean re
