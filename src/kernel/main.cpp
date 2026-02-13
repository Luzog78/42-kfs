/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 16:24:47 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include "keyboard.hpp"

const char *__42__[13] = { \
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"@                                                                              @",
	"@  /$$   /$$  /$$$$$$         /$$        /$$$$$$                               @",
	"@ | $$  | $$ /$$__  $$       | $$       /$$__  $$                              @",
	"@ | $$  | $$|__/  \\ $$       | $$   /$$| $$  \\__//$$$$$$$                      @",
	"@ | $$$$$$$$  /$$$$$$//$$$$$$| $$  /$$/| $$$$   /$$_____/                      @",
	"@ |_____  $$ /$$____/|______/| $$$$$$/ | $$_/  |  $$$$$$    ___                @",
	"@       | $$| $$             | $$_  $$ | $$     \\____  $$  | _ )_  _           @",
	"@       | $$| $$$$$$$$       | $$ \\  $$| $$     /$$$$$$$/  | _ \\ || | ysabik   @",
	"@       |__/|________/       |__/  \\__/|__/    |_______/   |___/\\_, | bsavinel @",
	"@                                                               |__/           @",
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	0
};

extern "C" bool	stack_check(bool halt) {
	if (stack_guard == 0xdeadbeef) // Check canary
		return true;
	TERM_PTR[0] = 0x4f53; // 'S'
	TERM_PTR[1] = 0x4f54; // 'T'
	TERM_PTR[2] = 0x4f4b; // 'K'
	while (halt)
		asm volatile ("hlt");
	return false;
}

extern "C" int	main() {
	Gdt gdt;
	
	gdt.set_entry(gdt.create_descriptor(0, 0, 0)); // Null segment
	gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0))); // Kernel code segment
	gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0))); // Kernel data segment
	gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3))); // User code segment
	gdt.set_entry(gdt.create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3))); // User data segment
	gdt.loadGDT();
	
	while (1) {
		__DEMO_RUN__ = true;
		VGA::fill();
		Demo::demo()();
	}
}
