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
