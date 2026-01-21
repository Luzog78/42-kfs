<div align="center">

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@                                                                              @
@  /$$   /$$  /$$$$$$         /$$        /$$$$$$                               @
@ | $$  | $$ /$$__  $$       | $$       /$$__  $$                              @
@ | $$  | $$|__/  \ $$       | $$   /$$| $$  \__//$$$$$$$                      @
@ | $$$$$$$$  /$$$$$$//$$$$$$| $$  /$$/| $$$$   /$$_____/                      @
@ |_____  $$ /$$____/|______/| $$$$$$/ | $$_/  |  $$$$$$    ___                @
@       | $$| $$             | $$_  $$ | $$     \____  $$  | _ )_  _           @
@       | $$| $$$$$$$$       | $$ \  $$| $$     /$$$$$$$/  | _ \ || | ysabik   @
@       |__/|________/       |__/  \__/|__/    |_______/   |___/\_, | bsavinel @
@                                                               |__/           @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
```

# 42 Cursus - kfs

<img src="https://upload.wikimedia.org/wikipedia/commons/4/45/Qemu_logo.svg" height="30" alt="qemu" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/docker/docker-original.svg" height="30" alt="docker" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cplusplus/cplusplus-original.svg" height="30" alt="c++" />
<img width="12" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/vscode/vscode-original.svg" height="30" alt="vscode" />

<br><br>

</div>


## Details

- **Summary:** *Let's recreate the Kernel! Because why not?*
- **Project version:** *`v1.1.1`*
- **Author(s):** *[ysabik](https://profile.intra.42.fr/users/ysabik)*, *[bsavinel](https://profile.intra.42.fr/users/bsavinel)*
- **Public repo:** [GitHub](https://github.com/Luzog78/42-kfs)

<br>

- **Architecture:** *i386 (x86, 32-bits)*
- **Bootloader:** *GRUB with Multiboot2*
- **Main code language:** *C++*

<br>

| Project | Subject | Version | Summary |
| :-----: | :------ | :-----: | :------ |
| **kfs-1** | [en.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/66157/en.subject.pdf) | v1 | The real code ! Code a basic OS bootable with GRUB in i386. |
| **kfs-2** | [en.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/66158/en.subject.pdf) | v2 | Let’s code the stack ! |

<br>

- [[KFS]](#42-cursus---kfs)
	- [[Details]](#details)
	- [[Installation]](#installation)
	- [[Overview]](#overview)
	- [[Objectives]](#objectives)
	- [[Changelog]](#changelog)


<br><br>

## Installation

**Requirements**:

- Make

- Docker

- QEMU

<br>

To install the project dependencies and build the required files, you can run:
```bash
make build
```

To run the built ISO image, you can use QEMU *(you obviously need to have it installed)*:
```bash
make qemu
```

If it takes too long, a heavier but quicker way to do it is:
```bash
make
```

Once you're done, just:
```bash
make fclean
```

For more information on the available commands, you can run:
```bash
make help
```


<br><br>

## Overview

The goal of the project is to recreate a basic operating system kernel from scratch, focusing on low-level programming and system architecture concepts.

For it, wee need 3 things:
1. A boot.asm, telling the processor where and how to boot ;
2. The code (here in C++), telling what to do once booted ;
3. A linker script (here in ld), telling how to link everything together.


<br><br>

## Objectives

#### kfs-1

- [x] GRUB Multiboot2 support
- [x] Final ISO: 10 MB Max.
- [x] Display "42"
- [x] Handle C++

<br>

- [ ] Scroll support
- [ ] Cursor support
- [x] Color support
- [x] `printf` / `printk` function
- [ ] Handle keyboard input
- [ ] Multiscreens + Keyboard Shortcuts


<br><br>

## Changelog

<br><br>

### v1.1.2 - + | Readme

---

***[2026-01-21]***

Added printk to Term class.



<br><br>

### v1.1.1 - + | Printk

---

***[2026-01-21]***

Added a Readme.

Not much to say.

```cpp
void printk(const char *fmt, ...)
{
	void **spec = (void **)&fmt;
	spec++;
}
```

The addresses of the arguments follow each other in memory, so we can access the arguments simply by incrementing the address of the first argument.

<br><br>

### v1.1.0 - + | C++, ISO compression, Makefile help, VGA print functions

---

***[2026-01-21]***

Big changes!

<br>

Add of `C++` support.

Makefile are now a lot cleaner and modular.

<br>

Add of CFLAGS: `-mno-sse` `-mno-sse2` `-mno-sse3` `-mno-mmx` `-mno-3dnow`.

The compiler is using SSE instructions (pxor, movups) to zero-initialize template objects (such as Vect2<size_t>) members. These are XMM (SSE) registers.

**Problem**: SSE instructions require the CPU to have SSE enabled, which it isn't by default in protected mode on boot. Using these instructions without enabling SSE causes an invalid opcode exception, leading to a triple fault and reboot.

**Solution**: Force the compiler to use regular x86 instructions instead of SSE/XMM registers for initialization.

<br>

The built ISO was about 13.8 MB. The goal is to reduce it below 10 MB.

We added the flags `--modules="multiboot biosdisk iso9660"` to the GRUB ISO maker, and it dropped to 7.5 MB.

The work is successful but it is a bit slower so we keep the original flags under the make target `quick` and added the flags `-serial stdio -d int,cpu_reset` to `qemu-quick` to debug fastly and easily.

<br>

In C++, when a member (a var inside a class) is declared and then used (get, set) in a constructor,
it gets executed in a function called a "global constructor" placed in the `.ctors` section.

There is many global constructors, and they are called by the kernel.
So we have to call them all in order to make the classes work.

First in the linker:
```ld
.ctors : {
	start_ctors = .;
	KEEP(*(.init_array))
	KEEP(*(SORT(.ctors.*)))
	KEEP(*(.ctors))
	end_ctors = .;
}
```
So now, we can use `start_ctors` and `end_ctors` in our code.

In C/C++, it would look something like that:
```c++
extern void (*start_ctors)();
extern void (*end_ctors)();

extern "C" void call_global_ctors(void) {
    for (void (**ctor)() = &start_ctors; ctor < &end_ctors; ctor++)
        (*ctor)();
}
```

But we called it directly in the `boot.asm`:
```asm
mov ebx, start_ctors   ; ebx = (void *) start_ctors
jmp .test_ctor         ; goto .test_ctor
.call_ctor:
   call [ebx]          ; (*ebx)() --> Call constructor
   add ebx, 4          ; ebx += sizeof(void *)
.test_ctor:
   cmp ebx, end_ctors  ; if (ebx < (void *) end_ctors)
   jb .call_ctor       ;   goto .call_ctor
```

<br>

Then we added a plenty of useful functions and here we are!

We now have two main classes: `VGA` and `Term`.

They handle breaklines, tabs, carriage returns, and other text positioning features, colors, and even 32 special chars!


<br><br>

### v1.0.3 - + | VGA put functions

---

***[2026-01-20]***

The basic screen when a Kernel boots is a simple text mode display using **VGA standard**.

It is `80x25` chars in size with `16` different colors, and start at `0xb8000`.

A VGA character is 16-bits long: `0bBBBB_FFFF_CCCC_CCCC` where `BBBB` (`uint4`) is the background color, `FFFF` (`uint4`) is the foreground color, and `CCCC_CCCC` (`uint8` == `char`) is the ASCII character.

To put it, this is simply:
```c
((uint16_t *) 0xb8000)[offset] = vga_bg << 12 | vga_fg << 8 | ascii_char;
```


<br><br>

### v1.0.2 - + | C

---

***[2026-01-20]***

Added C.

Fun fact, for whatever reason, `gcc`, even with every sigle flags combinaison, does not work as expected..
But `g++` does.. *(what? why? will we ever know?)* So it goes like this:
```bash
g++ -m32 -ffreestanding -O2 -Wall -Wextra -c -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs <source_files>
```

We setted the stack to 16 MiB.
```asm
section .bss
align 4
stack_top:
	resb 16384	; 16 KiB stack
stack_bottom:
```

When the kernel starts, it displays "OK" through C, through ASM!
```c
int main(void) {
    asm volatile ("movl $0x2f4b2f4f, 0xb8000\n");
    // ...
}
```
^^^ See, we used `movl`, that is the **AT&T syntax** for `mov` when you use GCC/G++ inline assembly.
It is revered and a bit confusing, but it works!

In a main, to give some rest to the cpu, we end by an infinite `hlt` loop:
```c
int main(void) {
    // ...
    while (1)
        asm volatile ("hlt");
}
```


<br><br>

### v1.0.1 - ~ | - Binutils, ~ x86_64 -> i386

---

***[2026-01-20]***

Found the correct flags for i386 architecture!
*How you wonder...?* By `ld --help` and reading the man.. -_- :
```bash
nasm -f elf32
ld -m elf32 -b elf32-i386 -o kernel.bin kernel.o
```

So got rid of binutils huge compilation.


<br><br>

### v1.0.0 - + | Basic ISO displaying `OK`

---

***[2026-01-19]***

Created Makefiles and Docker container to build the project in a controlled environment.

Goal: Make a [GNU Cross Compiler (OSDev Wiki)](https://wiki.osdev.org/GCC_Cross-Compiler).

Source code: firstly in assembly and with a linker only.

Because we did not find the correct flags, we compiled our own `binutils-2.45` lib to get the `x86_64-elf-ld` binary.

*We forgot it was 32 bits and not 64...*


<br><br>

---

<sup><i>This is an educational project proposed by 42 School through the 42Cursus program.</i><sup>
