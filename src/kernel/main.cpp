/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/22 17:54:09 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include "keyboard.hpp"

extern "C" uint32_t	stack_guard;

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

extern "C" int main() {
	Term interfaces[] = {Term(
		Vect2<size_t>(VGA_WIDTH, 13),
		Vect2<size_t>(0, 0),
		VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY)),
	Term(
		Vect2<size_t>(40, 13),
		Vect2<size_t>(0, 13),
		VGA::character(VGA_C_LIGHT_GREEN, VGA_C_LIGHT_BLUE)),
	Term(
		Vect2<size_t>(40, 13),
		Vect2<size_t>(40, 13),
		VGA::character(VGA_C_BLACK, VGA_C_LIGHT_CYAN))};
	int activeTerm = 0;
	int shortcut = SHORTCUT_NONE;

	interfaces[1].flush();
	interfaces[2].flush();
	interfaces[0].flush();
	for (int i = 0; i < 2; i++) {
		interfaces[0].put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		interfaces[0].put("@                                                                              @");
		interfaces[0].put("@  /$$   /$$  /$$$$$$         /$$        /$$$$$$                               @");
		interfaces[0].put("@ | $$  | $$ /$$__  $$       | $$       /$$__  $$                              @");
		interfaces[0].put("@ | $$  | $$|__/  \\ $$       | $$   /$$| $$  \\__//$$$$$$$                      @");
		interfaces[0].put("@ | $$$$$$$$  /$$$$$$//$$$$$$| $$  /$$/| $$$$   /$$_____/                      @");
		interfaces[0].put("@ |_____  $$ /$$____/|______/| $$$$$$/ | $$_/  |  $$$$$$    ___                @");
		interfaces[0].put("@       | $$| $$             | $$_  $$ | $$     \\____  $$  | _ )_  _           @");
		interfaces[0].put("@       | $$| $$$$$$$$       | $$ \\  $$| $$     /$$$$$$$/  | _ \\ || | ysabik   @");
		interfaces[0].put("@       |__/|________/       |__/  \\__/|__/    |_______/   |___/\\_, | bsavinel @");
		interfaces[0].put("@                                                               |__/           @");
		interfaces[0].put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		interfaces[0].put("\n");

		interfaces[0].put("Here is every supported chars: ");
		interfaces[0].setColor(VGA::character(VGA_C_GREEN, VGA_C_DARK_GREY));
		for (uchar_t c = 32; c < 160; c++)
			if (c != 127)
				interfaces[0].putc((char) c);

		interfaces[0].printk("\nThis is a number: %d\n", 42);
		interfaces[0].scrollToCursor();
		interfaces[0].flush();
	}

	while (1) {
		shortcut = keyboard_handler(&interfaces[activeTerm]);
		if (shortcut != SHORTCUT_NONE) {
			if (shortcut & TERMINAL_SWITCH_MASK)
				activeTerm = (shortcut & ~TERMINAL_SWITCH_MASK);
		}
	}
	return 0;
}
