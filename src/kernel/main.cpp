/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/02/13 17:24:40 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

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

static void	initGDT() {
	Gdt	gdt;

	gdt.setEntry(gdt.createDescriptor(0, 0, 0));						// Null segment
	gdt.setEntry(gdt.createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL0)));	// Kernel code segment
	gdt.setEntry(gdt.createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL0)));	// Kernel data segment
	gdt.setEntry(gdt.createDescriptor(0, 0x000FFFFF, (GDT_STACK_PL0)));	// Kernel stack segment
	gdt.setEntry(gdt.createDescriptor(0, 0x000FFFFF, (GDT_CODE_PL3)));	// User code segment
	gdt.setEntry(gdt.createDescriptor(0, 0x000FFFFF, (GDT_DATA_PL3)));	// User data segment
	gdt.setEntry(gdt.createDescriptor(0, 0x000FFFFF, (GDT_STACK_PL3)));	// User stack segment
	gdt.loadGDT();
}

extern "C" int	main() {
	initGDT();

	while (1) {
		__DEMO_RUN__ = true;
		VGA::fill();
		Demo::demo()();
	}
}
