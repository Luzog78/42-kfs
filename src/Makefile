# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 14:31:06 by luzog78           #+#    #+#              #
#    Updated: 2026/01/21 15:36:09 by bsavinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WD				:= /workspace
OBJ_DIR			:= /workspace/obj

ASM_SRC			:= src/kernel/boot.asm
ASM_OBJ			:= $(ASM_SRC:.asm=.asm.o)

CPP_SRC			:=	src/kernel/main.cpp \
					src/kernel/stdlib/VGA.cpp \
					src/kernel/stdlib/Term.cpp \
					src/kernel/stdlib/string.cpp
CPP_OBJ			:= $(CPP_SRC:.cpp=.cpp.o)

LINKER_FILE		:= src/kernel/linker.ld

MULTIBOOT_OUT	:= src/iso/boot/multiboot.bin
ISO_WD			:= src/iso
ISO_OUT			:= dist/kfs.iso
ISO_QUICK_OUT	:= dist/kfs_quick.iso


ASM_OBJ			:= $(addprefix $(OBJ_DIR)/, $(ASM_OBJ))
CPP_OBJ			:= $(addprefix $(OBJ_DIR)/, $(CPP_OBJ))
LINKER_FILE		:= $(addprefix $(WD)/, $(LINKER_FILE))
MULTIBOOT_OUT	:= $(addprefix $(WD)/, $(MULTIBOOT_OUT))
ISO_WD			:= $(addprefix $(WD)/, $(ISO_WD))
ISO_OUT			:= $(addprefix $(WD)/, $(ISO_OUT))
ISO_QUICK_OUT	:= $(addprefix $(WD)/, $(ISO_QUICK_OUT))


LD				:= ld
LD_FLAGS		:= -m elf_i386 -b elf32-i386

CC				:= g++
CFLAGS			:= -m32 -ffreestanding -O2 -Wall -Wextra -g -c -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -mno-sse -mno-sse2 -mno-sse3 -mno-mmx -mno-3dnow -I $(WD)/src/headers

NASM			:= nasm
NASM_FLAGS		:= -f elf32


# **************************************************************************** #


all: build-quick

help:
	@echo "Makefile targets:"
	@echo "  build        - Build the ISO file"
	@echo "  build-quick  - Build the ISO file quickly (no compression)"
	@echo "  verify       - Verify the multiboot binary"
	@echo
	@echo "  clean        - Remove object files and the multiboot binary"
	@echo "  fclean       - Remove all generated files"
	@echo "  re           - Rebuild everything"
	@echo
	@echo "  help         - Show this help message"


# **************************************************************************** #


build: $(ISO_OUT)

build-quick: $(ISO_QUICK_OUT)

$(ISO_OUT): $(MULTIBOOT_OUT) $(ASM_OBJ) $(CPP_OBJ)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO_OUT) $(ISO_WD) --modules="multiboot biosdisk iso9660" --compress=xz

$(ISO_QUICK_OUT): $(MULTIBOOT_OUT) $(ASM_OBJ) $(CPP_OBJ)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO_QUICK_OUT) $(ISO_WD)

$(MULTIBOOT_OUT): $(ASM_OBJ) $(CPP_OBJ)
	$(LD) $(LD_FLAGS) -n -o $(MULTIBOOT_OUT) -T $(LINKER_FILE) $(ASM_OBJ) $(CPP_OBJ)

$(OBJ_DIR)/%.asm.o: $(WD)/%.asm
	mkdir -p $(dir $@) && $(NASM) $(NASM_FLAGS) -o $@ $<

$(OBJ_DIR)/%.cpp.o: $(WD)/%.cpp
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(ASM_OBJ) $(CPP_OBJ) $(MULTIBOOT_OUT)

fclean: clean
	rm -rf $(ISO_OUT) $(ISO_QUICK_OUT)

re: fclean build

re-quick: fclean build-quick

verify: $(MULTIBOOT_OUT)
	-grub-file --is-x86-multiboot $(MULTIBOOT_OUT) \
		&& (echo "Multiboot1 verified"; exit 0) \
		|| (grub-file --is-x86-multiboot2 $(MULTIBOOT_OUT) \
			&& (echo "Multiboot1 verified"; exit 0) \
			&& (echo "Multiboot2 verification failed"; exit 1))


# **************************************************************************** #


.PHONY: all help build build-quick clean fclean re re-quick verify
