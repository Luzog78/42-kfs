; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    boot.asm                                           :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2026/01/20 16:49:59 by luzog78           #+#    #+#              ;
;    Updated: 2026/01/20 16:49:59 by luzog78          ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

section .multiboot

header_start:
	dd 0xe85250d6							; Magic number
	dd 0x00									; Architecture: Protected mode i386
	dd header_end - header_start			; Header length
	dd 0x100000000 - (0xe85250d6 + 0x00 \
			+ (header_end - header_start))	; Checksum

	; End tag
	dw 0x00
	dw 0x00
	dd 0x08

header_end:


; **************************************************************************** ;


section .bss

align 4

global stack_guard
stack_guard:
	resb 4		; Reserve space for stack canary for stack smashing protection
stack_bottom:
	resb 524288	; 512 KiB stack
stack_top:


; **************************************************************************** ;


section .text

global _start

extern main
extern start_ctors						; (void (*)()): Start of C++ global constructors
extern end_ctors						; (void (*)()): End of C++ global constructors

global read_port
global write_port
global reboot_system
global shutdown_system

read_port:
	mov		edx, [esp + 4]
	in		al, dx
	ret

write_port:
	mov		edx, [esp + 4]
	mov		al, [esp + 8]
	out		dx, al
	ret

reboot_system:
	jmp		0xFFFF:0					; Triple fault

shutdown_system:
	; First try ACPI shutdown via port 0x604 (QEMU/Bochs)
	mov		dx, 0x604					; I/O port for ACPI
	mov		ax, 0x2000					; ACPI function: Sleep
	out		dx, ax

	; Alternatively: Try legacy APM shutdown
	mov		ax, 0x5307					; APM function: Set power state
	mov		bx, 0x0001					; Device ID: All devices
	mov		cx, 0x0003					; Power state: Off
	int		0x15						; APM BIOS interrupt

	; If shutdown fails, halt the system
	cli									; Disable interrupts
	hlt									; Halt processor
	jmp		$							; Infinite loop as fallback

_start:
	mov dword [stack_guard], 0xdeadbeef	; Initialize stack canary
	mov esp, stack_top					; Set up stack pointer

	; Call global constructors
	mov ebx, start_ctors				; ebx = (void *) start_ctors
	jmp .test_ctor						; goto .test_ctor
	.call_ctor:
		call [ebx]						; (*ebx)() --> Call constructor
		add ebx, 4						; ebx += sizeof(void *)
	.test_ctor:
		cmp ebx, end_ctors				; if (ebx < (void *) end_ctors)
		jb .call_ctor					;   goto .call_ctor

	call main
	hlt
