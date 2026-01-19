# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 14:31:06 by luzog78           #+#    #+#              #
#    Updated: 2026/01/19 16:54:29 by luzog78          ###   ########.fr        #
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


BINUTILS_WD		:= /workspace/build/build-binutils
LD				:= /opt/cross/bin/x86_64-elf-ld


GCC_WD			:= /workspace/build/build-gcc
CC				:= /opt/cross/bin/x86_64-gcc


# **************************************************************************** #


build: $(LD) $(ASM_OBJ)
	$(LD) -n -o $(MULTIBOOT_OUT) -T $(LINKER_FILE) $(ASM_OBJ)
	grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO_OUT) $(ISO_WD)

%.o: %.asm
	nasm -f elf64 -o $@ $<

clean:
	rm -f $(ASM_OBJ) $(MULTIBOOT_OUT) $(ISO_OUT)


# **************************************************************************** #


binutils-build: $(LD)

$(BINUTILS_WD)/binutils-2.45:
	mkdir -p $(BINUTILS_WD)
	cd $(BINUTILS_WD) && wget https://ftp.gnu.org/gnu/binutils/binutils-2.45.tar.xz -O binutils-2.45.tar.xz
	cd $(BINUTILS_WD) && tar -xf binutils-2.45.tar.xz
	cd $(BINUTILS_WD) && rm -f binutils-2.45.tar.xz

$(LD): $(BINUTILS_WD)/binutils-2.45
	mkdir -p $(BINUTILS_WD)/build
	cd $(BINUTILS_WD)/build && ../binutils-2.45/configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror
	cd $(BINUTILS_WD)/build && make
	cd $(BINUTILS_WD)/build && make install

binutils-clean:
	rm -rf $(BINUTILS_WD)


# **************************************************************************** #


gcc-build: $(CC)

$(GCC_WD)/gcc-15.2.0:
	mkdir -p $(GCC_WD)
	cd $(GCC_WD) && wget https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.xz
	cd $(GCC_WD) && tar -xf gcc-15.2.0.tar.xz
	cd $(GCC_WD) && rm -f gcc-15.2.0.tar.xz

$(CC): $(GCC_WD)/gcc-15.2.0
	mkdir -p $(GCC_WD)/build
	cd $(GCC_WD)/build && ../gcc-15.2.0/configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
	cd $(GCC_WD)/build && make all-gcc
	cd $(GCC_WD)/build && make all-target-libgcc
	cd $(GCC_WD)/build && make all-target-libstdc++-v3
	cd $(GCC_WD)/build && make install-gcc
	cd $(GCC_WD)/build && make install-target-libgcc
	cd $(GCC_WD)/build && make install-target-libstdc++-v3

gcc-clean:
	rm -rf $(GCC_WD)

.PHONY: build clean binutils-build binutils-clean gcc-build gcc-clean
