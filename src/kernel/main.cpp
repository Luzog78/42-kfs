/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/22 18:56:17 by luzog78          ###   ########.fr       */
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
			VGA::character(VGA_C_LIGHT_GREEN, VGA_C_LIGHT_BLUE)
		),
		Term(
			Vect2<size_t>(40, 9),
			Vect2<size_t>(40, 16),
			VGA::character(VGA_C_RED, VGA_C_LIGHT_GREEN)
		)
	};
	int activeTerm = 0;
	int shortcut = SHORTCUT_NONE;

	terms[0].flush();
	terms[1].flush();
	terms[2].flush();

	terms[0].put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	terms[0].put("@                                                                              @");
	terms[0].put("@  /$$   /$$  /$$$$$$         /$$        /$$$$$$                               @");
	terms[0].put("@ | $$  | $$ /$$__  $$       | $$       /$$__  $$                              @");
	terms[0].put("@ | $$  | $$|__/  \\ $$       | $$   /$$| $$  \\__//$$$$$$$                      @");
	terms[0].put("@ | $$$$$$$$  /$$$$$$//$$$$$$| $$  /$$/| $$$$   /$$_____/                      @");
	terms[0].put("@ |_____  $$ /$$____/|______/| $$$$$$/ | $$_/  |  $$$$$$    ___                @");
	terms[0].put("@       | $$| $$             | $$_  $$ | $$     \\____  $$  | _ )_  _           @");
	terms[0].put("@       | $$| $$$$$$$$       | $$ \\  $$| $$     /$$$$$$$/  | _ \\ || | ysabik   @");
	terms[0].put("@       |__/|________/       |__/  \\__/|__/    |_______/   |___/\\_, | bsavinel @");
	terms[0].put("@                                                               |__/           @");
	terms[0].put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	terms[0].put("\n");

	terms[0].put("Here is every supported chars: ");
	terms[0].setColor(VGA::character(VGA_C_GREEN, VGA_C_DARK_GREY));
	for (uchar_t c = 32; c < 160; c++)
		if (c != 127)
			terms[0].putc((char) c);
	terms[0].scrollToCursor();

	for (int i = 0; i <= UCHAR_MAX; i++) {
		terms[1].putn(i);
		terms[1].putc(' ');
		terms[1].scrollToCursor();
		terms[2].putnHex(i, false);
		terms[2].putc(' ');
		terms[2].scrollToCursor();
	}

	stack_check(true);
	while (1) {
		shortcut = keyboardHandler(&terms[activeTerm]);
		if (shortcut != SHORTCUT_NONE) {
			if (shortcut & TERMINAL_SWITCH_MASK)
				activeTerm = (shortcut & ~TERMINAL_SWITCH_MASK);
		}
	}
	return 0;
}
