/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luzog78 <luzog78@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:03:28 by luzog78           #+#    #+#             */
/*   Updated: 2026/01/22 08:10:49 by luzog78          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

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
	Term	term(VGA::character(VGA_C_LIGHT_GREEN, VGA_C_DARK_GREY));

	for (int i = 0; i < 2; i++) {
		term.put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		term.put("@                                                                              @");
		term.put("@  /$$   /$$  /$$$$$$         /$$        /$$$$$$                               @");
		term.put("@ | $$  | $$ /$$__  $$       | $$       /$$__  $$                              @");
		term.put("@ | $$  | $$|__/  \\ $$       | $$   /$$| $$  \\__//$$$$$$$                      @");
		term.put("@ | $$$$$$$$  /$$$$$$//$$$$$$| $$  /$$/| $$$$   /$$_____/                      @");
		term.put("@ |_____  $$ /$$____/|______/| $$$$$$/ | $$_/  |  $$$$$$    ___                @");
		term.put("@       | $$| $$             | $$_  $$ | $$     \\____  $$  | _ )_  _           @");
		term.put("@       | $$| $$$$$$$$       | $$ \\  $$| $$     /$$$$$$$/  | _ \\ || | ysabik   @");
		term.put("@       |__/|________/       |__/  \\__/|__/    |_______/   |___/\\_, | bsavinel @");
		term.put("@                                                               |__/           @");
		term.put("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		term.put("\n");

		term.put("Here is every supported chars: ");
		term.setColor(VGA::character(VGA_C_GREEN, VGA_C_DARK_GREY));
		for (uchar_t c = 32; c < 160; c++)
			if (c != 127)
				term.putc((char) c);

		term.printk("\nThis is a number: %d\n", 42);
		term.scrollToCursor();
		term.flush();
	}

	while (1)
		asm volatile ("hlt");
	return 0;
}
