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
	dd 0xe85250d6														; Magic number
	dd 0x00																; Architecture: Protected mode i386
	dd header_end - header_start										; Header length
	dd 0x100000000 - (0xe85250d6 + 0x00 + (header_end - header_start))	; Checksum

	; End tag
	dw 0x00
	dw 0x00
	dd 0x08

header_end:


; **************************************************************************** ;


section .bss

align 4

stack_top:
	resb 16384	; 16 KiB stack
stack_bottom:


; **************************************************************************** ;


section .text

global _start

extern main
extern start_ctors			; (void (*)()): Start of C++ global constructors
extern end_ctors			; (void (*)()): End of C++ global constructors

_start:
	mov esp, stack_bottom	; Set up stack pointer

	; Call global constructors
	mov ebx, start_ctors	; ebx = (void *) start_ctors
	jmp .test_ctor			; goto .test_ctor
	.call_ctor:
		call [ebx]			; (*ebx)() --> Call constructor
		add ebx, 4			; ebx += sizeof(void *)
	.test_ctor:
		cmp ebx, end_ctors	; if (ebx < (void *) end_ctors)
		jb .call_ctor		;   goto .call_ctor

	call main
	hlt
