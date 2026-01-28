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
- **Project version:** *`v1.2.1`*
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

- [x] Scroll support
- [x] Cursor support
- [x] Color support
- [x] `printf` / `printk` function
- [x] Handle keyboard input
- [x] Multiscreens + Keyboard Shortcuts


<br><br>

## Changelog

<br><br>

### v1.2.1 - + | kfs-2: Extended character support

---

***[2026-01-28]***

Every single character of the [CP437 charset](https://en.wikipedia.org/wiki/Code_page_437) can be rendered using its corresponding hexadecimal code point using the `Alt` key.

[VGA charset (CP437)](https://en.wikipedia.org/wiki/Code_page_437):
```
    0 1 2 3 4 5 6 7 8 9 a b c d e f  0 1 2 3 4 5 6 7 8 9 a b c d e f
  *-----------------------------------------------------------------
0 |   ☺ ☻ ♥ ♦ ♣ ♠ • ◘ ○ ◙ ♂ ♀ ♪ ♫ ☼  ► ◄ ↕ ‼ ¶ § ▬ ↨ ↑ ↓ → ← ∟ ↔ ▲ ▼
2 |   ! " # $ % & ' ( ) * + , - . /  0 1 2 3 4 5 6 7 8 9 : ; < = > ?
4 | @ A B C D E F G H I J K L M N O  P Q R S T U V W X Y Z [ \ ] ^ _
6 | ` a b c d e f g h i j k l m n o  p q r s t u v w x y z { | } ~ ⌂
8 | Ç ü é â ä à å ç ê ë è ï î ì Ä Å  É æ Æ ô ö ò û ù ÿ Ö Ü ¢ £ ¥ ₧ ƒ
a | á í ó ú ñ Ñ ª º ¿ ⌐ ¬ ½ ¼ ¡ « »  ░ ▒ ▓ │ ┤ ╡ ╢ ╖ ╕ ╣ ║ ╗ ╝ ╜ ╛ ┐
c | └ ┴ ┬ ├ ─ ┼ ╞ ╟ ╚ ╔ ╩ ╦ ╠ ═ ╬ ╧  ╨ ╤ ╥ ╙ ╘ ╒ ╓ ╫ ╪ ┘ ┌ █ ▄ ▌ ▐ ▀
e | α ß Γ π Σ σ µ τ ≖ Θ Ω δ ∞ ⧞ ∈ ∩  ≡ ± ≥ ≤ ⌠ ⌡ ÷ ≈ ° ∙ · √ ⁿ ² ■  
```

> For example, to type the character `µ` (hex value `0xe6`), you would press `Alt + E` then `Alt + 6` on the keyboard.

> Another example, to type the character `É` (hex value `0x90`), you would press `Alt + 9` then `Alt + 0` on the keyboard.

<br>

To make the main function more readable, we moved the logic in a separate function.

It changed from:
```c++
extern "C" int	main() {
	Term terms[] = {
		Term(
			Vect2<size_t>(VGA_WIDTH, 16),
			Vect2<size_t>(0, 0),
			VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY)
		),
		Term(
			Vect2<size_t>(40, 9),
			Vect2<size_t>(0, 16),
			VGA::character(VGA_C_WHITE, VGA_C_BLACK)
		),

	// ... about 75 lines

		if (activeTerm >= 0 && !terms[activeTerm].isActive())
			activeTerm = -1;
		shortcut = handleKeyboard(activeTerm >= 0 ? &terms[activeTerm] : nullptr);
		if (shortcut != SHORTCUT_NONE) {
			if (shortcut & FLAG_TERM_SWITCH) {
				if (activeTerm >= 0)
					terms[activeTerm].setActive(false);
				activeTerm = (shortcut & ~FLAG_TERM_SWITCH);
				terms[activeTerm].setActive(true);
				VGA::showCursor();
			}
		}
	}
	return 0;
```
To something like:
```c++
extern "C" int	main() {
	return demo1();
}
```
```c++
int	demo1() {
	// The 75 lines behaviour
}
```

This way, we can create multiple demo functions and switch between them easily, while keeping the main function clean.

<br>

The terminals disposition and contents have been improved to look better and display more of what we can do.


<br><br>

### v1.2.0 - + | kfs-1: Keyboard extended support

---

***[2026-01-24]***

Added support for [Extended Keyset 1](https://wiki.osdev.org/PS/2_Keyboard#Scan_Code_Set_1).

PS_2 normally handles keys like that:
1. We read the scancode from the keyboard port.
2. To show to PS_2 that we received the scancode, we need to send an acknowledgment by nullifying the value in the port.
3. Then while PS_2 is acknowledging our acknowledgment, any read to the port result in `0xfa`.
4. Once PS_2 acknowledged, we can read again.

But some keys may generate multiple scancodes (like `R_CTRL`, `PAUSE`, `POWER`, `KP_ENTER`, etc.).
For those, the first read will result in `0xe0`, then we have to pass the acknowledgment handshake, and then read the next byte.

> For example, `L_CTRL` is `0x1d` | `R_CTRL` is `0xe0` then `0x1d`<br>
> Or `B` is `0x30` | `VOL_UP` is `0xe0` then `0x30`.

In the code, it looks something like this:
```c++
uint16_t	scancode;

scancode = (uint8_t) read_port(0x60);
if (scancode == 0xfa)
	return SHORTCUT_NONE;

if (scancode == 0xe0) {
	write_port(0x60, 0); // Flush the PS/2 port
	while (read_port(0x60) == 0xfa)
		/* Wait... */;
	scancode = 0x100 | read_port(0x60);
}

if (scancode == 0x11d) {
	// Key: R_CTRL
} else if (scancode == 0x1d) {
	// Key: L_CTRL
} else if (scancode == 0x130) {
	// Key: VOL_UP
} else if (scancode == 0x30) {
	// Key: B
}
```

This lets us handle more keys, like... the arrows!

<br>

With the new extended keyboard support, we can now move the cursor through the terminal using the arrow keys.

<br>

Moreover, the caps lock key is now supported!

<br>

The `Esc` key has a new functionality: it set the active terminal to none and hide the cursor.

If we want to type again, we before need to select the terminal to switch to using the keyboard shortcuts.

<br>

The combinations using `Ctrl` and `Alt` are now working on the left one as well as the right one.

<br>

Some errors about the VGA cursor positioning were fixed.

<br>

To make it flawless, we ensured that the stack is big enough to handle everything
 (multiple terminals) by once more increasing its size.
We switched from `64 KiB` to `128 KiB`.

<br>

Some parts of the code were modified to conform to the project's coding style,
 best practices, and performance optimizations.

<br>

And the most ***important*** thing: **kfs-1 is now complete with all the bonuses!**


<br><br>

### v1.1.7 - + | kfs-1: Terminal switching, VGA Cursor, Whitespace fill, lltox/ulltox

---

***[2026-01-22]***

Switch between different terminal screens using keyboard shortcuts `Ctrl/Alt + [1–3]`.

<br>

A cursor is now displayed in the active terminal.

To set it, we need to edit the VGA registers.

According to the wiki, we need to modify the [CRT Controller Registers](http://www.osdever.net/FreeVGA/vga/crtcreg.htm) (`0x3D4` for index and `0x3D5` for data).

To enable or disable the cursor, we need to set the 5th bit (Cursor Disable) of the [Cursor Start Register](http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A).

To set the location of the cursor, we need to modify the [Cursor Location High Register](http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0E) and the [Cursor Location Low Register](http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0F) to respectively set the high and low bytes of the cursor position.

The code looks something like this:
```c++
write_port(0x3D4, 0x0A);
write_port(0x3D5, read_port(0x3D5) & 0b11011111); // Show cursor
write_port(0x3D5, read_port(0x3D5) | 0b00100000); // Hide cursor

write_port(0x3D4, 0x0E);
write_port(0x3D5, (pos >> 8) & 0xff); // Set cursor high byte
write_port(0x3D4, 0x0F);
write_port(0x3D5, pos & 0xff); // Set cursor low byte
```

<br>

A line break, a backtick or a tab are now overriting with whitespaces the old displayed characters.

<br>

`lltox` and `ulltox` are now functions in their own right, allowing for better code organization and readability.

<br>

Some parts of the code were modified to conform to the project's coding style.


<br><br>

### v1.1.6 - ~ | kfs-1: Term fixed scroll and render issues

---

***[2026-01-22]***

Windowed terminals (terminal that are smaller than the VGA screen) are now fully displayable, and scrollable (using functions).

<br>

Because we can't allocate memory on the heap, the classic itoa does not work everytime:
```c++
char	*itoa(int n) {
	uchar_t	buffer[12];
	// ...
	return buffer;
}
```

It works sometimes, but not always, because after the end of the function,
 the buffer no longer belongs to anyone : it is inside of free-to-use memory.<br>
If this memory is not overwritten, it can still be accessed, but ***this is not guaranteed***...

So we changed it to use a static buffer:
```c++
void	itoa(int n, uchar_t buffer[12]) {
	// ...
}
```

<br>

Some parts of the code were modified to conform to the project's coding style.


<br><br>

### v1.1.5 - feat: multiscreens

---

***[2026-01-22]***

Added multiscreens support, it is possible to navigate between the different screens using Ctrl + [1–3].

Added defines to clarify the code.


<br><br>

### v1.1.4 - feat: add shortcut and maj character print on screen

---

***[2026-01-22]***

To read the keyboard, it is necessary to add assembly code in order to read from and write to a port.

```asm
read_port:
    mov edx, [esp + 4]
    in al, dx
    ret

write_port:
    mov   edx, [esp + 4]
    mov   al, [esp + 4 + 4]
    out   dx, al
    ret
```

To handle PS/2 (which is what the keyboard uses), you need to look at port 0x60.

In the keyboard response, if the last bit of the scan code is set to 1, it means the key has been released; otherwise, it is pressed or is being pressed.

After reading the code, it is important to reset it to 0, because when using polling we are running an infinite loop that reads the port, and we do not want to repeatedly read the same information. The keyboard constantly signals that it is connected by filling the port with 250.

Each key is numbered from 0 to 90 (in QWERTY), so a lookup table is required to map the scanned key to the corresponding character.

Do not forget to remove the unpressed flag if you want to use the code to detect the key that has just been released.

```c
int scancode = read_port(0x60);
unpresskey = scancode & ~0x80;
```

To add shortcuts, it is enough to map them in the ShortcutManager and define a return code; this code will then be propagated up to the main loop.


<br><br>

### v1.1.3 - + | kfs-1: Term history and scroll, stack smash checker

---

***[2026-01-22]***

Added Term history and scroll functions:
```c++
class Term {
	// ...

	public:
		// ...

		void	shiftHistUp(size_t lines);
		void	flush();

		// ...

		Vect2<size_t>	getSize() const;
		void			setSize(Vect2<size_t> size);

		size_t			getHistHeight() const;
		void			setHistHeight(size_t height);

		uint16_t		getColor() const;
		void			setColor(uint16_t color);

		Vect2<size_t>	getCursor() const;
		void			setCursor(Vect2<size_t> pos);
		void			moveCursor(int dx, int dy);
		void			resetCursor();

		Vect2<size_t>	getRenderPos() const;
		void			setRenderPos(Vect2<size_t> renderPos);

		size_t			getScrollY() const;
		void			setScrollY(size_t scrollY);
		size_t			incrScrollY(ssize_t delta);
		size_t			scrollToCursor();
		void			resetScrollY();

		bool			isRendering() const;
		bool			setRendering(bool enable);

		// ...
}
```

Because it was really expensive in stack memory, the stack size has increased from 16 KiB to 64 KiB:
```asm
stack_bottom:
	resb 65536	; 64 KiB stack
stack_top:
```

To check if the stack is being smashed, we can use a simple canary value placed at the end of the stack. If the canary value is changed, we know the stack has been smashed:
```asm
global stack_guard
stack_guard:
	resb 4		; Reserve space for stack canary for stack smashing protection
stack_bottom:

; ...

_start:
	mov dword [stack_guard], 0xdeadbeef	; Initialize stack canary
```
```c++
extern "C" uint32_t	stack_guard;

extern "C" bool	stack_check(bool halt) {
	if (stack_guard == 0xdeadbeef)
		return true; // Stack intact
	// Smashed!
	return false;
}
```


<br><br>

### v1.1.2 - + | Readme

---

***[2026-01-21]***

Added a Readme.

Not much to say.


<br><br>

### v1.1.1 - feat: printk ok

---

***[2026-01-21]***

Added printk to Term class.

```cpp
void printk(const char *fmt, ...) {
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
